#pragma once
#ifdef WATTY_OPENGL
#include <glad/glad.h>
#endif
#include <imgui/imgui.h>
#include "layer.h"
#include "../batchrenderer2d.h"
#ifdef WATTY_OPENGL
#include "../imgui/imgui_impl_opengl3.h"
#endif
#include "../imgui/imgui_impl_glfw.h"

namespace letc { namespace graphics {
	class GUILayer : public Layer {
		
	private:
		

	public: 
		GUILayer(std::string name, graphics::Shader* shader);

		virtual void draw() override;

	};



} }