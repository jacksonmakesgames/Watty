#pragma once
#include "Animation2D.h"
namespace letc { namespace graphics {


class SpriteSheetAnimation : public Animation2D
{
public:
private:
	int m_textureWidth;
	int m_textureHeight;
	int m_numberOfFrames;
	int m_currentFrame;


	

public:
	SpriteSheetAnimation(std::string name, math::Vector2 textureSize, float playbackRate, int numberOfFrames, bool loop = false);
	~SpriteSheetAnimation();

	void play() override;
	void update() override;
	void stop() override;

private:

};
}
}