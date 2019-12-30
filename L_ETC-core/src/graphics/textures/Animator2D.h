#pragma once
#include "Animation2D.h"
#include <map>
namespace letc {namespace graphics{
	class Animator2D{
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
		void addAnimation(Animation2D* animation);

		Animation2D* findByName(std::string name);

		inline std::string getCurrentAnimation() { return m_currentAnimationName; }
	private:

	};
}}