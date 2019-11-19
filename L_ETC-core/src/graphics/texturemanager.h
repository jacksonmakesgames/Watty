#pragma once
#include <vector>
#include <string>
#include <iostream>


namespace letc {namespace graphics {
	class TextureManager{
	public:
		static Texture* errorTexture;

	private:
		friend class Texture;

		static std::vector<Texture*> m_textures;
	public:
		~TextureManager();
		static void addTexture(const Texture* texture);
		static float getGLTextureID(unsigned int tid);
		static void clean();
		static void init();
		
		inline static std::vector<Texture*> getTextures() { 
			return m_textures;
		}





	private:
		TextureManager() {}

};


}}