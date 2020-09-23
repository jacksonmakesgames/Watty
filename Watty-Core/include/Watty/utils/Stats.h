#pragma once
#include <GLFW/glfw3.h>
namespace letc {
	class Stats {
	private:
		static int m_framesPerSecond, m_updatesPerSecond;
		static double m_msPerFrame;

	public:
		Stats();
		static void engineUpdate(unsigned int framesThisSec, unsigned int updates);
		static unsigned int getFramesPerSecond()  { return m_framesPerSecond; }
		static unsigned int getUpdatesPerSecond() { return m_updatesPerSecond; }
		static double getMSPerFrame() { return m_msPerFrame; }
	};
}