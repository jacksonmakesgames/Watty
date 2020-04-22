#include <graphics/DebugRenderer.h>
namespace letc {namespace graphics {
	DebugRenderer::DebugRenderer()
	{
		init();
	}
	DebugRenderer::~DebugRenderer()
	{
		delete m_indexBuffer;
		glDeleteBuffers(1, &m_vertexBuffer);
	}
	void DebugRenderer::begin()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); // bind vertex buffer
		m_currentBuffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY); // map the buffer and get the pointer to the first vertex
	}
	void DebugRenderer::submit(const Renderable2D* renderable){
	
	}

	void DebugRenderer::submit(std::vector<glm::vec3> vertices, int vertexCount, WattyColor color)
	{
		int uvX[] = { 0,0,1,1 };
		int uvY[] = { 0,1,1,0 };
		for (int i = 0; i < vertexCount; i++) {
			m_currentBuffer->vertex = *m_tranformationStackBack * glm::vec4(vertices[i].x, vertices[i].y, vertices[i].z, 1.0f);
			m_currentBuffer->uv = glm::vec2(uvX[i%4], uvY[i%4]);
			m_currentBuffer->tid = 0;
			m_currentBuffer->color = color.c;
			m_currentBuffer++;
		}

		m_indexCount += 6;

	}
	void DebugRenderer::end()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, NULL);
	}


	void DebugRenderer::flush(unsigned int mode, int indexCount)
	{
		//flush
		glBindVertexArray(m_vertexArray);
		m_indexBuffer->bind();
		glDrawElements(mode, indexCount, GL_UNSIGNED_SHORT, NULL);
		m_indexBuffer->unbind();
		glBindVertexArray(NULL);
		m_indexCount = 0;
		Renderer2D::globalFlushesThisFrame++;

	}

	void DebugRenderer::flush()
	{
		// draw
		glBindVertexArray(m_vertexArray);
		m_indexBuffer->bind();
		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, NULL);
		m_indexBuffer->unbind();
		glBindVertexArray(NULL);

		m_indexCount = 0;
		Renderer2D::globalFlushesThisFrame++;
	}

	

	void DebugRenderer::init()
	{

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
		glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::uv)));
		glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::tid)));
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));
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
	}
}}
