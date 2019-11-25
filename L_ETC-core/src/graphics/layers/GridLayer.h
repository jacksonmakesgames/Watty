#pragma once
#include "layer.h";
#include "../shader.h"
#include "../GridRenderer.h"
namespace letc { namespace graphics {

	class GridLayer : public Layer {
		
	public:
		GridLayer(graphics::Shader* shader, float left, float right, float bottom, float top, float near, float far);

		void draw() override {
			if (!enabled) return;
			m_renderer->flush();
		};




	};


} }