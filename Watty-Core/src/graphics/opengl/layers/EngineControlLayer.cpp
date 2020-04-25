#include <graphics/layers/EngineControlLayer.h>
namespace letc {namespace graphics {

	EngineControlLayer::EngineControlLayer(std::string name, bool& debugPhysics, bool& appReset, bool* windowVSync, std::vector<Layer*>& appLayers) :
		GUILayer(name, new graphics::Shader()),
		m_debugPhysics(debugPhysics),
		m_appLayers(appLayers),
		m_appReset(appReset),
		m_windowVSync(windowVSync)
	{
		GLfloat bkColor[4];
		glGetFloatv(GL_COLOR_CLEAR_VALUE, bkColor);
		m_clearColor = ImVec4(bkColor[0], bkColor[1], bkColor[2], bkColor[3]);
		hidden = true;
	}
	void EngineControlLayer::draw(){
		if (!enabled) return;

			ImGui::Begin("Application Info"); {
				ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::ColorEdit3("Clear Color", (float*)&m_clearColor);
				ImGui::Text("%4d draws/frame", Renderer2D::globalFlushesThisFrame); // TODO: note that global flushes this frame will only be accurate if this layer is last layer in stack
			}ImGui::End();

			graphics::Renderer2D::globalFlushesThisFrame = 0; // TODO: could be inaccurate if 


			// Inspector:
			ImGui::Begin("Inspector"); {
				std::vector<SelectableLayer> layerNames;
				for (size_t i = 0; i < m_appLayers.size(); i++) {
					if (!m_appLayers[i]->hidden) {
						layerNames.push_back(SelectableLayer(m_appLayers[i]));
					}
				}
				ImGui::PushItemWidth(-1);// "##empty"
				bool header = ImGui::ListBoxHeader("", ImVec2(0, -100));
				// Layers
				for (SelectableLayer item : layerNames) {
					std::string postfix = (item.layer->enabled ? "" : "(Disabled)");
					std::string item_name = item.text + postfix;
					ImVec4 col = item.layer->enabled ? ImVec4(0, 0, 0, 1) : ImVec4(.5, .5, .5, 1);
					ImGui::PushStyleColor(ImGuiCol_Text, col);
					ImGui::Checkbox("", &item.layer->enabled);
					ImGui::PopStyleColor();

					std::vector<SelectableObject> selectableLayerObjects;
					std::vector<GameObject*> layerObjs = item.layer->getGameObjects();
					ImGuiTreeNodeFlags layerFlags = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_DefaultOpen;
					if (layerObjs.size() == 0) layerFlags |= ImGuiTreeNodeFlags_Bullet;
					
					ImGui::SameLine();
					if (ImGui::TreeNodeEx(item_name.c_str(), layerFlags)) {
						// Objects
						for (size_t j = 0; j < layerObjs.size(); j++) {
							selectableLayerObjects.push_back(SelectableObject(layerObjs[j]));
						}

						if (selectableLayerObjects.size()>0) {
							for (SelectableObject objItem : selectableLayerObjects) {
								std::string postfix = (objItem.object->enabled ? "" : "(Disabled)");
								std::string item_name = objItem.text + postfix;
								ImVec4 col = objItem.object->enabled ? ImVec4(0, 0, 0, 1) : ImVec4(.5, .5, .5, 1);
								ImGui::PushStyleColor(ImGuiCol_Text, col);
								ImGui::Checkbox(item_name.c_str(), &objItem.object->enabled);
								ImGui::PopStyleColor();
							}
						}
					ImGui::TreePop();
					}
				}
				if(header)
				ImGui::ListBoxFooter();
#ifdef DEBUG
				ImGui::Checkbox("Debug Physics", &m_debugPhysics);

#endif // DEBUG
				ImGui::PopItemWidth();

				if (ImGui::Checkbox("VSync", m_windowVSync)) {
					*m_windowVSync = !*m_windowVSync;
					Window::toggleVSync();
				}

				if (ImGui::Button("Reset")) {
					m_appReset = true;
				};
			}ImGui::End();
			
		//}
		
		glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);

		//Layer::draw();

		//ImGui::Render();
		//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	}
}}