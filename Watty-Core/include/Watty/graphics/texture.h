#pragma once
#include <string>

#ifdef WATTY_EMSCRIPTEN
#include <emscripten.h>
#include <GLES3/gl32.h>

#else
#include <glad/glad.h>
#endif

#include <utils/file_utils.h>
#include <assert.h> 
#include <stdint.h> 
#include <vector>

#include <Resource.h>

namespace letc {namespace graphics {
	class Texture {
	private:
		std::string m_filename;
		unsigned int m_TID = -1; // -1 = invalid id
		int m_width;
		int m_height;

		
	public:
		//Texture(const std::string& name);
		Texture(const std::string& filename);
		Texture();
		Texture(int screenWidth, int screenHeight);
		Texture(std::string fileName, unsigned int* atlasID, unsigned int width,unsigned int height, unsigned int depth, const void* data);
		~Texture();

		Texture* regenerate(unsigned int width, unsigned int height, const void* data);

		void bind() const;
		void bind(unsigned int glActiveTID) const;
		void unbind() const;
		void unbind(unsigned int glActiveTID) const;

		inline const int getNumColumns() const  { return m_width; }
		inline const int getNumRows() const { return m_height; }
		inline const int getID() const { return m_TID; }



		unsigned int upload(uint8_t* data, bool deleteData = true);
	private:
		unsigned int load(uint8_t* data, bool deleteData = true);
		bool isPowerOfTwo(int value);
	};
}}