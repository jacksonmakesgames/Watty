#pragma once
#include "../renderer2d.h"
#include "group.h"
#include "../shader.h"
#include <vector>

namespace letc { namespace graphics{ 
	class Layer {
	protected:
		Renderer2D* m_renderer;
		std::vector<Renderable2D*> m_renderables;
		Shader* m_shader;
		math::Matrix4 m_prMatrix;
	protected:
		Layer(Renderer2D*, Shader* shader, math::Matrix4 prMatrix);
	public:
		virtual ~Layer();

		virtual void add(Renderable2D*	renderable);
		virtual void add(Group*			group);
		
		virtual void draw();

		inline const std::vector<Renderable2D*>& getRenderables() const { return m_renderables; }

	};

}}