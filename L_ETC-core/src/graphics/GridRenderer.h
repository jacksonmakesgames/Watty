#pragma once
#pragma once
#include "renderer2d.h"
#include "../math/math.h"
namespace letc {
	namespace graphics {
		class GridRenderer : public Renderer2D {
		private:
			float m_left;
			float m_right;
			float m_bottom;
			float m_top;
			float m_near;
			float m_far;
			
		public:
			GridRenderer(float left, float right, float bottom, float top, float near, float far) :m_left(left),m_right(right),m_bottom(bottom),m_top(top),m_near(near),m_far(far) {
				
			}
			void submit(const Renderable2D* renderable) override {};
			void begin() override {};
			void end() override {};
			void flush() override {



				//glClear(GL_COLOR_BUFFER_BIT);
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glLineWidth(.5); //thin lines

				glVertexAttrib4f(3, .5,.5,.5, .4f); // color

				for (int x = m_left; x < m_right; x++)
				{
					for (int y = m_bottom; y < m_top; y++)
					{
						glBegin(GL_POLYGON);
						glColor4f(0.0, 0.0, 0.3, .5);
						
						glVertex3f(x,		y,		0.0);
						glVertex3f(x + 1,	y,		0.0);
						glVertex3f(x + 1,	y + 1,	0.0);
						glVertex3f(x,		y + 1,	0.0);
						glEnd();
					}
			}
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glVertexAttrib4f(3, 1,1,1,1);
				glLineWidth(1); //regular lines


			};
			~GridRenderer();

		};


	}
}