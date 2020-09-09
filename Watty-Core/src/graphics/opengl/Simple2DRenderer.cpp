#include <Watty/graphics/Simple2DRenderer.h>
namespace letc {
	namespace graphics {

		void Simple2DRenderer::submit(const Renderable2D* renderable)
		{
			const unsigned int color = renderable->getColor().c;
			const GLuint tid = renderable->getTID();
			float glTID = (float)tid;

			Renderer2D::submit(glTID, color, { 0,0 }, { 1, 1});
		}
		void Simple2DRenderer::submit(WattyColor color)
		{
			Renderer2D::submit(0, color, { 0,0 }, { 1, 1 });
		}
		void Simple2DRenderer::submit(RenderableSpriteComponent* sprite)
		{
			Renderer2D::submit(sprite->texture.getID(), sprite->color, { 0,0 }, { 1, 1 });
		}
	}
}