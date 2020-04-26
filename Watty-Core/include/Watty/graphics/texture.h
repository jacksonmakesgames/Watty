#pragma once
//#include <ext/FreeImage/include/FreeImage.h>
#include <string>
#ifdef WATTY_OPENGL
#include <glad/glad.h>

#endif // WATTY_OPENGL


#include <assert.h> 
#include <stdint.h> 

#include <vector>

namespace letc {namespace graphics {
	class Texture {
	private:
		std::string m_filename;
		unsigned int m_TID;
		int m_width;
		int m_height;
		
	public:
		Texture(const std::string& filename);
		Texture(std::string fileName, unsigned int id, unsigned int width,unsigned int height,const void* data);
		~Texture();

		Texture* regenerate(unsigned int width, unsigned int height, const void* data);

		void bind() const;
		void bind(unsigned int glActiveTID) const;
		void unbind() const;
		void unbind(unsigned int glActiveTID) const;

		inline const int getNumColumns() const  { return m_width; }
		inline const int getNumRows() const { return m_height; }
		inline const int getID() const { return m_TID; }


	private:
		unsigned int load();

	};
}}