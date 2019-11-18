#pragma once

namespace letc {
	class Timer {
	private:
		double m_startTime;

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

	};
}