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
		int m_resolution;
		DebugRenderer* m_debugRenderer;

		glm::vec2 m_pixelToMeterRatio = { 80.0f, 80.0f }; // TODO: we should store this somewhere else

		int m_vertexCount;
		float max = 10000000.0f;

		glm::vec2 scale;

		int xStep;
		int yStep;

	public:
		GridLayer(graphics::Shader* shader,Camera& camera, int resolution, Window& window);

		void draw() override {
			// TODO: OPTIMIZE!
			if (!enabled) return;

			m_shader->enable();
			m_debugRenderer->begin();
			m_pixelToMeterRatio = glm::vec2(mWindow.getWidth(), mWindow.getHeight()) / mCamera.getSize();

			m_debugRenderer->push(glm::scale(glm::mat4(1),glm::vec3(scale.x, scale.y, 1.0f)));

			int width  =	mWindow.getWidth();
			int height =	mWindow.getHeight();

			int count = 0;

			//glm::vec3* vertices = new glm::vec3[m_vertexCount];

		/*	int xMin = (m_pixelToMeterRatio.x * (int)(.5f* mCamera.position.x) - width);
			int xMax = (m_pixelToMeterRatio.x * (int)(.5f* mCamera.position.x) + width);

			int yMin = (m_pixelToMeterRatio.y * (int)(.5f * mCamera.position.y) - height);
			int yMax = (m_pixelToMeterRatio.y * (int)(.5f * mCamera.position.y) + height);*/

			float xMin = (m_pixelToMeterRatio.x * (mCamera.position.x-.5f*mCamera.getSize().x));
			float xMax = xMin + mWindow.getWidth();
			
			float yMin = (m_pixelToMeterRatio.y * (mCamera.position.y - .5f * mCamera.getSize().y));
			float yMax = yMin + mWindow.getHeight();
		
			m_vertexCount = (4 * 2 * (yMax-yMin)/m_pixelToMeterRatio.y);
			m_vertexCount += (4 * 2 * (xMax-xMin)/m_pixelToMeterRatio.x);
			m_vertexCount *= 2;
			if (m_vertexCount < 0) m_vertexCount = 0;
			std::vector<glm::vec3> vertices = std::vector<glm::vec3>(m_vertexCount);

 		//	for (int x = xMin; x <= xMax; x+=10){
			//	if (x % (int)(.5f*m_pixelToMeterRatio.x)==0)
			//	{
			//	// make quad
			//	/*vertices[count + 0]		=   glm::vec3(x,  max, 0);
			//	vertices[count + 1]		=	glm::vec3(x, -max, 0);

			//	vertices[count + 2]		=	glm::vec3(x + xStep, -max, 0);
			//	vertices[count + 3]		=	glm::vec3(x + xStep,  max, 0);*/

			//	}


			//} 

			for (int y = yMin; y <= yMax; y += .5f*m_pixelToMeterRatio.y) {
				//if (y % (int)(.5f * m_pixelToMeterRatio.y) == 0)
				if (vertices.size() <= count + 4)break;
					//VERTICAL
					vertices[count + 0] = glm::vec3(xMin, y, 0);
					vertices[count + 1] = glm::vec3(xMin, y + m_pixelToMeterRatio.y, 0);

					vertices[count + 2] = glm::vec3(xMax, y + m_pixelToMeterRatio.y, 0);
					vertices[count + 3] = glm::vec3(xMax, y, 0);
					count += 4;
				}

			for (int x = xMin; x <= xMax; x += .5f*m_pixelToMeterRatio.x) {
				if (vertices.size() <= count + 8)break;

						//HORIZONTAL
						vertices[count + 4] = glm::vec3(x, yMin, 0);
						vertices[count + 5] = glm::vec3(x, yMax, 0);

						vertices[count + 6] = glm::vec3(x+m_pixelToMeterRatio.x, yMax, 0);
						vertices[count + 7] = glm::vec3(x + m_pixelToMeterRatio.x, yMin, 0);
						count += 4;

			}

			if(vertices.size()>3)
				m_debugRenderer->submit(vertices, count, 0x60808080);
			
			m_debugRenderer->end();
			glLineWidth(1.5f);
			glPointSize(20);
			m_debugRenderer->flush(GL_LINES, (int)m_vertexCount * 1.5);
			glLineWidth(1.0f);

			m_debugRenderer->pop();
			m_shader->disable();
		};




	};


} }