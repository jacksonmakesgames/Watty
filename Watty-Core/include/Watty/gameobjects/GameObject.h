#pragma once
#include "../graphics/renderable2d.h"
#include "../physics/PhysicsBody2d.h"
#include <vector>
#include <math.h>
#include "../graphics/textures/Animator2D.h"
#include <ext/glm/include/glm.hpp>
#include "Transform2D.h"

namespace letc {
	class GameObject {
	public:
		Transform2D* transform = nullptr;
		//glm::vec3& position		 = glm::vec3(0.0f);
		//glm::vec2& size			 = glm::vec2(0.0f);
		//glm::vec3 m_parentOffset = glm::vec3(0.0f);
	private:
		std::string m_tag = "";
		//std::vector<GameObject*> m_children;
		
		
		//glm::mat4 m_rotationMatrix		= glm::mat4(1.0f);
		//glm::mat4 m_translationMatrix	= glm::mat4(1.0f);
		


		//Graphics
		graphics::Renderable2D* m_renderable	= nullptr;
		graphics::Animator2D*	m_animator		= nullptr;
		
		//TODO: add transform struct
		//glm::vec3 m_position = glm::vec3(0.0f);
		//float m_angle = 0.0f;
		//glm::vec2 m_size = glm::vec2(1.0f);

		// Physics
		physics::PhysicsBody2D* m_physicsBody2D;

	public:
		GameObject(glm::vec3 position, glm::vec2 size);
		GameObject(glm::vec2 position, glm::vec2 size);
		GameObject(glm::vec3 position, glm::vec2 size, graphics::Renderable2D* renderable);
		GameObject(glm::vec2 position, glm::vec2 size, graphics::Renderable2D* renderable);
		GameObject(glm::vec3 position, graphics::Renderable2D* renderable);
		GameObject(glm::vec2 position, graphics::Renderable2D* renderable);
		GameObject();

		inline void setTag(std::string tag) { m_tag = tag; }
		inline std::string getTag() { return m_tag; }

		void addComponent(graphics::Renderable2D* renderable);
		void addAnimator();
		void addComponent(physics::PhysicsBody2D* physicsBody2D);
		
		/*void addChild(GameObject* object);
		void removeChild(GameObject* object);*/

		inline graphics::Animator2D* getAnimator() { return m_animator; }
		
		void disable();
		void enable();

		/*void translate(glm::vec2 translation);
		void rotate(float rotation);*/

		bool hasFixture(b2Fixture* fixture) {
			if (m_physicsBody2D == nullptr) return false;
			for (b2Fixture* f = m_physicsBody2D->getBody()->GetFixtureList(); f; f = f->GetNext()){
				if (f== fixture) {
					return true;
				}
			}
			return false;
		}

		/*inline void setPosition(glm::vec3 position) { 
			m_position.x = position.x - m_size.x/2.0f;
			m_position.y = position.y - m_size.y/2.0f;
			m_position.z = position.z;
		
		}*/

		virtual void submit(graphics::Renderer2D* renderer) const;

		virtual void update();
		virtual void update(glm::vec2 positionOffset);

		inline const graphics::Renderable2D * getRenderable()const { return m_renderable; }

		inline physics::PhysicsBody2D* getPhysicsBody2D() {
			return m_physicsBody2D;
		}

		~GameObject();

	private:


	};




}