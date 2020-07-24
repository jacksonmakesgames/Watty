#pragma once

#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"
#include "renderer.h" // TODO 3d
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

	struct FrameInfo {
		float currentFrame;
		float totalFrames;
		int rows = 1;
		int cols = 1;
	};

	class Renderable3D{
	public:
		glm::vec3& position;
	protected:
		glm::vec3 m_size = glm::vec3(1.0f);
		glm::vec3 m_position = glm::vec3(0.0f);
		float m_rotation = 0;
		WattyColor m_color = WattyColor(1,1,1,1);
		std::vector<glm::vec2> m_UVs = std::vector<glm::vec2>();
		Texture* m_texture; 
		glm::mat4 m_transformationMatrix = glm::mat4(1.0f);
		FrameInfo m_frameInfo;

	private:
		std::vector<Renderable3D*> m_childrenRenderables = std::vector<Renderable3D*>();


	protected:
		Renderable3D() : position(m_position){
			m_transformationMatrix = glm::mat4(1);
			setUVDefaults();
			m_texture = nullptr;
		}
			


	public:
		Renderable3D(glm::vec3 position, glm::vec3 size, WattyColor color)
		: m_position(position), m_size(size), m_color(color), position(m_position){
			m_transformationMatrix = glm::mat4(1);
			setUVDefaults();
			m_texture = nullptr;
			m_size = size;
			m_position = position;
		}

		void setTransformationMatrix(glm::mat4 matrix) {
			m_transformationMatrix = matrix;
		}

		virtual ~Renderable3D() {
		}

		virtual void submit(Renderer* renderer, glm::mat4 overrideMatrix)const {
			glm::mat4 originalMat = renderer->pop();
			{
				renderer->push(overrideMatrix);
				renderer->submit((Renderable*)this);
				renderer->pop();
			}
			renderer->push(originalMat);
		}


		virtual void submit(Renderer* renderer)const {
			renderer->submit((Renderable*)this);
		}

		inline void setColor(WattyColor color) { m_color = color; }
		inline void setColor(glm::vec4 color) {
			int	r = color.x * 255.0f;
			int	g = color.y * 255.0f;
			int	b = color.z * 255.0f;
			int	a = color.w * 255.0f;
			m_color = a << 24 | b << 16 | g << 8 | r;
		}

		virtual const std::vector<Renderable3D*>& getChildren() const {
			return m_childrenRenderables;
		}


		inline const glm::vec2& getSize()const{ return m_size; }
		inline const glm::vec2& getPosition()const{ return m_position; }
		inline void setPosition(glm::vec3 pos) { m_position = pos;}
		
		inline const WattyColor getColor()const{ return m_color; }
		inline const std::vector<glm::vec2>& getUVs()const{ return m_UVs; }

		inline const unsigned int getTID() const { return m_texture == nullptr ? 0 : m_texture->getID(); }
		inline const Texture* getTexture() const { return m_texture == nullptr ? nullptr : m_texture; }
		inline const FrameInfo getFrameInfo() const { return m_frameInfo; }

		inline void setFrameInfo(FrameInfo frameInfo) { m_frameInfo = frameInfo; }
		
		void setUvs(glm::vec2 sw, glm::vec2 nw, glm::vec2 ne, glm::vec2 se) {
			
		}

	private:
		void setUVDefaults() {
			m_UVs = std::vector<glm::vec2>();
			m_UVs.push_back(glm::vec2(0.0f, 0.0f));
			m_UVs.push_back(glm::vec2(0.0f, 1.0f));
			m_UVs.push_back(glm::vec2(1.0f, 1.0f));
			m_UVs.push_back(glm::vec2(1.0f, 0.0f));

			m_frameInfo.currentFrame = 0.0f;
			m_frameInfo.totalFrames = 1.0f;
		}
	};
}}