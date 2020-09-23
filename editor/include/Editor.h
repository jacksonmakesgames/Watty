#pragma once
#include <stdio.h>
#include <Watty.h>
#include <imgui_internal.h>
#include <math.h>

using namespace letc;


namespace WattyEditor {


	class EditorApplication : public WattyEngine {
	private:
		bool _guiFlagResetLayout = false;
	public:

		void init() override;
		void editorUpdate() override;
		void onEditorGui() override;
		int onExit();


	};


	struct SelectableLayer {
		SelectableLayer(Layer* layer) :text(layer->name), layer(layer) {}
		Layer* layer;
		std::string text = "";
		bool IsSelected = false;
	};


	struct SelectableObject {
		SelectableObject(GameObject* obj) :text(object->name), object(obj) {}
		GameObject* object;
		std::string text = "";
		bool IsSelected = false;
	};

}