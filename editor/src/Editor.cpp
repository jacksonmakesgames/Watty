#include <Editor.h>

#define WATTY_EDITOR 1

namespace WattyEditor {
	using namespace graphics;
	EditorApplication::EditorApplication() {}

	void EditorApplication::init()
	{
		WATTY_EDITOR_ATTACHED = true;
		window->setSize({ 1600,900 });
		window->setTitle("Editor - Watty Game Engine");
		window->useVSync = false;

		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		Window::allowMultipleSubWindows = true;

		GameObject* g0 = Instantiate<GameObject>({ 0,0 }, { 1,1 });
		g0->addComponent(new graphics::Sprite(graphics::Color::white));

		GameObject* g1 = Instantiate<GameObject>({ -5,-4 }, { 5,5 });
		g1->addComponent(new graphics::Sprite(graphics::Color::blue));

		GameObject* g2 = Instantiate<GameObject>({ 5,4 }, { 5,5 });
		g2->addComponent(new graphics::Sprite(graphics::Color::pink));


		testTexture = new graphics::Texture("textures/test.png");
		screenTexture = new graphics::Texture(window->getWidth(), window->getHeight());
		setupFrameBuffer();
		//new graphics::EngineControlLayer("Engine Control", debugPhysics, resetFlag, &graphics::Window::useVSync, Layer::allLayers);

		ImGui::StyleColorsDark(); // TODO option
	}
	void EditorApplication::editorUpdate() {
		/*sceneCamera->setSize(glm::vec2(
			sceneCamera->getSize().x - (10.0f * window->getAspectRatio().x * Input::getScrollAmountThisFrameY()) * Timer::delta,
			sceneCamera->getSize().y - (10.0f * window->getAspectRatio().y * Input::getScrollAmountThisFrameY()) * Timer::delta
		));*/
	}


	void EditorApplication::onEditorGui() {
		editorWindowSize = ImVec2(window->getWidth(), window->getHeight());

#ifdef WATTY_EDITOR

#ifdef DEBUG
		// Every frame?? TODO
		if (Layer::getLayerByName("Debug Physics Layer"))
			debugPhysics ?
			Layer::getLayerByName("Debug Physics Layer")->enable() : Layer::getLayerByName("Debug Physics Layer")->disable();
#endif
		setupEditorWindows();

		drawMenu();
		drawScene();
		drawHierarchy();
		drawConsole();
		drawProjectFiles();
		drawActions();


		if (false) {
			drawAppInfo();
		}
		graphics::Renderer2D::globalFlushesThisFrame = 0;


		ImGui::Begin("Debug Size");
		{
			ImGui::Text("Size: %f", sceneCamera->getSize());
			ImGui::Text("Viewport: %f, %f", sceneCamera->getViewportSize().x, sceneCamera->getViewportSize().y);
		}
		ImGui::End(); // debug


#endif // WATTY_EDITOR
	}

	void EditorApplication::setupEditorWindows() {
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (true)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->GetWorkPos());
			ImGui::SetNextWindowSize(viewport->GetWorkSize());
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;


