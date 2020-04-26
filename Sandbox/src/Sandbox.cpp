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
		//DebugPhysics* PhysicsWorld2D::debugDraw = new DebugPhysics();
		//b2World* PhysicsWorld2D::box2DWorld = new b2World(b2Vec2(0.0f, 0.0f));
	}
}

class Sandbox : public LETC {
private:
	Window* m_window;
	GameObject* jObject;
	GameObject* rObject;
public:
	void init() override{
		m_window = createWindow("Sandbox", 1280, 720, false, false);
		Layer* mainLayer = new Layer("Layer 1");
		mainLayer->add(new GameObject("Test", { 0,0 }, { 1,1 }, new Sprite(Color::white)));
		layers.push_back(mainLayer);
		
		Layer* mainLayer2 = new Layer("Layer 2");
		mainLayer2->add(new GameObject({ 0,2 }, { 1,1 }, new Sprite(Color::white)));
		jObject = new GameObject("Jackson's Object", { -1,2 }, { 1,1 }, new Sprite(new Texture(WATTYRESDIR "textures/error_texture.png")));
		rObject = new GameObject("Rachels's Object", { 1,2 }, { 1,1 }, new Sprite(Color::yellow));
		mainLayer2->add(jObject);
		mainLayer2->add(rObject);
		layers.push_back(mainLayer2);
		mainLayer2->enabled = true;
	}

	void tick() override {
		LETC::tick();
	}
	void update() override{
		sceneCamera->setSize( glm::vec2(	
					sceneCamera->getSize().x - 4.0f  * m_window->getScrollAmountThisFrameY(),
					sceneCamera->getSize().y - 2.25f * m_window->getScrollAmountThisFrameY()
				));

		if(m_window->keyIsDown(GLFW_KEY_SPACE))
			jObject->transform->setPosition({ -1,2+sin(gameTimer->elapsed()) });
		
		rObject->transform->setPosition({ 1,2-sin(gameTimer->elapsed()) });


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






