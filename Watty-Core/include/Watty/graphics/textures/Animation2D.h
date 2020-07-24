#pragma once
#include <graphics/renderable2d.h>
#include <utils/timer.h>
#include <graphics/textures/Animation.h>

namespace letc { namespace graphics {
	class Animation2D : public Animation
	{
	protected:
		Renderable2D* objectsRenderable;
		FrameInfo m_frameInfo;

	public:

		virtual void play(){}
		virtual void update(){}
		virtual void stop(){}

		inline virtual bool isDone() { return done; }
		inline std::string getName() { return name; }
		inline void setRenderable(Renderable2D* renderable) { objectsRenderable = renderable; }
		inline FrameInfo getCurrentFrameInfo() { return m_frameInfo; }
		inline int getMinFrame() { return m_minFrame; }
		inline int getMaxFrame() { return m_maxFrame; }

		Animation2D(std::string animationName, float playbackRate, bool loop = false): Animation(animationName,loop, playbackRate) {}

	};

	

} }
