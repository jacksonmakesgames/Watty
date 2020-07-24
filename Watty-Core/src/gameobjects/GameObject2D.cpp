#include <gameobjects/GameObject2D.h>
namespace letc {
	GameObject2D::GameObject2D(const char* objectName, glm::vec3 position, glm::vec2 size)
		:	transform(new Transform2D(this)),
			name(objectName){
		mProperties.renderable = nullptr;
		mProperties.physicsBody2D = nullptr;

		transform->setPosition(position);
		transform->setSize(size);
		transform->setRotation(0.0f);
	}
	GameObject2D::GameObject2D(glm::vec3 position, glm::vec2 size)
		: transform(new Transform2D(this)), name("GameObject2D") {
		mProperties.renderable = nullptr;
		mProperties.physicsBody2D = nullptr;

		transform->setPosition(position);
		transform->setSize(size);
		transform->setRotation(0.0f);
	}

	GameObject2D::GameObject2D(glm::vec2 position, glm::vec2 size)
		: transform(new Transform2D(this)), name("GameObject2D") {
		mProperties.renderable = nullptr;
		mProperties.physicsBody2D = nullptr;
		transform->setPosition(position);
		transform->setSize(size);
		transform->setRotation(0.0f);

	}

	GameObject2D::GameObject2D(const char* name, glm::vec2 position, glm::vec2 size, graphics::Renderable2D* renderable)
		: transform(new Transform2D(this)), name(name) {
		mProperties.renderable = renderable;
		mProperties.physicsBody2D = nullptr;
		transform->setPosition(position);
		transform->setSize(size);
		transform->setRotation(0.0f);
	}
	
	GameObject2D::GameObject2D(glm::vec3 position, glm::vec2 size, graphics::Renderable2D* renderable)
		: transform(new Transform2D(this)), name("GameObject2D") {
		mProperties.renderable = renderable;
		mProperties.physicsBody2D = nullptr;
		transform->setPosition(position);
		transform->setSize(size);
		transform->setRotation(0.0f);

	}
	GameObject2D::GameObject2D(glm::vec2 position, glm::vec2 size, graphics::Renderable2D* renderable)
		: transform(new Transform2D(this, position, size, 0.0f)), name("GameObject2D") {
		mProperties.renderable = renderable;
		mProperties.physicsBody2D = nullptr;
	/*	transform->setPosition(position);
		transform->setSize(size);
		transform->setRotation(0.0f);*/
	}

	GameObject2D::GameObject2D(glm::vec3 position, graphics::Renderable2D* renderable)
		: transform(new Transform2D(this)), name("GameObject2D") {
		mProperties.renderable = renderable;
		mProperties.physicsBody2D = nullptr;
		transform->setPosition(position);
		transform->setSize(glm::vec2(1));
		transform->setRotation(0.0f);

	}

	GameObject2D::GameObject2D():
		transform(new Transform2D(this)), name("GameObject2D") {
		mProperties.renderable = nullptr;
		mProperties.physicsBody2D = nullptr;
		transform->setPosition(glm::vec2(0.0f));
		transform->setPosition(glm::vec2(1));
		transform->setRotation(0.0f);
	}

	void GameObject2D::addComponent(graphics::Renderable2D* renderable){
		mProperties.renderable = renderable;

	}

	void GameObject2D::addAnimator(){
		using namespace graphics;
		if (mProperties.renderable == nullptr) {
			std::cout << "Cannot add animator to GameObject2D without Renderable";
			return;
		}
		mProperties.animator = new Animator2D((graphics::Renderable2D*)mProperties.renderable);
	}

	void GameObject2D::addComponent(physics::PhysicsBody2D* physicsBody2D){
		mProperties.physicsBody2D = physicsBody2D;
	}
	

	/*void GameObject2D::submit(graphics::Renderer2D* renderer) const {
		if (!enabled_) return;

		renderer->push(transform->getMatrix());
			
		if (mProperties.animator != nullptr)
			mProperties.animator->update();
		if (mProperties.renderable != nullptr) {
				mProperties.renderable->submit(renderer);
		}
		for (size_t i = 0; i < transform->children.size(); i++)
			transform->children[i]->GameObject2D->submit(renderer);

		renderer->pop();
	
	}*/


	void GameObject2D::update(){

		if (!mProperties.enabled) return;

		if (mProperties.physicsBody2D!=nullptr) {
			glm::vec2 pos = mProperties.physicsBody2D->getBodyPosition();
			// todo we can make this one function call:
			transform->setPosition(pos - mProperties.physicsBody2D->getOffset());
			transform->setRotation(mProperties.physicsBody2D->getBody()->GetAngle());
			//transform->setRotation(-mProperties.physicsBody2D->getBody()->GetAngle());
		}

		for (size_t i = 0; i < transform->getChildren().size(); i++) {
			GameObject2D* go2D = (GameObject2D*)(transform->getChild(i)->gameObject);
			go2D->update(transform->getPosition());
			//TODO no
		}

	}

	void GameObject2D::update(glm::vec2 parentPosition)
	{
		if (mProperties.physicsBody2D != nullptr) {
			glm::vec2 pos = mProperties.physicsBody2D->getBodyPosition();
			transform->setPosition(pos);
			transform->rotate(-mProperties.physicsBody2D->getBody()->GetAngle());
		}

		for (size_t i = 0; i < transform->getChildren().size(); i++) {
			GameObject2D* go2D = (GameObject2D*)(transform->getChild(i)->gameObject);
			go2D->update(transform->getPosition());
			//TODO no
		}
	}

	GameObject2D::~GameObject2D(){
		delete mProperties.renderable;
		delete mProperties.physicsBody2D;
		delete transform;

	}
}
