#include <Watty/graphics/Renderer2D.h>
#include "..\..\..\include\Watty\graphics\Renderable2D.h"
namespace watty { namespace graphics {

Renderable2D::Renderable2D()
{
	m_transformationMatrix = glm::mat4(1);
	setUVDefaults();
	m_texture = nullptr;
	recalculateBounds();
}

Renderable2D::Renderable2D(glm::vec2 position, glm::vec2 size, WattyColor color)
	: m_position(position), m_size(size), m_color(color){
		m_transformationMatrix = glm::mat4(1);
		setUVDefaults();
		m_texture = nullptr;
		m_size = size;
		m_position = position;
		recalculateBounds();
	}

void Renderable2D::setTransformationMatrix(glm::mat4 matrix)
{
	m_transformationMatrix = matrix;
}

void Renderable2D::submit(Renderer2D* renderer, glm::mat4 overrideMatrix) const
{
	glm::mat4 originalMat = renderer->pop();
	{
		renderer->push(overrideMatrix);
		renderer->submit(this);
		renderer->pop();
	}
	renderer->push(originalMat);
}

void Renderable2D::submit(Renderer2D* renderer) const
{
	renderer->submit(this);

}

inline void Renderable2D::setColor(glm::vec4 color)
{
	int	r = color.x * 255.0f;
	int	g = color.y * 255.0f;
	int	b = color.z * 255.0f;
	int	a = color.w * 255.0f;
	m_color = a << 24 | b << 16 | g << 8 | r;
}


void Renderable2D::recalculateBounds()
{
	
		bounds.lowerLeft = { m_position.x - (.5f * m_size.x), m_position.y - (.5f * m_size.y) };
		bounds.upperLeft = { m_position.x - (.5f * m_size.x), m_position.y + (.5f * m_size.y) };
		bounds.upperRight = { m_position.x + (.5f * m_size.x), m_position.y + (.5f * m_size.y) };
		bounds.lowerRight = { m_position.x + (.5f * m_size.x), m_position.y - (.5f * m_size.y) };
	
}

void Renderable2D::setUvs(glm::vec2 sw, glm::vec2 nw, glm::vec2 ne, glm::vec2 se)
{
		m_UVs = std::vector<glm::vec2>();
		m_UVs.push_back(sw);
		m_UVs.push_back(nw);
		m_UVs.push_back(ne);
		m_UVs.push_back(se);

		m_frameInfo.currentFrame = 0.0f;
		m_frameInfo.totalFrames = 1.0f;
}

void Renderable2D::setUVDefaults()
{
	m_UVs = std::vector<glm::vec2>();
	m_UVs.push_back(glm::vec2(0.0f, 0.0f));
	m_UVs.push_back(glm::vec2(0.0f, 1.0f));
	m_UVs.push_back(glm::vec2(1.0f, 1.0f));
	m_UVs.push_back(glm::vec2(1.0f, 0.0f));

	m_frameInfo.currentFrame = 0.0f;
	m_frameInfo.totalFrames = 1.0f;
}








}
}
