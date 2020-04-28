#pragma once
#include <vector>

#ifdef WATTY_EMSCRIPTEN
#include <emscripten.h>
#else
#include <glad/glad.h>
#endif
#include "buffer.h"

namespace letc {namespace graphics {
	class VertexArray {
	private:
		unsigned int m_arrayID;
		std::vector<Buffer*> m_buffers;
	public:
		VertexArray();
		~VertexArray();

		void addBuffer(Buffer * buffer, unsigned int index);
		void bind() const;
		void unbind() const;
	};
}}