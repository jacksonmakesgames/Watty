#pragma once
#include <glm.hpp>

#ifdef WATTY_EMSCRIPTEN
	#define GLFW_INCLUDE_ES3
	#define GL_GLEXT_PROTOTYPES
	#include <emscripten.h>
#undef GL_WITH_GLAD
#endif

#ifdef WATTY_OPENGL
	#include "./graphics/Window.h"

	#include <graphics/font/Label.h>

	#include <graphics/Renderer2D.h>
	#include <graphics/BatchRenderer2D.h>
	#include <graphics/Simple2DRenderer.h>
	#include <graphics/Shader.h>
	#include <graphics/Camera.h>
	#include <graphics/textures/SpriteSheetAnimation.h>
	#include <ft2build.h>
#endif
bool watty::graphics::Window::useVSync = false;

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

#ifdef ECS_ENABLED
	#include <ecs/ECS.h>
#endif

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


namespace watty {
#ifdef ECS_ENABLED

	struct Transform2DComponent : public ECSComponent<Transform2DComponent> {
		glm::mat4 transformMatrix = glm::mat4(1.0f);
		glm::vec2 position = glm::vec2(0.0f, 0.0f);
		glm::vec2 size = glm::vec2(1.0f, 1.0f);
		float rotation = 0.0f;
	};



	class RenderableSpriteSystem : public BaseECSSystem {
	private:
		graphics::Simple2DRenderer renderer = graphics::Simple2DRenderer(true);
		bool doneInit = false;
		graphics::Shader shader = graphics::Shader(true);
	public:
		RenderableSpriteSystem() {
			addComponentType(graphics::RenderableSpriteComponent::ID);
			addComponentType(Transform2DComponent::ID);
		}
		void pre(glm::mat4 projection) {
			shader.enable();
			renderer.begin();
			shader.setUniformMat4("pr_matrix", projection);
		}
		virtual void updateComponents(float deltaTime, BaseECSComponent** components) override {
			if (!doneInit) {
				renderer.init();
				shader.init();
				doneInit = true;
			}

			graphics::RenderableSpriteComponent* spriteComponent = (graphics::RenderableSpriteComponent*)components[0];
			Transform2DComponent* transformComponent = (Transform2DComponent*)components[1];
			renderer.push(transformComponent->transformMatrix);
			renderer.submit(spriteComponent);
			renderer.pop();

		}
		void post() {
			renderer.end();
			renderer.flush();
			shader.disable();
		}

	};
#endif
	class WattyEngine {
	public:
		bool debugPhysics = false;
		bool resetFlag = false;
		graphics::Camera* sceneCamera;
		unsigned int updates = 0;
		
#ifdef ECS_RENDER
		ECS ecs = ECS();
		ECSSystemList mainSystems;
		ECSSystemList renderSystems;
		RenderableSpriteSystem* spriteRenderer;
#endif
		bool WATTY_EDITOR_ATTACHED = false; // TODO: make compiler define

	protected:
		graphics::Window* window;

		unsigned int renderBufferObject;
		unsigned int texColorBuffer;
		graphics::Texture* screenTexture;
		graphics::Texture* testTexture;

	private:
		Timer* m_time;
		graphics::Shader* screenShader;

		double t = 0.0;
		double fixedTimeStep = 0.02; // amount of time between updates/physics steps. Default was 0.02.
		double currentTime = Timer::elapsed();
		double accumulator = 0.0;



	public:
		unsigned int FBO;
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

#if DEBUG
			screenShader = new graphics::Shader("shaders/screen.vert", "shaders/screen.frag");
			testTexture =  new graphics::Texture("textures/test.png");
			graphics::Texture* nt2 = new graphics::Texture("textures/test.png");
#endif // DEBUG

		}


		virtual void reset() {};

		


	protected:
		WattyEngine(){
			Timer::Timer();
			Stats::Stats();
		}
		

		virtual ~WattyEngine() {
			delete window;
			delete m_time;
			for (size_t i = 0; i < Layer::allLayers.size(); i++)
				delete Layer::allLayers[i];
		}

