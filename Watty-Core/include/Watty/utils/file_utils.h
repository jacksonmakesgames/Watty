#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include <json.hpp>

#ifdef WATTY_EMSCRIPTEN
#include <emscripten.h>
#else
	#include <glad/glad.h>
#endif

#include <stb_image.h>

namespace letc {
	using json = nlohmann::json;


	static uint8_t* load_image(const char* filename, int* width, int* height)
	{
#ifdef WATTY_OPENGL
		stbi_set_flip_vertically_on_load(true);
#endif
		int bpp;

		uint8_t* rgba_image = stbi_load(filename, width, height, &bpp, 4);

		return rgba_image;
	}

	static std::vector<char> read_file(const std::string& filename) {
		std::ifstream file(filename, std::ios::ate | std::ios::binary);
		if (!file.is_open()) {
			throw std::runtime_error("failed to open file!");
		}
		size_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);
		file.close();
		return buffer;
	}


}