#include "group.h"

namespace letc {namespace graphics {
	Group::Group(const math::Matrix4& transform) : m_transformationMatrix(transform) {}

	Group::~Group() {
		for (size_t i = 0; i < m_childrenRenderables.size(); i++)
		{
			delete m_childrenRenderables[i];
		}
	}
	
	void Group::add(Renderable2D* renderable){

		m_childrenRenderables.push_back(renderable);
	}

	void Group::submit(Renderer2D* renderer) const{
		renderer->push(m_transformationMatrix);
		for (const Renderable2D* renderable : m_childrenRenderables){
			renderable->submit(renderer);
		}
		renderer->pop();
	}

	
}}