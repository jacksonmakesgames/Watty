#pragma once
#include "../../ext/Box2D/Box2D.h"
#include "../../ext/Box2D/Common/b2Draw.h"
//#include <GL/glew.h>
#include <glad/glad.h>

#include "../graphics/shader.h"
#include "../math/math.h"
#include "../graphics/buffers/vertexarray.h"
#include "../graphics/buffers/buffer.h"
namespace letc { namespace physics {

	class DebugPhysics : public b2Draw
	{
	private:
	public:

		static DebugPhysics* instance;
	
		static void init() {

		}

		/// Draw a closed polygon provided in CCW order.
		void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {}

		/// Draw a solid closed polygon provided in CCW order.
		void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {

			//set up vertex array
			GLfloat glverts[16]; //allow for polygons up to 8 vertices
			
			glVertexPointer(2, GL_FLOAT, 0, glverts); //tell OpenGL where to find vertices
			glEnableClientState(GL_VERTEX_ARRAY); //use vertices in subsequent calls to glDrawArrays

			//fill in vertex positions as directed by Box2D
			for (int i = 0; i < vertexCount; i++) {
				glverts[i * 2] = vertices[i].x;
				glverts[i * 2 + 1] = vertices[i].y;
			}

			//draw solid area
			glVertexAttrib4f(3, 0.0f, .5f, 0.0f, .2f);
			glVertexAttrib4f(3, color.r/1.2f, color.g, color.b/1.2f, .3f);
			glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);

			//draw lines
			glLineWidth(2); //fat lines
			glVertexAttrib4f(3, color.r / 2, color.g*2.0f, color.b / 1.5f, .8f);
			glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
			glDisableClientState(GL_VERTEX_ARRAY);
			glVertexAttrib4f(3, 1.0f,1.0f,1.0f,1.0f);
			glLineWidth(1); //regular lines



		}

		/// Draw a circle.
		virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {
			

		
		}

		/// Draw a solid circle.
		virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {
			//set up vertex array
			const int resolution = 20;
			//call normal render at different position/rotation
			GLfloat glverts[2 * resolution];

			glVertexPointer(2, GL_FLOAT, 0, glverts); //tell OpenGL where to find vertices
			glEnableClientState(GL_VERTEX_ARRAY); //use vertices in subsequent calls to glDrawArrays

			int i = 0;
			// Create the circle in the coordinates origin
			float heading = 0.0f;
			for (int a = 0; a < 360; a += 360 / resolution)
			{
				heading = a * DEGTORAD;
				glverts[i * 2] = center.x + cos(heading) * radius;
				glverts[i * 2 + 1] = center.y + sin(heading) * radius;
				i++;
			}
			glVertexAttrib4f(3, color.r / 5.0f, color.g, color.b / 1.2f, .3f);

			glDrawArrays(GL_TRIANGLE_FAN, 0, resolution);

			//draw lines
			glLineWidth(2); //fat lines
			glVertexAttrib4f(3, color.r / 5.0f, color.g * 2.0f, color.b / 1.5f, .8f);
			glDrawArrays(GL_LINE_LOOP, 0, resolution);
			glDisableClientState(GL_VERTEX_ARRAY);
			glVertexAttrib4f(3, 1.0f, 1.0f, 1.0f, 1.0f);
			glLineWidth(1); //regular lines
		
		}

		/// Draw a line segment.
		virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
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
		
		
		}

		/// Draw a transform. Choose your own length scale.
		/// @param xf a transform.
		virtual void DrawTransform(const b2Transform& xf) {}

		/// Draw a point.
		virtual void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) {}

		DebugPhysics() {
			
		}
		~DebugPhysics() {
		}
	};



} }