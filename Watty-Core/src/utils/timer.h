#pragma once
#include "../../ext/GLFW/include/GLFW/glfw3.h"
namespace letc {
	class Timer {
	public:
		double delta;
	private:
		double m_startTime;
		double m_last = 0;
	public:
		Timer() {
			m_startTime = glfwGetTime();
		}

		void reset() {
			m_startTime = glfwGetTime();
		}

		float elapsed() {
		// return elapsed time in seconds
			double currentTime = glfwGetTime();
			return (currentTime - m_startTime);
		}

		void update() {
			delta = elapsed() - m_last;
			m_last = elapsed();
		}
		
	};
}