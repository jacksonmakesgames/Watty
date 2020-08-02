#pragma once
#include <GLFW/glfw3.h>
namespace letc {
	class Timer {
	public:
		double delta;
	private:
		double m_startTime;
		double m_last = 0;
		double _lastFrameTime = 0;
		double currentFrameTime=0;
	public:
		Timer() {
			m_startTime = glfwGetTime();
		}

		void reset() {
			m_startTime = glfwGetTime();
		}

		float elapsed() {
		// return elapsed time in seconds
			currentFrameTime = glfwGetTime();
			return (currentFrameTime - m_startTime);
		}

		void update() {
			currentFrameTime = glfwGetTime();
			delta = currentFrameTime - _lastFrameTime;
			_lastFrameTime = glfwGetTime();
		}
		
	};
}