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
#include <Resource.h>


namespace watty {
	using json = nlohmann::json;


	static uint8_t* load_image(const void* data, unsigned size, int* width, int* height) {

		int bpp;

		stbi_set_flip_vertically_on_load(true);

		uint8_t* rgba_image = stbi_load_from_memory((uint8_t*)data, size, width, height, &bpp, 4);

		return rgba_image;
	}

	static uint8_t* load_image_from_disk(const char* filename, int* width, int* height)
	{
#ifdef WATTY_OPENGL
		stbi_set_flip_vertically_on_load(true);
#endif
		int bpp;

		uint8_t* rgba_image = stbi_load(filename, width, height, &bpp, 4);
		

		return rgba_image;
	}

	static std::vector<char> read_file(const std::string& filename) {
#ifdef WATTY_EMSCRIPTEN
		std::ifstream file(filename, std::ios::ate | std::ios::binary);
		if (!file.is_open()) {
			std::cout << "Failed to open file: " << filename << std::endl;
			throw std::runtime_error("failed to open file!");
		}
		size_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);
		file.close();
		return buffer;

#else
		Resource* res = Resources::Load(filename.c_str());
		if (res == nullptr) {
			//TODO log error
			std::cout << "Error loading file: " << filename << std::endl;
			return std::vector<char>();
		}
		//int n = sizeof(res->size / sizeof(res->data[0]));
		std::vector<char> output(res->data, res->data+res->size);
		return output;
#endif // WATTY_EMSCRIPTEN
		
	}
	static std::vector<char> read_file_from_disk(const std::string& filename) {
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

	static bool write_string_to_file(const std::string& filename, const std::string& data) {
		std::ofstream out(filename);
		out << data;
		out.close();
		return true;
	}


}