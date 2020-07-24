#pragma once
#include <gameobjects/Transform.h>

namespace letc {
	class GameObject2D;

	class Transform2D : public Transform
	{
	private:
		glm::vec2 parentOffset = { 0.0f,0.0f };
		glm::vec2 position = { 0.0f, 0.0f };
		glm::vec2 size = { 0.0f,0.0f };
		float rotation = 0.0f;
	public:
		Transform2D(GameObject2D* go, glm::vec2 pos, glm::vec2 scale, float rot);
		Transform2D(GameObject2D* go, Transform2D* parentTransform);
		Transform2D(GameObject2D* go);

		GameObject2D* gameObject = nullptr;



		void rotate(float angle);
		void setRotation(float newRotation);
		float getRotation();
		void translate(glm::vec2 translation);
		void setPosition(glm::vec2 newPos);
		glm::vec2 getPosition();
		void grow(glm::vec2 sizeDelta);
		void setSize(glm::vec2 newSize);
		glm::vec2 getSize();
		glm::vec2 getParentOffset();

		void setParentOffset(glm::vec2 newParentOffset);
		void updateMatrix() override;
		
		void addChild(Transform* child) override;

		void lookAt(Transform2D& transform);



		~Transform2D();
	};
}