		graphics::Window* createWindow(const char* title, int width, int height, bool resizeable = true, bool fullscreen=false) {
			window = new graphics::Window(title, width, height, resizeable, fullscreen);

			float aspectRatio = width / height;
			
			//TODO we should calculate width and height in meters and allow the user to change camera modes once we support 3D
			sceneCamera = new graphics::Camera(
				&Layer::allLayers, 
				glm::vec3(0.0f, 0.0f, -10.0f),
				1,
				20,
				graphics::CameraMode::orthographic);

			if (WATTY_EDITOR_ATTACHED){
				sceneCamera->isEditorCamera = true;
			}

			return window;
		}

		

		
		// Runs on initialization
		virtual void init() = 0;


		// Runs once per second
		virtual void tick() {
			std::cout << "\t" << std::to_string(Stats::getFramesPerSecond()) << "fps | " << std::to_string(Stats::getMSPerFrame()) << "mspf \r" << std::flush;
		}

		virtual void OnGui() {};
		virtual void onEditorGui() {};
		virtual void update() {};

		virtual void editorUpdate() {}

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
				Input::listenForInput();

				Timer::update();

				updates++;

				physics::PhysicsWorld2D::step(Timer::delta); //TODO: could be fixedTimeStep instead
				update();
				#ifdef ECS_ENABLED
				ecs.updateSystems(mainSystems, Timer::delta);
				#endif
				Input::resetScroll();

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

		//TODO move to window
		void cleanFrameBuffer() {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			glDeleteFramebuffers(1, &FBO);
		}

		void setupFrameBuffer() {

			// Frame buffer
			glGenFramebuffers(1, &FBO);
			glBindFramebuffer(GL_FRAMEBUFFER, FBO);

			// attach texture
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTexture->getID(), 0);

			// check if FBO is complete
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

			glBindFramebuffer(GL_FRAMEBUFFER, 0); // Unbind framebuffer
	
		}

		void preFrameBuffer() {
			// Bind framebuffer
			glBindFramebuffer(GL_FRAMEBUFFER, FBO);

			// 3D:
			//glEnable(GL_DEPTH_TEST);

		}

		GLubyte* data = nullptr;

		void postFrameBuffer() {
			// now bind back to default framebuffer 
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			// clear all relevant buffers
			window->clear(.4, .4, .4, 1, false, false);
		}

		unsigned int getRenderTexture() {
			return screenTexture->getID();
		}

		// runs as fast as possible (unless vsync is enabled, then it runs at refresh rate)
		virtual void render() {
			if (WATTY_EDITOR_ATTACHED) {
				preFrameBuffer(); // bind framebuffer
			}
			window->clear(.5, .5, .5, 1, false, true); { // One frame, clear framebuffer
			//window->clear(sceneCamera->getClearColor(), true, true); { // One frame



#ifdef ECS_RENDER
				spriteRenderer->pre(sceneCamera->getProjection());
				ecs.updateSystems(renderSystems, Timer::delta);
				spriteRenderer->post();
#else
				// Draw
				for (size_t i = 0; i < Layer::allLayers.size(); i++) {
					Layer::allLayers[i]->draw();
				}

#endif // ECS_RENDER

				if (WATTY_EDITOR_ATTACHED) {
					postFrameBuffer(); // unbind framebuffer, clear
					onEditorGui();
				}

				OnGui();

			}window->update(); // End frame, swap buffers, check events

		}


private:
	void run() {
		Random::init();
		#ifdef ECS_RENDER
		spriteRenderer = new RenderableSpriteSystem();
		renderSystems.addSystem(*spriteRenderer);
		#endif
		watty::physics::PhysicsWorld2D::box2DWorld->SetContactListener(new Physics2DContactListener());
#ifdef DEBUG 

		watty::physics::DebugPhysics::init(&(sceneCamera->position), &(sceneCamera->getViewportSize()));
		watty::physics::PhysicsWorld2D::setDebugDraw();
		new graphics::DebugPhysicsLayer(*sceneCamera, *window);
		new graphics::GridLayer(*sceneCamera, *window);

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
			editorUpdate();
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


	watty::graphics::DebugRenderer* watty::physics::DebugPhysics::renderer = nullptr;
	watty::graphics::Shader* watty::physics::DebugPhysics::m_shader = nullptr;
	const glm::vec3* watty::physics::DebugPhysics::m_sceneCameraPosition = nullptr;
	const glm::vec2* watty::physics::DebugPhysics::m_sceneCameraScale = nullptr;




}