#pragma once
#include "renderable2d.h"

namespace letc {namespace graphics {
	class Sprite : public Renderable2D {
	private:
	public:
		Sprite(glm::vec2 position, glm::vec2 size, WattyColor color);
		Sprite(glm::vec2 position, glm::vec2 size, Texture* texture);
		Sprite(Texture* texture);
		Sprite(std::string texturePath);
		Sprite(WattyColor color);

	};



}}