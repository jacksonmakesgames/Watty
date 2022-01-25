#pragma once
#ifdef WATTY_OPENGL
#include <freetype-gl.h>
#endif
#include <string>
#include <map>
#include <graphics/texture.h>
#include <glm.hpp>
#include <iostream>
#include <graphics/shader.h>
#include <Resource.h>
namespace watty {namespace graphics {
	class Font{

	const char* characters =	" !\"#$%&'()*+,-./0123456789:;<=>?"
								"@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
								"`abcdefghijklmnopqrstuvwxyz{|}~";

	const unsigned short charCount = 94;
	private:
		ftgl::texture_atlas_t* m_FTAtlas;
		ftgl::texture_font_t* m_FTFont;
		std::string m_name;
		std::string m_fileName;
		glm::vec2 m_scale; // TODO seems to be backwards?
		
		unsigned int m_size;
		Texture * m_texture;
		float m_textureSize;
		unsigned int m_depth = 4;
		std::map<char, ftgl::texture_glyph_t*> m_glyphs;
		
		int m_maxChars = 256;

		float m_LineHeight = 2;

		//TODO: this is not where this should end up, we want to have the font system use our regular shaders
	public:

	private:
	public:
		void makeOpenGLTextureAtlas();
		void setScale(float X, float Y);

		Font(unsigned int size);
		Font(std::string name, std::string filename, unsigned int size, glm::vec2 scale);
		Font(ftgl::texture_font_t* ftglFont, ftgl::texture_atlas_t*);

		// TODO: there might be a faster way to cache
		inline const ftgl::texture_glyph_t* getGlyph(char c) const {return m_glyphs.find(c)->second;}

		inline const glm::vec2& getScale() const { return m_scale; }
		inline const std::string& getName() const { return m_name; }
		inline const std::string& getFileName() const { return m_fileName; }
		inline const unsigned int getSize() const { return m_size; }
		inline const float getLineHeight() const { return m_LineHeight; }

		inline const unsigned int getTexID() const { return m_texture->getID(); }
		inline ftgl::texture_font_t* getFTFont() const { return m_FTFont; }
		inline ftgl::texture_atlas_t* getFTAtlas() const { return m_FTAtlas; }
		inline Texture* getTexture() const { return m_texture; }
		~Font();
	};

}}