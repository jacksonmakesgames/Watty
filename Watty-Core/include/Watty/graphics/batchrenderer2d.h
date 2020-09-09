#pragma once

#include <cstddef>
#include "buffers/indexbuffer.h"
#include "renderer2d.h"
#include <graphics/font/label.h>

#define RENDERER_MAX_SPRITES		60000
#define RENDERER_VERTEX_SIZE		sizeof(VertexData)
#define RENDERER_SPRITE_SIZE		RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE		RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE		RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX		0
#define SHADER_UV_INDEX			1
#define SHADER_TID_INDEX		2
#define SHADER_COLOR_INDEX		3

namespace letc {namespace graphics {
	class BatchRenderer2D : public Renderer2D {
	private:
		int m_currentTextLine = 0;

#ifdef WATTY_EMSCRIPTEN

		VertexData* m_currentBufferBase;
#endif // WATTY_EMSCRIPTEN

	public:
		BatchRenderer2D();
		BatchRenderer2D(bool ECS);
		void submit(const Renderable2D* renderable) override;
		void flush() override;
#ifdef WATTY_OPENGL
		void drawString(const std::string& text, const glm::vec2& position, const Font* font, WattyColor labelColor, const Bounds2D bounds) override;
#endif
	};

}}