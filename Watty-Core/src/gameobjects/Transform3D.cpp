#include <gameobjects/Transform3D.h>

namespace letc {
	Transform3D::Transform3D(GameObject3D* go, glm::vec3 pos, glm::vec3 scale, float rot) : position(pos), size(scale), gameObject(go)
	{
		updateMatrix();

	}

	Transform3D::Transform3D(GameObject3D* go, Transform3D* parentTransform) : parent(parentTransform), gameObject(go)
	{
		updateMatrix();
	}

	Transform3D::Transform3D(GameObject3D* go) : parent(nullptr), gameObject(go)
	{
		updateMatrix();
	}

	void Transform3D::rotate(float angle, glm::vec3 axis)
	{
		//TODO
		updateMatrix();
	}

	void Transform3D::setRotation(float newRotation, glm::vec3 axis)
	{
		//TODO
		updateMatrix();
	}

	float Transform3D::getRotation(glm::vec3 axis)
	{
		//TODO
		return 0;
	}

	void Transform3D::translate(glm::vec3 translation)
	{
		position += translation;
		updateMatrix();
	}

	void Transform3D::setPosition(glm::vec3 newPos)
	{
		position = newPos;
		updateMatrix();
	}

	glm::vec3 Transform3D::getPosition()
	{
		return position;
	}

	void Transform3D::grow(glm::vec3 sizeDelta)
	{
		size += sizeDelta;
		updateMatrix();
	}

	void Transform3D::setSize(glm::vec3 newSize)
	{
		size = newSize;
		updateMatrix();
	}

	glm::vec3 Transform3D::getSize()
	{
		return size;
	}

	glm::vec3 Transform3D::getParentOffset()
	{
		return parentOffset;
	}

	
	void Transform3D::setParentOffset(glm::vec3 newParentOffset)
	{
		parentOffset = newParentOffset;
	}

	
	void Transform3D::updateMatrix()
	{

		transformMatrix = glm::mat4(1.0f);

		glm::vec3 drawPosition = { 
			position.x,
			position.y,
			position.z
		};
		
	
		// if local:
		if(parent!=nullptr)
			transformMatrix = glm::translate(transformMatrix, glm::vec3(0.25f * parent->getSize().x, 0.25f * parent->getSize().y, parent->getSize().z));

		drawPosition.x -= .5f * size.x;
		drawPosition.y -= .5f * size.y;
		drawPosition.z -= .5f * size.z;
		
	

		//Position
		transformMatrix = glm::translate(transformMatrix, drawPosition);

		//Rotation TODO
	/*	transformMatrix = glm::translate(transformMatrix, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
		transformMatrix = glm::rotate(transformMatrix, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		transformMatrix = glm::translate(transformMatrix, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));*/

		//Scale
		transformMatrix = glm::scale(transformMatrix, size);

	}

	Transform3D* Transform3D::getParent()
	{
		return parent;
	}

	void Transform3D::setParent(Transform3D* newParent)
	{
		parent = newParent;
		//parentOffset = parent->getPosition() - (position);
		//parentOffset = (parent->getPosition()-.5f*parent->getSize()) - position;
		parent->addChild(this);
		updateMatrix();
	}

	Transform3D* Transform3D::getChild(int index)
	{
		return children[index];
	}

	void Transform3D::addChild(Transform3D* child)
	{
		child->parent = this;
		child->parentOffset = position - child->getPosition();
		child->updateMatrix();
		//child->parentOffset = (position) - (child->getPosition() - .5f * child->getSize());
		//child->parentOffset = position - (child->getPosition());
		children.push_back(child);
	}

	void Transform3D::removeChild(Transform3D* child)
	{
		for (size_t i = 0; i < children.size(); i++)
		{
			if (child == children[i])
				children.erase(children.begin() + i);
		}
	
	}

	void Transform3D::removeChild(int index)
	{
		children.erase(children.begin() + index);
	}

	void Transform3D::lookAt(Transform3D& transform)
	{
		//TODO:
		//glm::mat4 lookMat = glm::look(glm::vec3(position.x, position.y, 0), { transform.position.x, transform.position.y, 0 }, { 0,1,0 });
		//transformMatrix *= lookMat;
	}
	Transform3D::~Transform3D()
	{
		for (size_t i = 0; i < children.size(); i++)
		{
			delete(children[i]);
		}
	}
}