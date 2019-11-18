#include "layer.h"
namespace letc {namespace graphics {
	Layer::Layer(Renderer2D* renderer, Shader* shader, math::Matrix4 prMatrix) {
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
		for (size_t i = 0; i < m_renderables.size(); i++){
			delete m_renderables[i];
		}
	}

	void Layer::add(Renderable2D* renderable) {
		if (renderable->getTID() > 0) {
			m_renderer->textureManager.addTexture(renderable->getTexture());

		}
		m_renderables.push_back(renderable);
	}

	void Layer::add(Group* group)
	{
		// get all the child textures:
		Renderable2D* topRenderable = group;
		for (size_t i = 0; i < group->getChildren().size(); i++) {
			if (group->getChildren()[i]->getTID() > 0) {
				m_renderer->textureManager.addTexture(group->getChildren()[i]->getTexture());
			}
		}

		m_renderables.push_back(group);

	}

	void Layer::draw(){
		m_shader->enable();
		m_renderer->begin();
		
		for (const Renderable2D* renderable : m_renderables){
			renderable->submit(m_renderer);
		}


		m_renderer->end();
		m_renderer->flush();

		m_renderer->nextFrame();
		
	}
	

}}