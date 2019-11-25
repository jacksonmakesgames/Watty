#include "PhysicsBody2D.h"

namespace letc { namespace physics {
	//TODO use inv_pixels_per_meter
	PhysicsBody2D::PhysicsBody2D(float screenX, float screenY, float width, float height, b2BodyType type, float bounciness, float friction)
		: 
		m_bounciness(bounciness),
		m_friction(friction),
		m_size((width * PhysicsConstants::inv_pixels_per_meter)/2.0f, (height * PhysicsConstants::inv_pixels_per_meter)/2.0f),
		m_worldPosition((screenX+width/2) * PhysicsConstants::inv_pixels_per_meter, (screenY +height/2)* PhysicsConstants::inv_pixels_per_meter),
		m_bodyType(type),
		m_bodyDef(),
		m_polygonShape(),
		m_fixtureDef()
	{
		// define body
		m_bodyDef.type = m_bodyType;
		m_bodyDef.position.Set(m_worldPosition.x, m_worldPosition.y);
		// create body in world
		m_body = PhysicsWorld2D::box2DWorld->CreateBody(&m_bodyDef);
		// create shape
		m_polygonShape.SetAsBox(m_size.x, m_size.y);
		// create fixture
		m_fixtureDef.shape =&m_polygonShape;
		m_fixtureDef.density = 1.0f;
		m_fixtureDef.restitution = m_bounciness;
		m_fixtureDef.friction = m_friction;
		// attach shape to body using fixture
		m_body->CreateFixture(&m_fixtureDef);


	}

	void PhysicsBody2D::addForce(math::Vector2 direction, float amount)
	{
		b2Vec2 force(direction.x * amount, direction.y * amount);
		m_body->ApplyForceToCenter(force, true);
	}
	void PhysicsBody2D::zeroVelocity()
	{
		m_body->SetLinearVelocity(b2Vec2(0,0));
	}

	math::Vector2 PhysicsBody2D::getBodyPositionPixels()
	{
		b2Vec2 pos = m_body->GetPosition();
		// quite unsure
		pos.x -= m_size.x;
		pos.y -= m_size.y;

		pos *= PhysicsConstants::pixels_per_meter;
		return math::Vector2(pos.x, pos.y);
	}

	PhysicsBody2D::~PhysicsBody2D()
	{
	}

	void PhysicsBody2D::init(){
	}

} }
