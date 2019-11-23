 #include "GameObject.h"
namespace letc {
	GameObject::GameObject(math::Vector3 position, math::Vector2 size)
		:position(m_position), size(m_size) {
		m_position = position;
		m_size = size;
		m_renderable = nullptr;
		m_boxCollider = nullptr;
	}
	
	GameObject::GameObject(math::Vector3 position, math::Vector2 size, graphics::Renderable2D* renderable)
		:position(m_position), size(m_size){
		m_position = position;
		m_size = size;
		m_boxCollider = nullptr;
		m_renderable = renderable;
	}
	GameObject::GameObject(math::Vector3 position, graphics::Renderable2D* renderable)
		:position(m_position), size(m_size){
		m_position = position;
		m_size = math::Vector2();
		m_boxCollider = nullptr;
		m_renderable = renderable;
	}

	GameObject::GameObject()
		: position(m_position), size(m_size){
		m_renderable = nullptr;
		m_boxCollider = nullptr;

	}

	void GameObject::addComponent(graphics::Renderable2D* renderable){
		m_renderable = renderable;
		
	}
	void GameObject::addComponent(physics::BoxCollider2D* boxCollider)
	{
		m_boxCollider = boxCollider;
	}
	void GameObject::submit(graphics::Renderer2D* renderer) const
	{
		if (m_renderable)
			m_renderable->submit(renderer);
	}

	void GameObject::update(){
		if (m_renderable) {
			m_renderable->position = m_position;
			m_renderable->size = m_size;
		}
	}
	GameObject::~GameObject()
	{
		delete m_renderable;
	}
}
