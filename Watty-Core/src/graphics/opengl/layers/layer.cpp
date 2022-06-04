#include <graphics/layers/layer.h>
namespace watty {
	std::vector<Layer*> Layer::allLayers = std::vector<Layer*>();

	Layer* Layer::getLayerByName(std::string name) {
		for (size_t i = 0; i < allLayers.size(); i++) {
			if (allLayers[i]->name == name) return allLayers[i];
		}
		//TODO log error
		std::cout << "Error: could not find layer: " << name << std::endl;
		return nullptr;
	};

	Layer::Layer(std::string name, graphics::Renderer2D* renderer, graphics::Shader* shader)
	: name(name){
		m_shader = shader;
		m_renderer = renderer;
		m_shader->enable();
		m_shader->disable();
		allLayers.push_back(this);
	}

	Layer::Layer(std::string name, graphics::Renderer2D* renderer)
		:name(name)
	{
		m_shader = new graphics::Shader();
		m_renderer = renderer;
		m_shader->enable();
		m_shader->disable();
		allLayers.push_back(this);

	}

	Layer::Layer(std::string name)
		:name(name)
	{
		m_shader = new graphics::Shader();
		m_renderer = new graphics::BatchRenderer2D();
		m_shader->enable();
		m_shader->disable();
		allLayers.push_back(this);

	}

	Layer::~Layer() {
		if(m_shader!=nullptr){
			delete m_shader;
		}
		else {
			// TODO log error, also this nullptr check won't do anything
			std::cout << "Warning: shader was destroyed before layer" << std::endl;
		}

		delete m_renderer;
		for (size_t i = 0; i < m_gameObjects.size(); i++){
			delete m_gameObjects[i];
		}

		int index = -1;
		for (size_t i = 0; i < allLayers.size(); i++){
			if (allLayers[i] == this) {
				index = i;
			}
		}
		if(index>=0)
			allLayers.erase(allLayers.begin() + index);
	}

	void Layer::add(GameObject* gameObject) {
		if (!enabled_ && gameObject->getPhysicsBody2D() != nullptr)
			gameObject->getPhysicsBody2D()->disable();
		m_gameObjects.push_back(gameObject);
	}


	void Layer::remove(GameObject* gameObject)
	{
		for (size_t i = 0; i < m_gameObjects.size(); i++){
			if (m_gameObjects[i] == gameObject) {
				delete m_gameObjects[i];
				m_gameObjects.erase(m_gameObjects.begin()+i);

			}
		}
	}



	void Layer::disable(){
		if (!enabled_) return;
		for (GameObject* gameObject : m_gameObjects)
			gameObject->disable();

		enabled_ = false;
	}

	void Layer::enable(){
		if (enabled_) return;
		for (GameObject* gameObject : m_gameObjects)
			gameObject->enable();
		enabled_ = true;
	}

	void Layer::draw(){
		if (!enabled_) return;
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
		if (!enabled_) return;
		std::vector<int> toRemoveThisFrame = std::vector<int>();
		for (size_t i = 0; i < m_gameObjects.size(); i++)
		{
			if (m_gameObjects[i]->_destroyFlag)
				toRemoveThisFrame.push_back(i);
			else
				m_gameObjects[i]->update();
		}

		for (size_t i = 0; i < toRemoveThisFrame.size(); i++) {
			delete m_gameObjects[toRemoveThisFrame[i]];
			m_gameObjects.erase(m_gameObjects.begin() + toRemoveThisFrame[i]);
		}


	}



	void Layer::setProjection(glm::mat4 projection)
	{
		mProjection = projection;
		m_shader->enable();
		m_shader->setUniformMat4("pr_matrix", projection);
		m_shader->disable();
	}
	
	

}