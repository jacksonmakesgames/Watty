#include <graphics/font/font.h>

namespace watty {namespace graphics {

	Font::Font(unsigned int size){
		m_size = size;
		m_name = "default";
		m_fileName = "fonts/Roboto-Regular.ttf";
		makeOpenGLTextureAtlas();
	}


	Font::Font(std::string name, std::string filename, unsigned int size, glm::vec2 scale): 
	m_name(name), m_fileName(filename), m_size(size), m_scale(scale){
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


	Font::~Font(){
		
		texture_atlas_delete(m_FTAtlas);
		texture_font_delete(m_FTFont);
	}



	void Font::makeOpenGLTextureAtlas(){
		if (m_scale == glm::vec2(0, 0)) {
		//todo: log error:
			std::cout << "Error: Font has no scale, not generating atlas" << std::endl;
			return;
		}

		m_textureSize = m_maxChars * m_size * 0.0625f; // 1/16th of font size * number of characters

		m_FTAtlas = ftgl::texture_atlas_new(m_textureSize, m_textureSize, m_depth);


#ifdef WATTY_EMSCRIPTEN
		m_FTFont = texture_font_new_from_file(m_FTAtlas, m_size, m_fileName.c_str());
#else

		Resource* res = Resources::Load(m_fileName.c_str());
		if (res == nullptr) {
			//TODO log error
			std::cout << "Could not find font resource: " << m_fileName << std::endl;
			return;
		}
		m_FTFont = texture_font_new_from_memory(m_FTAtlas, m_size, res->data, res->size);
#endif // WATTY_EMSCRIPTEN	

		if (m_FTFont == NULL) {
			// TODO log error
			std::cout << "Error loading font file at " << m_fileName << std::endl;
			exit(1);
		}

		m_FTFont->rendermode = RENDER_OUTLINE_NEGATIVE; // No clue why this works/ is necessary, needs research
		if (strlen(characters) > m_maxChars) {
		// TODO LOG ERROR
			std::cout << "Error, tried to add too many characters to the font atlas" << std::endl;
		}

		ftgl::texture_font_load_glyphs(m_FTFont, characters);

		 for (size_t i = 0; i < charCount; i++){
			 m_glyphs[characters[i]] = ftgl::texture_font_find_glyph(m_FTFont, &characters[i]);
		 }

		m_LineHeight = m_FTFont->height/m_scale.y;
		m_texture = new Texture(m_fileName, &m_FTAtlas->id, m_FTAtlas->width, m_FTAtlas->height, m_FTAtlas->depth, m_FTAtlas->data);

		 
	}


	void Font::setScale(float X, float Y){
		m_scale = { X, Y };
		
	}

}}