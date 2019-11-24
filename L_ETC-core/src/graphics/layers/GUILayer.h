#pragma once
#include "layer.h"
#include "../batchrenderer2d.h"
#include <imgui/imgui.h>
#include "../imgui/imgui_impl_opengl3.h"
#include "../imgui/imgui_impl_glfw.h"

namespace letc { namespace graphics {
	class GUILayer : public Layer {
	ImVec4 m_clearColor = ImVec4(0, 0, 0, 1.00f);

	public: 
		GUILayer(graphics::Shader* shader, math::Matrix4 prMatrix);

		void draw() override;

	};



} }