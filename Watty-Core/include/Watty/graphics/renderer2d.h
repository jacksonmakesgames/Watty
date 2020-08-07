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
#include <graphics/font/font.h>
#include <graphics/buffers/indexbuffer.h>
#include <graphics/buffers/vertexarray.h>
#include <glm.hpp>


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
		unsigned int m_vertexArray;
		unsigned int m_vertexBuffer;
		IndexBuffer* m_indexBuffer;
		int m_indexCount;
		VertexData* m_currentBuffer;
		std::vector<float> m_glTIDsThisFlush;
		unsigned int m_textureArrayID;
		std::vector<const Texture*> m_textures;

		Renderer2D();
		
	public:
		void push(const glm::mat4& mat, bool override = false);

		glm::mat4 pop();

		virtual ~Renderer2D();


		virtual void begin();

		virtual void submit(const Renderable2D* renderable)=0;
		virtual void submit(float glTID, WattyColor color, glm::vec2 textureCoord, glm::vec2 textureSize);
#ifdef WATTY_OPENGL
		virtual void drawString(const std::string& text, const glm::vec2& position, const Font* font, WattyColor color, const Bounds2D bounds) {};
#endif

		virtual void end();
		virtual void init();
		virtual void flush();

	public:
		inline void nextFrame() { m_flushesThisFrame=0; }

	};

}}