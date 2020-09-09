#pragma once
#include "renderer2d.h"
#include "renderable2d.h"
#include <deque>

namespace letc {namespace graphics {
	class Simple2DRenderer : public Renderer2D {
	public:
		Simple2DRenderer(bool ECS) : Renderer2D(ECS) {};
		virtual void submit(const Renderable2D* renderable) override;
		virtual void submit(WattyColor color);
		virtual void submit(RenderableSpriteComponent* sprite);
	};

}}