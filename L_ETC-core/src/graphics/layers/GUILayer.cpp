#include "GUILayer.h"
namespace letc {namespace graphics {
	GUILayer::GUILayer(graphics::Shader* shader, math::Matrix4 prMatrix):Layer(new BatchRenderer2D(), shader, prMatrix){

	}
	
	void GUILayer::draw(){

		// IMGUI
		// Start the Dear ImGui frame	
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		{
			ImGui::Begin("Application Info");                          // Create a window called "Hello, world!" and append into it.
			ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::ColorEdit3("Clear Color", (float*)&m_clearColor);
		}
		glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);

		Layer::draw();

		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}

}}