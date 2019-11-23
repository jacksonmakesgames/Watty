#include "group.h"

namespace letc {
	Group::Group(const math::Matrix4& transform) :m_transformationMatrix(transform){}

	Group::~Group() {
		for (size_t i = 0; i < m_childrenGameObjects.size(); i++)
		{
			delete m_childrenGameObjects[i];
		}
	}
	
	void Group::add(GameObject* gameOject){
		m_childrenGameObjects.push_back(gameOject);
	}

	void Group::submit(graphics::Renderer2D* renderer) const{
		renderer->push(m_transformationMatrix);
		for (const GameObject* gameObject : m_childrenGameObjects){
			gameObject->submit(renderer);
		}
		renderer->pop();
	}

	void Group::update()
	{
		for (GameObject* go : m_childrenGameObjects)
		{
			go->update();
		}
	}

	
}