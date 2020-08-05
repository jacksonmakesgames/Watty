#include <physics/PhysicsBody2D.h>
namespace letc { namespace physics {
	PhysicsBody2D::PhysicsBody2D(PhysicsBody2DParams params)
		:
		m_bounciness(params.bounciness),
		m_friction(params.friction),
		m_size((params.size.x* PhysicsConstants::inv_pixels_per_meter) / 2.0f, (params.size.y* PhysicsConstants::inv_pixels_per_meter) / 2.0f),
		m_worldPosition((params.offset.x + params.size.x / 2)* PhysicsConstants::inv_pixels_per_meter, (params.offset.y + params.size.y / 2)* PhysicsConstants::inv_pixels_per_meter),
		m_offset(params.offset),
		m_bodyType(params.bodyType),
		m_bodyDef(),
		m_polygonShape(),
		m_circleShape(),
		m_fixtureDef()
	{
		// define body
		m_bodyDef.type = m_bodyType;
		m_bodyDef.position.Set(m_worldPosition.x, m_worldPosition.y);
		// create body in world
		m_body = PhysicsWorld2D::box2DWorld->CreateBody(&m_bodyDef);
		//define fixture
		m_fixtureDef.isSensor = params.isSensor;
		m_fixtureDef.density = 1.0f;
		m_fixtureDef.restitution = m_bounciness;
		m_fixtureDef.friction = m_friction;
		// create shape
		if (params.shape == BodyShapes::box) {
			m_polygonShape.SetAsBox(m_size.x, m_size.y);
			m_fixtureDef.shape = &m_polygonShape;
			// attach shape to body using fixture
			m_body->CreateFixture(&m_fixtureDef);
		}
		else if (params.shape == BodyShapes::circle) {
			m_circleShape.m_radius = params.size.x/2.0f;
			m_fixtureDef.shape = &m_circleShape;
			// attach shape to body using fixture
			m_body->CreateFixture(&m_fixtureDef);
		}
		else {
			throw std::logic_error("Body type not yet implemented");
		}
	}

	void PhysicsBody2D::addForce(glm::vec2 direction, float amount)
	{
		b2Vec2 force(direction.x * amount, direction.y * amount);
		m_body->ApplyForceToCenter(force, true);
	}

	void PhysicsBody2D::addImpulse(glm::vec2 direction, float amount)
	{
		b2Vec2 impulse(direction.x * amount, direction.y * amount);
		m_body->ApplyLinearImpulse(impulse, m_body->GetWorldCenter(), true);
	}

	void PhysicsBody2D::setFixedRotation(bool fixed)
	{
		m_body->SetFixedRotation(fixed);
	}

	bool PhysicsBody2D::isFixedRotation()
	{
		return m_body->IsFixedRotation();
	}



	void PhysicsBody2D::setLinearVelocity(glm::vec2 newVelocity)
	{
		m_body->SetLinearVelocity(b2Vec2(newVelocity.x, newVelocity.y));

	}

	void PhysicsBody2D::zeroVelocity()
	{
		m_body->SetLinearVelocity(b2Vec2(0, 0));
	}

	glm::vec2 PhysicsBody2D::getBodyPosition()
	{
		b2Vec2 pos = m_body->GetPosition();
		pos *= PhysicsConstants::pixels_per_meter;
		return glm::vec2(pos.x, pos.y);
	}

	PhysicsBody2D::~PhysicsBody2D()
	{
		m_body->GetWorld()->DestroyBody(m_body);
	}

}}