		// Main
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos, ImGuiCond_Always);
		ImGui::SetNextWindowSize(editorWindowSize, ImGuiCond_Always);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("MainWindow", NULL,
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoSavedSettings |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoScrollWithMouse |
			ImGuiWindowFlags_MenuBar |
			ImGuiWindowFlags_NoBringToFrontOnFocus |
			ImGuiWindowFlags_NoNavFocus				/*|
			ImGuiWindowFlags_NoBackground*/
		);
		ImGui::PopStyleVar();
		if (true)
			ImGui::PopStyleVar(2);

		// DockSpace
		io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");

			// Reset layout if flag is tripped
			if (_guiFlagResetLayout) {
				ImGui::DockBuilderRemoveNode(dockspace_id); // Clear out existing layout
				_guiFlagResetLayout = false;
			}

			// Setup docking
			if (ImGui::DockBuilderGetNode(dockspace_id) == nullptr) {
				// First time or reset was tripped, create layout
				ImGui::DockBuilderRemoveNode(dockspace_id);
				ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_None);

				ImGuiID dock_main_id = dockspace_id;
				ImGuiID dock_right_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.2f, nullptr, &dock_main_id);
				ImGuiID dock_left_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.2f, nullptr, &dock_main_id);
				ImGuiID dock_up_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Up, 0.035f, nullptr, &dock_main_id);
				ImGuiID dock_up_right_id = ImGui::DockBuilderSplitNode(dock_up_id, ImGuiDir_Right, 0.4f, nullptr, &dock_up_id);
				ImGuiID dock_down_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.2f, nullptr, &dock_main_id);
				ImGuiID dock_down_right_id = ImGui::DockBuilderSplitNode(dock_down_id, ImGuiDir_Right, 0.6f, nullptr, &dock_down_id);

				ImGui::DockBuilderDockWindow("Actions", dock_up_id);
				ImGui::DockBuilderDockWindow("Hierarchy", dock_left_id);
				ImGui::DockBuilderDockWindow("Inspector", dock_right_id);
				ImGui::DockBuilderDockWindow("Console", dock_down_id);
				ImGui::DockBuilderDockWindow("Project files", dock_down_id);
				ImGui::DockBuilderDockWindow("Scene", dock_main_id);
				ImGui::DockBuilderDockWindow("Application Info", dock_up_right_id);

				// Disable tab bar for custom toolbar
				ImGuiDockNode* node = ImGui::DockBuilderGetNode(dock_up_id);
				node->LocalFlags |= ImGuiDockNodeFlags_NoTabBar;

				ImGui::DockBuilderFinish(dock_main_id);
			}
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);


		}
		else
		{
		}
	}


	//Windows
