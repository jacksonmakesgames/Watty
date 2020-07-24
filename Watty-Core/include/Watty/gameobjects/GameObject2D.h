#pragma once
#include <graphics/textures/Animator2D.h>
#include <physics/PhysicsBody2D.h>
#include <gameobjects/Transform2D.h>
#include <gameobjects/GameObject.h>
namespace letc {
	struct GameObject2DProperties : public GameObjectProperties {
		GameObject2DProperties():GameObjectProperties() {
			animator = (graphics::Animator2D*)animator;
			renderable = (graphics::Renderable2D*)renderable;
		}

		physics::PhysicsBody2D* physicsBody2D;

	};


	class GameObject2D : public GameObject {
	protected:
	public:
		Transform2D* transform = nullptr;
		const char* name;

	private:
		GameObject2DProperties mProperties;

		//Graphics
		
		// Physics

	public:
		GameObject2D(const char* name, glm::vec3 position, glm::vec2 size);
		GameObject2D(glm::vec2 position, glm::vec2 size);
		GameObject2D(glm::vec3 position, glm::vec2 size);
		GameObject2D(glm::vec3 position, glm::vec2 size, graphics::Renderable2D* renderable);
		GameObject2D(glm::vec2 position, glm::vec2 size, graphics::Renderable2D* renderable);
		GameObject2D(glm::vec3 position, graphics::Renderable2D* renderable);
		GameObject2D(glm::vec2 position, graphics::Renderable2D* renderable);
		GameObject2D(const char* name, glm::vec2 position, glm::vec2 size, graphics::Renderable2D* renderable);
		GameObject2D();


		void addComponent(graphics::Renderable2D* renderable);
		void addAnimator();
		void addComponent(physics::PhysicsBody2D* physicsBody2D);
		
		inline graphics::Animator2D* getAnimator() { return (graphics::Animator2D*) mProperties.animator; }

		bool hasFixture(b2Fixture* fixture) {
			if (mProperties.physicsBody2D == nullptr) return false;
			for (b2Fixture* f = mProperties.physicsBody2D->getBody()->GetFixtureList(); f; f = f->GetNext()){
				if (f== fixture) {
					return true;
				}
			}
			return false;
		}


		virtual void submit(graphics::Renderer2D* renderer) const;

		virtual void update();
		virtual void update(glm::vec2 positionOffset);

		inline const graphics::Renderable2D * getRenderable()const { return (graphics::Renderable2D*)mProperties.renderable; }

		inline physics::PhysicsBody2D* getPhysicsBody2D() {
			return mProperties.physicsBody2D;
		}

		~GameObject2D();

	private:


	};




}