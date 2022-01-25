#include <graphics/layers/GridLayer.h>
namespace watty { namespace graphics {
	GridLayer::GridLayer(Camera& camera, Window& window) :
			Layer("Grid Layer",new DebugRenderer(), new Shader()),
			mCamera(camera),
			m_debugRenderer(new DebugRenderer()),
			mWindow(window)

	{
		m_pixelToMeterRatio = glm::vec2(mWindow.getWidth(),mWindow.getHeight()) / camera.getSize();

		m_vertexCount =		4 * (2 * mWindow.getWidth() / (int)m_pixelToMeterRatio.x + 8); // 4 per step in x direction
		m_vertexCount +=	4 * (2 * mWindow.getHeight() / (int)m_pixelToMeterRatio.y + 8); // 4 per step in y direction

		//scale = glm::vec2((2 * mWindow.getWidth() / m_pixelToMeterRatio.x)/ mWindow.getWidth(), (2 * mWindow.getHeight() / m_pixelToMeterRatio.y )/mWindow.getHeight());
	}

	void GridLayer::draw(){
		if (!enabled_) return;

		m_shader->enable();
		glm::mat4 p = getProjection();
		m_shader->setUniformMat4("pr_matrix", getProjection());

		m_debugRenderer->begin();
		

		float xMin = mCamera.position.x - .5f * mCamera.getViewportSize().x;
		float xMax = xMin + mCamera.getViewportSize().x;

		float yMin = mCamera.position.y - .5f * mCamera.getViewportSize().y;
		float yMax = yMin + mCamera.getViewportSize().y;

		m_vertexCount = (4 * 2 * (yMax - yMin));
		m_vertexCount += (4 * 2 * (xMax - xMin));
		m_vertexCount *= 2;
		if (m_vertexCount < 0) m_vertexCount = 0;

		std::vector<glm::vec3> vertices = std::vector<glm::vec3>(m_vertexCount);
		
		int count = 0;
		for (int y = yMin; y <= yMax; y += 1) {
			if (vertices.size() <= count + 4)break;
			//VERTICAL
			vertices[count + 0] = glm::vec3(xMin,	(float) y,		0);
			vertices[count + 1] = glm::vec3(xMin,	(float) y + 1,	0);
			vertices[count + 2] = glm::vec3(xMax,	(float) y + 1,	0);
			vertices[count + 3] = glm::vec3(xMax,	(float) y,		0);
			count += 4;
		}
		for (int x = xMin; x <= xMax; x += 1) {
			if (vertices.size() <= count + 4)break;
			//HORIZONTAL
			vertices[count + 0] = glm::vec3((float) x,		yMin,		0);
			vertices[count + 1] = glm::vec3((float) x,		yMax,		0);
			vertices[count + 2] = glm::vec3((float) x +	1,	yMax,		0);
			vertices[count + 3] = glm::vec3((float) x + 1,	yMin,		0);
			count += 4;
		}

		if (vertices.size() > 3)
			m_debugRenderer->submit(vertices, vertices.size(), 0x60808080);

		m_debugRenderer->end();
		glLineWidth(1.f);
		m_debugRenderer->flush(GL_LINES, vertices.size());
		glLineWidth(1.0f);

		m_shader->disable();
	};


} }
