#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include<physics/PhysicsBody2D.h>
#include <vector>
namespace watty {
	class GameObject;

	class Transform2D : public Transform
	{
	private:
		glm::vec2 parentOffset = { 0.0f,0.0f };
		glm::vec2 position = { 0.0f, 0.0f };
		glm::vec2 size = { 0.0f,0.0f };
		float rotation = 0.0f;
	public:
		Transform2D(GameObject* go, glm::vec2 pos, glm::vec2 scale, float rot);
		Transform2D(GameObject* go, Transform2D* parentTransform);
		Transform2D(GameObject* go);
		Transform2D();

		GameObject2D* gameObject = nullptr;


		std::vector<Transform2D*> children = std::vector<Transform2D*>();
		
		bool wantsPhysicsMove = false;
		glm::vec2 physicsMoveTo = glm::vec2();

		void rotate(float angle);
		void setRotation(float newRotation);
		float getRotation();
		void translate(glm::vec2 translation);
		void setPosition(glm::vec2 newPos, bool movePhysicsBody = true);
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