#include <graphics/font/fontmanager.h>

namespace letc {namespace graphics {
	
	

	std::vector<Font*> FontManager::m_fonts;
	glm::vec2 FontManager::m_fontScale = {1,1};

	void FontManager::init(float xScale, float yScale)
	{
		m_fontScale = { xScale, yScale };

	}

	void FontManager::remakeAllFonts(float xScale, float yScale){
		m_fontScale = {xScale, yScale};
		for (size_t i = 0; i < m_fonts.size(); i++)
		{
			m_fonts[i]->setScale(xScale, yScale);
			m_fonts[i]->makeOpenGLTextureAtlas();
		}
	
	}

	void FontManager::add(std::string name, std::string filename, unsigned int size) {
		Font* font = new Font(name, filename, size, m_fontScale);
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
		return m_fonts[0];
	}

	void FontManager::clean() {
		for (size_t i = 0; i < m_fonts.size(); i++){
			
			m_fonts[i];
		}
	}

	

}}
