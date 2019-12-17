#include "ConwayLayer.h"
namespace letc { namespace graphics {
	ConwayLayer::ConwayLayer(std::string name, float& stepRate, bool& clear, bool& running, bool& funColors, graphics::Shader* shader) :
		GUILayer(name, shader),
		m_stepRate(stepRate),
		m_running(running),
		m_reset(clear),
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
			ImGui::Checkbox("Running", &m_running);

			ImGui::Checkbox("Fun Colors!", &m_funColors);
			if (ImGui::Button("Clear")) {
				m_reset = true;
			};
		

			ImGui::End();
		}

		Layer::draw();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}

} }
