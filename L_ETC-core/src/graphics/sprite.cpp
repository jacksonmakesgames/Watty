#include "sprite.h"

namespace letc {namespace graphics {
	Sprite::Sprite(float x, float y, float width, float height, unsigned int color)
		: Renderable2D(math::Vector3(x, y, 0.0f), math::Vector2(width, height), color) {
	}
	Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
		: Renderable2D(math::Vector3(x, y, 0.0f), math::Vector2(width, height), 0xffffffff) {
		m_texture = texture;
	}

	Sprite::Sprite(Texture* texture)
		: Renderable2D(math::Vector3(0,0, 0.0f), math::Vector2(0, 0), 0xffffffff){
		m_texture = texture;
	}
	Sprite::Sprite(unsigned int color)
		: Renderable2D(math::Vector3(0,0, 0.0f), math::Vector2(0, 0), color){
	}
	
}}