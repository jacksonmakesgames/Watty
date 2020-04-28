#pragma once
#include <box2d/box2d.h>
#include "PhysicsConstants.h"
#include "../physics/PhysicsWorld2D.h"
#include <glm.hpp>

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

		glm::vec2 m_offset;

	public:
		PhysicsBody2D(BodyShapes shape, glm::vec2 startingPos, float width, float height, b2BodyType type, glm::vec2 offset = glm::vec2(0,0), float bounciness = .3f, float friction = .3f);

		virtual void addForce(glm::vec2 direction, float amount);
		virtual void addImpulse(glm::vec2 direction, float amount);

		virtual void zeroVelocity();
		virtual void setLinearVelocity(glm::vec2 newVelocity);

		virtual inline b2Body* getBody() { return m_body; }
		virtual inline void disable() { 
#ifndef WATTY_EMSCRIPTEN

			m_body->SetEnabled(false);
#else
			m_body->SetAwake(false);
#endif // !WATTY_EMSCRIPTEN

		};
		virtual inline void enable() { 
#ifndef WATTY_EMSCRIPTEN
			m_body->SetEnabled(true); 

#else
			m_body->SetAwake(true);
#endif
		};

		virtual glm::vec2 getBodyPosition();
		inline virtual glm::vec2 getOffset() { return m_offset; }


		~PhysicsBody2D();


	};

} }
