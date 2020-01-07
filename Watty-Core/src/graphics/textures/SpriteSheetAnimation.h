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

SpriteSheetAnimation::SpriteSheetAnimation(std::string animationName, math::Vector2 textureSize, float playbackRate, int numberOfFrames, bool loop)
	: Animation2D(animationName, playbackRate, loop),
	m_textureWidth(textureSize.y),
	m_textureHeight(textureSize.x),
	m_currentFrame(0),
	m_numberOfFrames(numberOfFrames)
{
}

SpriteSheetAnimation::~SpriteSheetAnimation()
{
}

inline void SpriteSheetAnimation::play()
{
	std::cout << "Playing animation: " << name << std::endl;

	done = false;

}

inline void SpriteSheetAnimation::update()
{
	if (done) return;
	if (time.elapsed() >= nextUpdateTime)
	{
		nextUpdateTime = time.elapsed() + 1.0f / rate;
		// set image after this
		FrameInfo info;
		info.currentFrame = m_currentFrame;
		info.totalFrames = m_numberOfFrames;
		if(objectsRenderable != nullptr)
			objectsRenderable->setFrameInfo(info);

		m_currentFrame++;
		if (m_currentFrame >= m_numberOfFrames && loop) m_currentFrame = 0;
		else if (!loop) done = true;
	}
}

inline void SpriteSheetAnimation::stop()
{
	std::cout << "Stopping animtation: " << name << std::endl;

} }
}