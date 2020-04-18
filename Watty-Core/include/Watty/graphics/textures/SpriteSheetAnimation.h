#pragma once
#include "Animation2D.h"
#include <algorithm>

namespace letc { namespace graphics {

struct SpriteSheetAnimInfo {
	const char* name;
	float playbackRate;
	int numberOfRows;
	int numberOfCols;
	bool loop = false;
	int row = -1;
	int col = -1;
};


class SpriteSheetAnimation : public Animation2D
{
public:
	
private:
	SpriteSheetAnimInfo m_info;
	int m_numberOfFrames;
	int m_currentFrame;

	

public:
	SpriteSheetAnimation(SpriteSheetAnimInfo info);
	~SpriteSheetAnimation();

	void play() override;
	void update() override;
	void stop() override;
	void determineFrames();
private:

};
}
}