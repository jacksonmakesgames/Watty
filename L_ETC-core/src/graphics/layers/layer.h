#pragma once
#include "../renderer2d.h"
#include "../shader.h"
#include "../../GameObject.h"
#include <vector>


namespace letc {
	class Layer {
	public:
		bool enabled = true;
		std::string name;

	protected:
		graphics::Renderer2D* m_renderer;
		std::vector<GameObject*> m_gameObjects;
		graphics::Shader* m_shader;
	private:
		bool m_enabledLastFrame;
	public:
		Layer(std::string name, graphics::Renderer2D*, graphics::Shader* shader);
		virtual ~Layer();

		virtual void add(GameObject*	gameObject);
		
		virtual void remove(GameObject* gameObject);

		virtual void disable();
		virtual void enable();
		virtual void draw();
		virtual void update();
		virtual void setProjection(math::Matrix4 projection);

		inline const std::vector<GameObject*>& getGameObjects() const { return m_gameObjects; }

	};

}