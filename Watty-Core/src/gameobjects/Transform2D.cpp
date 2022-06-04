#include "../../include/Watty/gameobjects/Transform2D.h"
namespace watty {
	Transform2D::Transform2D(GameObject* go, glm::vec2 pos, glm::vec2 scale, float rot) : position(pos), size(scale), rotation(rot), gameObject(go)
	{
		updateMatrix();

	}

	Transform2D::Transform2D(GameObject2D* go, Transform2D* parentTransform) : Transform(), gameObject(go)
	{
		setParent(parentTransform);
		updateMatrix();
	}

	Transform2D::Transform2D(GameObject2D* go) : Transform(), gameObject(go)
	{
		updateMatrix();
	}

	// For ECS
	Transform2D::Transform2D() : parent(nullptr), position({ 0,0 }), size({1,1}), rotation(0), transformMatrix(glm::mat4(1)), gameObject(nullptr)
	{
		updateMatrix();
	}

	void Transform2D::rotate(float angle)
	{
		rotation += angle;
		updateMatrix();
	}

	void Transform2D::setRotation(float newRotation)
	{
		rotation = newRotation;
		updateMatrix();
	}

	float Transform2D::getRotation()
	{
		return rotation;
	}

	void Transform2D::translate(glm::vec2 translation){
		wantsPhysicsMove = true;
		position += translation;
		physicsMoveTo = position;
		updateMatrix();
	}

	void Transform2D::setPosition(glm::vec2 newPos, bool movePhysicsBody)
	{
		if (movePhysicsBody) {
			wantsPhysicsMove = true;
			physicsMoveTo = newPos;
		}
		position = newPos;
		updateMatrix();
	}

	glm::vec2 Transform2D::getPosition()
	{
		return position;
	}

	void Transform2D::grow(glm::vec2 sizeDelta)
	{
		size += sizeDelta;
		updateMatrix();
	}

	void Transform2D::setSize(glm::vec2 newSize)
	{
		size = newSize;
		updateMatrix();
	}

	glm::vec2 Transform2D::getSize()
	{
		return size;
	}

	glm::vec2 Transform2D::getParentOffset()
	{
		return parentOffset;
	}

	
	void Transform2D::setParentOffset(glm::vec2 newParentOffset)
	{
		parentOffset = newParentOffset;
	}

	
	void Transform2D::updateMatrix()
	{

		transformMatrix = glm::mat4(1.0f);

		glm::vec3 drawPosition = { 
			position.x,
			position.y,
			0.0f
		};
		
		Transform2D* parent2D = (Transform2D*) parent;
		// if local:
		if(parent!=nullptr)
			transformMatrix = glm::translate(transformMatrix, glm::vec3(0.25f * parent2D->getSize().x, 0.25f * parent2D->getSize().y, 0.0f));

		drawPosition.x -= .5f * size.x;
		drawPosition.y -= .5f * size.y;
		
	

		//Position
		transformMatrix = glm::translate(transformMatrix, drawPosition);

		//Rotation
		transformMatrix = glm::translate(transformMatrix, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
		transformMatrix = glm::rotate(transformMatrix, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		transformMatrix = glm::translate(transformMatrix, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

		//Scale
		transformMatrix = glm::scale(transformMatrix, glm::vec3(size, 1.0f));

	}



	void Transform2D::addChild(Transform* child)
	{
		Transform2D* child2D = (Transform2D*) child;
		child2D->setParent(this);
		child2D->setParentOffset(position - child2D->getPosition());
		child2D->updateMatrix();
		children.push_back(child2D);
	}


	void Transform2D::lookAt(Transform2D& transform)
	{
		//TODO: Test!
		//glm::mat4 lookMat = glm::look(glm::vec3(position.x, position.y, 0), { transform.position.x, transform.position.y, 0 }, { 0,1,0 });
		//transformMatrix *= lookMat;
	}
	Transform2D::~Transform2D()
	{
		for (size_t i = 0; i < children.size(); i++)
		{
			delete(children[i]);
		}
	}
}