#pragma once

#ifdef WATTY_EMSCRIPTEN
#include <emscripten.h>
#else
#include <glad/glad.h>
#endif


#include <imgui.h>
#include "layer.h"
#include "../batchrenderer2d.h"

//#include "../imgui/imgui_impl_opengl3.h"

//#include "../imgui/imgui_impl_glfw.h"

namespace letc { namespace graphics {
	class GUILayer : public Layer {
		
	private:
		

	public: 
		GUILayer(std::string name, graphics::Shader* shader);

		virtual void draw() override;

	};



} }