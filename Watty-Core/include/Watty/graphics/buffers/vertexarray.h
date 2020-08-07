#pragma once
#include <vector>

#ifdef WATTY_EMSCRIPTEN
#include <emscripten.h>
#else
#include <glad/glad.h>
#endif
#include <Watty/graphics/buffers/buffer.h>
#include <Watty/graphics/Color.h>

#include <glm.hpp>

namespace letc {namespace graphics {

	struct VertexData
	{
		glm::vec3 vertex;
		glm::vec2 uv;
		float tid;
		WattyColor color;
	};

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