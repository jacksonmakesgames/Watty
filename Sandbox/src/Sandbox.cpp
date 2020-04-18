
#ifdef WATTY_OPENGL
#include <Watty.h>

#define RESDIR "J:/OneDrive/Projects/Game_Development/Watty/Sandbox/res/"
#define PLAYERTEXTURE RESDIR  "textures/sprites/lpc/female_walkcycle.png"
#define TESTTEXTURE RESDIR  "textures/test.png"


#define SHADERVERT RESDIR  "shaders/basic.vert"
#define SHADERFRAG RESDIR "shaders/basic_unlit.frag"

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
		b2World* PhysicsWorld2D::box2DWorld = new b2World(b2Vec2(0.0f, -20.0f));
	}
}

class Sandbox : public LETC {
private:
	Window* m_window;
	GameObject* player; //todo make player class

	float playerSpeed = 2;
	float playerAcceleration = 2.0f;

public:
	void init() override{
		m_window = createWindow("Sandbox", 1280, 720, false,false);
		glClearColor(1.0f,1.0f,1.0f,1.0f);


		Layer* mainLayer = new Layer("main",new BatchRenderer2D(), new Shader(SHADERVERT,SHADERFRAG));
		layers.push_back(mainLayer);
		
		TileMap* tilemap = new TileMap(LEVELPATH, IMAGEPATH);
		tilemap->setPixelToMeterRatio(32);
		GameObject * tmGO = new GameObject(glm::vec2(.5f,-.5f), glm::vec2(1, 1), tilemap);

		mainLayer->add(tmGO);
		
		sceneCamera->setSize(glm::vec2(tilemap->getNumColumns(),tilemap->getNumRows()));
		//sceneCamera->position = glm::vec3(tilemapWidth*.5f, -tilemapHeight*.5f,-1);
		//GridLayer* g = new GridLayer(new Shader(SHADERVERT, SHADERFRAG), *sceneCamera, *m_window);
		//layers.push_back(g);

		glm::vec3 playerPos(0, 0, 0);
		glm::vec2 playerSize(2, 2);
		player = new GameObject(
			playerPos,
			playerSize,
			//new Sprite(new Texture("../../res/textures/Player.png")));
			new Sprite(new Texture(PLAYERTEXTURE)));

		player->setTag("Player");

		//player->addComponent(new PhysicsBody2D(
		//	physics::BodyShapes::box,
		//	playerPos.x, playerPos.y,
		//	playerSize.x, playerSize.y,
		//	b2_dynamicBody, 0.6f, 0.5f));

		player->addAnimator();


		player->getAnimator()->addAnimation(new SpriteSheetAnimation(
			SpriteSheetAnimInfo{ "idle", 10.0f, 4, 9, true,0,0}
		));

		player->getAnimator()->addAnimation(new SpriteSheetAnimation(
			SpriteSheetAnimInfo{ "walk_up", 10.0f, 4, 9, true,0 }
		));

		player->getAnimator()->addAnimation(new SpriteSheetAnimation(
			SpriteSheetAnimInfo{ "walk_left", 10.0f, 4, 9, true,1 }
		));

		player->getAnimator()->addAnimation(new SpriteSheetAnimation(
			SpriteSheetAnimInfo{ "walk_down", 10.0f, 4, 9, true,2 }
		));

		player->getAnimator()->addAnimation(new SpriteSheetAnimation(
			SpriteSheetAnimInfo{ "walk_right", 10.0f, 4, 9, true,3 }
		));

		player->getAnimator()->play("idle");
		mainLayer->add(player);

		layers.push_back(new EngineControlLayer("Engine Control", debugPhysics, resetFlag, &Window::useVSync, layers, new Shader(SHADERVERT, SHADERFRAG)));

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

		if (m_window->keyIsDown(GLFW_KEY_RIGHT)) {
			//sceneCamera->position.x+=10.0f*gameTimer->delta;
			player->transform->translate(glm::vec2(playerSpeed*gameTimer->delta,0));
			player->getAnimator()->play("walk_right");

		}
		
		if (m_window->keyIsDown(GLFW_KEY_LEFT)) {
			//sceneCamera->position.x-= playerSpeed.0f * gameTimer->delta;
			player->transform->translate(glm::vec2(-playerSpeed*gameTimer->delta,0));
			player->getAnimator()->play("walk_left");
		}		
		if (m_window->keyIsDown(GLFW_KEY_UP)) {
			//sceneCamera->position.y+= playerSpeed.0f * gameTimer->delta;
			player->transform->translate(glm::vec2(0,playerSpeed*gameTimer->delta));
			player->getAnimator()->play("walk_up");
		}
		
		if (m_window->keyIsDown(GLFW_KEY_DOWN)) {
			//sceneCamera->position.y-= playerSpeed.0f * gameTimer->delta;
			player->transform->translate(glm::vec2(0, -playerSpeed*gameTimer->delta));
			player->getAnimator()->play("walk_down");
		}

		if(!m_window->keyIsDown(GLFW_KEY_DOWN) 
		&& !m_window->keyIsDown(GLFW_KEY_UP)
		&& !m_window->keyIsDown(GLFW_KEY_LEFT)
		&& !m_window->keyIsDown(GLFW_KEY_RIGHT))
			player->getAnimator()->play("idle");

		LETC::update();
	}

	void render() override {
		ImGui::Begin("Animations"); {
			Animator2D anim = *player->getAnimator();
			std::string animName = anim.getCurrentAnimation();
			Animation2D animation = *anim.findByName(animName);
			int frame = animation.getCurrentFrameInfo().currentFrame;
			ImGui::Text(
				(animName + std::string(" ") + std::to_string(frame)).c_str()
			);
			ImGui::Text(
				(std::string("Min: ") + std::to_string(animation.getMinFrame())).c_str()
			);
			ImGui::Text(
				(std::string("Max: ") + std::to_string(animation.getMaxFrame())).c_str()
			);
		}ImGui::End();


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
#else

#include <graphics/Vulkan/VulkanDefaultInstance.h>


int main() {
	//DefaultVulkanInstance app;
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	glfwSetWindowUserPointer(window, 0);
}
























#endif






