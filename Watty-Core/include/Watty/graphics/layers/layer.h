#pragma once
#include "../batchrenderer2d.h"
#include "../../gameobjects/GameObject.h"

namespace letc {
	class Layer {
	public:
		bool enabled = true;
		bool hidden = false;
		std::string name;

	protected:
		graphics::Renderer2D* m_renderer;
		std::vector<GameObject*> m_gameObjects;
		graphics::Shader* m_shader;
	private:
		bool m_enabledLastFrame;
		glm::mat4 mProjection;
	public:
		Layer(std::string name, graphics::Renderer2D*, graphics::Shader* shader);
		Layer(std::string name, graphics::Renderer2D*);
		Layer(std::string name);
		virtual ~Layer();

		virtual void add(GameObject*	gameObject);
		
		virtual void remove(GameObject* gameObject);

		virtual void disable();
		virtual void enable();
		virtual void draw();
		virtual void update();
		virtual void setProjection(glm::mat4 projection);
		inline virtual glm::mat4 getProjection() {
			return mProjection; 
		};

		inline const std::vector<GameObject*>& getGameObjects() const { return m_gameObjects; }

	};

}