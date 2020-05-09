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
	class Renderable2D;
	struct Bounds2D {
		glm::vec2 lowerLeft = { -.5f, -.5f };
		glm::vec2 upperLeft = { -.5f,  .5f };
		glm::vec2 upperRight = { .5f,  .5f };
		glm::vec2 lowerRight = { .5f, -.5f };

	};
	class Renderer2D{
	public:
		static unsigned int globalFlushesThisFrame;
	protected:

		std::vector<glm::mat4> m_TransformationStack;
		const glm::mat4* m_tranformationStackBack;
		unsigned short m_flushesPerFrame = 1;
		unsigned short m_flushesThisFrame = 0;
		int m_maxTextureUnits = 0;

		Renderer2D();
		
	public:
		void push(const glm::mat4& mat, bool override = false);

		glm::mat4 pop();

		virtual ~Renderer2D() {}


		virtual void begin() {}

		virtual void submit(const Renderable2D* renderable) = 0;
#ifdef WATTY_OPENGL
		virtual void drawString(const std::string& text, const glm::vec2& position, const Font* font, WattyColor color, const Bounds2D bounds) {};
#endif

		virtual void end() {}
		virtual void flush() = 0;

	public:
		inline void nextFrame() { m_flushesThisFrame=0; }

	};

}}