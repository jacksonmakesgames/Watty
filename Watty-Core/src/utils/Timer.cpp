#include <utils/timer.h>
namespace watty {
	double Timer::delta = 0;

	double Timer::m_startTime = 0;
	double Timer::m_last = 0;
	double Timer::_lastFrameTime = 0;
	double Timer::currentFrameTime = 0;

	Timer::Timer() {
		m_startTime = glfwGetTime();
	}

	void Timer::reset() {
		m_startTime = glfwGetTime();
	}

	float Timer::elapsed() {
		// return elapsed time in seconds
		currentFrameTime = glfwGetTime();
		return (currentFrameTime - m_startTime);
	}

	void Timer::update() {
		currentFrameTime = glfwGetTime();
		if (_lastFrameTime > 0)
			delta = currentFrameTime - _lastFrameTime;
		else
			delta = 0.02;
		_lastFrameTime = glfwGetTime();
	}
}