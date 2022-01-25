#pragma once

#ifdef WATTY_EMSCRIPTEN
#include <emscripten.h>
#else
#include <glad/glad.h>
#endif


#include <imgui.h>
#include "layer.h"
#include "../batchrenderer2d.h"

namespace watty { namespace graphics {
	class GUILayer : public Layer {
		
	private:
		

	public: 
		GUILayer(std::string name, graphics::Shader* shader);

		virtual void draw() override;

	};



} }