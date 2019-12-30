#pragma once
#include "layer.h";
#include "../shader.h"
#include"../DebugRenderer.h"
#include <math.h>       /* fmod */
namespace letc { namespace graphics {

	class GridLayer : public Layer {
	private:
		math::Vector3& m_cameraPosition;
		math::Vector2  m_screenSize;
		int m_resolution;
		DebugRenderer* m_debugRenderer;

		float m_pixelToMeterRatio = 80.0f; // TODO: we should store this somewhere else

		int m_vertexCount;
		float max = 10000000.0f;

		math::Vector2 scale;

		int xStep;
		int yStep;

	public:
		GridLayer(graphics::Shader* shader, math::Vector3& cameraPosition, int resolution, math::Vector2 screenSize);

		void draw() override {
			// TODO: OPTIMIZE!
			if (!enabled) return;

			m_shader->enable();
			m_debugRenderer->begin();
			m_debugRenderer->push(math::Matrix4::scale(math::Vector3(scale.x, scale.y, 1.0f)));

			int width  =	m_screenSize.x;
			int height =	m_screenSize.y;

			int count = 0;

			math::Vector3* vertices = new math::Vector3[m_vertexCount];


			int xMin = (80 * (int)(.5f*m_cameraPosition.x) - width);
			int xMax = (80 * (int)(.5f*m_cameraPosition.x) + width);

 			for (int x = xMin; x <= xMax; x+=10){
				if (x%80==0)
				{
				// make quad
				vertices[count + 0]		=   math::Vector3(x,  max, 0);
				vertices[count + 1]		=	math::Vector3(x, -max, 0);

				vertices[count + 2]		=	math::Vector3(x + xStep, -max, 0);
				vertices[count + 3]		=	math::Vector3(x + xStep,  max, 0);
				count += 4;

				}
			} 
			
			int yMin = (80 * (int)(.5f * m_cameraPosition.y) - width);
			int yMax = (80 * (int)(.5f * m_cameraPosition.y) + width);
		
			for (float y =yMin - m_pixelToMeterRatio/2.0f; y <= yMax- m_pixelToMeterRatio/2.0f; y += m_pixelToMeterRatio)
			{
				vertices[count + 0]		=	math::Vector3( max, y, 0);
				vertices[count + 1]		=	math::Vector3(-max, y, 0);

 				vertices[count + 2]		=	math::Vector3(-max, y + yStep, 0);
				vertices[count + 3]		=	math::Vector3( max, y + yStep, 0);

				count += 4;
			} 


			m_debugRenderer->submit(vertices, m_vertexCount, 0x60808080);
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