#pragma once
#include "../renderable2d.h"
#include "../../utils/timer.h"
#include <vector>
#include "../../math/math.h"

namespace letc { namespace graphics {
	class Animation2D
	{
	protected:
		bool done = false;
		float rate;
		bool loop;
		Timer time;
		float nextUpdateTime = 0;
		std::string name;
		Renderable2D* objectsRenderable;
		FrameInfo m_frameInfo;
		int m_minFrame;
		int m_maxFrame;


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

		Animation2D(std::string animationName, float playbackRate, bool loop = false): time(Timer()), name(animationName), loop(loop), rate(playbackRate) {}

	};

	

} }
