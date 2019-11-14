#pragma once
#include "../renderable2d.h"

namespace letc {namespace graphics {
	class Group : public Renderable2D {
	private:
		std::vector<Renderable2D*> m_childrenRenderables;
		math::Matrix4 m_transformationMatrix;
	public:
		Group(const math::Matrix4& transform);
		~Group();
		void add(Renderable2D* renderable);
		void submit(Renderer2D* renderer)const  override;

	};
}}