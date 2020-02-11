#include <graphics/layers/GridLayer.h>
namespace letc { namespace graphics {
	GridLayer::GridLayer(graphics::Shader* shader, Camera& camera, int resolution, Window& window) :
			Layer("Grid Layer",new DebugRenderer(), shader),
			mCamera(camera),
			m_resolution(resolution),
			m_debugRenderer(new DebugRenderer()),
			mWindow(window)

	{
		m_pixelToMeterRatio = glm::vec2(mWindow.getWidth(),mWindow.getHeight()) / camera.getSize();

		m_vertexCount =		4 * (2 * mWindow.getWidth() / (int)m_pixelToMeterRatio.x + 8); // 4 per step in x direction
		m_vertexCount +=	4 * (2 * mWindow.getHeight() / (int)m_pixelToMeterRatio.y + 8); // 4 per step in y direction

		scale = glm::vec2((2 * mWindow.getWidth() / m_pixelToMeterRatio.x)/ mWindow.getWidth(), (2 * mWindow.getHeight() / m_pixelToMeterRatio.y )/mWindow.getHeight());

		xStep = mWindow.getWidth()/resolution;
		yStep = mWindow.getHeight()/resolution;
	}

} }
