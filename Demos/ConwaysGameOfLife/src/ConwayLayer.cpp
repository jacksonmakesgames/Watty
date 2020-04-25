#include "ConwayLayer.h"
namespace letc { namespace graphics {
	ConwayLayer::ConwayLayer(std::string name, float& stepRate, bool& reset, bool& running, bool& funColors, bool& stepFlag, bool& stepBackFlag) :
		GUILayer(name, new Shader()),
		m_stepRateConway(stepRate),
		m_running(running),
		m_reset(reset),
		m_stepFlag(stepFlag),
		m_stepBackFlag(stepBackFlag),
		m_funColors(funColors)
	{
		m_stepRateInternal = stepRate;
	}

	void ConwayLayer::draw() {
		if (!enabled) return;
		// IMGUI
		// Start the Dear ImGui frame	
		ImGui::Begin("Conway"); {
			ImGui::Text("Simulation Speed:");
			ImGui::SameLine();
			ImGui::SliderFloat("", &m_stepRateInternal, .5f, 100.0f);
			ImGui::Checkbox("Run Simulation", &m_running);
			ImGui::SameLine();
			ImGui::Checkbox("x10 Speed", &m_x10Speed);
			if (m_x10Speed) m_stepRateConway = 10.0f * m_stepRateInternal;
			else m_stepRateConway = m_stepRateInternal;


			if (ImGui::Button("Back")) {
				m_stepBackFlag = true;
			};
			ImGui::SameLine();
			if (ImGui::Button("Next")) {
				m_stepFlag = true;
			};

			if (ImGui::Button("Clear")) {
				m_reset = true;
			};

			if (ImGui::BeginMenu("Settings"))
			{
				ImGui::Checkbox("Colors", &m_funColors);
				ImGui::EndMenu();
			}
		}ImGui::End();
		Layer::draw();


	}

} }
