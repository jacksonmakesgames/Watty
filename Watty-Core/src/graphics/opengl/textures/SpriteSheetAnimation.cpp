#include <graphics/textures/SpriteSheetAnimation.h>
namespace letc { namespace graphics {

	SpriteSheetAnimation::SpriteSheetAnimation(SpriteSheetAnimInfo info)
		: Animation2D(info.name, info.playbackRate, info.loop),
		m_currentFrame(0),
		m_info(info)
	{
		determineFrames();
		m_currentFrame = m_minFrame;

	}

	SpriteSheetAnimation::~SpriteSheetAnimation(){
	}

	void SpriteSheetAnimation::determineFrames() {
		//Just Row Override
		if (m_info.row != -1 && m_info.col == -1) {
			m_numberOfFrames = m_info.numberOfCols;
			m_minFrame = m_info.row * m_info.numberOfCols;
			m_maxFrame = m_minFrame + m_info.numberOfCols-1;

		}
		// Just Col Override
		else if (m_info.col != -1 && m_info.row == -1) {
			m_numberOfFrames = m_info.numberOfRows;
			m_minFrame = m_info.col * m_info.numberOfRows;
			m_maxFrame = m_minFrame + m_info.numberOfCols-1;
		}
		// Both Override: One Frame
		else if (m_info.row != -1 && m_info.col != -1) {
			m_numberOfFrames = 1;
			//int frame = (m_info.row * (m_info.numberOfCols - 1)) + (m_info.col * (m_info.numberOfRows - 1));
			int frame = ((m_info.row-1) * (m_info.numberOfCols) + (m_info.col));
			m_minFrame = frame;
			m_maxFrame = frame;
		}
		// No Override
		else{
			
			m_numberOfFrames = m_info.numberOfCols * m_info.numberOfRows;
			m_minFrame = 0;
			m_maxFrame = m_numberOfFrames - 1;
		}

	}

	void SpriteSheetAnimation::play(){
		if (done)
			m_currentFrame = m_minFrame;
		done = false;
		nextUpdateTime = time.elapsed();

	}

	void SpriteSheetAnimation::update()
	{
		if (done) return;
		if (time.elapsed() >= nextUpdateTime)
		{
			nextUpdateTime = time.elapsed() + 1.0f / rate;

			m_frameInfo = {
				(float)m_currentFrame, 
				(float)m_numberOfFrames,
				m_info.numberOfRows, 
				m_info.numberOfCols
			};

			if (objectsRenderable != nullptr)
				objectsRenderable->setFrameInfo(m_frameInfo);
			
			m_currentFrame++;
			if (m_currentFrame > m_maxFrame && loop) { m_currentFrame = m_minFrame;  }
			else if (!loop) done = true;
		}
	}

	void SpriteSheetAnimation::stop(){
		m_currentFrame = m_minFrame;
		done = true;
	}


} }