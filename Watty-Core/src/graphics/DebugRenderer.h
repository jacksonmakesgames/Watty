#pragma once
#include "buffers/indexbuffer.h"
#include "renderer2d.h"
#include "renderable2d.h"
#include <glad/glad.h>

#define RENDERER_MAX_SPRITES		60000
#define RENDERER_VERTEX_SIZE		sizeof(VertexData)
#define RENDERER_SPRITE_SIZE		RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE		RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE		RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX		0
#define SHADER_UV_INDEX			1
#define SHADER_TID_INDEX		2
#define SHADER_COLOR_INDEX		3

namespace letc { namespace graphics {
class DebugRenderer : public Renderer2D
{
private:
	GLuint m_vertexArray;
	GLuint m_vertexBuffer;
	IndexBuffer* m_indexBuffer;
	GLsizei m_indexCount;
	VertexData* m_currentBuffer;
	std::vector<float> m_glTIDsThisFlush;
	unsigned int m_textureArrayID;
	std::vector<const Texture*> m_textures;

public:
	DebugRenderer();
	~DebugRenderer();

	void begin() override;
	void submit(const Renderable2D* renderable) override;
	void submit(math::Vector3* vertices, int vertexCount, unsigned int color);
	void end() override;
	void flush() override;
	void flush(unsigned int mode, int indexCount);
	void drawString(const std::string& text, const math::Vector3& position, const Font& font, unsigned int color) override;

private:
	void init();


};


} }

