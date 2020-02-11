#include "../../include/Watty/gameobjects/Transform2D.h"
namespace letc {
	Transform2D::Transform2D(GameObject* go, glm::vec2 pos, glm::vec2 scale, float rot) : position(pos), size(scale), rotation(rot), gameObject(go)
	{
		updateMatrix();

	}

	Transform2D::Transform2D(GameObject* go, Transform2D* parentTransform) : parent(parentTransform), gameObject(go)
	{
		updateMatrix();
	}

	Transform2D::Transform2D(GameObject* go) : parent(nullptr), gameObject(go)
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

	void Transform2D::translate(glm::vec2 translation)
	{
		position += translation;
		updateMatrix();
	}

	void Transform2D::setPosition(glm::vec2 newPos)
	{
		position = newPos;
		updateMatrix();
	}

	glm::vec2 Transform2D::getPosition()
	{
		return position;
	}

	void Transform2D::resize(glm::vec2 sizeDelta)
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

	void Transform2D::setMatrix(glm::mat4 newMatrix)
	{
		transformMatrix = newMatrix;
	}

	glm::mat4 Transform2D::getMatrix()
	{
		return transformMatrix;
	}

	void Transform2D::updateMatrix()
	{
		transformMatrix = glm::mat4(1.0f);

		glm::vec3 drawPosition = { 
			position.x,
			position.y,
			0.0f
		};
		
		// adjust position for size
		if (parent != nullptr) {
			/*drawPosition.x += .5f * parent->getSize().x;
			drawPosition.y += .5f * parent->getSize().y;*/
			drawPosition.x += .5f * size.x;
			drawPosition.y += .5f * size.y;
		}
		else {
			drawPosition.x -= .5f * size.x;
			drawPosition.y -= .5f * size.y;
		}


		//Position
		transformMatrix = glm::translate(transformMatrix, drawPosition);

		//Rotation
		transformMatrix = glm::translate(transformMatrix, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
		transformMatrix = glm::rotate(transformMatrix, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		transformMatrix = glm::translate(transformMatrix, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

		//Scale
		transformMatrix = glm::scale(transformMatrix, glm::vec3(size, 1.0f));

	}

	Transform2D* Transform2D::getParent()
	{
		return parent;
	}

	void Transform2D::setParent(Transform2D* newParent)
	{
		parent = newParent;
		//parentOffset = parent->getPosition() - (position);
		//parentOffset = (parent->getPosition()-.5f*parent->getSize()) - position;
		parent->addChild(this);
		updateMatrix();
	}

	Transform2D* Transform2D::getChild(int index)
	{
		return children[index];
	}

	void Transform2D::addChild(Transform2D* child)
	{
		child->parent = this;
		child->updateMatrix();
		//child->parentOffset = (position) - (child->getPosition() - .5f * child->getSize());
		//child->parentOffset = position - (child->getPosition());
		children.push_back(child);
	}

	void Transform2D::removeChild(Transform2D* child)
	{
		for (size_t i = 0; i < children.size(); i++)
		{
			if (child == children[i])
				children.erase(children.begin() + i);
		}
	
	}

	void Transform2D::removeChild(int index)
	{
		children.erase(children.begin() + index);
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