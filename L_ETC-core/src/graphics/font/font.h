#pragma once
#include "../../ext/freetype-gl/freetype-gl.h"
#include <string>

namespace letc {namespace graphics {
	class Font{
	private:
		ftgl::texture_atlas_t* m_FTAtlas;
		ftgl::texture_font_t* m_FTFont;
		std::string m_name;
		std::string m_fileName;
		unsigned int m_size;
	private:
	public:
		void remakeOpenGLTextureAtlas();
		Font(unsigned int size);
		Font(std::string name, std::string filename, unsigned int size);
		Font(ftgl::texture_font_t* ftglFont, ftgl::texture_atlas_t*);

		inline const std::string& getName() const { return m_name; }
		inline const std::string& getFileName() const { return m_fileName; }
		inline const unsigned int getSize() const { return m_size; }

		inline const unsigned int getTexID() const { return m_FTAtlas->id; }
		inline ftgl::texture_font_t* getFTFont() const { return m_FTFont; }
	};
}}