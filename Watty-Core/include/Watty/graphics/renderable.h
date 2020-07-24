#pragma once

#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"
#include "renderer.h"
#include "texture.h"
#include "shader.h"
#include "Color.h"

namespace letc { namespace graphics {

	struct VertexData
	{
		glm::vec3 vertex;
		glm::vec2 uv;
		float tid;
		WattyColor color;
	};

	class Renderable{
	public:
	protected:
		WattyColor m_color = WattyColor(1,1,1,1);
		std::vector<glm::vec2> m_UVs = std::vector<glm::vec2>();
		Texture* m_texture; 
		glm::mat4 m_transformationMatrix = glm::mat4(1.0f);

	private:
		std::vector<Renderable*> m_childrenRenderables = std::vector<Renderable*>();


	protected:
		Renderable(){
			m_transformationMatrix = glm::mat4(1);
			m_texture = nullptr;
		}
			


	public:
		Renderable(WattyColor color)
		: m_color(color){
			m_transformationMatrix = glm::mat4(1);
			m_texture = nullptr;
		}

		void setTransformationMatrix(glm::mat4 matrix) {
			m_transformationMatrix = matrix;
		}

		virtual ~Renderable() {
		}

		virtual void submit(Renderer* renderer, glm::mat4 overrideMatrix)const {
			glm::mat4 originalMat = renderer->pop();
			{
				renderer->push(overrideMatrix);
				renderer->submit(this);
				renderer->pop();
			}
			renderer->push(originalMat);
		}


		virtual void submit(Renderer* renderer)const {
			renderer->submit(this);
		}

		inline void setColor(WattyColor color) { m_color = color; }
		inline void setColor(glm::vec4 color) {
			int	r = color.x * 255.0f;
			int	g = color.y * 255.0f;
			int	b = color.z * 255.0f;
			int	a = color.w * 255.0f;
			m_color = a << 24 | b << 16 | g << 8 | r;
		}

		virtual const std::vector<Renderable*>& getChildren() const {
			return m_childrenRenderables;
		}
		
		inline const WattyColor getColor()const{ return m_color; }
		inline const std::vector<glm::vec2>& getUVs()const{ return m_UVs; }

		inline const unsigned int getTID() const { return m_texture == nullptr ? 0 : m_texture->getID(); }
		inline const Texture* getTexture() const { return m_texture == nullptr ? nullptr : m_texture; }

		

	private:

	};
}}