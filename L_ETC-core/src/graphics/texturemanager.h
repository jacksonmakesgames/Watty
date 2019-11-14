#pragma once
#include <vector>
#include <string>

#include "texture.h"

namespace letc {namespace graphics {
	//each renderer should have one of these

	class TextureManager{
	public:
		TextureManager();
		~TextureManager();
		void addTexture(Texture* texture);
		void addTexture(unsigned int tid);
		float getGLTextureID(unsigned int tid);

		Texture* generateNewTexture(const std::string filename);
		Texture* generateNewTexture();

	private:
		std::vector<Texture*> m_textures;

};

}}