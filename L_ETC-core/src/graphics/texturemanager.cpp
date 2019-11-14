#include "texturemanager.h"
namespace letc {namespace graphics {
	TextureManager::TextureManager(){
		
	}

	TextureManager::~TextureManager(){
		for (size_t i = 0; i < m_textures.size(); i++){
			delete m_textures[i];
		}
	}

	//void TextureManager::addTexture(Texture* texture){
	//	for (size_t i = 0; i < m_textures.size(); i++) {
	//		if (m_textureSlots[i] == font.getTexID()) {
	//			ts = (float)(i + 1);
	//			found = true;
	//			break;
	//		}
	//	}

	//	if (!found) {
	//		if (m_textureSlots.size() >= 32) {
	//			end();
	//			flush();
	//			begin();
	//		}
	//		m_textureSlots.push_back(font.getTexID());
	//		ts = (float)(m_textureSlots.size());
	//	}

	//}

	float TextureManager::getGLTextureID(unsigned int tid){
		float output = 0.0;
		bool found = false;
		for (size_t i = 0; i < m_textures.size(); i++) {
			if (m_textures[i]->getID() ==tid) {
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

	}

	Texture* TextureManager::generateNewTexture(const std::string filename)
	{
		return new Texture(filename);
		
	}


}}