#include "../../L_ETC-core/src/letc.h"


#define VERTPATH "J:/OneDrive/Projects/Game_Development/L_ETC/Demos/res/shaders/basic.vert"
#define FRAGLITPATH "J:/OneDrive/Projects/Game_Development/L_ETC/Demos/res/shaders/basic_lit.frag"
#define FRAGUNLITPATH "J:/OneDrive/Projects/Game_Development/L_ETC/Demos/res/shaders/basic_unlit.frag"

using namespace letc;
using namespace graphics;
using namespace math;
using namespace audio;
using namespace physics;

namespace letc {
	namespace physics {
		DebugPhysics* PhysicsWorld2D::debugDraw = new DebugPhysics();
		b2World* PhysicsWorld2D::box2DWorld = new b2World(b2Vec2(0.0f, -20.0f));
	}
}
class PlatformerDemo : public LETC {
private:
	Window* m_window;
	GUILayer* m_engineControlLayer;
	GameObject* player; //todo make player class
	Camera* m_camera;

	float playerSpeed = 70;
	float playerAcceleration = .9f;
	float playerJumpForce = 35;

public:
	PlatformerDemo() {}
	~PlatformerDemo() {}

	void init() override {
		m_window = createWindow("This little engine could", 1280, 720);
		m_window->setVSync(true);

		Vector2 fontScale = Vector2(m_window->getWidth() / 32.0f, m_window->getHeight() / 18.0f);
		letc::physics::PhysicsWorld2D::setDebugDraw();

		Shader* shader0 = new Shader(VERTPATH, FRAGLITPATH);
		shader0->setUniform3f("light_pos", Vector3(16, 16, 0));
		shader0->setUniform1f("light_radius", 250.0f);
		shader0->setUniform1f("light_intensity", 1.1f);


		Layer* layer0 = new Layer("Play Layer", new BatchRenderer2D(), shader0);
		layers.push_back(layer0);
		
		Layer* layer1 = new Layer("Play Layer2", new BatchRenderer2D(), new Shader(VERTPATH, FRAGLITPATH));
		layers.push_back(layer1);

		layer0->add(
			new GameObject(
				Vector3(-100, -100, 0),
				Vector2(200, 200),
				new Sprite(0xffF5F0F0)
			)
		);

		Vector3 playerPos(-2, -2, 0);
		Vector2 playerSize(2, 2);
		player = new GameObject(
			playerPos,
			playerSize,
			new Sprite(new Texture("J:/OneDrive/Projects/Game_Development/L_ETC/Demos/res/textures/Player.png")));

		player->addComponent(new PhysicsBody2D(
			physics::BodyShapes::circle,
			playerPos.x, playerPos.y,
			playerSize.x, playerSize.y,
			b2_dynamicBody, 0.6f, 0.5f));
		player->setTag("Player");
		layer0->add(player);

		Texture* floorTexture = new Texture("J:/OneDrive/Projects/Game_Development/L_ETC/Demos/res/textures/floor.png");

		Vector3 floorPos(-16.0f, -9.0f, 0);
		Vector2 floorSize(32, 2);
		GameObject* floor = new GameObject(floorPos, floorSize);
		floor->addComponent(new Sprite(floorPos.x, floorPos.y, floorSize.x, floorSize.y, floorTexture));
		floor->addComponent(new physics::PhysicsBody2D(physics::BodyShapes::box, floorPos.x, floorPos.y, floorSize.x, floorSize.y, b2_staticBody));
		//TODO BUG, physics bodies are still enabled even if the object is not in a layer
		layer0->add(floor);

		math::Vector2 screenScale = math::Vector2(m_window->getWidth() / 32, m_window->getHeight() / 18);

		GridLayer* gridLayer = new GridLayer(new Shader(VERTPATH, FRAGUNLITPATH), -16, 16, -9, 9, -10, 10);
		layers.push_back(gridLayer);
		gridLayer->disable();

		EngineControlLayer* engineControlLayer = new EngineControlLayer("LETC GUI Layer", debugPhysics, resetFlag, &Window::useVSync, layers, new Shader(VERTPATH, FRAGUNLITPATH));
		layers.push_back(engineControlLayer);
		engineControlLayer->disable();


		m_camera = new Camera(&layers, Vector3(0, 0, -10), Vector2(32.0f, 18.0f), 20, CameraMode::orthographic);


	}

	void update() override {
		getInput();
		PhysicsWorld2D::step(gameTimer->delta);
		LETC::update();
		m_camera->position = player->position + Vector3(0.0f, 3.0f, -1.0f);
	}

	void render() override {

		LETC::render();
		if (debugPhysics) PhysicsWorld2D::box2DWorld->DrawDebugData();

	}

	void tick() override {
		LETC::tick();
	}


	void getInput() {
		// ENGINE
		if (m_window->keyWasPressed(GLFW_KEY_GRAVE_ACCENT))
			getLayerByName("LETC GUI Layer")->enabled = !getLayerByName("LETC GUI Layer")->enabled;

		// PLAYER
		float horizontal = -1 * (float)(m_window->keyIsDown(GLFW_KEY_A) || m_window->keyIsDown(GLFW_KEY_LEFT)) + (float)(m_window->keyIsDown(GLFW_KEY_D) || m_window->keyIsDown(GLFW_KEY_RIGHT));
		float vertical = (float)(m_window->keyIsDown(GLFW_KEY_W) || m_window->keyIsDown(GLFW_KEY_UP)) + -1*(float)(m_window->keyIsDown(GLFW_KEY_S) || m_window->keyIsDown(GLFW_KEY_DOWN));
		if (m_window->keyWasPressed(GLFW_KEY_SPACE))
			player->getPhysicsBody2D()->addImpulse(Vector2(0, 1), playerJumpForce);

		player->getPhysicsBody2D()->addImpulse(Vector2(1, 0), horizontal * playerSpeed * gameTimer->delta);
		//player->position.x += playerSpeed * horizontal * (float)gameTimer->delta;

		if (player->position.y < -10.0f) {
			player->position.y = 10.0f;
			player->getPhysicsBody2D()->getBody()->SetTransform(b2Vec2(0, 0), 0.0f);
			player->getPhysicsBody2D()->zeroVelocity();
		}
	}


};

int main() {
	PlatformerDemo game;
	game.start();
	return 0;
}