#include "..\..\..\..\include\Watty\graphics\textures\Animator.h"
#include <graphics/textures/Animator.h>
namespace letc {namespace graphics {
	Animator::Animator(Renderable* renderable) : m_objectsRenderable(renderable)
	{
	}


	void Animator::play(std::string name)
	{
		// Already playing an animation other than current
		if (isPlaying && m_currentAnimationName!=name) 
			findByName(m_currentAnimationName)->stop();
		
		isPlaying = true;


		Animation* animation = findByName(name);
		if (animation == nullptr) return;
		animation->play();
		m_currentAnimationName = name;
	}

	void Animator::stop()
	{
		if (m_currentAnimationName.empty()) {
			std::cout << "Cannot stop animation: none currently playing" << std::endl;
			return;
		}
		Animation* animation = findByName(m_currentAnimationName);
		if (animation != nullptr) {
			animation->stop();
			isPlaying = false;
		}
	}

	void Animator::update()
	{
		if (m_currentAnimationName.empty()) {
			std::cout << "Cannot update animation: none currently playing" << std::endl;
			return;
		}
		Animation* animation = findByName(m_currentAnimationName);
		if (animation != nullptr) {
			animation->update();
			if (!animation->isDone())isPlaying = true;
			else isPlaying = false;
		}


	}

	void Animator::addAnimation(Animation* animation)
	{
		if (findByName(animation->getName()) != nullptr) {
			std::cout << "Animation: <" << animation->getName() << "> already existed in animator, not adding duplicate" << std::endl;
			return;
		}
		animation->setRenderable(m_objectsRenderable);
		animations[animation->getName()] = animation;
	}

	Animation* Animator::findByName(std::string name)
	{
		if (!(animations.count(name))) { // if the animation exists in our map
			return nullptr;
		}

		auto iter = animations.find(name);
		return iter->second;
	}


}}