#pragma once
//#include <GL/glew.h>
#include <glad/glad.h>


namespace letc {namespace graphics {
	
	class Buffer {
	private:
		GLuint m_bufferID;
		GLuint m_componentCount;
	public:
		Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
		~Buffer();
		void bind() const;
		void unbind() const;

		inline GLuint getComponentCount() const { return m_componentCount; };
	};
	
}}
