#pragma once
#include "../../ext/freetype-gl/freetype-gl.h"
#include <string>
#include "../texture.h"
#include "../../math/vector2.h"

namespace letc {namespace graphics {
	class Font{
	const char* characters = " !\"#$%&'()*+,-./0123456789:;<=>?"
			"@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
			"`abcdefghijklmnopqrstuvwxyz{|}~";

	private:
		ftgl::texture_atlas_t* m_FTAtlas;
		ftgl::texture_font_t* m_FTFont;
		std::string m_name;
		std::string m_fileName;
		math::Vector2 m_scale;
		unsigned int m_size;
		Texture * m_texture;
	private:
	public:
		void makeOpenGLTextureAtlas();
		void remakeOpenGLTextureAtlas(float scaleX, float scaleY);
		Font(unsigned int size);
		Font(std::string name, std::string filename, unsigned int size);
		Font(std::string name, std::string filename, unsigned int size, math::Vector2 scale);
		Font(ftgl::texture_font_t* ftglFont, ftgl::texture_atlas_t*);

		inline void setScale(float x, float y) { m_scale = math::Vector2(x, y); }

		inline const math::Vector2& getScale() const { return m_scale; }
		inline const std::string& getName() const { return m_name; }
		inline const std::string& getFileName() const { return m_fileName; }
		inline const unsigned int getSize() const { return m_size; }

		inline const unsigned int getTexID() const { return m_texture->getID(); }
		inline ftgl::texture_font_t* getFTFont() const { return m_FTFont; }
		inline ftgl::texture_atlas_t* getFTAtlas() const { return m_FTAtlas; }
		inline Texture* getTexture() const { return m_texture; }
	};
}}