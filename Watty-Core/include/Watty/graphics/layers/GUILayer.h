#pragma once
#include <ext/glad/include/glad/glad.h>
#include <ext/imgui/include/imgui/imgui.h>
#include "layer.h"
#include "../batchrenderer2d.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "../imgui/imgui_impl_glfw.h"

namespace letc { namespace graphics {
	class GUILayer : public Layer {
		
	private:
		

	public: 
		GUILayer(std::string name, graphics::Shader* shader);

		virtual void draw() override;

	};



} }