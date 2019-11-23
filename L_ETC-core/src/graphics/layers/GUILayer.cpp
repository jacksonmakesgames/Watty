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
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}

		Layer::draw();

		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}
}}