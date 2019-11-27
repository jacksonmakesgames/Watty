 #include "GameObject.h"
namespace letc {
	GameObject::GameObject(math::Vector3 position, math::Vector2 size)
		:position(m_position), size(m_size) {
		m_position = position;
		m_size = size;
		m_renderable = nullptr;
		m_physicsBody2D = nullptr;
	}
	
	GameObject::GameObject(math::Vector3 position, math::Vector2 size, graphics::Renderable2D* renderable)
		:position(m_position), size(m_size){
		m_position = position;
		m_size = size;
		m_physicsBody2D = nullptr;
		m_renderable = renderable;
	}
	GameObject::GameObject(math::Vector3 position, graphics::Renderable2D* renderable)
		:position(m_position), size(m_size){
		m_position = position;
		m_size = math::Vector2();
		m_physicsBody2D = nullptr;
		m_renderable = renderable;
	}

	GameObject::GameObject()
		: position(m_position), size(m_size){
		m_renderable = nullptr;
		m_physicsBody2D = nullptr;

	}

	void GameObject::addComponent(graphics::Renderable2D* renderable){
		m_renderable = renderable;
		
	}
	void GameObject::addComponent(physics::PhysicsBody2D* physicsBody2D)
	{
		m_physicsBody2D = physicsBody2D;
	}
	void GameObject::translate(math::Vector2 translation)
	{
		m_position.x += translation.x;
		m_position.y += translation.y;
	}
	void GameObject::rotate(float angleInRadians)
	{
		math::Vector3 origin = math::Vector3(m_position.x + m_size.x/2.0f, m_position.y + m_size.y/2.0f, m_position.z);

		if (m_renderable) m_renderable->setTransformationMatrix(math::Matrix4::rotationAroundPoint(origin, angleInRadians* RADTODEG, math::Vector3(0, 0, 1)));
	}
	void GameObject::submit(graphics::Renderer2D* renderer) const
	{
		if (m_renderable)
			m_renderable->submit(renderer);
	}

	void GameObject::update(){
		if (m_physicsBody2D!=nullptr) {
			math::Vector2 pos = m_physicsBody2D->getBodyPosition();
			m_position.x = pos.x;
			m_position.y = pos.y;
			// TODO, HANDLE ROTATION!
			rotate(-m_physicsBody2D->getBody()->GetAngle());
			//m_angle = m_physicsBody2D->getBody()->GetAngle();
		}
		
		if (m_renderable) {
			m_renderable->position = m_position;
			m_renderable->size = m_size;
		}
	}
	GameObject::~GameObject()
	{
		delete m_renderable;
		delete m_physicsBody2D;

	}
}
