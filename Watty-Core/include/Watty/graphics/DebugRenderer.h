#pragma once
#include "buffers/indexbuffer.h"
#include "renderer2d.h"
#include "renderable2d.h"

#ifdef WATTY_OPENGL
#include <glad/glad.h>
#endif // WATTY_OPENGL


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
	unsigned int m_vertexArray;
	unsigned int m_vertexBuffer;
	IndexBuffer* m_indexBuffer;
	int m_indexCount;
	VertexData* m_currentBuffer;
	std::vector<float> m_glTIDsThisFlush;
	unsigned int m_textureArrayID;
	std::vector<const Texture*> m_textures;

public:
	DebugRenderer();
	~DebugRenderer();

	void begin() override;
	void submit(const Renderable2D* renderable) override;
	void submit(std::vector<glm::vec3> vertices, int vertexCount, WattyColor color);
	void end() override;
	void flush(unsigned int mode, int indexCount);

	void flush() override;

	inline int getIndexCount() { return m_indexCount; };

private:
	void init();


};


} }

