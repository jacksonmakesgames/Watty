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
	void GameObject::submit(graphics::Renderer2D* renderer) const
	{
		if (m_renderable)
			m_renderable->submit(renderer);
	}

	void GameObject::update(){
		if (m_physicsBody2D!=nullptr) {
			math::Vector2 pos = m_physicsBody2D->getBodyPositionPixels();
			m_position.x = pos.x;
			m_position.y = pos.y;
			// TODO, HANDLE ROTATION!
			m_physicsBody2D->getBody()->SetTransform(m_physicsBody2D->getBody()->GetPosition(), 0.0f);
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
