#include "font.h"

namespace letc {namespace graphics {
	Font::Font(unsigned int size){
		m_size = size;
		m_name = "default";
		m_fileName = "fonts/Roboto-Regular.ttf";
		makeOpenGLTextureAtlas();
	}

	Font::Font(std::string name, std::string filename, unsigned int size){
		m_name = name;
		m_fileName = filename;
		m_size = size;
		makeOpenGLTextureAtlas();

	}
	
	Font::Font(std::string name, std::string filename, unsigned int size, math::Vector2 scale){
		m_name = name;
		m_fileName = filename;
		m_size = size;
		m_scale = scale;
		makeOpenGLTextureAtlas();

	}


	Font::Font(ftgl::texture_font_t* ftglFont, ftgl::texture_atlas_t* ftglAtlas){
		m_name = ftglFont->filename;
		m_fileName = ftglFont->filename;
		m_size = ftglFont->size;
		m_FTFont = ftglFont;
		m_FTAtlas = ftglAtlas;

		
		makeOpenGLTextureAtlas();

	}
	void Font::makeOpenGLTextureAtlas(){
		m_FTAtlas = ftgl::texture_atlas_new(512, 512, 2);

		m_FTFont = texture_font_new_from_file(m_FTAtlas, m_size, m_fileName.c_str());

		texture_font_load_glyphs(m_FTFont, characters);

		 m_texture = new Texture(m_fileName, m_FTAtlas->id, m_FTAtlas->width, m_FTAtlas->height, m_FTAtlas->data);

	}
	void Font::remakeOpenGLTextureAtlas(float scaleX, float scaleY){
		m_scale = math::Vector2(scaleX, scaleY);
		
		m_FTAtlas = ftgl::texture_atlas_new(512, 512, 2);

		m_FTFont = texture_font_new_from_file(m_FTAtlas, m_size, m_fileName.c_str());

		texture_font_load_glyphs(m_FTFont, characters);
		

		 m_texture = m_texture->regenerate(m_texture->getID(), m_FTAtlas->width, m_FTAtlas->height, m_FTAtlas->data);

	}

}}