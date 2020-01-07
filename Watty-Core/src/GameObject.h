#pragma once
#include "graphics/renderable2d.h"
#include "math/math.h"
#include "physics/PhysicsBody2d.h"
#include <vector>
#include <math.h>
#include "graphics/textures/Animator2D.h"

namespace letc {
	class GameObject {
	public:
		math::Vector3& position;
		math::Vector2& size;
		math::Vector3 m_parentOffset;
	private:
		std::string m_tag = "";
		std::vector<GameObject*> m_children;
		
		
		math::Matrix4 m_rotationMatrix;
		math::Matrix4 m_translationMatrix;
		


		//Graphics
		graphics::Renderable2D* m_renderable	= nullptr;
		graphics::Animator2D*	m_animator		= nullptr;
		
		//TODO: add transform struct
		math::Vector3 m_position;
		float m_angle =0;
		math::Vector2 m_size;

		// Physics
		physics::PhysicsBody2D* m_physicsBody2D;

	public:
		GameObject(math::Matrix4 transformationMatrix);
		GameObject(math::Vector3 position, math::Vector2 size);
		GameObject(math::Vector2 position, math::Vector2 size);
		GameObject(math::Vector3 position, math::Vector2 size, graphics::Renderable2D* renderable);
		GameObject(math::Vector2 position, math::Vector2 size, graphics::Renderable2D* renderable);
		GameObject(math::Vector3 position, graphics::Renderable2D* renderable);
		GameObject(math::Vector2 position, graphics::Renderable2D* renderable);
		GameObject();

		inline void setTag(std::string tag) { m_tag = tag; }
		inline std::string getTag() { return m_tag; }

		void addComponent(graphics::Renderable2D* renderable);
		void addAnimator();
		void addComponent(physics::PhysicsBody2D* physicsBody2D);
		
		void addChild(GameObject* object);
		void removeChild(GameObject* object);

		inline graphics::Animator2D* getAnimator() { return m_animator; }
		
		void disable();
		void enable();

		void translate(math::Vector2 translation);
		void rotate(float rotation);

		bool hasFixture(b2Fixture* fixture) {
			if (m_physicsBody2D == nullptr) return false;
			for (b2Fixture* f = m_physicsBody2D->getBody()->GetFixtureList(); f; f = f->GetNext()){
				if (f== fixture) {
					return true;
				}
			}
			return false;
		}

		virtual void submit(graphics::Renderer2D* renderer) const;

		virtual void update();
		virtual void update(math::Vector3 positionOffset);

		inline const graphics::Renderable2D * getRenderable()const { return m_renderable; }
		virtual inline const std::vector<GameObject*>& getChildren()const { return m_children; }

		inline physics::PhysicsBody2D* getPhysicsBody2D() {
			return m_physicsBody2D;
		}

		~GameObject();

	private:


	};




}