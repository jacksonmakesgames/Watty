#pragma once
#include <box2d/box2d.h>
#include "PhysicsConstants.h"
#include "../physics/PhysicsWorld2D.h"
#include <glm.hpp>

namespace letc { 
	class GameObject;

	namespace physics {
	
	enum class BodyShapes {
		box, circle, polygon, edge, chain
	};

	struct PhysicsBody2DParams {
		PhysicsBody2DParams(BodyShapes shape, glm::vec2 startingPos, glm::vec2 size, b2BodyType type, bool isSensor = false, glm::vec2 offset = {0,0}, float bounciness=.3f, float friction=.3f) 
			:
			bounciness(bounciness),
			friction(friction),
			size(size),
			offset(offset),
			bodyType(type),
			shape(shape),
			isSensor(isSensor)
		{};
		float bounciness = .3f;
		float friction = .3f;
		glm::vec2 size = {1,1};
		b2BodyType bodyType = b2_dynamicBody;
		BodyShapes shape = BodyShapes::box;
		glm::vec2 offset = {};
		bool isSensor = false;

	};

	
	
	class PhysicsBody2D
	{
	public:
		GameObject* gameObject;
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
		PhysicsBody2D(PhysicsBody2DParams params);

		virtual void addForce(glm::vec2 direction, float amount);
		virtual void addImpulse(glm::vec2 direction, float amount);
		virtual void setFixedRotation(bool fixed);
		virtual bool isFixedRotation();
		virtual void zeroVelocity();
		virtual void setLinearVelocity(glm::vec2 newVelocity);

		virtual inline b2Body* getBody() { return m_body; }
		virtual inline void disable() { 
			m_body->SetActive(false);
		};
		virtual inline void enable() { 
			m_body->SetActive(true);
		};

		virtual glm::vec2 getBodyPosition();
		inline virtual glm::vec2 getOffset() { return m_offset; }


		~PhysicsBody2D();


	};

} }
