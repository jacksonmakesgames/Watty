#pragma once
#include "../shader.h"
#include"../DebugRenderer.h"
#include "../Camera.h"
#include "../window.h"
namespace watty { namespace graphics {

	class GridLayer : public Layer {
	private:
		Camera& mCamera;
		Window& mWindow;
		DebugRenderer* m_debugRenderer;
		glm::vec2 m_pixelToMeterRatio = { 80.0f, 80.0f }; // TODO: we should store this somewhere else
		int m_vertexCount;

	public:
		GridLayer(Camera& camera, Window& window);

		void draw() override;



	};


} }