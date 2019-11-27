#pragma once
#include "graphics/renderable2d.h"
#include "math/math.h"
#include "physics/PhysicsBody2d.h"
#include <vector>
#include <math.h>

namespace letc {
	class GameObject {
	public:
		math::Vector3& position;
		math::Vector2& size;
	private:
		std::string m_tag = "";
		graphics::Renderable2D* m_renderable;
		math::Vector3 m_position;
		float m_angle = 0;
		math::Vector2 m_size;
		physics::PhysicsBody2D* m_physicsBody2D;
		std::vector<GameObject*> m_children;

	public:
		GameObject(math::Vector3 position, math::Vector2 size);
		GameObject(math::Vector3 position, math::Vector2 size, graphics::Renderable2D* renderable);
		GameObject(math::Vector3 position, graphics::Renderable2D* renderable);
		GameObject();

		inline void setTag(std::string tag) { m_tag = tag; }
		inline std::string getTag() { return m_tag; }

		void addComponent(graphics::Renderable2D* renderable);
		void addComponent(physics::PhysicsBody2D* physicsBody2D);

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

		inline const graphics::Renderable2D * getRenderable()const { return m_renderable; }
		virtual inline const std::vector<GameObject*>& getChildren()const { return m_children; }

		inline physics::PhysicsBody2D* getPhysicsBody2D() { return m_physicsBody2D; }

		~GameObject();

	private:


	};




}