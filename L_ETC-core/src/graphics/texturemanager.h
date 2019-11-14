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
		void addTexture(const Texture* texture);
		float getGLTextureID(unsigned int tid);
		inline std::vector<const Texture*> getTextures() { 
			return m_textures;
		}

	private:
		std::vector<const Texture*> m_textures;

};

}}