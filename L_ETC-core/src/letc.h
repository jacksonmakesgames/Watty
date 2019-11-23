#pragma once
#include "math/math.h"

#include "graphics/window.h"
#include "graphics/sprite.h"
#include "graphics/font/label.h"
#include "graphics/renderer2d.h"
#include "graphics/batchrenderer2d.h"
#include "graphics/shader.h"
#include "graphics/layers/layer.h"
#include "graphics/layers/GUILayer.h"

#include "utils/timer.h"

namespace letc {
	class LETC {
	
	private:
		graphics::Window* m_window;
		Timer* m_time;
		int m_framesPerSecond, m_updatesPerSecond;
		double m_msPerFrame;

	public:
		void start() {
			init();
			run();
		}

	protected:
		LETC() {
			m_framesPerSecond  =	0;
			m_updatesPerSecond =	0;
			m_msPerFrame =	0;
		}
		
		virtual ~LETC() {
			delete m_window;
			delete m_time;
		}

		graphics::Window* createWindow(const char* title, int width, int height) {
			m_window = new graphics::Window(title, width, height);
			return m_window;
		}

		
		// runs on initialization
		virtual void init() = 0;

		// runs once per second
		virtual void tick() {}

		// runs 60 times per second
		virtual void update() {}

		// runs as fast as possible (unless vsync is enabled, then it runs at refresh rate)
		virtual void render() = 0;

		const unsigned int getFramesPerSecond()  const  { return m_framesPerSecond;  }
		const unsigned int getUpdatesPerSecond() const  { return m_updatesPerSecond; }
		const double getMSPerFrame() const  { return m_msPerFrame; }

private:
	void run() {
		m_time = new Timer();
		float timer = 0.0f;
		float updateTimer = 0.0f;
		float updateTick = 1.0 / 60.0f;
		unsigned int frames = 0;
		unsigned int updates = 0;
		while (!m_window->closed()) {
			m_window->clear();
			
			if (m_time->elapsed() - updateTimer > updateTick) {
				update();
				updateTimer += updateTick;
				updates++;
			}
			frames++;

			render();
			m_window->update();
			
			if ((m_time->elapsed() - timer) > 1.0f) {
				timer += 1.0f;
				m_framesPerSecond = frames;
				m_updatesPerSecond = updates;
				m_msPerFrame = 1000.0 / (double)frames;
				
				tick();
				frames = 0;
				updates = 0;
			}
		}
	}
	};

}