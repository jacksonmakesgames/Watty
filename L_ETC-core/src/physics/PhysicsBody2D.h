#pragma once
#include "../../ext/Box2D/Box2D.h"

#include "PhysicsConstants.h"
#include "../physics/PhysicsWorld2D.h"

#include "../math/math.h"
namespace letc { namespace physics {

	class PhysicsBody2D {
	public:

	private:
		float m_bounciness;
		float m_friction;
		b2Vec2 m_worldPosition;
		b2Vec2 m_size;
		b2BodyDef m_bodyDef;
		b2Body* m_body;
		b2BodyType m_bodyType;

		b2PolygonShape m_polygonShape;

		b2FixtureDef m_fixtureDef;

	public:
		PhysicsBody2D(float screenX, float screenY, float width, float height, b2BodyType type, float bounciness = .5f, float friction = .3f);
		void addForce(math::Vector2 direction, float amount);
		
		void zeroVelocity();

		inline b2Body* getBody() { return m_body; }
		inline void disable() { m_body->SetActive(false); };
		inline void enable() { m_body->SetActive(true); };

		math::Vector2 getBodyPositionPixels();

		~PhysicsBody2D();
	private:
		void init();

	};

} }