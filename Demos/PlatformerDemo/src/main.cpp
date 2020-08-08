#include <Watty.h>
#include <res.h>

#define FRAGLITPATH			"shaders/basic_lit.frag"
#define FLOORTEXTUREPATH	"textures/floor.png"

using namespace letc;
using namespace graphics;
using namespace math;
using namespace physics;

namespace letc {
	namespace physics {
		DebugPhysics* PhysicsWorld2D::debugDraw = new DebugPhysics();
		b2World* PhysicsWorld2D::box2DWorld = new b2World(b2Vec2(0.0f, -20.0f));
	}
}
class PlatformerDemo : public LETC {
private:
	GameObject* player; //todo make player class

	float playerSpeed = 70;
	float playerJumpForce = 60.0f;

public:
	PlatformerDemo() {}
	~PlatformerDemo() {}

	void init() override {
		RawResources::Init();
		glm::vec2 screenSize(1280.0f, 720.0f);
		window->setSize(screenSize);
		window->setVSync(true);

		glm::vec2 fontScale = glm::vec2(window->getWidth() / 32.0f, window->getHeight() / 18.0f);
		letc::physics::PhysicsWorld2D::setDebugDraw();

		Shader* shader0 = new Shader();
		shader0->setUniform3f("light_pos", glm::vec3(16.0f, 16.0f, 0.0f));
		shader0->setUniform1f("light_radius", 250.0f);
		shader0->setUniform1f("light_intensity", 1.1f);


		Layer* layer0 = new Layer("Play Layer", new BatchRenderer2D(), shader0);
		
		layer0->add(
			new GameObject(
				glm::vec3(0, 0, 0),
				glm::vec2(200, 200),
				new Sprite(0xffF5F0F0)
			)
		);

		glm::vec3 playerPos(0, 0, 0);
		glm::vec2 playerSize(2, 2);
		player = new GameObject(
			playerPos,
			playerSize,
			new Sprite(new Texture( "textures/AnimationTest.png")));
		
		player->setTag("Player");

		player->addComponent(new PhysicsBody2D(PhysicsBody2DParams(
			physics::BodyShapes::box,
			playerPos,
			playerSize,
			b2_dynamicBody, 
			false,
			{0,0},
			0.3f,
			0.3f)));

		player->addAnimator();

		player->getAnimator()->addAnimation(new SpriteSheetAnimation(
			SpriteSheetAnimInfo{
			"Test",
			1.0f, 
			1,
			6,
			true
			}

		));
		player->getAnimator()->play("Test");

		//player->getAnimator()->play("Test");

		layer0->add(player);

		GameObject* childTest = new GameObject(glm::vec2(.33f, .33f), glm::vec2(.15, .15), new Sprite(Color::white));
		GameObject* childTest2 = new GameObject(glm::vec2(.2f, -.15f), glm::vec2(.6f, .15), new Sprite(Color::RGBA(0,.4,.8,.5)));
		player->transform->addChild(childTest->transform);
		player->transform->addChild(childTest2->transform);

		Texture* floorTexture = new Texture(FLOORTEXTUREPATH);

		glm::vec3 floorPos(-100000, -9.0f, 0);
		glm::vec2 floorSize(10000000, 2);
		GameObject* floor = new GameObject(floorPos, floorSize);
		floor->addComponent(new Sprite(floorPos, floorSize, floorTexture));
		floor->addComponent(new physics::PhysicsBody2D(PhysicsBody2DParams(
			physics::BodyShapes::box, floorPos, floorSize, b2_staticBody))
		);
		layer0->add(floor);

		for (int x = 0; x < 100; x+=10)
		{
			for (int y = -5; y < 100; y+=10)
			{
				if (x % 20 == 0) continue;
				floorPos = glm::vec3(x, y, 0);
				floorSize = glm::vec2(5, 2);
				GameObject* floor = new GameObject(floorPos, floorSize);
				floor->addComponent(new Sprite(floorPos, floorSize, floorTexture));
				floor->addComponent(new physics::PhysicsBody2D(PhysicsBody2DParams(
					physics::BodyShapes::box, floorPos, floorSize, b2_staticBody)));
				layer0->add(floor);
			}

		}

		glm::vec2 screenScale = glm::vec2(window->getWidth() / 32, window->getHeight() / 18);
	}

	void update() override {
		PhysicsWorld2D::step(Timer::delta);
		LETC::update();
		sceneCamera->position = { player->transform->getPosition().x, player->transform->getPosition().y+3.0f, -1.0f};
		


	}

	void render() override {
		getInput();

		LETC::render();

	}

	void tick() override {
		LETC::tick();
	}

	void getInput() {
		if (Input::keyWasPressed(GLFW_KEY_V))
			Window::toggleVSync();
		// PLAYER
		float horizontal = -1 * (float)(Input::keyIsDown(GLFW_KEY_A) || Input::keyIsDown(GLFW_KEY_LEFT)) + (float)(Input::keyIsDown(GLFW_KEY_D) || Input::keyIsDown(GLFW_KEY_RIGHT));
		float vertical = (float)(Input::keyIsDown(GLFW_KEY_W) || Input::keyIsDown(GLFW_KEY_UP)) + -1*(float)(Input::keyIsDown(GLFW_KEY_S) || Input::keyIsDown(GLFW_KEY_DOWN));
		if (Input::keyWasPressed(GLFW_KEY_SPACE))
			player->getPhysicsBody2D()->addImpulse(glm::vec2(0, 1), playerJumpForce);

		player->getPhysicsBody2D()->addImpulse(glm::vec2(1, 0), horizontal * playerSpeed * Timer::delta);

		//player->position.x += playerSpeed * horizontal * (float)Timer::delta;

		glm::vec2 playerPos = player->transform->getPosition();
		if (playerPos.y < -10.0f) {
			player->transform->setPosition({ playerPos.x, 10 });
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