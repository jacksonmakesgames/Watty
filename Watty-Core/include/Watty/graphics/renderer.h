#pragma once
#include <vector>
#include <iostream>
#include "Color.h"


#ifdef WATTY_EMSCRIPTEN
#include <emscripten.h>
#include <GLES3/gl32.h>
#else
#include <glad/glad.h>
#endif


#include "font/font.h"


#include <glm.hpp>

namespace letc {namespace graphics {
	class Renderable;
	struct VertexData;
	class Renderer{
	public:
		static unsigned int globalFlushesThisFrame;
	protected:

		std::vector<glm::mat4> m_TransformationStack;
		const glm::mat4* m_tranformationStackBack;
		unsigned short m_flushesPerFrame = 1;
		unsigned short m_flushesThisFrame = 0;
		int m_maxTextureUnits = 0;

		Renderer();
		
	public:
		void push(const glm::mat4& mat, bool override = false);

		glm::mat4 pop();

		virtual ~Renderer() {}

		virtual void begin() = 0;
		virtual void submit(const Renderable* renderable) = 0;
		virtual void end() = 0;
		virtual void flush() = 0;

	public:
		inline void nextFrame() { m_flushesThisFrame=0; }

	};

}}