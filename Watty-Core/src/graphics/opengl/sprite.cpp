#include <graphics/sprite.h>
namespace watty {namespace graphics {
	Sprite::Sprite(glm::vec2 position, glm::vec2 size, WattyColor color)
		: Renderable2D(glm::vec2(position.x, position.y), glm::vec2(size.x, size.y), color) {
	}
	Sprite::Sprite(glm::vec2 position, glm::vec2 size, Texture* texture)
		: Renderable2D({ position.x, position.y}, size, 0xffffffff) {
		m_texture = texture;
	}

	Sprite::Sprite(Texture* texture)
		: Renderable2D(glm::vec3(0.0f), glm::vec2(1.0f, 1.0f), 0xffffffff){
		m_texture = texture;
	}

	Sprite::Sprite(std::string texturePath): Sprite(new Texture(texturePath)){
	}

	Sprite::Sprite(WattyColor color)
		: Renderable2D(glm::vec2(0.0f,0.0f), glm::vec2(1, 1), color){
	}
	
}}