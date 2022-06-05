#pragma once
#include <Watty.h>
#include <imgui_internal.h>
#include <stdio.h>
#include <math.h>
#include <tinyfiledialogs.h>
#include <ProjectManager.h>

using namespace watty;

namespace WattyEditor {

	
	class EditorApplication : public WattyEngine {
		typedef std::function<void (std::string name)> OnNameCallback;
	private:
		bool _guiFlagResetLayout = false;
		ImVec2 editorWindowSize = ImVec2(0,0);
		ImGuiIO& io = ImGuiIO();
		
		Project project;
		ProjectManager projectManager;
		
		bool _waitingForSaveNameNew = false;
		bool _waitingForSaveNameSaveAs = false;

	public:
		EditorApplication();

		// Engine Overrides
		void init() override;
		void editorUpdate() override;
		void onEditorGui() override;

		void setupEditorWindows();

		void openProject();
		void saveProject();
		void saveProjectAs(std::string name);
		void newProject(std::string name);

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
			void drawProjectSaveAsDialog(OnNameCallback callback);
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