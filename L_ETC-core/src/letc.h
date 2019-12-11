#pragma once

#include "./math/math.h"
#include "./graphics/window.h"
#include "./graphics/sprite.h"
#include "./graphics/font/label.h"
#include "./graphics/renderer2d.h"
#include "./graphics/batchrenderer2d.h"
#include "./graphics/shader.h"
#include "./graphics/layers/layer.h"
#include "./graphics/layers/GuiLayer.h"
#include "./graphics/layers/EngineControlLayer.h"
#include "./graphics/layers/GridLayer.h"

#include "./utils/timer.h"
#include "../ext/Box2D/Box2D.h"
#include "./physics/QueryAABBCallback.h"
#include "GameObject.h"

#include <imgui/imgui.h>

#define LETC_UPDATE_RATE 144.0f


namespace letc {
	class LETC {
	public:
		Timer* gameTimer;
		std::vector<Layer*> layers;
		bool debugPhysics = false;
		bool resetFlag = false;

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

		void initPhysics() {
		}

		virtual void reset() {};

		Layer* getLayerByName(std::string name) {

			for (Layer* layer : layers) {
				if (layer->name == name) return layer;
			}
		
			return nullptr;
		}


	protected:
		LETC(){
			gameTimer = new Timer();
			m_framesPerSecond  =	0;
			m_updatesPerSecond =	0;
			m_msPerFrame =	0;
		}
		
		virtual ~LETC() {
			delete m_window;
			delete m_time;
			for (size_t i = 0; i < layers.size(); i++)
				delete layers[i];
		}

		graphics::Window* createWindow(const char* title, int width, int height) {
			m_window = new graphics::Window(title, width, height);
			return m_window;
		}

		
		// runs on initialization
		virtual void init() = 0;

		// runs once per second
		virtual void tick() {}

		// runs LETC_UPDATE_RATE times per second
		virtual void update() {
			gameTimer->update();
			for (size_t i = 0; i < layers.size(); i++)
			{
				layers[i]->update();
			}
			if (resetFlag) {
				reset();
				resetFlag = false;
			}
		}

		// runs as fast as possible (unless vsync is enabled, then it runs at refresh rate)
		virtual void render() {
			for (size_t i = 0; i < layers.size(); i++){
				layers[i]->draw();
			}
		}

		const unsigned int getFramesPerSecond()  const  { return m_framesPerSecond;  }
		const unsigned int getUpdatesPerSecond() const  { return m_updatesPerSecond; }
		const double getMSPerFrame() const  { return m_msPerFrame; }

private:
	void run() {
		m_time = new Timer();
		float timer = 0.0f;
		float updateTimer = 0.0f;
		float updateTick = 1.0 / LETC_UPDATE_RATE;
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