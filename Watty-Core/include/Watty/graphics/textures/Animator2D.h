#pragma once
#include "Animation2D.h"
#include <graphics/textures/Animator.h>
#include <map>
namespace letc {namespace graphics{
	class Animator2D : public Animator{
	protected:
		bool isPlaying = false;
	public:
		std::map<std::string, Animation2D*> animations;
	private:
		Renderable2D* m_objectsRenderable;
		std::string m_currentAnimationName;
		
	public:
		Animator2D(Renderable2D* renderable);
		void addAnimation(Animation2D* animation);

	private:

	};
}}