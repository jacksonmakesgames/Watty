#pragma once
#include "../Camera.h"
#include "../shader.h"
#include"../DebugRenderer.h"
#include "../window.h"
namespace letc { namespace graphics {

	class DebugPhysicsLayer : public Layer {
	private:
		Camera& mCamera;
		glm::vec3 posLastFrame;
		Window& mWindow;
		DebugRenderer* m_debugRenderer;
		glm::vec2 m_pixelToMeterRatio = { 80.0f, 80.0f }; // TODO: we should store this somewhere else

	public:
		DebugPhysicsLayer(Camera& camera, Window& window);
		void draw() override;



	};


} }