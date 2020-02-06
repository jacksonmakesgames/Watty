#include <graphics/layers/GridLayer.h>
namespace letc { namespace graphics {
	GridLayer::GridLayer(graphics::Shader* shader, glm::vec3& cameraPosition, int resolution, glm::vec2 screenSize) :
			Layer("Grid Layer",new DebugRenderer(), shader),
			m_cameraPosition(cameraPosition),
			m_resolution(resolution),
			m_debugRenderer(new DebugRenderer()),
			m_screenSize(screenSize)

	{
		m_vertexCount =		4 * (2 * m_screenSize.x / m_pixelToMeterRatio + 8); // 4 per step in x direction
		m_vertexCount +=	4 * (2 * m_screenSize.y / m_pixelToMeterRatio + 8); // 4 per step in y direction

		scale = glm::vec2((2 * m_screenSize.x / m_pixelToMeterRatio)/screenSize.x, (2 * m_screenSize.y / m_pixelToMeterRatio )/screenSize.y);

		xStep = m_resolution / m_screenSize.x;
		yStep = m_resolution / m_screenSize.y;
	}

} }
