#include <gameobjects/GameObject.h>
namespace watty {

	GameObject::GameObject(const char* objectName, glm::vec3 position, glm::vec2 size)
		:	transform(new Transform2D(this)),
			name(objectName){
		init();
		m_renderable = nullptr;
		m_physicsBody2D = nullptr;

		transform->setPosition(position);
		transform->setSize(size);
		transform->setRotation(0.0f);
	}
	GameObject::GameObject(glm::vec3 position, glm::vec2 size)
		: transform(new Transform2D(this)), name("GameObject") {
		init();
		m_renderable = nullptr;
		m_physicsBody2D = nullptr;

		transform->setPosition(position);
		transform->setSize(size);
		transform->setRotation(0.0f);
	}

	GameObject::GameObject(glm::vec2 position, glm::vec2 size)
		: transform(new Transform2D(this)), name("GameObject") {
		init();
		m_renderable = nullptr;
		m_physicsBody2D = nullptr;
		transform->setPosition(position);
		transform->setSize(size);
		transform->setRotation(0.0f);

	}

	GameObject::GameObject(const char* name, glm::vec2 position, glm::vec2 size, graphics::Renderable2D* renderable)
		: transform(new Transform2D(this)), name(name) {
		init();
		m_renderable = renderable;
		m_physicsBody2D = nullptr;
		transform->setPosition(position);
		transform->setSize(size);
		transform->setRotation(0.0f);
	}
	
	GameObject::GameObject(glm::vec3 position, glm::vec2 size, graphics::Renderable2D* renderable)
		: transform(new Transform2D(this)), name("GameObject") {
		init();
		m_renderable = renderable;
		m_physicsBody2D = nullptr;
		transform->setPosition(position);
		transform->setSize(size);
		transform->setRotation(0.0f);

	}
	GameObject::GameObject(glm::vec2 position, glm::vec2 size, graphics::Renderable2D* renderable)
		: transform(new Transform2D(this, position, size, 0.0f)), name("GameObject") {
		init();
		m_renderable = renderable;
		m_physicsBody2D = nullptr;

	}
	
	GameObject::GameObject(bool ECS)
		: name("GameObject") {
		init();
		m_renderable = nullptr;
		m_physicsBody2D = nullptr;
	}

	GameObject::GameObject(glm::vec3 position, graphics::Renderable2D* renderable)
		: transform(new Transform2D(this)), name("GameObject") {
		init();
		m_renderable = renderable;
		m_physicsBody2D = nullptr;
		transform->setPosition(position);
		transform->setSize(glm::vec2(1));
		transform->setRotation(0.0f);

	}

	GameObject::GameObject():
		transform(new Transform2D(this)), name("GameObject") {
		init();
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
		m_physicsBody2D->gameObject = this;
		m_physicsBody2D->getBody()->SetUserData(this); // store a reference to PhysicsBody2D 

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
		if (!enabled_) return;
		enabled_ = false;
		if (m_physicsBody2D != nullptr) 
			m_physicsBody2D->disable();
		for (size_t i = 0; i < transform->children.size(); i++)
			transform->children[i]->gameObject->disable();
	}

	void GameObject::enable(){
		if (enabled_) return;
		enabled_ = true;
		if (m_physicsBody2D != nullptr) 
			m_physicsBody2D->enable();

		for (size_t i = 0; i < transform->children.size(); i++)
			transform->children[i]->gameObject->enable();
	}


	void GameObject::submit(graphics::Renderer2D* renderer) const {
		if (!enabled_) return;
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

		if (!enabled_) return;

		if (m_physicsBody2D!=nullptr) {
			glm::vec2 pos = m_physicsBody2D->getBodyPosition();
			
			if (transform->wantsPhysicsMove) {
				m_physicsBody2D->getBody()->SetTransform(b2Vec2(transform->physicsMoveTo.x, transform->physicsMoveTo.y), m_physicsBody2D->getBody()->GetAngle());
				transform->wantsPhysicsMove = false;
			}else
				transform->setPosition(pos - m_physicsBody2D->getOffset(), false);
			
			transform->setRotation(m_physicsBody2D->getBody()->GetAngle());
		}

		//Update renderable (not rendering, but for things like particles)
		if (m_renderable)
			m_renderable->update();


		// Update children
		for (size_t i = 0; i < transform->children.size(); i++) {
			transform->children[i]->gameObject->update();
		}


	}



	GameObject::~GameObject(){
		if(m_renderable)
			delete m_renderable;
		if(m_physicsBody2D)
			delete m_physicsBody2D;
		if(transform)
			delete transform;
		/*for (size_t i = 0; i < m_children.size(); i++)
		{
			delete m_children[i];
		}*/

	}

	void Physics2DContactListener::BeginContact(b2Contact* contact)
	{
		// Fixture A
		void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		if (contact->GetFixtureA()->IsSensor()) {
			if (bodyUserData)
				static_cast<GameObject*>(bodyUserData)->onSensorEnter(contact);
		}
		else {
			if (bodyUserData)
				static_cast<GameObject*>(bodyUserData)->onCollisionEnter(contact);
		}

		// Fixture B
		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
		if (contact->GetFixtureB()->IsSensor()) {
			if (bodyUserData)
				static_cast<GameObject*>(bodyUserData)->onSensorEnter(contact);
		}
		else {
			if (bodyUserData)
				static_cast<GameObject*>(bodyUserData)->onCollisionEnter(contact);
		}
	}

	void Physics2DContactListener::EndContact(b2Contact* contact)
	{
		// Fixture A
		void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		if (contact->GetFixtureA()->IsSensor()) {
			if (bodyUserData)
				static_cast<GameObject*>(bodyUserData)->onSensorExit(contact);
		}
		else {
			if (bodyUserData)
				static_cast<GameObject*>(bodyUserData)->onCollisionExit(contact);
		}

		// Fixture B
		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
		if (contact->GetFixtureB()->IsSensor()) {
			if (bodyUserData)
				static_cast<GameObject*>(bodyUserData)->onSensorExit(contact);
		}
		else {
			if (bodyUserData)
				static_cast<GameObject*>(bodyUserData)->onCollisionEnter(contact);
		}
	}
}
