#pragma once
#include "../renderer2d.h"
#include "group.h"
#include "../shader.h"
#include "../../GameObject.h"
#include <vector>

namespace letc {
	class Layer {
	protected:
		graphics::Renderer2D* m_renderer;
		std::vector<GameObject*> m_gameObjects;
		graphics::Shader* m_shader;
		math::Matrix4 m_prMatrix;
	public:
		Layer(graphics::Renderer2D*, graphics::Shader* shader, math::Matrix4 prMatrix);
		virtual ~Layer();

		virtual void add(GameObject*	gameObject);
		virtual void add(Group*			group);
		
		virtual void draw();
		virtual void update();

		inline const std::vector<GameObject*>& getGameObjects() const { return m_gameObjects; }

	};

}