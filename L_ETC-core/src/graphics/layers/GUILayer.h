#pragma once
#include <GL/glew.h>
#include "../../letc.h"
#include "layer.h"
#include "../batchrenderer2d.h"
#include <imgui/imgui.h>
#include "../imgui/imgui_impl_opengl3.h"
#include "../imgui/imgui_impl_glfw.h"

namespace letc { namespace graphics {
	class GUILayer : public Layer {
		struct SelectableLayer {
			SelectableLayer(Layer* layer):text(layer->name), layer(layer) {}
			Layer *layer;
			std::string text = "";
			bool IsSelected = false;
		};

	private:
		ImVec4 m_clearColor;
		LETC& m_app;

	public: 
		GUILayer(std::string name, LETC& app, graphics::Shader* shader, math::Matrix4 prMatrix);

		void draw() override;

	};



} }