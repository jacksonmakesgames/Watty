#pragma once
#include "../sprite.h"

namespace letc {namespace graphics {
	class Tile : public Sprite {
	private:
	public:
		Tile(float pixelMeterRatio, Texture* texture, float x, float y, int width, int height, int offsetIndex);
		void submit(Renderer2D* renderer)const override {
			renderer->push(glm::translate(glm::mat4(1.0f), glm::vec3(getPosition().x, getPosition().y, 0)));
			renderer->push(glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 0)));
			renderer->submit(this);
			renderer->pop();
			renderer->pop();

		}
	};
}}