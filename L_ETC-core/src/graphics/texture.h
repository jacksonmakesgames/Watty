#pragma once
#include "FreeImage.h"
#include <string>
#include <GL/glew.h>
#include <vector>
//#include "texturemanager.h"

namespace letc {namespace graphics {
	class Texture {
	public:
		static std::vector<const Texture*> allTextures;

	private:
		std::string m_filename;
		GLuint m_TID;
		GLsizei m_width;
		GLsizei m_height;
	public:
		Texture(const std::string& filename);
		Texture(std::string fileName, unsigned int id, unsigned int width,unsigned int height,const void* data);
		//~Texture();

		Texture* regenerate(unsigned int id, unsigned int width, unsigned int height, const void* data);

		void bind() const;
		void unbind() const;

		inline const GLsizei getWidth() const  { return m_width; }
		inline const GLsizei getHeight() const { return m_height; }
		inline const GLsizei getID() const { return m_TID; }

		static std::vector<const Texture*> getAllTextures();
		static void clean();

	private:
		GLuint load();
		static void addGlobalTexture(Texture* texture);

	};
}}