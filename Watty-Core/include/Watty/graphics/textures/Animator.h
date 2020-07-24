#pragma once
#include "Animation.h"
#include <map>
namespace letc {namespace graphics{
	class Animator{
	protected:
		bool isPlaying = false;
	public:
		std::map<std::string, Animation*> animations;
	private:
		Renderable* m_objectsRenderable;
		std::string m_currentAnimationName;
		
	public:
		Animator();
		virtual void play(std::string name);
		virtual void stop();
		virtual void update();
		virtual void addAnimation(Animation* animation);

		Animation* findByName(std::string name);

		inline std::string getCurrentAnimation() { return m_currentAnimationName; }
	private:

	};
}}