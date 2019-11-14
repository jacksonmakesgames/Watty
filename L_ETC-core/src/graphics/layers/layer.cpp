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
			m_renderables.push_back(renderable);
		}

	void Layer::draw(){
		
		m_shader->enable();
		
		m_renderer->begin();
		
		for (const Renderable2D* renderable : m_renderables){
			renderable->submit(m_renderer);
		}


		m_renderer->end();
		m_renderer->flush();
		
	}
	

}}