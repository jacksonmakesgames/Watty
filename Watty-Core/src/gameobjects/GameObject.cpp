#include <gameobjects/GameObject.h>
namespace letc {

	GameObject::GameObject(glm::vec3 position, glm::vec2 size)
		: transform(new Transform2D(this)) {
		m_renderable = nullptr;
		m_physicsBody2D = nullptr;

		transform->setPosition(position);
		transform->setSize(size);
		transform->setRotation(0.0f);
	}

	GameObject::GameObject(glm::vec2 position, glm::vec2 size)
		: transform(new Transform2D(this)) {
		m_renderable = nullptr;
		m_physicsBody2D = nullptr;
		transform->setPosition(position);
		transform->setSize(size);
		transform->setRotation(0.0f);

	}
	
	GameObject::GameObject(glm::vec3 position, glm::vec2 size, graphics::Renderable2D* renderable)
		: transform(new Transform2D(this)) {
		m_renderable = renderable;
		m_physicsBody2D = nullptr;
		transform->setPosition(position);
		transform->setSize(size);
		transform->setRotation(0.0f);

	}
	GameObject::GameObject(glm::vec2 position, glm::vec2 size, graphics::Renderable2D* renderable)
		: transform(new Transform2D(this, position, size, 0.0f)) {
		m_renderable = renderable;
		m_physicsBody2D = nullptr;
	/*	transform->setPosition(position);
		transform->setSize(size);
		transform->setRotation(0.0f);*/
	}

	GameObject::GameObject(glm::vec3 position, graphics::Renderable2D* renderable)
		: transform(new Transform2D(this)) {
		m_renderable = renderable;
		m_physicsBody2D = nullptr;
		transform->setPosition(position);
		transform->setSize(glm::vec2(1));
		transform->setRotation(0.0f);

	}

	GameObject::GameObject():
		transform(new Transform2D(this)) {
		m_renderable = nullptr;
		m_physicsBody2D = nullptr;
		transform->setPosition(glm::vec2(0.0f));
		transform->setPosition(glm::vec2(1));
		transform->setRotation(0.0f);
	}

	void GameObject::addComponent(graphics::Renderable2D* renderable){
		m_renderable = renderable;

	}

	void GameObject::addAnimator(){
		using namespace graphics;
		if (m_renderable == nullptr) {
			std::cout << "Cannot add animator to GameObject without Renderable";
			return;
		}
		m_animator = new Animator2D(m_renderable);
	}

	void GameObject::addComponent(physics::PhysicsBody2D* physicsBody2D){
		m_physicsBody2D = physicsBody2D;
	}
	/*void GameObject::addChild(GameObject* object){
		object->position = m_position + object->position;
		object->m_parent
		= object->position - m_position;
		m_children.push_back(object);
	}*/

	/*void GameObject::removeChild(GameObject* object){
		for (size_t i = 0; i < m_children.size(); i++)
		{
			if (object == m_children[i])
				m_children.erase(m_children.begin() +i);
		}
	}*/

	void GameObject::disable(){
		if (m_physicsBody2D != nullptr) 
			m_physicsBody2D->disable();
		for (size_t i = 0; i < transform->children.size(); i++)
			transform->children[i]->gameObject->disable();
	}

	void GameObject::enable(){
		if (m_physicsBody2D != nullptr) 
			m_physicsBody2D->enable();

		for (size_t i = 0; i < transform->children.size(); i++)
			transform->children[i]->gameObject->enable();
	}

	/*void GameObject::translate(glm::vec2 translation){

		m_position.x += translation.x;
		m_position.y += translation.y;

		for (size_t i = 0; i < m_children.size(); i++)
			m_children[i]->translate(translation);
	}*/

	//void GameObject::rotate(float angleInRadians){
	//	m_angle = angleInRadians;
	//	glm::vec3 origin = glm::vec3(m_position.x + m_size.x/2.0f, m_position.y + m_size.y/2.0f, m_position.z);

	//	//if (m_renderable) m_renderable->setTransformationMatrix(glm::mat4::rotationAroundPoint(origin, angleInRadians* RADTODEG, glm::vec3(0, 0, 1)));
	//	//m_rotationMatrix =math::Matrix4::rotationAroundPoint(origin, angleInRadians * RADTODEG, glm::vec3(0, 0, 1));

	//	//for (size_t i = 0; i < m_children.size(); i++)
	//	//	m_children[i]->rotate(angleInRadians);

	//	//TODO: QUATERNIONS

	//	glm::mat4 rot = glm::rotate(glm::mat4(1), angleInRadians, glm::vec3(0, 0, -1));
	//	rot = glm::translate(glm::mat4(1), origin) * rot * glm::translate(glm::mat4(1),-origin);
	//	m_rotationMatrix = rot;
	//}

	void GameObject::submit(graphics::Renderer2D* renderer) const {
		m_tag;
	
		//if (transform->children.size()>0) {
		//	//has children, don't pass scale
		//	renderer->push(transform->getMatrixNoScale());
		//}
		//else 
		//glm::mat4 matToPush = transform->parent == nullptr ? transform->getMatrix() : transform->getMatrix()*transform->parent->getMatrixNoScale();

		renderer->push(transform->getMatrix());
			
		if (m_animator != nullptr)
			m_animator->update();
		if (m_renderable != nullptr) {
				m_renderable->submit(renderer);
		}
		for (size_t i = 0; i < transform->children.size(); i++)
			transform->children[i]->gameObject->submit(renderer);

		renderer->pop();
	
	}


	void GameObject::update(){
		

		if (m_physicsBody2D!=nullptr) {
			glm::vec2 pos = m_physicsBody2D->getBodyPosition();
			// todo we can make this one function call:
			transform->setPosition(pos);
			transform->setRotation(m_physicsBody2D->getBody()->GetAngle());
			//transform->setRotation(-m_physicsBody2D->getBody()->GetAngle());
		}

		
		/*if (m_renderable!=nullptr) {
			m_renderable->position = m_position;
			m_renderable->size = m_size;
		}*/

		for (size_t i = 0; i < transform->children.size(); i++) {
			//glm::vec3 offset = m_position - m_children[i]->position;
			//m_children[i]->position = m_position + offset;
			transform->children[i]->gameObject->update(transform->getPosition());
		}

	}

	void GameObject::update(glm::vec2 parentPosition)
	{
		if (m_physicsBody2D != nullptr) {
			glm::vec2 pos = m_physicsBody2D->getBodyPosition();
			transform->setPosition(pos);
			transform->rotate(-m_physicsBody2D->getBody()->GetAngle());
		}
		else {
			/*transform->setPosition(
				parentPosition
				+ transform->getParentOffset());*/
		}

		/*if (m_renderable != nullptr) {
			m_renderable->position = m_position;
			m_renderable->size = m_size;
		}*/

		for (size_t i = 0; i < transform->children.size(); i++) {
			transform->children[i]->gameObject->update(transform->getPosition());
		}
	}

	GameObject::~GameObject(){
		delete m_renderable;
		delete m_physicsBody2D;
		delete transform;
		/*for (size_t i = 0; i < m_children.size(); i++)
		{
			delete m_children[i];
		}*/

	}
}
