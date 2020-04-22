#include <Watty.h>

#define RESDIR "J:/OneDrive/Projects/Game_Development/Watty/Sandbox/res/"
#define PLAYERTEXTURE RESDIR  "textures/sprites/lpc/soldier.png"
#define PLAYERCLOTHESTEXTURE RESDIR  "textures/sprites/lpc/female_chainmail.png"
#define TESTTEXTURE RESDIR  "textures/test.png"

#define LEVELPATH RESDIR "tilemaps/levelOne.json"
#define IMAGEPATH RESDIR "tilemaps/terrain_all.png"

using namespace letc;
using namespace graphics;
using namespace math;
//using namespace audio;
using namespace physics;
using namespace glm;

namespace letc {
	namespace physics {
		DebugPhysics* PhysicsWorld2D::debugDraw = new DebugPhysics();
		b2World* PhysicsWorld2D::box2DWorld = new b2World(b2Vec2(0.0f, 0.0f));
	}
}

class Sandbox : public LETC {
private:
	Window* m_window;
	GameObject* player;

	double playerSpeed = 500;
	int lastPlayerDir = 0;
	float playerAcceleration = 2.0f;

public:
	void init() override{
		debugPhysics = true;
		m_window = createWindow("Sandbox", 1280, 734, false,false);
		glClearColor(1.0f,1.0f,1.0f,1.0f);


		Layer* mainLayer = new Layer("main",new BatchRenderer2D());
		layers.push_back(mainLayer);
		
		TileMap* tilemap = new TileMap(LEVELPATH, IMAGEPATH);
		tilemap->setPixelToMeterRatio(32);
		tilemap->buildPhysicsShapes();

		GameObject * tmGO = new GameObject(glm::vec2(0,0), glm::vec2(1, 1), tilemap);
		mainLayer->add(tmGO);

		sceneCamera->setSize(glm::vec2(tilemap->getNumColumns(),tilemap->getNumRows()));
	
		glm::vec3 playerPos(9, -8, 0);
		glm::vec2 playerSize(2, 2);
		player = new GameObject(
			playerPos,
			playerSize,
			new Sprite(new Texture(PLAYERTEXTURE)));

		player->setTag("Player");

		player->addComponent(new PhysicsBody2D(
			physics::BodyShapes::box,
			playerPos,
			playerSize.x*.5f, playerSize.y*.5f,
			b2_dynamicBody,
			glm::vec2(0,-.5f),
			0.0f, 1.0f));


		player->getPhysicsBody2D()->getBody()->SetFixedRotation(true);

		player->addAnimator();


		player->getAnimator()->addAnimation(new SpriteSheetAnimation(
			SpriteSheetAnimInfo{ "idle_down",	10.0f, 4, 9, true, 3, 0}
		));player->getAnimator()->addAnimation(new SpriteSheetAnimation(
			SpriteSheetAnimInfo{ "idle_left",	10.0f, 4, 9, true, 2, 0}
		));player->getAnimator()->addAnimation(new SpriteSheetAnimation(
			SpriteSheetAnimInfo{ "idle_right",	10.0f, 4, 9, true, 4, 0}
		));player->getAnimator()->addAnimation(new SpriteSheetAnimation(
			SpriteSheetAnimInfo{ "idle_up",		10.0f, 4, 9, true, 1, 0}
		));player->getAnimator()->addAnimation(new SpriteSheetAnimation(
			SpriteSheetAnimInfo{ "walk_up",		10.0f, 4, 9, true, 0 }
		));player->getAnimator()->addAnimation(new SpriteSheetAnimation(
			SpriteSheetAnimInfo{ "walk_left",	10.0f, 4, 9, true, 1 }
		));player->getAnimator()->addAnimation(new SpriteSheetAnimation(
			SpriteSheetAnimInfo{ "walk_down",	10.0f, 4, 9, true, 2 }
		));player->getAnimator()->addAnimation(new SpriteSheetAnimation(
			SpriteSheetAnimInfo{ "walk_right",	10.0f, 4, 9, true, 3 }
		));

		mainLayer->add(player);

	}

	void tick() override {
		LETC::tick();
	}
	void update() override{
		sceneCamera->setSize(
				glm::vec2(	
					sceneCamera->getSize().x - 4.0f  * m_window->getScrollAmountThisFrameY(),
					sceneCamera->getSize().y - 2.25f * m_window->getScrollAmountThisFrameY()
				));
		

		double horizontal = -1 * (double)(m_window->keyIsDown(GLFW_KEY_A) || m_window->keyIsDown(GLFW_KEY_LEFT)) + (float)(m_window->keyIsDown(GLFW_KEY_D) || m_window->keyIsDown(GLFW_KEY_RIGHT));
		double vertical = (double)(m_window->keyIsDown(GLFW_KEY_W) || m_window->keyIsDown(GLFW_KEY_UP)) + -1*(float)(m_window->keyIsDown(GLFW_KEY_S) || m_window->keyIsDown(GLFW_KEY_DOWN));

		if (vertical<0) {
			player->getAnimator()->play("walk_down");
			lastPlayerDir = 0;
		}
		if (horizontal < 0) {
			player->getAnimator()->play("walk_left");
			lastPlayerDir = 1;
		}		
		if (vertical>0) {
			player->getAnimator()->play("walk_up");
			lastPlayerDir = 2;
		}
		if (horizontal > 0) {
			player->getAnimator()->play("walk_right");
			lastPlayerDir = 3;
		}
		
		

		if (horizontal == 0 && vertical == 0) {
			switch (lastPlayerDir){
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
			horizontal * playerSpeed * gameTimer->delta,
			vertical * playerSpeed * gameTimer->delta
		));

		LETC::update();
	}

	void render() override {

		LETC::render();
	}

	~Sandbox() {
	}

};


int main() {
	Sandbox* sandbox = new Sandbox();
	sandbox->start();
	return 0;
}






