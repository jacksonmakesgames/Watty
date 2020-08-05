#pragma once
#include <GLFW/glfw3.h>
namespace letc {
	static class Timer {
	public:
		static double delta;
	private:
		static double m_startTime;
		static double m_last;
		static double _lastFrameTime;
		static double currentFrameTime;
	public:
		Timer();

		static void reset();
		static float elapsed(); 
		static void update();
		
	};
}