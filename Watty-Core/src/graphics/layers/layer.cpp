#include <graphics/layers/layer.h>
namespace letc {
	Layer::Layer(std::string name, graphics::Renderer2D* renderer, graphics::Shader* shader)
	: name(name){
		m_shader = shader;
		m_renderer = renderer;
		m_shader->enable();
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
		if (!enabled && gameObject->getPhysicsBody2D() != nullptr)
			gameObject->getPhysicsBody2D()->disable();
		m_gameObjects.push_back(gameObject);
	}


	void Layer::remove(GameObject* gameObject)
	{
		for (size_t i = 0; i < m_gameObjects.size(); i++)
		{
			if (m_gameObjects[i] == gameObject) {
				delete m_gameObjects[i];
				m_gameObjects.erase(m_gameObjects.begin()+i);

			}
		}
	}



	void Layer::disable(){
		for (GameObject* gameObject : m_gameObjects)
			gameObject->disable();

		enabled = false;
	}

	void Layer::enable(){
		for (GameObject* gameObject : m_gameObjects)
			gameObject->enable();

		enabled = true;
	}

	void Layer::draw(){
		if (!enabled) return;
		m_shader->enable();
		m_renderer->begin();


		for (GameObject* gameObject : m_gameObjects){
			gameObject->submit(m_renderer);
		}


		m_renderer->end();
		m_renderer->flush();
		m_shader->disable();

		m_renderer->nextFrame();

		
	}

	void Layer::update(){
		if (!m_enabledLastFrame && enabled)
			enable();
		else if (m_enabledLastFrame && !enabled)
			disable();
		m_enabledLastFrame = enabled;
		if (!enabled) return;
		for (GameObject* gameObject : m_gameObjects) {
				gameObject->update();
			}

	}



	void Layer::setProjection(math::Matrix4 projection)
	{
		m_shader->enable();
		m_shader->setUniformMat4("pr_matrix", projection);
		m_shader->disable();
	}
	
	

}