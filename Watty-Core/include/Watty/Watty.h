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

#include <res/res_watty.h> // From Watty-Core

#include <input/Input.h>
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

#include <gameobjects/GameObject.h>
#include <utils/timer.h>
#include <utils/Random.h>
#include <utils/Stats.h>

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

	template <class T, class Enable = void>
	struct is_defined
	{
		static constexpr bool value = false;
	};

	template <class T>
	struct is_defined<T, std::enable_if_t<(sizeof(T) > 0)>>
	{
		static constexpr bool value = true;
	};

namespace letc {



	class LETC {
	public:
		bool debugPhysics = false;
		bool resetFlag = false;
		graphics::Camera* sceneCamera;
		unsigned int updates = 0;

	protected:
		graphics::Window* window;
	private:
		Timer* m_time;

		double t = 0.0;
		double fixedTimeStep = 0.02; // amount of time between updates/physics steps. Default was 0.02.
		double currentTime = Timer::elapsed();
		double accumulator = 0.0;

	public:
		void start() {
			preInit();
			init();
			run();
		}
		

		void initPhysics() {
		}

		virtual void preInit() {
			RawWattyResources::Init();
			Input::init();
			window = createWindow("Watty Game Engine", 1280, 720, true, false);
			new Layer("Default");
		}
		virtual void reset() {};

		


	protected:
		LETC(){
			Timer::Timer();
			Stats::Stats();
		}
		

		virtual ~LETC() {
			delete window;
			delete m_time;
			for (size_t i = 0; i < Layer::allLayers.size(); i++)
				delete Layer::allLayers[i];
		}

		graphics::Window* createWindow(const char* title, int width, int height, bool resizeable = true, bool fullscreen=false) {
			window = new graphics::Window(title, width, height, resizeable, fullscreen);

			float aspectRatio = width / height;

			sceneCamera = new graphics::Camera(&Layer::allLayers, glm::vec3(0.0f, 0.0f, -10.0f), glm::vec2(32, 18), 20, graphics::CameraMode::orthographic); //TODO we should calculate width and height in meters and allow the user to change camera modes once we support 3D
			return window;
		}

		

		
		// Runs on initialization
		virtual void init() = 0;


		// Runs once per second
		virtual void tick() {
			std::cout << "\t" << std::to_string(Stats::getFramesPerSecond()) << "fps | " << std::to_string(Stats::getMSPerFrame()) << "mspf \r" << std::flush;
		}

		virtual void OnGui() {}
		virtual void update() {};

		// Runs as fast as possible
		void engineUpdate() {
			
			double newTime = Timer::elapsed();
			double frameTime = newTime - currentTime;


			if (frameTime > 0.25)
				frameTime = 0.25;
			
			currentTime = newTime;
			accumulator += frameTime;

			while (accumulator >= fixedTimeStep)
			{
				Input::update();
				Input::listenForInput();

				Timer::update();

				updates++;
				//physics::PhysicsWorld2D::step(Timer::delta);
				physics::PhysicsWorld2D::step(fixedTimeStep);
				update();
				t += fixedTimeStep;
				accumulator -= fixedTimeStep;

				for (size_t i = 0; i < Layer::allLayers.size(); i++){
					Layer::allLayers[i]->update();
				}

				// For now, if there is more than one camera, ignore the default "Scene Camera"
				size_t i = graphics::Camera::allCameras.size() > 1 ? 1 : 0;
			
				for (i = i; i < graphics::Camera::allCameras.size(); i++){
					graphics::Camera::allCameras[i]->update();
				}
			}
		
		}

		// runs as fast as possible (unless vsync is enabled, then it runs at refresh rate)
		virtual void render() {
			window->clear(); { // One frame


				ImGui_ImplOpenGL3_NewFrame();
				ImGui_ImplGlfw_NewFrame();
				ImGui::NewFrame();

#ifdef DEBUG 
				if(Layer::getLayerByName("Debug Physics Layer"))
					debugPhysics ? 
					Layer::getLayerByName("Debug Physics Layer")->enable() : Layer::getLayerByName("Debug Physics Layer")->disable();
#endif
				for (size_t i = 0; i < Layer::allLayers.size(); i++){
					Layer::allLayers[i]->draw();
				}
				//window->listenForInput();

				OnGui();
				ImGui::Render();
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

				// ImGui Multiple Viewports:
				if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
					GLFWwindow* backup_current_context = glfwGetCurrentContext();
					ImGui::UpdatePlatformWindows();
					ImGui::RenderPlatformWindowsDefault();
					glfwMakeContextCurrent(backup_current_context);
				}

			}window->update(); // End frame, swap buffers

		}


private:
	void run() {
		Random::init();
		letc::physics::PhysicsWorld2D::box2DWorld->SetContactListener(new Physics2DContactListener());
#ifdef DEBUG 

		letc::physics::DebugPhysics::init(&(sceneCamera->position), &(sceneCamera->getSize()));
		letc::physics::PhysicsWorld2D::setDebugDraw();
		new graphics::DebugPhysicsLayer(*sceneCamera, *window);
		new graphics::GridLayer(*sceneCamera, *window);
		new graphics::EngineControlLayer("Engine Control", debugPhysics, resetFlag, &graphics::Window::useVSync, Layer::allLayers);

#endif
		m_time = new Timer();
		float timer = 0.0f;
		float updateTimer = 0.0f;
		float updateTick = 1.0 / window->getRefreshRate();
		unsigned int framesThisSec = 0;

#ifdef WATTY_EMSCRIPTEN
		if (window->getRefreshRate() < 1) 
			updateTick = 1 / 60.0f; // in WebGL, refresh rate can be 0
		
		std::function<void()> mainLoop = [&]() {
#else
		while (!window->closed()) {
#endif 
			engineUpdate();
			if (Timer::elapsed() - updateTimer > updateTick) {
				if (window->useVSync) render(); // With Vsync enabled, render at the refresh rate of the window
				updateTimer += updateTick;
				framesThisSec++;
			}
			if (!window->useVSync) {
				render(); // as fast as possible
				framesThisSec++;
			}

		
			
			// Timing/FPS
			if ((Timer::elapsed() - timer) > 1.0f) {
				timer += 1.0f;
				Stats::engineUpdate(framesThisSec, updates);
				tick();
				framesThisSec = 0;
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

}