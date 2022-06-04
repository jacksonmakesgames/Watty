#pragma once
#include "GUILayer.h"
#include "../window.h"
#include <gameobjects/GameObject.h>
#include <utils/Stats.h>
namespace watty { namespace graphics {

	class EngineControlLayer : public GUILayer
	{
		struct SelectableLayer {
			SelectableLayer(Layer* layer) :text(layer->name), layer(layer) {}
			Layer* layer;
			std::string text = "";
			bool IsSelected = false;
		};

		
		struct SelectableObject {
			SelectableObject(GameObject* obj) :text(object->name), object(obj){}
			GameObject* object;
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