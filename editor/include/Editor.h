#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>

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

		
		/**
		* @brief 
		* Opens a project folder. Asks the user to select a folder.
		*/
		void openProject();
		
		/**
		 * @brief 
		 * Saves the current project to a folder. Asks the user to select a folder.
		 */
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


		/**
		 * @brief 
		 * Called before the editor exits. Cleans the frame buffer.
		*/
		int onExit();


	};

	/**
	 * @brief 
	 * A selectable layer to be shown in the inspector hierarchy.
	*/
	struct SelectableLayer {
		SelectableLayer(Layer* layer) :text(layer->name), layer(layer) {}
		Layer* layer;
		std::string text = "";
		bool IsSelected = false;
	};



	/**
	 * @brief 
	 * A selectable GameObject to be shown in the inspector hierarchy.
	*/
	struct SelectableObject {
		SelectableObject(GameObject* obj) :text(object->name), object(obj) {}
		GameObject* object;
		std::string text = "";
		bool IsSelected = false;
	};



}