#pragma once
#include <ext/glm/include/glm.hpp>
#include <ext/glm/include/gtc/matrix_transform.hpp>
//#include <ext/glm/include/gtx/matrix_transform_2d.hpp>
#include <vector>
namespace letc {
	class GameObject;

	class Transform2D
	{
	public:
		Transform2D(GameObject* go, glm::vec2 pos, glm::vec2 scale, float rot);
		Transform2D(GameObject* go, Transform2D* parentTransform);
		Transform2D(GameObject* go);

		GameObject* gameObject = nullptr;

		Transform2D* parent = nullptr;

		std::vector<Transform2D*> children = std::vector<Transform2D*>();

		void rotate(float angle);
		void setRotation(float newRotation);
		float getRotation();
		void translate(glm::vec2 translation);
		void setPosition(glm::vec2 newPos);
		glm::vec2 getPosition();
		void resize(glm::vec2 sizeDelta);
		void setSize(glm::vec2 newSize);
		glm::vec2 getSize();
		glm::vec2 getParentOffset();
		void setParentOffset(glm::vec2 newParentOffset);

		void setMatrix(glm::mat4 newMatrix);
		glm::mat4 getMatrix();
		glm::mat4 getMatrixNoScale();

		void updateMatrix();

		Transform2D* getParent();
		void setParent(Transform2D* newParent);
		Transform2D* getChild(int index);
		void addChild(Transform2D* child);
		void removeChild(Transform2D* child);
		void removeChild(int index);

		void lookAt(Transform2D& transform);



		~Transform2D();
	private:
		glm::mat4 transformMatrix = glm::mat4(1.0f);
		glm::vec2 parentOffset = { 0.0f,0.0f };
		glm::vec2 position = { 0.0f, 0.0f };
		glm::vec2 size = { 0.0f,0.0f };
		float rotation = 0.0f;
	};
}