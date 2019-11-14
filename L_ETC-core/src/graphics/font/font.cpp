#include "font.h"

namespace letc {namespace graphics {
	Font::Font(unsigned int size){
		m_size = size;
		m_name = "default";
		m_fileName = "fonts/Roboto-Regular.ttf";
		remakeOpenGLTextureAtlas();
	}

	Font::Font(std::string name, std::string filename, unsigned int size){
		m_name = name;
		m_fileName = filename;
		m_size = size;
		remakeOpenGLTextureAtlas();

	}

	Font::Font(ftgl::texture_font_t* ftglFont, ftgl::texture_atlas_t* ftglAtlas){
		m_name = ftglFont->filename;
		m_fileName = ftglFont->filename;
		m_size = ftglFont->size;
		m_FTFont = ftglFont;
		m_FTAtlas = ftglAtlas;

		
		//remakeOpenGLTextureAtlas();

	}
	void Font::remakeOpenGLTextureAtlas(){
		m_FTAtlas = ftgl::texture_atlas_new(512, 512, 2);

		m_FTFont = texture_font_new_from_file(m_FTAtlas, m_size, m_fileName.c_str());

		const char* cache = " !\"#$%&'()*+,-./0123456789:;<=>?"
			"@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
			"`abcdefghijklmnopqrstuvwxyz{|}~";

		texture_font_load_glyphs(m_FTFont, cache);

		//TODO: this will move
		// make GL texture
		glGenTextures(1, &m_FTAtlas->id);
		glBindTexture(GL_TEXTURE_2D, m_FTAtlas->id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, m_FTAtlas->width, m_FTAtlas->height,
			0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, m_FTAtlas->data);



	}

}}