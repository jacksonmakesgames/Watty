#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>

//#include <GL/glew.h>
#include "../../ext/glad/include/glad/glad.h"
#include "../../ext/FreeImage/include/FreeImage.h"


namespace fs = std::experimental::filesystem;

namespace letc {

	static BYTE* load_image(const char* filename, GLsizei* width, GLsizei* height)
	{
		//image format
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		//pointer to the image, once loaded
		FIBITMAP* dib = nullptr;


		//check the file signature and deduce its format
		fif = FreeImage_GetFileType(filename, NULL);
		//if still unknown, try to guess the file format from the file extension
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filename);
		//if still unkown, return failure
		if (fif == FIF_UNKNOWN)
			return nullptr;

		//check that the plugin has reading capabilities and load the file
		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filename);
		//if the image failed to load, return failure
		if (!dib)
			return nullptr;

		//retrieve the image data
		BYTE* pixels = FreeImage_GetBits(dib);

		//get the image width and height
		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);

		int bits = FreeImage_GetBPP(dib);

		size_t size = *width * *height * bits / 8;
		BYTE* output = new BYTE[size];
		memcpy(output, pixels, size);
		FreeImage_Unload(dib);

		//if this somehow one of these failed (they shouldn't), return failure
		if ((output == 0) || (width == 0) || (height == 0))
			return nullptr;

		return output;

	}

	static std::string read_file(const char* filepath) {
		FILE* file = &FILE();
		fopen_s(&file, filepath, "rt");
		if (file == NULL) {
			std::cout << "Error loading file: " << filepath << std::endl;
			exit(1);
		}
		fseek(file, 0, SEEK_END);
		unsigned long length = ftell(file);
		char* data = new char[length + 1];
		memset(data, 0, length + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);
		fclose(file);
		std::string output(data);
		delete[] data;
		return output;
	}





}