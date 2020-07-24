#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <vector>

namespace letc {
	class GameObject;
	class Transform {
	public:
		GameObject* gameObject = nullptr;

	protected:
		glm::mat4 transformMatrix = glm::mat4(1.0f);
		Transform* parent = nullptr;
		std::vector<Transform*> children = std::vector<Transform*>();



	public:
		void setMatrix(glm::mat4 newMatrix);
		void setMatrix(glm::mat4 newMatrix);
		glm::mat4 getMatrix();
		virtual void updateMatrix() = 0;

		virtual Transform* getParent();
		virtual void setParent(Transform* newParent);
		virtual Transform* getChild(int index);
		virtual std::vector<Transform*> getChildren();
		virtual void addChild(Transform* child) = 0;
		virtual void removeChild(Transform* child);
		virtual void removeChild(int index);


	};
}