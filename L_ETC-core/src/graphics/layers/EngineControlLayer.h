#pragma once
#include "GuiLayer.h"
namespace letc { namespace graphics {

	class EngineControlLayer : public GUILayer
	{
		struct SelectableLayer {
			SelectableLayer(Layer* layer) :text(layer->name), layer(layer) {}
			Layer* layer;
			std::string text = "";
			bool IsSelected = false;
		};
	private:
		ImVec4 m_clearColor;
		bool& m_debugPhysics;
		bool& m_appReset;
		std::vector<Layer*>& m_appLayers;

	public:
		EngineControlLayer(std::string name, bool& debugPhysics, bool& appReset, std::vector<Layer*>& appLayers, graphics::Shader* shader, math::Matrix4 prMatrix);
		void draw() override;

	private:
	};

	
} }