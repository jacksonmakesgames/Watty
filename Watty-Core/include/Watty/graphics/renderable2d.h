#pragma once

#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"
#include "renderer2d.h"
#include "texture.h"
#include "shader.h"
#include "ecs/ECS.h"

namespace letc { namespace graphics {


	struct FrameInfo {
		float currentFrame;
		float totalFrames;
		int rows = 1;
		int cols = 1;
	};

	class Renderable2D{
	public:
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
			


	public:

		Renderable2D();

		Renderable2D(glm::vec2 position, glm::vec2 size, WattyColor color);
		

		void setTransformationMatrix(glm::mat4 matrix);
		virtual ~Renderable2D(){}
		virtual void submit(Renderer2D* renderer, glm::mat4 overrideMatrix)const;
		virtual void update() {};

		virtual void submit(Renderer2D* renderer)const;

		inline void setColor(WattyColor color) { m_color = color; }
		void setColor(glm::vec4 color);

		inline virtual const std::vector<Renderable2D*>& getChildren() const {return m_childrenRenderables;}


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

		// public??
		void recalculateBounds();

		void setUvs(glm::vec2 sw, glm::vec2 nw, glm::vec2 ne, glm::vec2 se);

	private:
		void setUVDefaults();

	};

	struct RenderableSpriteComponent : public ECSComponent<RenderableSpriteComponent> {
		WattyColor color = Color::white;
		std::vector<glm::vec2> UVs = std::vector<glm::vec2>();
		Texture texture;
		glm::mat4 transformationMatrix = glm::mat4(1.0f);
		Bounds2D bounds;
		FrameInfo frameInfo;
	};

}}
