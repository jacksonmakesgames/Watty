#pragma once
#include "../batchrenderer2d.h"
#include "../../gameobjects/GameObject.h"

namespace watty {
	class Layer {
	public:
		static std::vector<Layer*> allLayers;
		static Layer* getLayerByName(std::string name);

		bool hidden = false;
		std::string name;

	protected:
		graphics::Renderer2D* m_renderer;
		std::vector<GameObject*> m_gameObjects;
		graphics::Shader* m_shader;
		bool enabled_ = true;
	private:
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
		inline virtual bool isEnabled() { return enabled_; }

		virtual void draw();
		virtual void update();
		virtual void setProjection(glm::mat4 projection);


		inline virtual glm::mat4 getProjection() {
			return mProjection; 
		};

		inline const std::vector<GameObject*>& getGameObjects() const { return m_gameObjects; }

		inline virtual graphics::Renderer2D* getRenderer() { return m_renderer; }
		inline virtual graphics::Shader* getShader() { return m_shader; }
	};

}