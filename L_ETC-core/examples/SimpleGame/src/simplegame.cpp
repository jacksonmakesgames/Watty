#include "../../../src/letc.h"

using namespace letc;
using namespace graphics;
using namespace math;

class SimpleGame : public LETC {
private:
	Window* m_window;
	Layer* m_layer;
	Label* fpsLabel; 
	Label* upsLabel; 
	Label* mpsLabel; 

public:
	SimpleGame() {}
	~SimpleGame() {
		delete m_layer;
	}

	void init() override {
		m_window = createWindow("The First Game Made With the LETC!", 1600,900);
		m_layer = new Layer(new BatchRenderer2D(), new Shader("res/shaders/basic.vert", "res/shaders/basic_unlit.frag"), math::Matrix4::orthographic(-16, 16,-9, 9,-10, 10));
		glClearColor(1,1,1,1);

		math::Vector2 screenScale = math::Vector2(m_window->getWidth() / 32, m_window->getHeight() / 18);

		//TODO for some reason, every label needs a new font 
		FontManager::add(new Font("Roboto-R", "J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/fonts/Roboto-Regular.ttf", 16, screenScale));
		FontManager::add(new Font("Roboto-I", "J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/fonts/Roboto-Italic.ttf", 14, screenScale));
		FontManager::add(new Font("Roboto-I", "J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/fonts/Roboto-Italic.ttf", 13, screenScale));

		Group* profileGroup = new Group(math::Matrix4::translation(Vector3(-15.5, 6.8, 0)));
		profileGroup->add(new Sprite(0, 0, 3.8f, 1.8, 0x80808080));
		fpsLabel = new Label("", .3f, 1.2, "Roboto-R", 16, 0xffffffff);
		upsLabel = new Label("", .3f, .8f, "Roboto-I", 14, 0xffffffff);
		mpsLabel = new Label("", .3f, .4, "Roboto-I", 13, 0xffffffff);
		profileGroup->add(fpsLabel);
		profileGroup->add(upsLabel);
		profileGroup->add(mpsLabel);

		m_layer->add(profileGroup);;

		Texture* alien = new Texture("J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/examples/SimpleGame/res/alien.png");

		m_layer->add(new Sprite(2,0,4,4, alien));
		m_layer->add(new Sprite(-2,0,4,4, alien));

		//for (float y = -9.0f; y < 9.0f; y += .25f) {
		//	for (float x = -16.0f; x < 16.0f; x += .25f) {
		//		Sprite* sprite = new Sprite(x, y, .095f, .095f, alien);
		//		//sprite->setColor(math::Vector4((y + 9.0f) / 18.0f, rand() % 1000 / 1000.0f, (x + 16.0f) / 32.0f, 1));
		//		m_layer->add(sprite);
		//	}
		//}
	}

	void render() override {
		m_layer->draw();
	}

	void tick() override {
		fpsLabel->text = std::to_string(getFramesPerSecond()) +  " frames / second";
		upsLabel->text = std::to_string(getUpdatesPerSecond()) + " updates / second";
		mpsLabel->text = std::to_string(getMSPerFrame()).substr(0, 5) + "ms / frame";
	}

};


int main() {
	SimpleGame game;
	game.start();
	return 0;
}