#include <graphics/font/font.h>

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
	Font::~Font()
	{
		
		texture_atlas_delete(m_FTAtlas);
		texture_font_delete(m_FTFont);
	}
	void Font::makeOpenGLTextureAtlas(){

		// glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  //?
		m_FTAtlas = ftgl::texture_atlas_new(512, 512, 2);

		m_FTFont = texture_font_new_from_file(m_FTAtlas, m_size, m_fileName.c_str());
		if (m_FTFont == NULL) {
			std::cout << "Error loading font file at " << m_fileName << std::endl;
			exit(1);
		}
		texture_font_load_glyphs(m_FTFont, characters);

		 m_texture = new Texture(m_fileName, m_FTAtlas->id, m_FTAtlas->width, m_FTAtlas->height, m_FTAtlas->data);

		 
		 for (size_t i = 0; i < charCount; i++){
			 m_glyphs[characters[i]] = ftgl::texture_font_find_glyph(m_FTFont, &characters[i]);
		 }
	}
	void Font::remakeOpenGLTextureAtlas(float scaleX, float scaleY){
		m_scale = math::Vector2(scaleX, scaleY);
		
		m_FTAtlas = ftgl::texture_atlas_new(512, 512, 2);

		m_FTFont = texture_font_new_from_file(m_FTAtlas, m_size, m_fileName.c_str());

		texture_font_load_glyphs(m_FTFont, characters);
		

		 m_texture = m_texture->regenerate( m_FTAtlas->width, m_FTAtlas->height, m_FTAtlas->data);

	}

}}