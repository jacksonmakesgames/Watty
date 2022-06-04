#pragma once
#include <graphics/textures/Animator2D.h>
#include <physics/PhysicsBody2D.h>
#include <gameobjects/Transform2D.h>
#include <utils/Guid.hpp>


namespace watty {
	class GameObject {
	protected:
	public:
		Transform* transform = nullptr;
		const char* name;
		bool _destroyFlag = false;

	private:
		bool enabled_ = true;
		std::string m_uuid;
		std::string m_tag = "";
		//std::vector<GameObject*> m_children;


		//glm::mat4 m_rotationMatrix		= glm::mat4(1.0f);
		//glm::mat4 m_translationMatrix	= glm::mat4(1.0f);



		//Graphics
		graphics::Renderable2D* m_renderable = nullptr;
		graphics::Animator2D* m_animator = nullptr;

		//TODO: add transform struct
		//glm::vec3 m_position = glm::vec3(0.0f);
		//float m_angle = 0.0f;
		//glm::vec2 m_size = glm::vec2(1.0f);

		// Physics
		physics::PhysicsBody2D* m_physicsBody2D;

	public:
		GameObject(const char* name, glm::vec3 position, glm::vec2 size);
		GameObject(glm::vec2 position, glm::vec2 size);
		GameObject(glm::vec3 position, glm::vec2 size);
		GameObject(bool ECS);
		GameObject(glm::vec3 position, glm::vec2 size, graphics::Renderable2D* renderable);
		GameObject(glm::vec2 position, glm::vec2 size, graphics::Renderable2D* renderable);
		GameObject(glm::vec3 position, graphics::Renderable2D* renderable);
		GameObject(glm::vec2 position, graphics::Renderable2D* renderable);
		GameObject(const char* name, glm::vec2 position, glm::vec2 size, graphics::Renderable2D* renderable);
		GameObject();
		inline std::string getUUID() { return m_uuid; }
		inline void setTag(std::string tag) { m_tag = tag; }
		inline std::string getTag() { return m_tag; }

		void addAnimator();
		void addComponent(physics::PhysicsBody2D* physicsBody2D);

		/*void addChild(GameObject* object);
		void removeChild(GameObject* object);*/

		inline graphics::Animator* getAnimator() { return mProperties.animator; }
		inline graphics::Renderable* getRenderable() { return mProperties.renderable; }
		inline bool isEnabled() { return mProperties.enabled; }
		void disable();
		void enable();
	



		bool hasFixture(b2Fixture* fixture) {
			if (m_physicsBody2D == nullptr) return false;
			for (b2Fixture* f = m_physicsBody2D->getBody()->GetFixtureList(); f; f = f->GetNext()) {
				if (f == fixture) {
					return true;
				}
			}
			return false;
		}


		virtual void submit(graphics::Renderer2D* renderer) const;

		virtual void update();

		inline const graphics::Renderable2D* getRenderable()const { return m_renderable; }


		virtual void onCollisionEnter(b2Contact* contact) {};
		virtual void onSensorEnter(b2Contact* contact) {};

		virtual void onCollisionExit(b2Contact* contact) {};
		virtual void onSensorExit(b2Contact* contact) {};

		~GameObject();

	private:
		
		inline void init(){m_uuid = xg::newGuid();}
	
	};
	
	class Physics2DContactListener : public b2ContactListener {
		void BeginContact(b2Contact* contact);
		void EndContact(b2Contact* contact);
	};




	template <class type>
	static type* Instantiate(glm::vec2 position, glm::vec2 size = { 1,1 }, std::string layerName = "Default") {
		type* go = new type(position, size);
		if (layerName != "") {
			Layer* layer = Layer::getLayerByName(layerName);
			if (layer != nullptr)
				layer->add((GameObject*)go);
			else {
				//TODO log error
				std::cout << "Cannot add object of type: <" << typeid(type).name() << "> to layer: " << layerName << ", layer does not exist. Exiting" << std::endl;
				exit(1);
			}
		}
		return go;
	};

	static void Destroy(GameObject* g) {
		//TODO no
		if (!g->_destroyFlag) {
			g->_destroyFlag = true;
		}
		else {
			std::cout << "Cannot delete the same GameObject twice!" << std::endl; // TODO log error
		}
	
	}
}
