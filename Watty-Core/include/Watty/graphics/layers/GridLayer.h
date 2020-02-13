#pragma once
#include "layer.h";
#include "../shader.h"
#include"../DebugRenderer.h"
#include "../Camera.h"
#include "../window.h"
#include <math.h>       /* fmod */
namespace letc { namespace graphics {

	class GridLayer : public Layer {
	private:
		Camera& mCamera;
		Window& mWindow;
		DebugRenderer* m_debugRenderer;
		glm::vec2 m_pixelToMeterRatio = { 80.0f, 80.0f }; // TODO: we should store this somewhere else
		int m_vertexCount;

	public:
		GridLayer(graphics::Shader* shader,Camera& camera, Window& window);

		void draw() override {
			if (!enabled) return;

			m_shader->enable();
			m_debugRenderer->begin();

			m_pixelToMeterRatio = glm::vec2(mWindow.getWidth(), mWindow.getHeight()) / mCamera.getSize();

			m_debugRenderer->push(glm::scale(glm::mat4(1),glm::vec3(1.0f/m_pixelToMeterRatio.x, 1.0f/m_pixelToMeterRatio.y, 1.0f)));

			int count = 0;

			float xMin = mCamera.position.x -.5f*mCamera.getSize().x;
			float xMax = xMin +  mCamera.getSize().x;
			
			float yMin = mCamera.position.y - .5f * mCamera.getSize().y;
			float yMax = yMin + mCamera.getSize().y;
		
			m_vertexCount = (4 * 2 * (yMax-yMin));
			m_vertexCount += (4 * 2 * (xMax-xMin));
			m_vertexCount *= 2;
			if (m_vertexCount < 0) m_vertexCount = 0;

			std::vector<glm::vec3> vertices = std::vector<glm::vec3>(m_vertexCount);

			for (int y = yMin; y <= yMax; y += 1) {
				if (vertices.size() <= count + 4)break;
				//VERTICAL
				vertices[count + 0] = glm::vec3(xMin*m_pixelToMeterRatio.x,		m_pixelToMeterRatio.y * (float) y,							0);
				vertices[count + 1] = glm::vec3(xMin*m_pixelToMeterRatio.x,		m_pixelToMeterRatio.y * (float) y + m_pixelToMeterRatio.y,	0);
				vertices[count + 2] = glm::vec3(xMax*m_pixelToMeterRatio.x,		m_pixelToMeterRatio.y * (float) y + m_pixelToMeterRatio.y,	0);
				vertices[count + 3] = glm::vec3(xMax*m_pixelToMeterRatio.x,		m_pixelToMeterRatio.y * (float) y,							0);
				count += 4;
				}
			for (int x = xMin; x <= xMax; x += 1) {
				if (vertices.size() <= count + 4)break;
				//HORIZONTAL
				vertices[count + 0] = glm::vec3(m_pixelToMeterRatio.x * (float) x,							yMin * m_pixelToMeterRatio.y, 0);
				vertices[count + 1] = glm::vec3(m_pixelToMeterRatio.x * (float) x,							yMax * m_pixelToMeterRatio.y, 0);
				vertices[count + 2] = glm::vec3(m_pixelToMeterRatio.x * (float) x + m_pixelToMeterRatio.x,	yMax * m_pixelToMeterRatio.y, 0);
				vertices[count + 3] = glm::vec3(m_pixelToMeterRatio.x * (float) x + m_pixelToMeterRatio.x,	yMin * m_pixelToMeterRatio.y, 0);
				count += 4;
			}

			if(vertices.size()>3)
				m_debugRenderer->submit(vertices, vertices.size(), 0x60808080);
			
			m_debugRenderer->end();
			glLineWidth(1.f);
			m_debugRenderer->flush(GL_LINES, vertices.size());
			glLineWidth(1.0f);

			m_debugRenderer->pop();
			m_shader->disable();
		};




	};


} }