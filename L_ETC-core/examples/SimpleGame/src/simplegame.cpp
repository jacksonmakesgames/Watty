#include "../../../src/letc.h"
#include <math.h>


using namespace letc;
using namespace graphics;
using namespace math;

class SimpleGame : public LETC {
private:
	Window* m_window;
	GUILayer* m_guiLayer;
	Label* fpsLabel; 
	Label* upsLabel; 
	Label* mpsLabel; 

	float playerSpeed = 10;

	float time = 0.0f;

	GameObject* playerGO;
	GameObject* enemyGO;

public:
	SimpleGame() {}
	~SimpleGame() {
	
	}

	void init() override {
		m_window = createWindow("The First Game Made With the LETC!", 1600,900);
		m_window->setVSync(true);

		Layer* playerLayer= new Layer(new BatchRenderer2D(), new Shader("res/shaders/basic.vert", "res/shaders/basic_unlit.frag"), math::Matrix4::orthographic(-16, 16,-9, 9,-10, 10));
		Layer* uiLayer= new Layer(new BatchRenderer2D(), new Shader("res/shaders/basic.vert", "res/shaders/basic_unlit.frag"), math::Matrix4::orthographic(-16, 16,-9, 9,-10, 10));
		layers.push_back(playerLayer);
		layers.push_back(uiLayer);

		m_guiLayer = new GUILayer(new Shader("res/shaders/basic.vert", "res/shaders/basic_unlit.frag"), math::Matrix4::orthographic(-16, 16, -9, 9, -10, 10));

		glClearColor(.976f,.972f,.972f,1);

		math::Vector2 screenScale = math::Vector2(m_window->getWidth() / 32, m_window->getHeight() / 18);


		Texture* playerTexture = new Texture("J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/examples/SimpleGame/res/Player.png");
		playerGO = new GameObject(Vector3(0,0,0), Vector2(4,4), new Sprite(playerTexture));
		playerLayer->add(playerGO);
		
		Texture* enemyTexture = new Texture("J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/examples/SimpleGame/res/Enemy.png");
		enemyGO = new GameObject(Vector3(5,0,0), Vector2(4,4), new Sprite(enemyTexture));
		playerLayer->add(enemyGO);


		//TODO for now, it's best to keep the creation of textures close to where they get added to the layer. This is because if a texture is used in two separate draw calls, things won't show up properly
		FontManager::add(new Font("Roboto", "J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/fonts/Roboto-Regular.ttf", 16, screenScale));
		FontManager::add(new Font("Roboto", "J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/fonts/Roboto-Italic.ttf", 14, screenScale));

		Group* profileGroup = new Group(math::Matrix4::translation(Vector3(-15.5, 6.8, 0)));
		profileGroup->add(new GameObject(Vector3(0, 0, 0), Vector2( 3.8f, 1.8), new Sprite(0x80808080)));
		fpsLabel = new Label("", "Roboto", 16, 0xffffffff);
		upsLabel = new Label("", "Roboto", 14, 0xffffffff);
		mpsLabel = new Label("", "Roboto", 14, 0xffffffff);
		profileGroup->add(new GameObject(Vector3(.3f, 1.2f, 0), fpsLabel));
		profileGroup->add(new GameObject(Vector3(.3f, .8f, 0), upsLabel));
		profileGroup->add(new GameObject(Vector3(.3f, .4f, 0), mpsLabel));
		uiLayer->add(profileGroup);
	
	}

	void update() override {
		getInput();
		LETC::update();
	}

	void render() override {

		LETC::render();
	}

	void tick() override {

		fpsLabel->text = std::to_string(getFramesPerSecond()) +  " frames / second";
		upsLabel->text = std::to_string(getUpdatesPerSecond()) + " updates / second";
		mpsLabel->text = std::to_string(getMSPerFrame()).substr(0, 5) + "ms / frame";
		LETC::tick();
	}

	void getInput() {
		/*float horizontal = -1*(float)(m_window->keyIsDown(GLFW_KEY_A) || m_window->keyIsDown(GLFW_KEY_LEFT)) + (float)(m_window->keyIsDown(GLFW_KEY_D) || m_window->keyIsDown(GLFW_KEY_RIGHT));
		float vertical = (float)(m_window->keyIsDown(GLFW_KEY_W) || m_window->keyIsDown(GLFW_KEY_UP)) + -1*(float)(m_window->keyIsDown(GLFW_KEY_S) || m_window->keyIsDown(GLFW_KEY_DOWN));
		*/
		//Vector2 input(horizontal, vertical);

		float horizontalP1 = -1*(float)(m_window->keyIsDown(GLFW_KEY_A)) + (float)(m_window->keyIsDown(GLFW_KEY_D));
		float verticalP1 = (float)(m_window->keyIsDown(GLFW_KEY_W))+ -1*(float)(m_window->keyIsDown(GLFW_KEY_S));
		
		float horizontalP2 = -1*(float) m_window->keyIsDown(GLFW_KEY_LEFT) + m_window->keyIsDown(GLFW_KEY_RIGHT);
		float verticalP2 = (float) m_window->keyIsDown(GLFW_KEY_UP) + -1*(float)(m_window->keyIsDown(GLFW_KEY_DOWN));
		
		playerGO->position.x += playerSpeed * horizontalP1 * gameTimer->delta;
		playerGO->position.y += playerSpeed * verticalP1 * gameTimer->delta;
		enemyGO->position.x += playerSpeed * horizontalP2 * gameTimer->delta;
		enemyGO->position.y += playerSpeed * verticalP2 * gameTimer->delta;

	}


};


int main() {
	SimpleGame game;
	game.start();
	return 0;
}