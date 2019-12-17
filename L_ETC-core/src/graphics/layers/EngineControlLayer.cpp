#include "EngineControlLayer.h"
namespace letc {namespace graphics {

	EngineControlLayer::EngineControlLayer(std::string name, bool& debugPhysics, bool& appReset, bool* windowVSync, std::vector<Layer*>& appLayers, graphics::Shader* shader) :
		GUILayer(name, shader),
		m_debugPhysics(debugPhysics),
		m_appLayers(appLayers),
		m_appReset(appReset),
		m_windowVSync(windowVSync)
	{
		GLfloat bkColor[4];
		glGetFloatv(GL_COLOR_CLEAR_VALUE, bkColor);
		m_clearColor = ImVec4(bkColor[0], bkColor[1], bkColor[2], bkColor[3]);

	}
	void EngineControlLayer::draw(){
		if (!enabled) return;
		// IMGUI
		// Start the Dear ImGui frame	
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		{
			ImGui::Begin("Application Info");
			ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::ColorEdit3("Clear Color", (float*)&m_clearColor);
			ImGui::End();
		}
		//layers:
		{
			ImGui::Begin("Layers");
			std::vector<SelectableLayer> layerNames;
			for (size_t i = 0; i < m_appLayers.size(); i++) {
				layerNames.push_back(SelectableLayer(m_appLayers[i]));
			}
			ImGui::PushItemWidth(-1);// "##empty"
			ImGui::ListBoxHeader("");
			for (SelectableLayer item : layerNames) {
				std::string postfix = (item.layer->enabled ? "" : "- Disabled");
				std::string item_name = item.text + postfix;
				ImVec4 col = item.layer->enabled ? ImVec4(0, 0, 0, 1) : ImVec4(.5, .5, .5, 1);
				ImGui::PushStyleColor(ImGuiCol_Text, col);
				ImGui::Checkbox(item.text.c_str(), &item.layer->enabled);
				ImGui::PopStyleColor();
			}
			ImGui::Checkbox("Debug Physics", &m_debugPhysics);

			ImGui::ListBoxFooter();
			ImGui::PopItemWidth();

			if (ImGui::Button("Reset")) {
				m_appReset = true;
			};

			if (ImGui::Checkbox("VSync", m_windowVSync)) {
				*m_windowVSync = !*m_windowVSync;
				Window::toggleVSync();
			}
		

			ImGui::End();
		}
		glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);

		Layer::draw();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	}
}}