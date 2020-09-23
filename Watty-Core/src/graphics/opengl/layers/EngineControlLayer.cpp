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
		if (!enabled_) return;

			ImGui::Begin("Application Info"); {
				ImGui::Text("%.3f ms/frame (%.1f FPS) | %d updates/s", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate, Stats::getUpdatesPerSecond());
				ImGui::ColorEdit3("Clear Color", (float*)&m_clearColor);
				ImGui::Text("%4d draws/frame", Renderer2D::globalFlushesThisFrame); // TODO: note that global flushes this frame will only be accurate if this layer is last layer in stack
			}ImGui::End();

			graphics::Renderer2D::globalFlushesThisFrame = 0;

			// Inspector:
			ImGui::Begin("Inspector"); {
				std::vector<SelectableLayer> layerNames;
				for (size_t i = 0; i < m_appLayers.size(); i++) {
					if (!m_appLayers[i]->hidden) {
						layerNames.push_back(SelectableLayer(m_appLayers[i]));
					}
				}

				ImGui::PushItemWidth(-1); // "##empty"
				bool header = ImGui::ListBoxHeader("", ImVec2(0, -100));
				// Layers
				for (size_t layerIndex = 0; layerIndex < layerNames.size(); layerIndex++){
					SelectableLayer item = layerNames[layerIndex];
					bool layerEnabled = item.layer->isEnabled();

					std::string postfix = (layerEnabled ? "" : "(Disabled)");
					std::string item_name = item.text + postfix;

					ImVec4 col = layerEnabled ? ImVec4(0, 0, 0, 1) : ImVec4(.5, .5, .5, 1);

					ImGui::PushStyleColor(ImGuiCol_Text, col);
					if(ImGui::Checkbox(("##layer"+std::to_string(layerIndex)).c_str(), &layerEnabled))
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

			}ImGui::End();
			

		
		Camera::sceneCamera->setClearColor(WattyColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w));


	
	}
}}