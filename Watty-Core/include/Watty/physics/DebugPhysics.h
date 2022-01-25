#pragma once
#include <box2d/box2d.h>
//#include <box2d/Common/b2Draw.h>

#include <box2d/b2_draw.h>

#include <glm.hpp>
#include "../graphics/DebugRenderer.h"


#ifdef WATTY_EMSCRIPTEN
#include <emscripten.h>
//#include <GLFW/glfw3.h>
#include <GLES3/gl32.h>
#endif
#include <math/math.h> //DEGREETORAD


namespace watty { namespace physics { 

	class DebugPhysics : public b2Draw
	{

	private:
	private:
		static graphics::DebugRenderer* renderer;
		static graphics::Shader* m_shader;
		static const glm::vec3* m_sceneCameraPosition;
		static const glm::vec2* m_sceneCameraScale;
		glm::vec3 m_positionLastFrame = glm::vec3();
	public:

		static inline graphics::DebugRenderer* getRenderer() { return renderer; }

		static DebugPhysics* instance;
		static void init(const glm::vec3* sceneCameraPosition, const glm::vec2* sceneCameraScale) {
			m_sceneCameraPosition = sceneCameraPosition;
			m_sceneCameraScale = sceneCameraScale;
			DebugPhysics::m_shader = new graphics::Shader();
			DebugPhysics::renderer = new graphics::DebugRenderer();
		}

		/// Draw a closed polygon provided in CCW order.
		void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {}

		/// Draw a solid closed polygon provided in CCW order.
		void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
			#ifdef WATTY_OPENGL
			m_shader->enable();
			renderer->begin();


			std::vector<glm::vec3> vecVertices = std::vector<glm::vec3>(vertexCount);
			for (size_t i = 0; i < vertexCount; i++){
				vecVertices[i].x = vertices[i].x;
				vecVertices[i].y = vertices[i].y;

			}

			int	r = color.r * 255.0f / 2.0f;
			int	g = color.g * 255.0f;
			int	b = color.b * 255.0f / 2.0f;
			int	a = color.a * 255.0f / 2.0f;
			unsigned int col = a << 24 | b << 16 | g << 8 | r;

			renderer->submit(vecVertices, vertexCount, col);
			renderer->end();
			glLineWidth(2.5f);
			renderer->flush(GL_LINE_LOOP, (int)vertexCount * 1.5);
			glLineWidth(1.0f);
			renderer->flush(GL_TRIANGLES, (int)vertexCount * 1.5);
			m_shader->disable();
#endif
		}

		/// Draw a circle.
		virtual void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) {
			

		
		}

		/// Draw a solid circle.
		virtual void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) {
#ifdef WATTY_OPENGL
			
			const int resolution = 60;
			m_shader->enable();
			renderer->begin();

			std::vector<glm::vec3> vecVertices = std::vector<glm::vec3>(resolution);

			float heading = 0.0f;
			int i = 0;

			for (int a = 0; a < 360; a += 360 / (resolution))
			{
				heading = a * DEGTORAD;
				vecVertices[i].x = center.x + cos(heading) * radius;
				vecVertices[i].y = center.y + sin(heading) * radius;
				vecVertices[i].z = 0.0f;
				i++;
			}

			int	r = color.r * 255.0f / 2.0f;
			int	g = color.g * 255.0f;
			int	b = color.b * 255.0f / 2.0f;
			int	a = color.a * 255.0f / 2.0f;
			unsigned int col = a << 24 | b << 16 | g << 8 | r;

			renderer->submit(vecVertices, resolution, col);
			renderer->end();
			glLineWidth(2.5f);
			renderer->flush(GL_LINE_LOOP, (int)resolution * 1.5);
#ifndef WATTY_EMSCRIPTEN

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif // WATTY_EMSCRIPTEN

			renderer->flush(GL_TRIANGLE_FAN, (int)resolution * 1.5);
			glLineWidth(1.0f);

			m_shader->disable();
#endif
		}

		/// Draw a line segment.
		virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
#ifdef WATTY_OPENGL
			m_shader->enable();
			renderer->begin();

			std::vector<glm::vec3> vecVertices = std::vector<glm::vec3>(2);
			vecVertices[0].x = p1.x;
			vecVertices[0].y = p1.y;
			vecVertices[1].x = p2.x;
			vecVertices[1].y = p2.y;


			int	r = color.r * 255.0f / 2.0f;
			int	g = color.g * 255.0f;
			int	b = color.b * 255.0f / 2.0f;
			int	a = color.a * 255.0f / 2.0f;
			unsigned int col = a << 24 | b << 16 | g << 8 | r;

			renderer->submit(vecVertices, 2, col);
			renderer->end();
			glLineWidth(2.5f);
			renderer->flush(GL_LINE_LOOP, (int)2);
			glLineWidth(1.0f);
			renderer->flush(GL_TRIANGLES, (int)2);

			m_shader->disable();

			/*


			GLfloat glverts[4];

			glVertexPointer(2, GL_FLOAT, 0, glverts); //tell OpenGL where to find vertices
			glEnableClientState(GL_VERTEX_ARRAY); //use vertices in subsequent calls to glDrawArrays
			glverts[0] = p1.x;
			glverts[1] = p1.y,
			glverts[2] = p2.x,
			glverts[3] = p2.y,
			//draw lines
			glLineWidth(4); //fat lines
			glVertexAttrib4f(3, color.r, color.g, color.b, color.a);
			glDrawArrays(GL_LINES, 0, 2);
			glDisableClientState(GL_VERTEX_ARRAY);
			glVertexAttrib4f(3, 1.0f, 1.0f, 1.0f, 1.0f);
			glLineWidth(1); //regular lines
			*/
#endif
		
		}

		/// Draw a transform. Choose your own length scale.
		/// @param xf a transform.
		virtual void DrawTransform(const b2Transform& xf) {}

		/// Draw a point.
		virtual void DrawPoint(const b2Vec2& p, float size, const b2Color& color) {}

		DebugPhysics() {
			
		}
		~DebugPhysics() {
			delete DebugPhysics::renderer;
		}

		static void setProjection(glm::mat4 projection) {
			m_shader->enable();
			m_shader->setUniformMat4("pr_matrix", projection);
			m_shader->disable();
		}
	};


} }
