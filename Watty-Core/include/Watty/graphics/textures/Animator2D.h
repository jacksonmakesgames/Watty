#pragma once
#include "Animation2D.h"
#include <map>
namespace watty {namespace graphics{
	class Animator2D{
	protected:
		bool isPlaying = false;
	public:
		std::map<std::string, Animation2D*> animations;
	private:
		Renderable2D* m_objectsRenderable;
		std::string m_currentAnimationName;
		
	public:
		Animator2D(Renderable2D* renderable);
		void play(std::string name);
		void stop();
		void update();
		Animation2D* addAnimation(Animation2D* animation);

		Animation2D* findByName(std::string name);

		inline std::string getCurrentAnimation() { return m_currentAnimationName; }
	private:

	};
}}