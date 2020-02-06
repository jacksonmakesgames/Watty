#include <graphics/textures/Animator2D.h>
namespace letc {namespace graphics {
	Animator2D::Animator2D(Renderable2D* renderable)
		:m_objectsRenderable(renderable)
	{

	}

	void Animator2D::play(std::string name)
	{
		Animation2D* animation = findByName(name);
		if (animation == nullptr) return;
		m_currentAnimationName = name;
		animation->play();
	}

	void Animator2D::stop()
	{
		if (m_currentAnimationName.empty()) {
			std::cout << "Cannot stop animation: none currently playing" << std::endl;
			return;
		}
		Animation2D* animation = findByName(m_currentAnimationName);
		if (animation != nullptr)
			animation->stop();
	}

	void Animator2D::update()
	{
		if (m_currentAnimationName.empty()) {
			std::cout << "Cannot update animation: none currently playing" << std::endl;
			return;
		}
		Animation2D* animation = findByName(m_currentAnimationName);
		if (animation != nullptr)
			animation->update();


	}

	void Animator2D::addAnimation(Animation2D* animation)
	{
		if (findByName(animation->getName()) != nullptr) {
			std::cout << "Animation: <" << animation->getName() << "> already existed in animator, not adding duplicate" << std::endl;
			return;
		}
		animation->setRenderable(m_objectsRenderable);
		animations[animation->getName()] = animation;
	}

	Animation2D* Animator2D::findByName(std::string name)
	{
		if (!(animations.count(name))) { // if the animation exists in our map
			return nullptr;
		}

		auto iter = animations.find(name);
		return iter->second;
	}


}}