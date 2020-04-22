#pragma once
#include "layer.h";
#include "../shader.h"
#include"../DebugRenderer.h"
#include "../Camera.h"
#include "../window.h"
#include <math.h>       /* fmod */
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