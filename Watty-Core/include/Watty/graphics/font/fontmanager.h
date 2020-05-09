#pragma once
#include <vector>
#include "font.h"

namespace letc {namespace graphics {

	class FontManager {
	private:
		static std::vector<Font*> m_fonts;
		static::glm::vec2 m_fontScale;
	public:

	public:
		static void init(float xScale, float yScale);
		static void remakeAllFonts(float xScale, float yScale);

		static void add(std::string name, std::string filename, unsigned int size);
		static Font* get(const std::string& name);
		static Font* get(const std::string& name, unsigned int size);
		static void clean();


	private:
		FontManager() {}
	};
}}