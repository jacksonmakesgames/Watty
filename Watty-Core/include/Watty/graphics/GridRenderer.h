#pragma once
#pragma once
#include "renderer2d.h"
#include <ext/glm/include/glm.hpp>
namespace watty {
	namespace graphics {
		class GridRenderer : public Renderer2D {
		private:
			float m_left;
			float m_right;
			float m_bottom;
			float m_top;
			float m_near;
			float m_far;

			Shader* m_shader;
			
		public:
			// TODO this should use projection matrices
			GridRenderer(float left, float right, float bottom, float top, float near, float far) :m_left(left),m_right(right),m_bottom(bottom),m_top(top),m_near(near),m_far(far) {
				m_shader = new Shader("J:/OneDrive/Projects/Game_Development/L_ETC/Demos/res/shaders/grid.vert","J:/OneDrive/Projects/Game_Development/L_ETC/Demos/res/shaders/grid.frag");
			}
			void submit(const Renderable2D* renderable) override {};
			void begin() override {};
			void end() override {};
			void flush() override {

				m_shader->enable();
				glRectf(m_left, m_bottom, m_right, m_top);
				m_shader->disable();

			};
			~GridRenderer();

		};


	}
}