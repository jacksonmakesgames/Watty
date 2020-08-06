#include <Watty.h>
#include <res.h>

#define PLAYERTEXTURE   "textures/sprites/lpc/soldier.png"
#define PLAYERCLOTHESTEXTURE   "textures/sprites/lpc/female_chainmail.png"
#define TESTTEXTURE   "textures/test.png"

#define LEVELPATH  "tilemaps/levelOne.json"
#define IMAGEPATH  "tilemaps/terrain_all.png"

using namespace letc;
using namespace graphics;
using namespace math;
using namespace audio;
using namespace physics;
using namespace glm;

namespace letc {
	namespace physics {
		DebugPhysics* PhysicsWorld2D::debugDraw = new DebugPhysics();
		b2World* PhysicsWorld2D::box2DWorld = new b2World(b2Vec2(0.0f, 0.0f));
	}
}

class TileMapDemoApp : public LETC {
private:
	Window* m_window;
	GameObject* player;

	double playerSpeed = 7;
	int lastPlayerDir = 0;
	double playerAcceleration = 2.0f;
	std::vector<double> velocities = std::vector<double>();
	std::vector<double> timeIntervals = std::vector<double>();
	double lastMeasureTime = 0;

public:
	void init() override {
		RawResources::Init();
		debugPhysics = true;
		window->setSize({1280,734});
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);


		Layer* mainLayer = new Layer("main");

		TileMap* tilemap = new TileMap(LEVELPATH, IMAGEPATH);
		tilemap->setPixelToMeterRatio(32);
		tilemap->buildPhysicsShapes();

		GameObject* tmGO = new GameObject(glm::vec2(0, 0), glm::vec2(1, 1), tilemap);
		mainLayer->add(tmGO);

		sceneCamera->setSize(glm::vec2(tilemap->getNumColumns(), tilemap->getNumRows()));

		glm::vec3 playerPos(9, -8, 0);
		glm::vec2 playerSize(2, 2);
		player = new GameObject(
			playerPos,
			playerSize,
			new Sprite(new Texture(PLAYERTEXTURE)));

		player->setTag("Player");

		player->addComponent(new PhysicsBody2D(PhysicsBody2DParams(
			physics::BodyShapes::box,
			playerPos,
			playerSize* .5f,
			b2_dynamicBody,
			false,
			glm::vec2(0, -.5f),
			0.0f, 1.0f)));


		player->getPhysicsBody2D()->setFixedRotation(true);

		player->addAnimator();

		player->getAnimator()->addAnimation(new SpriteSheetAnimation(
			SpriteSheetAnimInfo{ "idle_down",	10.0f, 4, 9, true, 3, 0 }
		)); player->getAnimator()->addAnimation(new SpriteSheetAnimation(
			SpriteSheetAnimInfo{ "idle_left",	10.0f, 4, 9, true, 2, 0 }
		)); player->getAnimator()->addAnimation(new SpriteSheetAnimation(
			SpriteSheetAnimInfo{ "idle_right",	10.0f, 4, 9, true, 4, 0 }
		)); player->getAnimator()->addAnimation(new SpriteSheetAnimation(
			SpriteSheetAnimInfo{ "idle_up",		10.0f, 4, 9, true, 1, 0 }
		)); player->getAnimator()->addAnimation(new SpriteSheetAnimation(
			SpriteSheetAnimInfo{ "walk_up",		10.0f, 4, 9, true, 0 }
		)); player->getAnimator()->addAnimation(new SpriteSheetAnimation(
			SpriteSheetAnimInfo{ "walk_left",	10.0f, 4, 9, true, 1 }
		)); player->getAnimator()->addAnimation(new SpriteSheetAnimation(
			SpriteSheetAnimInfo{ "walk_down",	10.0f, 4, 9, true, 2 }
		)); player->getAnimator()->addAnimation(new SpriteSheetAnimation(
			SpriteSheetAnimInfo{ "walk_right",	10.0f, 4, 9, true, 3 }
		));

		mainLayer->add(player);

	}

	void tick() override {
		LETC::tick();
	}
	void update() override {
		LETC::update();
		getInput();

		sceneCamera->setSize(
			glm::vec2(
				sceneCamera->getSize().x - 4.0f * Input::getScrollAmountThisFrameY(),
				sceneCamera->getSize().y - 2.25f * Input::getScrollAmountThisFrameY()
			));


	}

	void OnGui() override {
		return;
		double velSum = 0;
		for (size_t i = 0; i < velocities.size(); i++){
			velSum += (velocities[i]);
		}
		
		double timeSum = 0;
		for (size_t i = 0; i < timeIntervals.size(); i++){
			timeSum += (timeIntervals[i]);
		}

		double avgDist = (velSum * timeSum)/30;
		ImGui::Begin("Average Distance:");
		ImGui::LabelText("", std::to_string(avgDist).c_str());
		ImGui::End();
	}

	void render() override {
		LETC::render();
		

	}

	~TileMapDemoApp() {
	}


	void getInput() {

		double horizontal = -1 * (double)(Input::keyIsDown(GLFW_KEY_A) || Input::keyIsDown(GLFW_KEY_LEFT)) + (float)(Input::keyIsDown(GLFW_KEY_D) || Input::keyIsDown(GLFW_KEY_RIGHT));
		double vertical = (double)(Input::keyIsDown(GLFW_KEY_W) || Input::keyIsDown(GLFW_KEY_UP)) + -1 * (float)(Input::keyIsDown(GLFW_KEY_S) || Input::keyIsDown(GLFW_KEY_DOWN));
		
		
		if (vertical < 0 && horizontal == 0) {
			player->getAnimator()->play("walk_down");
			lastPlayerDir = 0;
		}
		if (horizontal < 0 && vertical == 0) {
			player->getAnimator()->play("walk_left");
			lastPlayerDir = 1;
		}
		if (vertical > 0 && horizontal == 0) {
			player->getAnimator()->play("walk_up");
			lastPlayerDir = 2;
		}
		if (horizontal > 0 && vertical == 0) {
			player->getAnimator()->play("walk_right");
			lastPlayerDir = 3;
		}



		if (horizontal == 0 && vertical == 0) {
			switch (lastPlayerDir) {
			case(0):
				player->getAnimator()->play("idle_down");
				break;
			case(1):
				player->getAnimator()->play("idle_left");
				break;
			case(2):
				player->getAnimator()->play("idle_up");
				break;
			case(3):
				player->getAnimator()->play("idle_right");
				break;
			}
		}

		player->getPhysicsBody2D()->setLinearVelocity(glm::vec2(
			horizontal * playerSpeed,
			vertical * playerSpeed
		));

		

		velocities.push_back(playerSpeed);
		if (velocities.size() > 30) {
			velocities.erase(velocities.begin());
			velocities.shrink_to_fit();
		}
		timeIntervals.push_back(Timer::delta);
		if (timeIntervals.size() > 30) {
			timeIntervals.erase(timeIntervals.begin());
			timeIntervals.shrink_to_fit();
		}

	}
};


int main() {
	TileMapDemoApp* demoApp = new TileMapDemoApp();
	demoApp->start();
	return 0;
}






