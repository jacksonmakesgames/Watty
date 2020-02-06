#pragma once
#ifdef WATTY_OPENGL
// TODO: Abstract out atlases and fonts so that we can use this same header with vulkan
#include <ext/freetype-gl/freetype-gl.h>
#endif

#include <string>
#include <map>
#include "../texture.h"
#include <ext/glm/include/glm.hpp>
#include <iostream>

namespace letc {namespace graphics {
	class Font{
#ifdef WATTY_OPENGL

	const char* characters = " !\"#$%&'()*+,-./0123456789:;<=>?"
			"@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
			"`abcdefghijklmnopqrstuvwxyz{|}~";
	const unsigned short charCount = 94;
	private:
		ftgl::texture_atlas_t* m_FTAtlas;
		ftgl::texture_font_t* m_FTFont;
		std::string m_name;
		std::string m_fileName;
		glm::vec2 m_scale;
		unsigned int m_size;
		Texture * m_texture;
		std::map<char, ftgl::texture_glyph_t*> m_glyphs;

	private:
	public:
		void makeOpenGLTextureAtlas();
		void remakeOpenGLTextureAtlas(float scaleX, float scaleY);
		Font(unsigned int size);
		Font(std::string name, std::string filename, unsigned int size);
		Font(std::string name, std::string filename, unsigned int size, glm::vec2 scale);
		Font(ftgl::texture_font_t* ftglFont, ftgl::texture_atlas_t*);

		// TODO: there might be a faster way to cache
		inline const ftgl::texture_glyph_t* getGlyph(char c) const {return m_glyphs.find(c)->second;}
		inline void setScale(float x, float y) { m_scale = glm::vec2(x, y); }

		inline const glm::vec2& getScale() const { return m_scale; }
		inline const std::string& getName() const { return m_name; }
		inline const std::string& getFileName() const { return m_fileName; }
		inline const unsigned int getSize() const { return m_size; }

		inline const unsigned int getTexID() const { return m_texture->getID(); }
		inline ftgl::texture_font_t* getFTFont() const { return m_FTFont; }
		inline ftgl::texture_atlas_t* getFTAtlas() const { return m_FTAtlas; }
		inline Texture* getTexture() const { return m_texture; }
		~Font();
#endif
	};

}}