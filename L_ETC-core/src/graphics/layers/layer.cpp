#include "layer.h"
namespace letc {
	Layer::Layer(graphics::Renderer2D* renderer, graphics::Shader* shader, math::Matrix4 prMatrix) {
		m_shader = shader;
		m_prMatrix = prMatrix;
		m_renderer = renderer;

		m_shader->enable();
		m_shader->setUniformMat4("pr_matrix", prMatrix);
		m_shader->disable();
	}

	Layer::~Layer() {
		delete m_shader;
		delete m_renderer;
		for (size_t i = 0; i < m_gameObjects.size(); i++){
			delete m_gameObjects[i];
		}
	}

	void Layer::add(GameObject* gameObject) {
		m_gameObjects.push_back(gameObject);
	}

	void Layer::add(Group* group)
	{
		m_gameObjects.push_back(group);
	}

	void Layer::draw(){
		m_shader->enable();
		m_renderer->begin();


		for (GameObject* gameObject : m_gameObjects){
			gameObject->submit(m_renderer);
			
		}


		m_renderer->end();
		m_renderer->flush();

		m_renderer->nextFrame();
		
	}

	void Layer::update(){
		for (GameObject* gameObject : m_gameObjects) {
				gameObject->update();
			}

	}
	

}