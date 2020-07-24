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

#include "renderer.h"
#include <glm.hpp>

namespace letc {namespace graphics {
	class Renderable2D;
	struct VertexData;
	struct Bounds2D {
		glm::vec2 lowerLeft = { -.5f, -.5f };
		glm::vec2 upperLeft = { -.5f,  .5f };
		glm::vec2 upperRight = { .5f,  .5f };
		glm::vec2 lowerRight = { .5f, -.5f };

	};
	class Renderer2D : public Renderer{
	public:
	protected:
		Renderer2D();
		
	public:

		virtual ~Renderer2D() {}

		virtual void submit(const Renderable2D* renderable) = 0;
		virtual void drawString(const std::string& text, const glm::vec2& position, const Font* font, WattyColor color, const Bounds2D bounds) {};


	public:

	};

}}