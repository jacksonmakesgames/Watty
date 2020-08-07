#include <graphics/batchrenderer2d.h>

namespace letc {namespace graphics {
	BatchRenderer2D::BatchRenderer2D() : Renderer2D()
	{
		
	}
	void BatchRenderer2D::submit(const Renderable2D* renderable){
		const glm::vec2& pos = renderable->getPosition();
		const glm::vec2& size = renderable->getSize();
		const unsigned int color = renderable->getColor().c;
		const std::vector<glm::vec2>& uvs = renderable->getUVs();
		const GLuint tid = renderable->getTID();
		float glTID = (float)tid;
		FrameInfo frameInfo = renderable->getFrameInfo();

		//TODO we can move this into the struct to save on divides in the render loop
		const float tw = 1.0f / frameInfo.cols;
		const float th = 1.0f / frameInfo.rows;

		const float tx = ((int)frameInfo.currentFrame % (int)frameInfo.cols) * tw;
		const float ty = 1 - (floor(frameInfo.currentFrame / frameInfo.cols + 1)) * th;

		Renderer2D::submit(glTID, color, {tx,ty}, {tw, th});

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

	void BatchRenderer2D::flush(){
		m_currentTextLine = 0; // TODO: rethink, maybe move to label
		Renderer2D::flush();
	}



}}