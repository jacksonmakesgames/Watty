#pragma once
#include "../../ext/Box2D/Box2D.h"
#include <iostream>
namespace watty { namespace physics {
	class RaycastCallback : public b2RayCastCallback
	{
	public:
		RaycastCallback() {}


		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override{
			std::cout << "hit" << std::endl;
			return fraction;
		}


	private:

	};

} }