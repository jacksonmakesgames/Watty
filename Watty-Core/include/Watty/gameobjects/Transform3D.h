#pragma once
#include <gameobjects/Transform.h>

namespace letc {
	class GameObject3D;

	class Transform3D : public Transform
	{
	private:
		glm::vec3 parentOffset = { 0.0f,0.0f,0.0f };
		glm::vec3 position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 size = { 0.0f,0.0f, 0.0f };
	public:
		Transform3D(GameObject3D* go, glm::vec3 pos, glm::vec3 scale, float rot);
		Transform3D(GameObject3D* go, Transform3D* parentTransform);
		Transform3D(GameObject3D* go);

		GameObject3D* gameObject = nullptr;

		Transform3D* parent = nullptr;

		std::vector<Transform3D*> children = std::vector<Transform3D*>();

		void rotate(float angle, glm::vec3 axis);
		void setRotation(float newRotation, glm::vec3 axis);
		float getRotation(glm::vec3 axis);
		void translate(glm::vec3 translation);
		void setPosition(glm::vec3 newPos);
		glm::vec3 getPosition();
		void grow(glm::vec3 sizeDelta);
		void setSize(glm::vec3 newSize);
		glm::vec3 getSize();
		glm::vec3 getParentOffset();
		void setParentOffset(glm::vec3 newParentOffset);

		void updateMatrix();

		Transform3D* getParent();
		void setParent(Transform3D* newParent);
		Transform3D* getChild(int index);
		void addChild(Transform3D* child);
		void removeChild(Transform3D* child);
		void removeChild(int index);

		void lookAt(Transform3D& transform);



		~Transform3D();
	};
}