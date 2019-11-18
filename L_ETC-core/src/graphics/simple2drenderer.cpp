#include "simple2drenderer.h"

namespace letc {namespace graphics {

	void Simple2DRenderer::submit(const Renderable2D* renderable) {
		m_renderQueue.push_back(renderable);
	}


	void Simple2DRenderer::flush() {
		while (!m_renderQueue.empty()) {
			//const StaticSprite* renderable = (StaticSprite*) m_renderQueue.front();
			renderable->getVertexArray()->bind();
			renderable->getIndexBuffer()->bind();

			renderable->getShader().setUniformMat4("ml_matrix",
												   math::Matrix4::translation(renderable->getPosition()));
			glDrawElements(GL_TRIANGLES,
						   renderable->getIndexBuffer()->getCount(),
						   GL_UNSIGNED_SHORT,
						   0);

			renderable->getIndexBuffer()->unbind();
			renderable->getVertexArray()->unbind();
			m_renderQueue.pop_front();
		}
	}

}}