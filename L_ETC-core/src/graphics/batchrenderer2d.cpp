#include "batchrenderer2d.h"

namespace letc {namespace graphics {
	
	BatchRenderer2D::BatchRenderer2D() {
		init();
	}

	BatchRenderer2D::~BatchRenderer2D() {
		delete m_indexBuffer;
		glDeleteBuffers(1, &m_vertexBuffer);
		//ftgl::texture_font_delete(m_FTFont); // TODO THIS SHOULD BE IN DESTROY

	}

	void BatchRenderer2D::init(){
		// Generate
		glGenVertexArrays(1, &m_vertexArray);
		glGenBuffers(1, &m_vertexBuffer);
		//Bind
		glBindVertexArray(m_vertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
		//Enable
		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(SHADER_UV_INDEX);
		glEnableVertexAttribArray(SHADER_TID_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);
		//Assign
		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*) 0);
		glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::uv)));
		glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::tid)));
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));
		//Unbind
		glBindBuffer(GL_ARRAY_BUFFER, NULL);

		//Indices
		int indexOffset = 0;
		GLushort indices[RENDERER_INDICES_SIZE];

		for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6) {
			indices[i+0] = indexOffset + 0;
			indices[i+1] = indexOffset + 1;
			indices[i+2] = indexOffset + 2;
			
			indices[i+3] = indexOffset + 2;
			indices[i+4] = indexOffset + 3;
			indices[i+5] = indexOffset + 0;

			indexOffset += 4;
		}
		
		m_indexBuffer = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

		m_indexCount = 0;

		//Unbind array
		glBindVertexArray(NULL);

		//m_textureManager = TextureManager();


	}

	void BatchRenderer2D::begin(){
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		m_buffer = (VertexData*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void BatchRenderer2D::submit(const Renderable2D* renderable){
		const math::Vector3& pos = renderable->getPosition();
		const math::Vector2& size = renderable->getSize();
		const unsigned int color = renderable->getColor();
		const std::vector<math::Vector2>& uvs = renderable->getUVs();
		const GLuint tid = renderable->getTID();


		float ts = 0.0f;

		if (tid > 0) {
			bool found = false;
			for (size_t i = 0; i < m_textureSlots.size(); i++){
				if (m_textureSlots[i] == tid) {
					ts = (float)(i+1);
					found = true;
					break;
				}
			}
			if (!found) {
				if (m_textureSlots.size() >= 32) {
					end();
					flush();
					begin();
				}
				m_textureSlots.push_back(tid);
				ts =(float)(m_textureSlots.size());
			}
		}
		

		m_buffer->vertex = *m_tranformationStackBack * pos;
		m_buffer->uv = uvs[0];
		m_buffer->tid = ts;
		m_buffer->color = color;
		m_buffer++;

		m_buffer->vertex = *m_tranformationStackBack * math::Vector3(pos.x, pos.y+size.y, pos.z);
		m_buffer->uv = uvs[1];
		m_buffer->tid = ts;
		m_buffer->color = color;
		m_buffer++;

		m_buffer->vertex = *m_tranformationStackBack * math::Vector3(pos.x + size.x, pos.y + size.y, pos.z);
		m_buffer->uv = uvs[2];
		m_buffer->tid = ts;
		m_buffer->color = color;
		m_buffer++;

		m_buffer->vertex = *m_tranformationStackBack * math::Vector3(pos.x + size.x, pos.y, pos.z);
		m_buffer->uv = uvs[3];
		m_buffer->tid = ts;
		m_buffer->color = color;
		m_buffer++;

		m_indexCount += 6;
	}

	void BatchRenderer2D::drawString(const std::string& text, const math::Vector3& position, const Font& font, unsigned int color){
		using namespace ftgl;
		float ts = 0.0f;
		bool found = false;


		for (size_t i = 0; i < m_textureSlots.size(); i++) {
			if (m_textureSlots[i] == font.getTexID()) {
				ts = (float)(i + 1);
				found = true;
				break;
			}
		}

		if (!found) {
			if (m_textureSlots.size() >= 32) {
				end();
				flush();
				begin();
			}
			m_textureSlots.push_back(font.getTexID());
			ts = (float)(m_textureSlots.size());
		}

		texture_font_t* ftFont = font.getFTFont();
		float scaleX = 1280 / 32.0f;
		float scaleY = 720 / 18.0f;
		float x = position.x;

		for (int i = 0; i < text.length(); i++){
			
			char c = text[i];
			texture_glyph_t* glyph = texture_font_find_glyph(ftFont, &c); // right now, we preload all the possible characters, not sure we want to do that
			
			//texture_glyph_t* glyph = texture_font_get_glyph(m_FTFont, &c); // right now, we preload all the possible characters, not sure we want to do that
			


			if (glyph != NULL) {
				if (x > 0) {
					/*float kerning = texture_glyph_get_kerning(glyph, &text[i-1]);
					x += kerning / scaleX;*/
				}

			

				float x0 = x + glyph->offset_x / scaleX;
				float y0 = position.y + glyph->offset_y / scaleY;
				float x1 = x0 + glyph->width / scaleX;
				float y1 = y0 - glyph->height / scaleY;
				
				float s0 = glyph->s0;
				float t0 = glyph->t0;
				float s1 = glyph->s1;
				float t1 = glyph->t1;

			

				m_buffer->vertex = *m_tranformationStackBack * math::Vector3(x0,y0,0.0f);
				m_buffer->uv = math::Vector2(s0, t0);
				m_buffer->tid = ts;
				m_buffer->color = color;
				m_buffer++;

				m_buffer->vertex = *m_tranformationStackBack * math::Vector3(x0,y1,0.0f);
				m_buffer->uv = math::Vector2(s0, t1);
				m_buffer->tid = ts;
				m_buffer->color = color;
				m_buffer++;

				m_buffer->vertex = *m_tranformationStackBack * math::Vector3(x1,y1,0.0f);
				m_buffer->uv = math::Vector2(s1, t1);
				m_buffer->tid = ts;
				m_buffer->color = color;
				m_buffer++;
				
				m_buffer->vertex = *m_tranformationStackBack * math::Vector3(x1,y0,0.0f);
				m_buffer->uv = math::Vector2(s1, t0);
				m_buffer->tid = ts;
				m_buffer->color = color;
				m_buffer++;


				m_indexCount += 6;
				x += glyph->advance_x/scaleX;
			}
		}


	}

	void BatchRenderer2D::end(){
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, NULL);
	}

	void BatchRenderer2D::flush(){
		//bind all the textures 
		for (size_t i = 0; i < m_textureSlots.size(); i++){
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_textureSlots[i]);

		}

		glBindVertexArray(m_vertexArray);
		
		m_indexBuffer->bind();

		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, NULL);

		m_indexBuffer->unbind();
		glBindVertexArray(NULL);

		m_indexCount = 0;

	}

}}