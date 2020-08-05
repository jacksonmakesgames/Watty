#include <utils/Stats.h>
namespace letc {
	int Stats::m_framesPerSecond =0;
	int Stats::m_updatesPerSecond =0;
	double Stats::m_msPerFrame =0;

	Stats::Stats(){
		m_framesPerSecond = 0;
		m_updatesPerSecond = 0;
		m_msPerFrame = 0;
	}

	void Stats::engineUpdate(unsigned int framesThisSec, unsigned int updates) {
		m_framesPerSecond = framesThisSec;
		m_updatesPerSecond = updates;
		m_msPerFrame = 1000.0 / (double)framesThisSec;
	}

}