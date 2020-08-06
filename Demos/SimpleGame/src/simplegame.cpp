#include <Watty.h>
#include <res.h>
// TODO: relative 

#define PLAYERTEXTUREPATH "textures/Player.png"
#define ENEMYTEXTUREPATH "textures/Enemy.png"

using namespace letc;
using namespace graphics;
using namespace math;

namespace letc {
	namespace physics {
		DebugPhysics* PhysicsWorld2D::debugDraw = new DebugPhysics();
		b2World* PhysicsWorld2D::box2DWorld = new b2World(b2Vec2(0.0f, -20.0f));

	}
}

class SimpleGame : public LETC {
private:
	Window* m_window;
	//Label* fpsLabel; 
	//Label* upsLabel; 
	//Label* mpsLabel; 

	float playerSpeed = 10;

	float time = 0.0f;

	GameObject* playerGO;
	GameObject* enemyGO;

public:
	SimpleGame() {}
	~SimpleGame() {
	
	}

	void init() override {
		RawResources::Init();
		window->setTitle("The First Game Made With the LETC!");
		window->setSize({1600,900});
		
		Layer* playerLayer= new Layer("Player Layer", new BatchRenderer2D());
		Layer* uiLayer= new Layer("UI Layer", new BatchRenderer2D());

		glClearColor(.976f,.972f,.972f,1);

		Texture* playerTexture = new Texture(PLAYERTEXTUREPATH);
	
		playerGO = new GameObject(glm::vec3(0,0,0), glm::vec2(4,4), new Sprite(playerTexture));
		playerLayer->add(playerGO);
		
		Texture* enemyTexture = new Texture(ENEMYTEXTUREPATH);
		enemyGO = new GameObject(glm::vec3(5,0,0), glm::vec2(4,4), new Sprite(enemyTexture));
		playerLayer->add(enemyGO);

	


		//TODO for now, it's best to keep the creation of textures close to where they get added to the layer. This is because if a texture is used in two separate draw calls, things won't show up properly

		/*Group* profileGroup = new Group(math::Matrix4::translation(glm::vec3(-15.5, 6.8, 0)));
		profileGroup->add(new GameObject(glm::vec3(0, 0, 0), glm::vec2( 3.8f, 1.8), new Sprite(0x80808080)));
		fpsLabel = new Label("", "Roboto", 16, 0xffffffff);
		upsLabel = new Label("", "Roboto", 14, 0xffffffff);
		mpsLabel = new Label("", "Roboto", 14, 0xffffffff);
		profileGroup->add(new GameObject(glm::vec3(.3f, 1.2f, 0), fpsLabel));
		profileGroup->add(new GameObject(glm::vec3(.3f, .8f, 0), upsLabel));
		profileGroup->add(new GameObject(glm::vec3(.3f, .4f, 0), mpsLabel));
		uiLayer->add(profileGroup);*/

	
	}

	void update() override {

		getInput();
		LETC::update();
	}

	void render() override {

		LETC::render();
	}

	void tick() override {

		//fpsLabel->text = std::to_string(getFramesPerSecond()) +  " frames / second";
		//upsLabel->text = std::to_string(getUpdatesPerSecond()) + " updates / second";
		//mpsLabel->text = std::to_string(getMSPerFrame()).substr(0, 5) + "ms / frame";
		LETC::tick();
	}

	void getInput() {
		float horizontal = -1*(float)(Input::keyIsDown(GLFW_KEY_A) || Input::keyIsDown(GLFW_KEY_LEFT)) + (float)(Input::keyIsDown(GLFW_KEY_D) || Input::keyIsDown(GLFW_KEY_RIGHT));
		float vertical = (float)(Input::keyIsDown(GLFW_KEY_W) || Input::keyIsDown(GLFW_KEY_UP)) + -1*(float)(Input::keyIsDown(GLFW_KEY_S) || Input::keyIsDown(GLFW_KEY_DOWN));
		
		glm::vec2 input(horizontal, vertical);

		float horizontalP1 = -1*(float)(Input::keyIsDown(GLFW_KEY_A)) + (float)(Input::keyIsDown(GLFW_KEY_D));
		float verticalP1 = (float)(Input::keyIsDown(GLFW_KEY_W))+ -1*(float)(Input::keyIsDown(GLFW_KEY_S));
		
		float horizontalP2 = -1*(float) Input::keyIsDown(GLFW_KEY_LEFT) + Input::keyIsDown(GLFW_KEY_RIGHT);
		float verticalP2 = (float) Input::keyIsDown(GLFW_KEY_UP) + -1*(float)(Input::keyIsDown(GLFW_KEY_DOWN));
		
		playerGO->transform->translate({playerSpeed * horizontalP1 * Timer::delta, playerSpeed * verticalP1 * Timer::delta});
		enemyGO->transform->translate({playerSpeed * horizontalP2 *  Timer::delta, playerSpeed * verticalP2 * Timer::delta});

	}


};


int main() {
	SimpleGame game;
	game.start();
	return 0;
}