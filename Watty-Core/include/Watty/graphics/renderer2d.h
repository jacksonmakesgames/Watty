#pragma once
#include <vector>
#include <iostream>
#include "Color.h"
#ifdef WATTY_OPENGL
#include <ext/glad/include/glad/glad.h>
#include "font/font.h"
#endif // WATTY_OPENGL



#include <ext/glm/include/glm.hpp>

//#include "texturemanager.h"

namespace letc {namespace graphics {
	class Renderable2D;

	class Renderer2D{
	public:
		static unsigned int globalFlushesThisFrame;
	protected:

		std::vector<glm::mat4> m_TransformationStack;
		const glm::mat4* m_tranformationStackBack;
		unsigned short m_flushesPerFrame = 1;
		unsigned short m_flushesThisFrame = 0;
		int m_maxTextureUnits = 0;

		Renderer2D() {
			//TODO: MOVE TO CPP
			m_TransformationStack.push_back(glm::mat4(1.0));
			m_tranformationStackBack = &m_TransformationStack.back();
#ifdef WATTY_OPENGL
			glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &m_maxTextureUnits);
#endif
		}
		
			
	public:
		void push(const glm::mat4& mat, bool override = false) {
			if (override) {
				m_TransformationStack.push_back(mat);
			}
			else {
				m_TransformationStack.push_back(m_TransformationStack.back() * mat);
			}
			m_tranformationStackBack = &m_TransformationStack.back();
		}

		glm::mat4 pop() {
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
		~Renderer2D() {
		}


		virtual void begin() {}

		virtual void submit(const Renderable2D* renderable) = 0;
#ifdef WATTY_OPENGL
		virtual void drawString(const std::string& text, const glm::vec2& position, const Font& font, WattyColor color) {};
#endif

		virtual void end() {}
		virtual void flush() = 0;

	public:
		inline void nextFrame() { m_flushesThisFrame=0; }

	};

}}