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
	GameObject* jObject;
	GameObject* rObject;
	std::vector<GameObject*> allObjects;
	std::vector<glm::vec2> allObjectPos;
	std::vector<Sprite*> allSprites;
public:
	void init() override{
		m_window = createWindow("Sandbox", 1280, 720, true, false);
		glClearColor(.7,.9,1,1);
		Layer* mainLayer = new Layer("Layer 1");
		//mainLayer->add(new GameObject("Test", { 0,0 }, { 1,1 }, new Sprite(Color::white)));
		layers.push_back(mainLayer);
	
		/*for (int x = -20; x < 20; x++)
		{
			for (int y = -20; y < 20; y++) {
				Sprite* sprite = new Sprite(Color::random());
				GameObject* tmp = new GameObject({ x,y }, {.8,.8},sprite);
				allSprites.push_back(sprite);
				allObjects.push_back(tmp);
				allObjectPos.push_back({x,y});
				mainLayer->add(tmp);
			}

		}*/

		//mainLayer2->add(new GameObject({ 0,2 }, { 1,1 }, new Sprite(Color::white)));
		//jObject = new GameObject("Jackson's Object", { -1,2 }, { 1,1 }, new Sprite(new Texture(WATTYRESDIR "textures/error_texture.png")));
		//rObject = new GameObject("Rachels's Object", { 1,2 }, { 1,1 }, new Sprite(Color::yellow));
		//mainLayer2->add(jObject);
		//mainLayer2->add(rObject);

		mainLayer->add(
			new GameObject(
				{-1,0 }, {1,1},
				new Sprite(new Texture(RESDIR "textures/sprites/lpc/female_hurt.png"))
		));

		mainLayer->add(
			new GameObject(
				{1,0 }, {1,1},
				new Sprite(new Texture(RESDIR "textures/asterisk.png"))
		));
	}

	void tick() override {
		LETC::tick();
	}
	void update() override{
		sceneCamera->setSize( glm::vec2(	
					sceneCamera->getSize().x - 4.0f  * m_window->getScrollAmountThisFrameY(),
					sceneCamera->getSize().y - 2.25f * m_window->getScrollAmountThisFrameY()
				));

		for (size_t objI = 0; objI < allObjects.size(); objI++)
		{
			GameObject* tmp = allObjects[objI];
			float rX = Random::range(0, .2f);
			float rY = Random::range(0, .2f);
			int x = allObjectPos[objI].x;
			int y = allObjectPos[objI].y;
			tmp->transform->setPosition({x+ sin(gameTimer->elapsed()), y+sin(y + sin(gameTimer->elapsed()))});
			tmp->transform->setRotation(cos(x*2.0f*y) + sin(gameTimer->elapsed()));

			allSprites[objI]->setColor(
				glm::vec4(
					abs(tan(10 + tmp->transform->getPosition().x))>1? 1 : abs(tan(10 + tmp->transform->getPosition().x)),
					abs(sin(50 + tmp->transform->getPosition().y))>1? 1: abs(sin(50 + tmp->transform->getPosition().y)),
					abs(cos(-50 + tmp->transform->getPosition().x) / (tmp->transform->getPosition().y) + 1),
					1
				));
			
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






