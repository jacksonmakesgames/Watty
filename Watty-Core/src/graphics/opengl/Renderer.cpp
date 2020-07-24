#include <graphics/renderer2d.h>

namespace letc { namespace graphics {

	unsigned int Renderer::globalFlushesThisFrame = 0;
	Renderer::Renderer() {
		m_TransformationStack.push_back(glm::mat4(1.0));
		m_tranformationStackBack = &m_TransformationStack.back();
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &m_maxTextureUnits);
	}

	void Renderer::push(const glm::mat4& mat, bool override)
	{
		if (override) {
			m_TransformationStack.push_back(mat);
		}
		else {
			m_TransformationStack.push_back(m_TransformationStack.back() * mat);
		}
		m_tranformationStackBack = &m_TransformationStack.back();
	}

	glm::mat4 Renderer::pop()
	{
		if (m_TransformationStack.size() > 1) {
			m_TransformationStack.pop_back();
		}
		else {
			//TODO: log error
			std::cout << "ERROR: TRIED TO POP TOO MANY MATRIX4s" << std::endl;
			return glm::mat4(1.0f);
		}
		m_tranformationStackBack = &m_TransformationStack.back();
		return *m_tranformationStackBack;
	}

}}