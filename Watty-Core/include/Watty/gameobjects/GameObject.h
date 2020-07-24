#pragma once
#include <gameobjects/Transform.h>
#include <graphics/textures/Animator.h>
#include <iostream>

namespace letc {
	struct GameObjectProperties {
		bool enabled = true;
		std::string name = "GameObject";
		std::string tag = "";
		Transform* transform;
		graphics::Animator* animator = nullptr;
		graphics::Renderable* renderable = nullptr;

	};


	class GameObject {
	protected:
	public:
		Transform* transform = nullptr;
		const char* name;

	private:
		GameObjectProperties mProperties;

	public:
		GameObject();

		inline void setTag(std::string tag) { mProperties.tag = tag; }
		inline std::string getTag() { return mProperties.tag; }

		void addAnimator();
		

		inline graphics::Animator* getAnimator() { return mProperties.animator; }
		inline graphics::Renderable* getRenderable() { return mProperties.renderable; }
		inline bool isEnabled() { return mProperties.enabled; }
		void disable();
		void enable();
	

		virtual void submit(graphics::Renderer* renderer) const;

		virtual void update() = 0;


		~GameObject();

	private:


	};




}