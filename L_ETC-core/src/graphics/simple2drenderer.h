#pragma once
#include "renderer2d.h"
#include "renderable2d.h"
#include <deque>

namespace letc {namespace graphics {
	class Simple2DRenderer : public Renderer2D {
	private:
		std::deque<const Renderable2D*> m_renderQueue;
	public:

		virtual void submit(const Renderable2D* renderable) override;
		virtual void flush() override;
	};

}}