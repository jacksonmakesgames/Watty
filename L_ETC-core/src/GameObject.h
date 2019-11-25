#pragma once
#include "graphics/renderable2d.h"
#include "math/math.h"
#include "physics/PhysicsBody2D.h"
#include <vector>


namespace letc {
	class GameObject {
	public:
		math::Vector3& position;
		math::Vector2& size;
	private:
		graphics::Renderable2D* m_renderable;
		math::Vector3 m_position;
		math::Vector2 m_size;
		physics::PhysicsBody2D* m_physicsBody2D;
		std::vector<GameObject*> m_children;

	public:
		GameObject(math::Vector3 position, math::Vector2 size);
		GameObject(math::Vector3 position, math::Vector2 size, graphics::Renderable2D* renderable);
		GameObject(math::Vector3 position, graphics::Renderable2D* renderable);
		GameObject();

		void addComponent(graphics::Renderable2D* renderable);
		void addComponent(physics::PhysicsBody2D* physicsBody2D);
		virtual void submit(graphics::Renderer2D* renderer) const;

		virtual void update();

		inline const graphics::Renderable2D * getRenderable()const { return m_renderable; }
		virtual inline const std::vector<GameObject*>& getChildren()const { return m_children; }

		inline physics::PhysicsBody2D* getPhysicsBody2D() { return m_physicsBody2D; }

		~GameObject();

	private:


	};




}