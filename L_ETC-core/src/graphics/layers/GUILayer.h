#pragma once
#include <GL/glew.h>
#include "layer.h"
#include "../batchrenderer2d.h"
#include <imgui/imgui.h>
#include "../imgui/imgui_impl_opengl3.h"
#include "../imgui/imgui_impl_glfw.h"

namespace letc { namespace graphics {
	class GUILayer : public Layer {
		
	private:
		

	public: 
		GUILayer(std::string name, graphics::Shader* shader, math::Matrix4 prMatrix);

		virtual void draw() override;

	};



} }