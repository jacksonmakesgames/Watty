#include "ConwayLayer.h"
namespace letc { namespace graphics {
	ConwayLayer::ConwayLayer(std::string name, float& stepRate, bool& reset, bool& running, bool& funColors, bool& stepFlag, bool& stepBackFlag, graphics::Shader* shader) :
		GUILayer(name, shader),
		m_stepRate(stepRate),
		m_running(running),
		m_reset(reset),
		m_stepFlag(stepFlag),
		m_stepBackFlag(stepBackFlag),
		m_funColors(funColors)
	{
	}

	void ConwayLayer::draw() {
		if (!enabled) return;
		// IMGUI
		// Start the Dear ImGui frame	
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		{
			ImGui::Begin("Conway");
			ImGui::Text("Simulation Speed:");
			ImGui::SameLine();
			ImGui::SliderFloat("", &m_stepRate, .5f, 10.0f);
			ImGui::Checkbox("Run Simulation", &m_running);


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
			ImGui::End();

		}

		Layer::draw();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}

} }
