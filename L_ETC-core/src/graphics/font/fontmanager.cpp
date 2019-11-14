#include "fontmanager.h"

namespace letc {namespace graphics {
	std::vector<Font*> FontManager::m_fonts;

	void FontManager::add(Font* font) {
		m_fonts.push_back(font);

	}

	Font* FontManager::get(const std::string& name){
		for (size_t i = 0; i < m_fonts.size(); i++){
			if (m_fonts[i]->getName() == name) return m_fonts[i];
		}
		return nullptr;
	}

	Font* FontManager::get(const std::string& name, unsigned int size){
		for (size_t i = 0; i < m_fonts.size(); i++) {
			if (m_fonts[i]->getSize() == size && m_fonts[i]->getName() == name) return m_fonts[i];
		}
		return nullptr;
	}

	void FontManager::clean() {
		for (size_t i = 0; i < m_fonts.size(); i++){
			delete m_fonts[i];
		}
	}

	

}}
