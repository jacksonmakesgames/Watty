#include <graphics/textures/Animator2D.h>
namespace watty {namespace graphics {
	Animator2D::Animator2D(Renderable2D* renderable)
		:m_objectsRenderable(renderable)
	{

	}

	void Animator2D::play(std::string name)
	{
		// Already playing an animation other than current
		if (isPlaying && m_currentAnimationName!=name) 
			findByName(m_currentAnimationName)->stop();
		
		isPlaying = true;


		Animation2D* animation = findByName(name);
		if (animation == nullptr) return;
		animation->play();
		m_currentAnimationName = name;
	}

	void Animator2D::stop()
	{
		if (m_currentAnimationName.empty()) {
			std::cout << "Cannot stop animation: none currently playing" << std::endl;
			return;
		}
		Animation2D* animation = findByName(m_currentAnimationName);
		if (animation != nullptr) {
			animation->stop();
			isPlaying = false;
		}
	}

	void Animator2D::update()
	{
		if (m_currentAnimationName.empty()) {
			return;
		}
		Animation2D* animation = findByName(m_currentAnimationName);
		if (animation != nullptr) {
			animation->update();
			if (!animation->isDone())isPlaying = true;
			else isPlaying = false;
		}


	}

	Animation2D* Animator2D::addAnimation(Animation2D* animation)
	{
		if (findByName(animation->getName()) != nullptr) {
			std::cout << "Animation: <" << animation->getName() << "> already existed in animator, not adding duplicate" << std::endl;
			return animations[animation->getName()];
		}
		animation->setRenderable(m_objectsRenderable);
		animations[animation->getName()] = animation;
		return animations[animation->getName()];
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