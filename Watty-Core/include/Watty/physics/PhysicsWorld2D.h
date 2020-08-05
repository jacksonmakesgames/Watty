#pragma once
#include <Box2D/Box2D.h>
#include "DebugPhysics.h"
namespace letc { namespace physics {
	
	class PhysicsWorld2D
	{
	public:
		static b2World* box2DWorld;
		static DebugPhysics* debugDraw;
	private:
	public:
		static void setDebugDraw() {
			box2DWorld->SetDebugDraw(debugDraw);
			debugDraw->SetFlags(b2Draw::e_shapeBit);
		}
		
		static void step(float stepTime) {
			PhysicsWorld2D::box2DWorld->Step(stepTime,8,3); // TODO default, change later/make configurable
		}

	private:
		PhysicsWorld2D(){
			

		}
	};


} }
