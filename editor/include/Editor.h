#pragma once
#include <Watty.h>
#include <ProjectManager.h>
#include <imgui_internal.h>
#include <tinyfiledialogs.h>
#include <stdio.h>
#include <math.h>

using namespace watty;


namespace WattyEditor {


	class EditorApplication : public WattyEngine {
	private:
		bool _guiFlagResetLayout = false;
		ImVec2 editorWindowSize = ImVec2(0,0);
		ImGuiIO& io = ImGuiIO();
		
		Project project;
		ProjectManager projectManager;

	public:
		EditorApplication();

		// Engine Overrides
		void init() override;
		void editorUpdate() override;
		void onEditorGui() override;

		void setupEditorWindows();

		void openProject();
		void saveProject();
		void saveProjectAs();
		void newProject();

		// Editor windows
		#pragma region windows
			void drawInspector();
			void drawHierarchy();
			void drawScene();
			void drawConsole();
			void drawMenu();
			void drawActions();
			void drawProjectFiles();
			void drawAppInfo();
		#pragma endregion windows

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