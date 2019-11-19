#include "texturemanager.h"

namespace letc {namespace graphics {

	Texture* TextureManager::errorTexture = nullptr;
	std::vector<Texture*> TextureManager::m_textures = std::vector<Texture*>();

	TextureManager::~TextureManager(){
		clean();
	}

	void TextureManager::addTexture(const Texture* texture){
		bool found = false;
		for (size_t i = 0; i < m_textures.size(); i++) {
				if (m_textures[i]->getID() == texture->getID()) {
					found = true;
					m_textures[i] = texture;
					break;
				}
			}
		if (!found) {
			m_textures.push_back(texture);
		}
	}

	float TextureManager::getGLTextureID(unsigned int tid){
		float output = 0.0;
		bool found = false;
		for (size_t i = 0; i < m_textures.size(); i++) {
			if (m_textures[i]->getID() == tid) {
				output = (float)(m_textures[i]->getID());
				found = true;
				break;
			}
		}

		if (!found) {
			std::cout << "Could not get glTID from id: " << std::to_string(tid) << std::endl;
			return -1;
		}

		return output;
	}

	void TextureManager::clean(){
		for (size_t i = 0; i < m_textures.size(); i++){
			delete m_textures[i];
		}
		m_textures.clear();
	
	}

	void TextureManager::init()
	{
		m_textures = std::vector<const Texture*>();
		//addTexture(TextureManager::errorTexture);
	}




}}