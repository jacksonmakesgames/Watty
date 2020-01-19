#pragma once
#include "../renderable2d.h"
#include "../../utils/timer.h"
#include <vector>
#include "../../math/math.h"

namespace letc { namespace graphics {
	class Animation2D
	{
	protected:
		float rate;
		bool loop;
		bool done = false;
		Timer time;
		float nextUpdateTime = 0;
		std::string name;
		Renderable2D* objectsRenderable;

	public:
		virtual void play(){}
		virtual void update(){}
		virtual void stop(){}

		inline std::string getName() { return name; }
		inline void setRenderable(Renderable2D* renderable) { objectsRenderable = renderable; }

		Animation2D(std::string animationName, float playbackRate, bool loop = false): time(Timer()), name(animationName), loop(loop), rate(playbackRate) {}

	};

	

} }
