#pragma once
#include "buffers/indexbuffer.h"
#include "renderer2d.h"
#include "renderable2d.h"

#ifdef WATTY_OPENGL
#include <ext/glad/include/glad/glad.h>
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
class ParticleRenderer : public Renderer2D
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
	ParticleRenderer();
	~ParticleRenderer();

	void begin() override;
	void submit(const Renderable2D* renderable) override;
	void submit(glm::mat4 tranform, unsigned int color, glm::vec2 size);
	void submit(glm::vec3* vertices, int vertexCount, WattyColor color);
	void end() override;
	void flush() override;
private:
	void init();


};


} }

