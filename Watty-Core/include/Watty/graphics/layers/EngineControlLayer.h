#pragma once
#include "GuiLayer.h"
#include "../window.h"

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
		bool* m_windowVSync;
		std::vector<Layer*>& m_appLayers;

	public:
		EngineControlLayer(std::string name, bool& debugPhysics, bool& appReset, bool* windowVSync, std::vector<Layer*>& appLayers);
		void draw() override;

	private:
	};

	
} }