#pragma once
#include <glm.hpp>

#ifdef WATTY_EMSCRIPTEN
	#define GLFW_INCLUDE_ES3
	#define GL_GLEXT_PROTOTYPES
	#include <emscripten.h>
#undef GL_WITH_GLAD
#endif

#ifdef WATTY_OPENGL
	#include "./graphics/window.h"

	#include <graphics/font/label.h>

	#include <graphics/renderer2d.h>
	#include <graphics/batchrenderer2d.h>
	#include <graphics/shader.h>
	#include <graphics/Camera.h>
	#include <graphics/textures/SpriteSheetAnimation.h>
	#include <ft2build.h>
#endif
bool letc::graphics::Window::useVSync = false;


#include <levels/Level2D.h>
#include <levels/Level3D.h>

#include <graphics/tilemap/TileMap.h>
#include <physics/MapBodyBuilder.h>
#include <graphics/sprite.h>
#include <graphics/layers/layer.h>
#include <graphics/layers/GUILayer.h>
#include <graphics/layers/DebugPhysicsLayer.h>
#include <graphics/layers/EngineControlLayer.h>
#include <graphics/layers/GridLayer.h>
#include <graphics/ParticleSystem.h>
#include <graphics/Color.h>
#include <math/math.h>

#include "gameobjects/GameObject2D.h"
//#include "gameobjects/GameObject3D.h"
#include <utils/timer.h>
#include <utils/Random.h>
#include <physics/QueryAABBCallback.h>
#include <imgui.h>

//Should be last so it is only included once!
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_TRUETYPE_IMPLEMENTATION
#define STBTT_STATIC
#include <stb_truetype.h>


#ifdef WATTY_EMSCRIPTEN
	static void start_main(void* funcPtr) {
		std::function<void()>* func = (std::function<void()>*)funcPtr;
		(*func)();
	}
#endif // WATTY_EMSCRIPTEN


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

		std::vector<const Level*> mLevels;


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

		std::vector<const Level*> getLevels();
		const Level2D* newLevel2D(Level2DProperties levelProps);
		//const Level3D* newLevel3D(Level3DProperties levelProps);

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

		
		// Runs on initialization
		virtual void init() = 0;


		// Runs once per second
		virtual void tick() {
			std::cout << "\t" << std::to_string(getFramesPerSecond()) << "fps | " << std::to_string(getMSPerFrame()) << "mspf \r" << std::flush;
		}


		// Runs as fast as possible
		virtual void update() {
			updates++;
			gameTimer->update();

			physics::PhysicsWorld2D::step(gameTimer->delta);


			for (size_t i = 0; i < layers.size(); i++)
			{
				layers[i]->update();
			}
			if (resetFlag) { // not sure this is worth having in the main update load
				reset();
				resetFlag = false;
			}

			// For now, if there is more than one camera, ignore the default "Scene Camera"
			size_t i = graphics::Camera::allCameras.size() > 1 ? 1 : 0;
			
			for (i = i; i < graphics::Camera::allCameras.size(); i++)
			{
				graphics::Camera::allCameras[i]->update();
			}
		}

		// runs as fast as possible (unless vsync is enabled, then it runs at refresh rate)
		virtual void render() {
			m_window->clear(); { // One frame

				ImGui_ImplOpenGL3_NewFrame();
				ImGui_ImplGlfw_NewFrame();
				ImGui::NewFrame();

#ifdef DEBUG 
				if(getLayerByName("Debug Physics Layer"))
					debugPhysics ? 
					getLayerByName("Debug Physics Layer")->enable() : getLayerByName("Debug Physics Layer")->disable();
#endif

				for (size_t i = 0; i < layers.size(); i++){
					layers[i]->draw();
				}
				m_window->listenForInput();

				ImGui::Render();
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

				// ImGui Multiple Viewports:
				if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
					GLFWwindow* backup_current_context = glfwGetCurrentContext();
					ImGui::UpdatePlatformWindows();
					ImGui::RenderPlatformWindowsDefault();
					glfwMakeContextCurrent(backup_current_context);
				}

			}m_window->update(); // End frame, swap buffers

		}

		const unsigned int getFramesPerSecond()  const  { return m_framesPerSecond;  }
		const unsigned int getUpdatesPerSecond() const  { return m_updatesPerSecond; }
		const double getMSPerFrame() const  { return m_msPerFrame; }

private:
	void run() {
		Random::init();

#ifdef DEBUG 
		letc::physics::DebugPhysics::init(&(sceneCamera->position), &(sceneCamera->getSize()));
		letc::physics::PhysicsWorld2D::setDebugDraw();
		layers.push_back(new graphics::DebugPhysicsLayer(*sceneCamera, *m_window));
		layers.push_back(new graphics::GridLayer(*sceneCamera, *m_window));
		layers.push_back(new graphics::EngineControlLayer("Engine Control", debugPhysics, resetFlag, &graphics::Window::useVSync, layers));

#endif
		m_time = new Timer();
		float timer = 0.0f;
		float updateTimer = 0.0f;
		float updateTick = 1.0 / m_window->getRefreshRate();
		unsigned int frames = 0;

#ifdef WATTY_EMSCRIPTEN
		if (m_window->getRefreshRate() < 1) 
			updateTick = 1 / 60.0f; // in WebGL, refresh rate can be 0
		
		std::function<void()> mainLoop = [&]() {
#else
		while (!m_window->closed()) {
#endif 
			update(); // Physics frame (run as fast as possible)

			if (m_time->elapsed() - updateTimer > updateTick) {
				if (m_window->useVSync) render(); // With Vsync enabled, render at the refresh rate of the window
				updateTimer += updateTick;
			}
			if (!m_window->useVSync)
				render(); // as fast as possible

			frames++;
			
			// Timing/FPS
			if ((m_time->elapsed() - timer) > 1.0f) {
				timer += 1.0f;
				m_framesPerSecond = frames;
				m_updatesPerSecond = updates;
				m_msPerFrame = 1000.0 / (double)frames;
				tick();
				frames = 0;
				updates = 0;
			}


#ifdef WATTY_EMSCRIPTEN
		};
		emscripten_set_main_loop_arg(start_main, &mainLoop, 0, 1);
#else
		}
#endif // WATTY_EMSCRIPTEN

	}
	};

	letc::graphics::DebugRenderer* letc::physics::DebugPhysics::renderer = nullptr;
	letc::graphics::Shader* letc::physics::DebugPhysics::m_shader = nullptr;
	const glm::vec3* letc::physics::DebugPhysics::m_sceneCameraPosition = nullptr;
	const glm::vec2* letc::physics::DebugPhysics::m_sceneCameraScale = nullptr;



	std::vector<const Level*> LETC::getLevels() {
		return mLevels;
	}

	const Level2D* LETC::newLevel2D(Level2DProperties levelProps)
	{
		return nullptr;
	}


}