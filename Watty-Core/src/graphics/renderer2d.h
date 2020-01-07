#pragma once
#include <vector>
//#include <GL/glew.h>
#include <glad/glad.h>

#include "../math/math.h"
#include "font/font.h"

//#include "texturemanager.h"

namespace letc {namespace graphics {
	class Renderable2D;

	class Renderer2D{
	protected:
		std::vector<math::Matrix4> m_TransformationStack;
		const math::Matrix4* m_tranformationStackBack;
		unsigned short m_flushesPerFrame = 1;
		unsigned short m_flushesThisFrame = 0;
		GLint m_maxTextureUnits = 0;

		Renderer2D() {
			m_TransformationStack.push_back(math::Matrix4::identity());
			m_tranformationStackBack = &m_TransformationStack.back();
			glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &m_maxTextureUnits);
		}
		
			
	public:
		void push(const math::Matrix4& mat, bool override = false) {
			if (override) {
				m_TransformationStack.push_back(mat);
			}
			else {
				m_TransformationStack.push_back(m_TransformationStack.back() * mat);
			}
			m_tranformationStackBack = &m_TransformationStack.back();
		}

		void pop() {
			if (m_TransformationStack.size() > 1) {
				m_TransformationStack.pop_back();
			}
			else {
				//TODO: log error
				std::cout << "ERROR: TRIED TO POP TOO MANY MATRIX4s" << std::endl;
				return;
			}
			m_tranformationStackBack = &m_TransformationStack.back();

		}
		~Renderer2D() {
		}


		virtual void begin() {}
		virtual void submit(const Renderable2D* renderable) = 0;
		virtual void drawString(const std::string& text, const math::Vector3& position, const Font& font, unsigned int color) {};
		virtual void end() {}
		virtual void flush() = 0;

	public:
		inline void nextFrame() { m_flushesThisFrame=0; }

	};

}}