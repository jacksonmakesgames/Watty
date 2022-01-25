#pragma once


#ifdef WATTY_EMSCRIPTEN
#include <emscripten.h>
//#include <GLFW/glfw3.h>
#include <GLES3/gl32.h>
#else
#include <glad/glad.h>
#endif
namespace watty {
	namespace graphics {

		class IndexBuffer {
		private:
			unsigned int m_bufferID;
			unsigned int m_count;
		public:
			IndexBuffer(unsigned short* data, int count);
			~IndexBuffer();
			void bind() const;
			void unbind() const;

			inline unsigned int getCount() const { return m_count; };
		};

	}
}
