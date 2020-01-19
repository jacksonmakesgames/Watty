#pragma once
#include <ext/Box2D/Box2D.h>
#include "PhysicsConstants.h"
#include "../physics/PhysicsWorld2D.h"
#include "../math/math.h"
namespace letc { namespace physics {
	
	enum class BodyShapes {
		box, circle
	};

	class PhysicsBody2D
	{
	public:
	private:
		float m_bounciness;
		float m_friction;
		b2Vec2 m_worldPosition;
		b2Vec2 m_size;
		b2BodyDef m_bodyDef;
		b2Body* m_body;
		b2BodyType m_bodyType;
		b2FixtureDef m_fixtureDef;
		b2PolygonShape m_polygonShape;
		b2CircleShape m_circleShape;

	public:
		PhysicsBody2D(BodyShapes shape, float xPos, float yPos, float width, float height, b2BodyType type, float bounciness = .3f, float friction = .3f);

		virtual void addForce(math::Vector2 direction, float amount);
		virtual void addImpulse(math::Vector2 direction, float amount);

		virtual void zeroVelocity();
		virtual void setLinearVelocity(math::Vector2 newVelocity);

		virtual inline b2Body* getBody() { return m_body; }
		virtual inline void disable() { m_body->SetActive(false); };
		virtual inline void enable() { m_body->SetActive(true); };

		virtual math::Vector2 getBodyPosition();


		~PhysicsBody2D();

	private:

	};

	


} }