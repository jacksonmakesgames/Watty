#pragma once

#ifdef WATTY_EMSCRIPTEN
#include <emscripten.h>
#include <GLES3/gl32.h>

#else
#include <glad/glad.h>
#endif

namespace watty {namespace graphics {
	
	class Buffer {
	private:
		unsigned int m_bufferID;
		unsigned int m_componentCount;
	public:
		Buffer(float* data, int count, unsigned int componentCount);
		~Buffer();
		void bind() const;
		void unbind() const;

		inline unsigned int getComponentCount() const { return m_componentCount; };
	};
	
}}
