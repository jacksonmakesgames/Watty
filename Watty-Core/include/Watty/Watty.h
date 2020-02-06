#pragma once

#include "ext/glm/include/glm.hpp"
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
#include "./graphics/Camera.h"
#include "./graphics/Color.h"
#include "./graphics/textures/SpriteSheetAnimation.h"
#include <graphics/ParticleSystem.h>

#include "gameobjects/GameObject.h"
#include "./utils/timer.h"
#include "./utils/Random.h"
#include "ext/Box2D/Box2D.h"
#include "./physics/QueryAABBCallback.h"
#include "ext/imgui/include/imgui/imgui.h"


bool letc::graphics::Window::useVSync = false;


namespace letc {

	class LETC {
	public:
		Timer* gameTimer;
		std::vector<Layer*> layers;
		bool debugPhysics = false;
		bool resetFlag = false;
		graphics::Camera* sceneCamera;

	private:
		graphics::Window* m_window;
		Timer* m_time;
		int m_framesPerSecond, m_updatesPerSecond;
		double m_msPerFrame;
		unsigned int updates = 0;

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
			std::cout << "Error: could not find layer: " << name << std::endl;
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

		graphics::Window* createWindow(const char* title, int width, int height, bool resizeable = true, bool fullscreen=false) {
			m_window = new graphics::Window(title, width, height, resizeable, fullscreen);

			float aspectRatio = width / height;

			sceneCamera = new graphics::Camera(&layers, glm::vec3(0.0f, 0.0f, -10.0f), glm::vec2(32, 18), 20, graphics::CameraMode::orthographic); //TODO we should calculate width and height in meters and allow the user to change camera modes once we support 3D
			return m_window;
		}

		
		// runs on initialization
		virtual void init() = 0;

		// runs once per second
		virtual void tick() {}

		// runs LETC_UPDATE_RATE times per second
		virtual void update() {
			updates++;

			gameTimer->update();


			for (size_t i = 0; i < layers.size(); i++)
			{
				layers[i]->update();
			}
			if (resetFlag) { // is this for conways? we should move it 
				reset();
				resetFlag = false;
			}

			// For now, if there is more than one camera, ignore the default "Scene Camera"
			size_t i = graphics::Camera::allCameras.size() > 1 ? 1 : 0;
			
			for (i; i < graphics::Camera::allCameras.size(); i++)
			{
				graphics::Camera::allCameras[i]->update();
			}
		}

		// runs as fast as possible (unless vsync is enabled, then it runs at refresh rate)
		virtual void render() {
			for (size_t i = 0; i < layers.size(); i++){
				layers[i]->draw();
			}
			m_window->listenForInput();

		}

		const unsigned int getFramesPerSecond()  const  { return m_framesPerSecond;  }
		const unsigned int getUpdatesPerSecond() const  { return m_updatesPerSecond; }
		const double getMSPerFrame() const  { return m_msPerFrame; }

private:
	void run() {
		Random::init();
		letc::physics::DebugPhysics::init(&(sceneCamera->position));
		letc::physics::PhysicsWorld2D::setDebugDraw();
		m_time = new Timer();
		float timer = 0.0f;
		float updateTimer = 0.0f;
		float updateTick = 1.0 / m_window->getRefreshRate();
		unsigned int frames = 0;
		while (!m_window->closed()) {
			m_window->clear();
			if (m_time->elapsed() - updateTimer > updateTick) {
				if (m_window->useVSync) update(); // With Vsync enabled, update at the refresh rate of the window
				updateTimer += updateTick;
			}

			if (!m_window->useVSync) update(); // With Vsync disabled, update as fast as possible
			frames++;
			render();
			m_window->update();
			
			if ((m_time->elapsed() - timer) > 1.0f) {
				timer += 1.0f;
				m_framesPerSecond = frames;
				m_updatesPerSecond = updates;
				m_msPerFrame = 1000.0 / (double)frames;
				
				tick();
				std::cout <<"\t"<< std::to_string(getFramesPerSecond()) << "fps | " << std::to_string(getMSPerFrame()) << "mspf \r" << std::flush;

				frames = 0;
				updates = 0;
			}
		}
	}
	};
	letc::graphics::DebugRenderer* letc::physics::DebugPhysics::renderer = nullptr;
	letc::graphics::Shader* letc::physics::DebugPhysics::m_shader = nullptr;
	glm::vec3* letc::physics::DebugPhysics::m_sceneCameraPosition = nullptr;

}