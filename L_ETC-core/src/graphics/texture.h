#pragma once
#include "FreeImage.h"
#include <string>
#include <GL/glew.h>


namespace letc {namespace graphics {
	class Texture {
	private:
		std::string m_filename;
		GLuint m_TID;
		GLsizei m_width;
		GLsizei m_height;
	public:
		Texture(const std::string& filename);
		Texture(std::string fileName, unsigned int id, unsigned int width,unsigned int height,const void* data);
		//~Texture();

		void bind() const;
		void unbind() const;

		inline const GLsizei getWidth() const  { return m_width; }
		inline const GLsizei getHeight() const { return m_height; }
		inline const GLsizei getID() const { return m_TID; }
	private:
		GLuint load();

	};
}}