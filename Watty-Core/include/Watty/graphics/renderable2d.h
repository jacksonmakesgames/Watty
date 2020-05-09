#pragma once

#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"
#include "renderer2d.h"
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

	class Renderable2D{
	public:
		glm::vec2& position;
	protected:
		glm::vec2 m_size = glm::vec2(1.0f);
		glm::vec2 m_position = glm::vec2(0.0f);
		float m_rotation = 0;
		WattyColor m_color = WattyColor(1,1,1,1);
		std::vector<glm::vec2> m_UVs = std::vector<glm::vec2>();
		Texture* m_texture; 
		glm::mat4 m_transformationMatrix = glm::mat4(1.0f);
		Bounds2D bounds; // TODO: right now, only used for labels
		FrameInfo m_frameInfo;

	private:
		std::vector<Renderable2D*> m_childrenRenderables = std::vector<Renderable2D*>();


	protected:
		Renderable2D() : position(m_position){
			m_transformationMatrix = glm::mat4(1);
			setUVDefaults();
			m_texture = nullptr;
			recalculateBounds();
		}
			


	public:
		Renderable2D(glm::vec3 position, glm::vec2 size, WattyColor color)
		: m_position(position), m_size(size), m_color(color), position(m_position){
			m_transformationMatrix = glm::mat4(1);
			setUVDefaults();
			m_texture = nullptr;
			m_size = size;
			m_position = position;
			recalculateBounds();
		}

		void setTransformationMatrix(glm::mat4 matrix) {
			m_transformationMatrix = matrix;
		}

		virtual ~Renderable2D() {
		}

		virtual void submit(Renderer2D* renderer, glm::mat4 overrideMatrix)const {
			glm::mat4 originalMat = renderer->pop();
			{
				renderer->push(overrideMatrix);
				renderer->submit(this);
				renderer->pop();
			}
			renderer->push(originalMat);
		}


		virtual void submit(Renderer2D* renderer)const {
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

		virtual const std::vector<Renderable2D*>& getChildren() const {
			return m_childrenRenderables;
		}


		inline const glm::vec2& getSize()const{ return m_size; }
		inline const Bounds2D& getBounds()const{ return bounds; }
		inline const glm::vec2& getPosition()const{ return m_position; }
		inline void setPosition(glm::vec3 pos) { m_position = pos; recalculateBounds(); }
		inline void setSize(glm::vec2 newSize) { m_size = newSize; recalculateBounds(); }
		
		inline const WattyColor getColor()const{ return m_color; }
		inline const std::vector<glm::vec2>& getUVs()const{ return m_UVs; }

		inline const unsigned int getTID() const { return m_texture == nullptr ? 0 : m_texture->getID(); }
		inline const Texture* getTexture() const { return m_texture == nullptr ? nullptr : m_texture; }
		inline const FrameInfo getFrameInfo() const { return m_frameInfo; }

		inline void setFrameInfo(FrameInfo frameInfo) { m_frameInfo = frameInfo; }
		inline void recalculateBounds() {
			bounds.lowerLeft = { m_position.x - (.5f * m_size.x), m_position.y - (.5f * m_size.y) };
			bounds.upperLeft = { m_position.x - (.5f * m_size.x), m_position.y + (.5f * m_size.y) };
			bounds.upperRight = { m_position.x + (.5f * m_size.x), m_position.y + (.5f * m_size.y) };
			bounds.lowerRight = { m_position.x + (.5f * m_size.x), m_position.y - (.5f * m_size.y) };
		}
		void setUvs(glm::vec2 sw, glm::vec2 nw, glm::vec2 ne, glm::vec2 se) {
			m_UVs = std::vector<glm::vec2>();
			m_UVs.push_back(sw);
			m_UVs.push_back(nw);
			m_UVs.push_back(ne);
			m_UVs.push_back(se);

			m_frameInfo.currentFrame = 0.0f;
			m_frameInfo.totalFrames = 1.0f;
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