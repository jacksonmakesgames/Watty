#pragma once
#include "../renderer2d.h"
#include "group.h"
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
		math::Matrix4 m_prMatrix;
	private:
		bool m_enabledLastFrame;
	public:
		Layer(std::string name, graphics::Renderer2D*, graphics::Shader* shader, math::Matrix4 prMatrix);
		virtual ~Layer();

		virtual void add(GameObject*	gameObject);
		virtual void add(Group*			group);
		
		virtual void disable();
		virtual void enable();
		virtual void draw();
		virtual void update();

		inline const std::vector<GameObject*>& getGameObjects() const { return m_gameObjects; }

	};

}