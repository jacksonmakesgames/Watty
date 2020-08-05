#pragma once
#include "renderable2d.h"

namespace letc {namespace graphics {
	class Sprite : public Renderable2D {
	private:
	public:
		Sprite(float x, float y, float width, float height, const WattyColor color);
		Sprite(float x, float y, float width, float height, Texture* texture);
		Sprite(Texture* texture);
		Sprite(std::string texturePath);
		Sprite(WattyColor color);

	};
}}