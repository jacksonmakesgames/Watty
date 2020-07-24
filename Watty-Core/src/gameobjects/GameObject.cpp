#include <gameobjects/GameObject.h>
namespace letc {
	GameObject::GameObject():mProperties() {
		mProperties.transform = transform;
		std::cout << "Error tried to use GameObject base class, use GameObject2D or 3D" << std::endl;
	}

	void GameObject::disable(){
		if (!mProperties.enabled) return;
		mProperties.enabled = false;
		for (size_t i = 0; i < transform->getChildren().size(); i++)
			transform->getChild(i)->gameObject->disable();
	}

	void GameObject::enable(){
		if (mProperties.enabled) return;
		mProperties.enabled = true;
		for (size_t i = 0; i < transform->getChildren().size(); i++)
			transform->getChild(i)->gameObject->enable();
	}


	void GameObject::submit(graphics::Renderer* renderer) const {
		if (!mProperties.enabled) return;

		renderer->push(transform->getMatrix());

		if (mProperties.animator != nullptr)
			mProperties.animator->update();
		if (mProperties.renderable != nullptr) {
				mProperties.renderable->submit(renderer);
		}

		for (size_t i = 0; i < transform->getChildren().size(); i++)
			transform->getChild(i)->gameObject->submit(renderer);

		renderer->pop();

	}

	GameObject::~GameObject(){
		delete transform;
	}
}
