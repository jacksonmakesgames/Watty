#pragma once
#include "../../ext/Box2D/Box2D.h"
#include "../../ext/Box2D/Common/b2Draw.h"
#include <GL/glew.h>

namespace letc { namespace physics {
	class DebugPhysics : public b2Draw
	{
		public:
			static DebugPhysics* instance;
	
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
				glColor4f(color.r, color.g, color.b, 1);
				glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);

				//draw lines
				glLineWidth(2); //fat lines
				glColor4f(1, 0, 1, 1); //purple
				glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
			
			}

			/// Draw a circle.
			virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {}

			/// Draw a solid circle.
			virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {}

			/// Draw a line segment.
			virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {}

			/// Draw a transform. Choose your own length scale.
			/// @param xf a transform.
			virtual void DrawTransform(const b2Transform& xf) {}

			/// Draw a point.
			virtual void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) {}
		DebugPhysics() {}
		};

	

} }