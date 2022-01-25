#include <graphics/renderer2d.h>

namespace watty { namespace graphics {

	unsigned int Renderer2D::globalFlushesThisFrame = 0;
	Renderer2D::Renderer2D() {
		m_TransformationStack.push_back(glm::mat4(1.0));
		m_tranformationStackBack = &m_TransformationStack.back();
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &m_maxTextureUnits);
		init();
	}

	Renderer2D::Renderer2D(bool ECS){
		m_TransformationStack.push_back(glm::mat4(1.0));
		m_tranformationStackBack = &m_TransformationStack.back();
	}

	void Renderer2D::push(const glm::mat4& mat, bool override)
	{
		if (override) {
			m_TransformationStack.push_back(mat);
		}
		else {
			m_TransformationStack.push_back(m_TransformationStack.back() * mat);
		}
		m_tranformationStackBack = &m_TransformationStack.back();
	}

	glm::mat4 Renderer2D::pop()
	{
		if (m_TransformationStack.size() > 1) {
			m_TransformationStack.pop_back();
		}
		else {
			//TODO: log error
			std::cout << "ERROR: TRIED TO POP TOO MANY MATRIX4s" << std::endl;
			return glm::mat4(1.0f);
		}
		m_tranformationStackBack = &m_TransformationStack.back();
		return *m_tranformationStackBack;
	}

	Renderer2D::~Renderer2D()
	{
		delete m_indexBuffer;
		glDeleteBuffers(1, &m_vertexBuffer);
	}

	void Renderer2D::begin(){

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); // bind vertex buffer
#ifdef WATTY_EMSCRIPTEN
		m_currentBuffer = m_currentBufferBase;
#else
		m_currentBuffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY); // map the buffer and get the pointer to the first vertex
		if (m_currentBuffer == NULL) {
			//TODO log error
			//std::cout << "ERROR mapping opengl buffer in 2D renderer: GL error "<< glGetError() << std::endl;
			//exit(1);
		}
#endif

	}

	void Renderer2D::submit(float glTID, WattyColor color, glm::vec2 textureCoord, glm::vec2 textureSize)
	{
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
		

		//TODO: log error
		if (m_currentBuffer == NULL) {
			//std::cout << "Vertex Buffer was null while rendering texture with ID: " << glTID << " Attempting to restart renderer.." << std::endl;

			return;
		}

		m_currentBuffer->vertex = *m_tranformationStackBack * glm::vec4(0, 0, 0, 1);
		m_currentBuffer->uv.x = textureCoord.x;
		m_currentBuffer->uv.y = textureCoord.y;
		m_currentBuffer->tid = idForShader;
		m_currentBuffer->color = color;
		m_currentBuffer++;

		m_currentBuffer->vertex = *m_tranformationStackBack * glm::vec4(0, 1, 0, 1);
		m_currentBuffer->uv.x = textureCoord.x;
		m_currentBuffer->uv.y = textureCoord.y + textureSize.y;
		m_currentBuffer->tid = idForShader;
		m_currentBuffer->color = color;
		m_currentBuffer++;

		m_currentBuffer->vertex = *m_tranformationStackBack * glm::vec4(1, 1, 0, 1);
		m_currentBuffer->uv.x = textureCoord.x + textureSize.x,
		m_currentBuffer->uv.y = textureCoord.y + textureSize.y;
		m_currentBuffer->tid = idForShader;
		m_currentBuffer->color = color;
		m_currentBuffer++;

		m_currentBuffer->vertex = *m_tranformationStackBack * glm::vec4(1, 0, 0, 1);
		m_currentBuffer->uv.x = textureCoord.x + textureSize.x,
		m_currentBuffer->uv.y = textureCoord.y;
		m_currentBuffer->tid = idForShader;
		m_currentBuffer->color = color;
		m_currentBuffer++;

		m_indexCount += 6;
	}




	void Renderer2D::end()
	{
#ifdef WATTY_EMSCRIPTEN
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		if ((m_currentBuffer - m_currentBufferBase) * RENDERER_VERTEX_SIZE > 0)
			glBufferSubData(GL_ARRAY_BUFFER, 0, (m_currentBuffer - m_currentBufferBase) * RENDERER_VERTEX_SIZE, m_currentBufferBase);
		m_currentBuffer = m_currentBufferBase;
#else
		glUnmapBuffer(GL_ARRAY_BUFFER);
#endif // WATTY_EMSCRIPTEN

		glBindBuffer(GL_ARRAY_BUFFER, NULL);

	}

	void Renderer2D::init()
	{
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &m_maxTextureUnits);

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
		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
		glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, uv)));
		glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, tid)));
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, color)));
		//Unbind
		glBindBuffer(GL_ARRAY_BUFFER, NULL);

		//Indices
		int indexOffset = 0;
		GLushort indices[RENDERER_INDICES_SIZE];

		for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6) {
			indices[i + 0] = indexOffset + 0;
			indices[i + 1] = indexOffset + 1;
			indices[i + 2] = indexOffset + 2;

			indices[i + 3] = indexOffset + 2;
			indices[i + 4] = indexOffset + 3;
			indices[i + 5] = indexOffset + 0;

			indexOffset += 4;
		}

		m_indexBuffer = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

		m_indexCount = 0;

		//Unbind array
		glBindVertexArray(NULL);

#ifdef WATTY_EMSCRIPTEN
		m_currentBufferBase = new VertexData[RENDERER_MAX_SPRITES * 4]; // 4 verts
#endif

	}

	void Renderer2D::flush()
	{
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