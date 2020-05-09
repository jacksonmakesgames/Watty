#include <graphics/batchrenderer2d.h>

namespace letc {namespace graphics {
	
	BatchRenderer2D::BatchRenderer2D() {
		init();
	}

	BatchRenderer2D::~BatchRenderer2D() {
		delete m_indexBuffer;
		glDeleteBuffers(1, &m_vertexBuffer);
	}

	void BatchRenderer2D::init(){
		// Generate
		glGenVertexArrays(1, &m_vertexArray);
		glGenBuffers(1, &m_vertexBuffer);
		//Bind
		glBindVertexArray(m_vertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
		//Enable attribs
		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(SHADER_UV_INDEX);
		glEnableVertexAttribArray(SHADER_TID_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);
		//Assign
		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*) 0);
		glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, uv)));
		glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, tid)));
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, color)));
		//Unbind
		glBindBuffer(GL_ARRAY_BUFFER, NULL);

		// Texture Arrays:


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

#ifdef WATTY_EMSCRIPTEN
		m_currentBufferBase = new VertexData[RENDERER_MAX_SPRITES*4]; // 4 verts
#endif



	}

	void BatchRenderer2D::begin(){
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); // bind vertex buffer
#ifdef WATTY_EMSCRIPTEN
		m_currentBuffer = m_currentBufferBase;
#else
		m_currentBuffer = (VertexData*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY); // map the buffer and get the pointer to the first vertex
