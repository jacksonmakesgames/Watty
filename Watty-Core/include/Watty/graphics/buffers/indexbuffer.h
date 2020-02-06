#pragma once
#ifdef WATTY_OPENGL
#include <ext/glad/include/glad/glad.h>
#endif
namespace letc {
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
