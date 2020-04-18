#include <graphics/sprite.h>
namespace letc {namespace graphics {
	Sprite::Sprite(float x, float y, float width, float height, WattyColor color)
		: Renderable2D(glm::vec3(x, y, 0.0f), glm::vec2(width, height), color) {
	}
	Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
		: Renderable2D(glm::vec3(x, y, 0.0f), glm::vec2(width, height), 0xffffffff) {
		m_texture = texture;
	}

	Sprite::Sprite(Texture* texture)
		: Renderable2D(glm::vec3(0.0f), glm::vec2(1.0f, 1.0f), 0xffffffff){
		m_texture = texture;
	}

	Sprite::Sprite(WattyColor color)
		: Renderable2D(glm::vec3(0,0, 0.0f), glm::vec2(0, 0), color){
	}
	
}}