#endif // WATTY_EMSCRIPTEN


	}

	void BatchRenderer2D::submit(const Renderable2D* renderable){
		const glm::vec2& pos = renderable->getPosition();
		const glm::vec2& size = renderable->getSize();
		const unsigned int color = renderable->getColor().c;
		const std::vector<glm::vec2>& uvs = renderable->getUVs();
		const GLuint tid = renderable->getTID();
		float glTID = (float)tid;

		FrameInfo frameInfo = renderable->getFrameInfo();

		float idForShader = 0.0f;
		if (glTID > 0) {
			bool found = false;
			for (size_t i = 0; i < m_glTIDsThisFlush.size(); i++)
			{
				if (m_glTIDsThisFlush[i] == glTID) {
					found = true;
				}
				
			}
			if (!found) {

				m_glTIDsThisFlush.push_back(glTID);
			}
			idForShader = (float)(m_glTIDsThisFlush.size() % m_maxTextureUnits);
			if (idForShader == 0.0f) idForShader = 1.0f;
		}

		if (m_glTIDsThisFlush.size() >= m_maxTextureUnits) {
			end();
			flush();
			begin();
			m_glTIDsThisFlush.push_back(glTID);

		}
		const float tw = 1.0f / frameInfo.cols;
		const float th = 1.0f / frameInfo.rows;
		
		const float tx = ((int)frameInfo.currentFrame % frameInfo.rows) * tw;
		const float ty = 1- ((int)frameInfo.currentFrame / frameInfo.cols+1) * th;


		//TODO: log error
		if (m_currentBuffer == nullptr) {
			std::cout << "Vertex Buffer was null while rendering texture with ID: " << tid << " Attempting to restart renderer.." <<std::endl;
		
			return;
		}

		m_currentBuffer->vertex = *m_tranformationStackBack * glm::vec4(0, 0, 0, 1);
		m_currentBuffer->uv.x = tx;
		m_currentBuffer->uv.y = ty;
		m_currentBuffer->tid = idForShader;
		m_currentBuffer->color = color;
		m_currentBuffer++;

		m_currentBuffer->vertex = *m_tranformationStackBack * glm::vec4(0, 1, 0, 1);
		m_currentBuffer->uv.x = tx;
		m_currentBuffer->uv.y = ty+th;
		m_currentBuffer->tid = idForShader;
		m_currentBuffer->color = color;
		m_currentBuffer++;

		m_currentBuffer->vertex = *m_tranformationStackBack * glm::vec4(1, 1, 0, 1);
		m_currentBuffer->uv.x = tx + tw,
		m_currentBuffer->uv.y = ty+th;
		m_currentBuffer->tid = idForShader;
		m_currentBuffer->color = color;
		m_currentBuffer++;

		m_currentBuffer->vertex = *m_tranformationStackBack * glm::vec4(1, 0, 0, 1);
		m_currentBuffer->uv.x = tx + tw,
		m_currentBuffer->uv.y = ty;
		m_currentBuffer->tid = idForShader;
		m_currentBuffer->color = color;
		m_currentBuffer++;

		m_indexCount += 6;

	}

	void BatchRenderer2D::drawString(const std::string& text, const glm::vec2& position, const Font* font, WattyColor labelColor, const Bounds2D bounds){
		bool found = false;
		ftgl::texture_font_t* ftFont = font->getFTFont();
		const GLuint tid = font->getTexID();
		float glTID = (float)tid;
		const unsigned int color = labelColor.c;
		float idForShader = 0.0f;
		
		if (glTID > 0) {
			bool found = false;
			for (size_t i = 0; i < m_glTIDsThisFlush.size(); i++)
			{
				if (m_glTIDsThisFlush[i] == glTID) {
					found = true;
				}

			}
			if (!found) {

				m_glTIDsThisFlush.push_back(glTID);
			}
			idForShader = (float)(m_glTIDsThisFlush.size() % m_maxTextureUnits);
			if (idForShader == 0.0f) idForShader = 1.0f;

		}

		if (m_glTIDsThisFlush.size() >= m_maxTextureUnits) {
			end();
			flush();
			begin();
			m_glTIDsThisFlush.push_back(glTID);

		}

		const glm::vec2 scale = font->getScale();
		//float x = position.x;
		

		float x = bounds.upperLeft.x;
		for (int i = 0; i < text.length(); i++){
			const char* c = &text[i];
			//const ftgl::texture_glyph_t* glyph = font.getGlyph(c); 

			ftgl::texture_glyph_t* glyph = texture_font_get_glyph(ftFont, c);
			if (glyph == NULL) {
				//TODO log error
				std::cout << "Failed loading glyph: " << c << std::endl;
				continue;
			}

			if (i > 0) {
				float kerning = ftgl::texture_glyph_get_kerning(glyph, c);
				x += kerning / scale.x;
			}

			if (*c == '\n') {
				m_currentTextLine++;
				x = bounds.upperLeft.x;
				continue; 
			}
		
			float y = bounds.upperLeft.y - (m_currentTextLine * font->getLineHeight());

			float x0 = x + glyph->offset_x / scale.x;
			float y0 = y + glyph->offset_y / scale.y;
			float x1 = x0 + glyph->width / scale.x;
			float y1 = y0 - glyph->height / scale.y;
				
			float s0 = glyph->s0;
			float t0 = glyph->t0;
			float s1 = glyph->s1;
			float t1 = glyph->t1;


			m_currentBuffer->vertex = *m_tranformationStackBack * glm::vec4(x0, y0, 0.0f, 1);
			m_currentBuffer->uv = glm::vec2(s0, t0);
			m_currentBuffer->tid = idForShader;
			m_currentBuffer->color = color;
			m_currentBuffer++;

			m_currentBuffer->vertex = *m_tranformationStackBack * glm::vec4(x0, y1, 0.0f, 1);
			m_currentBuffer->uv = glm::vec2(s0, t1);
			m_currentBuffer->tid = idForShader;
			m_currentBuffer->color = color;
			m_currentBuffer++;

			m_currentBuffer->vertex = *m_tranformationStackBack * glm::vec4(x1, y1, 0.0f, 1);
			m_currentBuffer->uv = glm::vec2(s1, t1);
			m_currentBuffer->tid = idForShader;
			m_currentBuffer->color = color;
			m_currentBuffer++;
				
			m_currentBuffer->vertex = *m_tranformationStackBack * glm::vec4(x1, y0 ,0.0f, 1);
			m_currentBuffer->uv = glm::vec2(s1, t0);
			m_currentBuffer->tid = idForShader;
			m_currentBuffer->color = color;
			m_currentBuffer++;

			m_indexCount += 6;
			x += glyph->advance_x/scale.x;
		}
	
	}

	void BatchRenderer2D::end(){
#ifdef WATTY_EMSCRIPTEN
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		if((m_currentBuffer - m_currentBufferBase) * RENDERER_VERTEX_SIZE > 0)
			glBufferSubData(GL_ARRAY_BUFFER, 0, (m_currentBuffer - m_currentBufferBase) * RENDERER_VERTEX_SIZE, m_currentBufferBase);
		m_currentBuffer = m_currentBufferBase;
#else
		glUnmapBuffer(GL_ARRAY_BUFFER);
#endif // WATTY_EMSCRIPTEN
		
	glBindBuffer(GL_ARRAY_BUFFER, NULL);

	}

	void BatchRenderer2D::flush(){
		m_currentTextLine = 0; // TODO: rethink, maybe move to label
		//bind all the textures
		for (size_t glIndex = 0; glIndex < m_glTIDsThisFlush.size(); glIndex++) {
			float thisGlTID = m_glTIDsThisFlush[glIndex];
			if (thisGlTID == 0) 
				continue;
			
			glActiveTexture(GL_TEXTURE0 + glIndex);
			glBindTexture(GL_TEXTURE_2D, thisGlTID);

		}

		// draw
		glBindVertexArray(m_vertexArray);
		m_indexBuffer->bind();
		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, NULL);
		m_indexBuffer->unbind();
		glBindVertexArray(NULL);
		
		
		// unbind all the textures 
		for (size_t glIndex = 0; glIndex < m_maxTextureUnits; glIndex++) {
			glActiveTexture(GL_TEXTURE0 + glIndex);
			glBindTexture(GL_TEXTURE_2D, NULL);
		}

		m_indexCount = 0;
		m_glTIDsThisFlush.clear();
		Renderer2D::globalFlushesThisFrame++;

	}



}}