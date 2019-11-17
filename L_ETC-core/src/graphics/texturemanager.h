#pragma once
#include <vector>
#include <string>

#include "texture.h"

namespace letc {namespace graphics {
	//each renderer should have one of these

	class TextureManager{

	private:
		std::vector<const Texture*> m_textures;
		unsigned int m_counter;
	public:
		TextureManager();
		~TextureManager();
		void addTexture(const Texture* texture);
		float getGLTextureID(unsigned int tid);
		void clean();
		
		inline std::vector<const Texture*> getTextures() { 
			return m_textures;
		}

		inline void resetCounter() { m_counter = 0; }
		inline unsigned int getCounter() { return m_counter; }


};

}}