#pragma windows

	void EditorApplication::drawInspector() {
		ImGui::Begin("Inspector");
		{


		}ImGui::End(); // Inspector
	}

	void EditorApplication::drawHierarchy() {
		ImGui::Begin("Hierarchy");
		{
			std::vector<SelectableLayer> layerNames;
			for (size_t i = 0; i < Layer::allLayers.size(); i++) {
				if (!Layer::allLayers[i]->hidden) {
					layerNames.push_back(SelectableLayer(Layer::allLayers[i]));
				}
			}

			ImGui::PushItemWidth(-1); // "##empty"
			bool header = ImGui::ListBoxHeader("", ImVec2(0, -100));
			// Layers
			for (size_t layerIndex = 0; layerIndex < layerNames.size(); layerIndex++) {
				SelectableLayer item = layerNames[layerIndex];
				bool layerEnabled = item.layer->isEnabled();

				std::string postfix = (layerEnabled ? "" : "(Disabled)");
				std::string item_name = item.text + postfix;

				ImVec4 col = layerEnabled ? ImVec4(0, 0, 0, 1) : ImVec4(.5, .5, .5, 1);

				ImGui::PushStyleColor(ImGuiCol_Text, col);
				if (ImGui::Checkbox(("##layer" + std::to_string(layerIndex)).c_str(), &layerEnabled))
					layerEnabled ? item.layer->enable() : item.layer->disable();

				ImGui::PopStyleColor();

				std::vector<GameObject*> layerObjs = item.layer->getGameObjects();
				ImGuiTreeNodeFlags layerFlags = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_CollapsingHeader;
				if (layerObjs.size() == 0) layerFlags |= ImGuiTreeNodeFlags_Bullet;

				ImGui::SameLine();
				if (ImGui::CollapsingHeader((item_name + "##layer_tree" + std::to_string(layerIndex)).c_str(), layerFlags)) {
					// Objects
					for (size_t objIndex = 0; objIndex < layerObjs.size(); objIndex++) {
						ImGui::Indent();
						SelectableObject selectable = SelectableObject(layerObjs[objIndex]);
						bool enabled = selectable.object->isEnabled();

						std::string postfix = (enabled ? "" : "(Disabled)");
						std::string item_name_obj = selectable.text + postfix;
						ImVec4 colObj = enabled ? ImVec4(0, 0, 0, 1) : ImVec4(.5, .5, .5, 1);

						ImGui::PushStyleColor(ImGuiCol_Text, colObj);

						if (ImGui::Checkbox((item_name_obj + "##obj" + std::to_string(objIndex)).c_str(), &enabled))
							enabled ? selectable.object->enable() : selectable.object->disable();

						ImGui::PopStyleColor();
						ImGui::Unindent();
					}

				}

			}

			if (header)
				ImGui::ListBoxFooter();

#ifdef DEBUG
			ImGui::Checkbox("Debug Physics", &debugPhysics);

#endif // DEBUG
			ImGui::PopItemWidth();

			if (ImGui::Checkbox("VSync", &window->useVSync)) {
				/**m_windowVSync = !*m_windowVSync;
				Window::toggleVSync();*/
			}
		}
		ImGui::End(); // Hierarchy


	}

	void EditorApplication::drawMenu() {

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("Import")) {}
				if (ImGui::MenuItem("New")) {}
				if (ImGui::MenuItem("Open", "Ctrl+O")) {}
				if (ImGui::BeginMenu("Open Recent"))
				{
					ImGui::MenuItem("fish_hat.c");
					ImGui::MenuItem("fish_hat.inl");
					ImGui::MenuItem("fish_hat.h");
					if (ImGui::BeginMenu("More.."))
					{
						ImGui::MenuItem("Hello");
						ImGui::MenuItem("Sailor");
						ImGui::EndMenu();
					}
					ImGui::EndMenu();
				}
				if (ImGui::MenuItem("Save", "Ctrl+S")) {}
				if (ImGui::MenuItem("Save As..")) {}
				ImGui::EndMenu(); // File
			}

			if (ImGui::BeginMenu("View")) {
				if (ImGui::MenuItem("Reset Layout")) { _guiFlagResetLayout = true; }
				ImGui::EndMenu(); // View
			}
			//App info:
			ImGui::NextColumn();
			ImGui::SameLine(ImGui::GetWindowWidth() - 600);

			char text[200];
			std::sprintf(text,
				"%.3f ms/frame (%.1f FPS) |  %3d updates/s | %4d draws/frame",
				1000.0f / io.Framerate,
				io.Framerate,
				Stats::getUpdatesPerSecond(),
				Renderer2D::globalFlushesThisFrame);

			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetColumnWidth() - ImGui::CalcTextSize(text).x
				- ImGui::GetScrollX() - 2 * ImGui::GetStyle().ItemSpacing.x);
			ImGui::Text("%s", text);
			ImGui::EndMenuBar();
		}

		ImGui::End();
	}

	void EditorApplication::drawConsole() {
		ImGui::Begin("Console");
		{

		}
		ImGui::End(); // Console
	}

	void EditorApplication::drawActions() {
		ImGui::Begin("Actions", NULL,
			ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoScrollWithMouse);
		{
			static float buttonSize = 100;
			static float indent = 10;
			static ImVec2 winSize = ImGui::GetWindowSize();
			float startx = (winSize.x - ((buttonSize * 3) + (indent * 2))) / 2;
			ImGui::SetCursorPosX(startx);
			ImGui::PushItemWidth(buttonSize);
			if (ImGui::Button("Play")) {}
			ImGui::SameLine();
			if (ImGui::Button("Pause")) {}
			ImGui::SameLine();
			if (ImGui::Button("More")) {}
			ImGui::PopItemWidth();
		}
		ImGui::End(); // Actions
	}

	void EditorApplication::drawScene() {
		//ImGui::SetNextWindowSize(ImVec2(window->getWidth()/1.5f - 10, window->getHeight() - 10));
		ImGui::Begin("Scene");
		{
			ImGui::BeginChild("Watty Render");

			//glm::vec2 windowViewport = .5f * sceneCamera->getViewportSize() * window->PIXEL_TO_METER_RATIO;


			auto initialCursorPos = ImGui::GetCursorPos();
			ImVec2 winSize = ImGui::GetWindowSize();
			auto centralizedCursorpos = ImVec2((winSize.x - editorWindowSize.x) * 0.5f, (winSize.y - editorWindowSize.y) * 0.5f);
			ImGui::SetCursorPos(centralizedCursorpos);




			ImGui::GetWindowDrawList()->AddImage(
				(void*)getRenderTexture(),
				ImVec2(ImGui::GetCursorScreenPos()),
				ImVec2(ImGui::GetCursorScreenPos().x + editorWindowSize.x,
					ImGui::GetCursorScreenPos().y + editorWindowSize.y), ImVec2(0, .5), ImVec2(.5, 0));

		

			
			sceneCamera->setWindowSize(glm::vec2(2 * (ImGui::GetWindowSize().x / window->PIXEL_TO_METER_RATIO), 2 * (ImGui::GetWindowSize().y / window->PIXEL_TO_METER_RATIO)));
			
			
			//ImGui::GetWindowDrawList()->AddImage(
			//	(void*)getRenderTexture(),
			//	ImVec2(ImGui::GetCursorScreenPos()),
			//	ImVec2(ImGui::GetCursorScreenPos().x + editorWindowSize.x,
			//		ImGui::GetCursorScreenPos().y + editorWindowSize.y), ImVec2(0, 1), ImVec2(1, 0));

			/*		ImGui::GetWindowDrawList()->AddImage(
						(void*)getRenderTexture(),
						ImVec2(ImGui::GetCursorScreenPos()),
						ImVec2(ImGui::GetCursorScreenPos().x + 1600.0f,
							ImGui::GetCursorScreenPos().y + 900.0f), ImVec2(0, 1), ImVec2(1, 0));*/


							/*ImVec2(ImGui::GetCursorScreenPos().x + .5f*sceneCamera->getViewportSize().x * window->PIXEL_TO_METER_RATIO,
								ImGui::GetCursorScreenPos().y + .5f*sceneCamera->getViewportSize().y * window->PIXEL_TO_METER_RATIO), ImVec2(0, 1), ImVec2(1, 0));*/

			ImGui::SetCursorPos(initialCursorPos);

			if (ImGui::IsWindowHovered()) {
				sceneCamera->setSize(sceneCamera->getSize() - Input::getScrollAmountThisFrameY() * Timer::delta);
			}

			ImGui::EndChild();
		}
		ImGui::End(); // Scene
	}
	void EditorApplication::drawProjectFiles() {
		ImGui::Begin("Project files");
		{
			if (ImGui::BeginMenuBar()) {

				ImGui::EndMenuBar();
			}

		}
		ImGui::End(); // Project files
	}
	void EditorApplication::drawAppInfo() {
		ImGui::Begin("Application Info", NULL, ImGuiWindowFlags_NoTitleBar); {
			ImGui::Text("%.3f ms/frame (%.1f FPS) | %d updates/s", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate, Stats::getUpdatesPerSecond());
			ImGui::SameLine();
			ImGui::Text(" | %4d draws/frame", Renderer2D::globalFlushesThisFrame); // TODO: note that global flushes this frame will only be accurate if this layer is last layer in stack
			ImGui::ColorEdit3("Clear Color", (float*)&sceneCamera->getClearColor());
		}ImGui::End(); //Application info
	}

	int EditorApplication::onExit() {
		cleanFrameBuffer();
		return 0;
	}


	#pragma windows
}
	
	

using namespace WattyEditor;
int main(int ac, char** av) {
	EditorApplication app = EditorApplication();
	app.start();
	return app.onExit();
}



