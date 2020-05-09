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
using namespace audio;
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
	Label* fpsLabel;
	std::vector<Sprite*> allSprites;
	std::vector<GameObject*> allObjects;
	std::vector<glm::vec2> allObjectPos;
public:
	void init() override {
		m_window = createWindow("Sandbox", 1280, 720, true, false);
		glClearColor(.45, .23, .23, 1);
		Layer* mainLayer = new Layer("Layer 1");
		//mainLayer->add(new GameObject("Test", { 0,0 }, { 1,1 }, new Sprite(Color::white)));
		layers.push_back(mainLayer);

		for (int x = -20; x < 20; x++)
		{
			for (int y = -20; y < 20; y++) {
				Sprite* sprite = new Sprite(Color::random());
				GameObject* tmp = new GameObject({ x,y }, {.8,.8},sprite);
				allSprites.push_back(sprite);
				allObjects.push_back(tmp);
				allObjectPos.push_back({x,y});
				mainLayer->add(tmp);
			}

		}

		AudioManager::addClip("drums", RESDIR "audio/drums.wav");
		AudioManager::getClip("drums")->play(true);
		AudioManager::getClip("drums")->setGain(.5f);


		FontManager::add("test", RESDIR "fonts/Lobster.ttf", 100);
		LabelProperties labelProps;
		labelProps.charsPerLine = 30;
		labelProps.text =	"";
		labelProps.font = FontManager::get("test");
		labelProps.color = Color::orange;
		labelProps.overflowMode = OverflowMode::Expand;
		fpsLabel = new Label(labelProps);
		GameObject* fpsGO = new GameObject({-14,7}, {1,1}, fpsLabel);
		mainLayer->add(fpsGO);

	}

	void tick() override {
		LETC::tick();
		fpsLabel->setText(std::string("FPS: ") + std::to_string(getFramesPerSecond()));
	}
	void update() override{
		sceneCamera->setSize( glm::vec2(	
					sceneCamera->getSize().x - 4.0f  * m_window->getScrollAmountThisFrameY(),
					sceneCamera->getSize().y - 2.25f * m_window->getScrollAmountThisFrameY()
				));

		float r = Random::range(-1,1);
		for (GameObject* go : allObjects)
		{
			float x = abs(go->transform->getPosition().x);
			float y = abs(go->transform->getPosition().y);

			go->transform->translate({ sin(x * gameTimer->elapsed()) / 10, cos(y * gameTimer->elapsed()) / x });

			go->transform->rotate(tan(.25+x*tan(gameTimer->elapsed()/100)));

		}

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






