#include "texturemanager.h"
namespace letc {namespace graphics {
	TextureManager::TextureManager(){
		m_textures = std::vector<const Texture*>();
	}

	TextureManager::~TextureManager(){
		for (size_t i = 0; i < m_textures.size(); i++){
			delete m_textures[i];
		}
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
			if (m_textures.size() >= 32) {
				// DO SOMETHING
				/*end();
				flush();
				begin();*/
			}
			m_textures.push_back(texture);
		}
	}
	

	float TextureManager::getGLTextureID(unsigned int tid){
		float output = 0.0;
		bool found = false;
		for (size_t i = 0; i < m_textures.size(); i++) {
			if (m_textures[i]->getID() == tid) {
				output = (float)(i + 1);
				found = true;
				break;
			}
		}

		if (!found) {
			if (m_textures.size() >= 32) {
				return -1;
				/*m_renderer->end();
				m_renderer->flush();
				m_renderer->begin();*/
			}

			//m_textures.push_back(tid);
			output = (float)(m_textures.size());
		}

		return output;
	}



}}