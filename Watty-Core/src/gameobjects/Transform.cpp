#include <gameobjects/Transform.h>
namespace letc {
	void Transform::setMatrix(glm::mat4 newMatrix)
	{
		transformMatrix = newMatrix;
	}

	glm::mat4 Transform::getMatrix()
	{
		return transformMatrix;
	}


	Transform* Transform::getParent()
	{
		return parent;
	}

	void Transform::setParent(Transform* newParent)
	{
		parent = newParent;
		//parentOffset = parent->getPosition() - (position);
		//parentOffset = (parent->getPosition()-.5f*parent->getSize()) - position;
		parent->addChild(this);
		updateMatrix();
	}

	Transform* Transform::getChild(int index)
	{
		return children[index];
	}

	std::vector<Transform*> Transform::getChildren()
	{
		return children;
	}

	

	void Transform::removeChild(Transform* child)
	{
		for (size_t i = 0; i < children.size(); i++)
		{
			if (child == children[i])
				children.erase(children.begin() + i);
		}

	}

	void Transform::removeChild(int index)
	{
		children.erase(children.begin() + index);
	}

}
