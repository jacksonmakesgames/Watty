#include <Watty.h>
#include <res.h>

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
	Label* fpsLabel;
	Label* upsLabel;
	std::vector<Sprite*> allSprites;
	std::vector <GameObject*> allObjects;
	std::vector<GameObject*> allObjects2;
	std::vector<glm::vec2> allObjectPos;
public:
	void init() override {
		RawResources::Init(); //TODO

		window->setSize({1920,1080});
		window->setTitle("{Watty Game Engine}");
		window->useVSync = false;
		glClearColor(.45, .23, .23, 1);

		Layer* guiLayer = new Layer("GUI");
		//setupSquares();
		AudioManager::addClip("drums", "audio/drums.wav");
		AudioManager::getClip("drums")->play(true);
		AudioManager::getClip("drums")->setGain(.5f);

		
		FontManager::add("test", "fonts/Lobster.ttf", 100);
		LabelProperties labelProps;
		labelProps.charsPerLine = 30;
		labelProps.text =	"";
		labelProps.font = FontManager::get("test");
		labelProps.color = Color::orange;
		labelProps.overflowMode = OverflowMode::Expand;
		fpsLabel = new Label(labelProps);
		labelProps.color = Color::white;
		upsLabel = new Label(labelProps);
		GameObject* fpsGO = Instantiate::Create<GameObject>({ -14, 7 }, {1,1},"GUI");
		GameObject* upsGO = Instantiate::Create<GameObject>({ -14, 5 }, {.5,.4}, "GUI");
		fpsGO->addComponent(fpsLabel);
		upsGO->addComponent(upsLabel);

		setupMotionTest();
	}
	glm::vec2 startKinematic;
	Transform2D* testTransform;
	PhysicsBody2D* testBody;
	void setupMotionTest() {
		GameObject* go = Instantiate::Create<GameObject>({ -10,2 }, { 2,2 });
		go->addComponent(new Sprite(0xffffffff));
		testTransform = go->transform;
		GameObject* child = Instantiate::Create<GameObject>({ 0,0 }, {.1f,.1f},"");
		child->addComponent(new Sprite(Color::orange));
		go->transform->addChild(child->transform);
		startKinematic = testTransform->getPosition();

		GameObject* go2 = Instantiate::Create<GameObject>({ -10,-2 }, { 2,2 });
		go2->addComponent(new Sprite(0xffffffff));
		GameObject* child2 = Instantiate::Create<GameObject>({ 0,0 }, { .1f,.1f }, "");
		child2->addComponent(new Sprite(Color::blue));
		go2->addComponent(new PhysicsBody2D(PhysicsBody2DParams(BodyShapes::box, { -10,2 }, { 2,2 }, b2BodyType::b2_dynamicBody)));
		testBody = go2->getPhysicsBody2D();
		testBody->getBody()->SetLinearDamping(0.0f);
		testBody->getBody()->SetLinearVelocity({1,0});
		testBody->addForce({1,0}, 1 );
		go2->transform->addChild(child2->transform);
		startPosPhysical = testBody->getBodyPosition();

	}

	void setupSquares() {
		for (int x = -20; x < 20; x++)
		{
			for (int y = -20; y < 20; y++) {
				//ABGR
				WattyColor col = Color::random();
				Sprite* sprite = new Sprite(col);
				GameObject* tmp = Instantiate::Create<GameObject>({ x,y }, { .8,.8 });
				tmp->addComponent(sprite);
				allSprites.push_back(sprite);
				allObjects.push_back(tmp);
				allObjectPos.push_back({ x,y });
			}

		}	for (int x = -20; x < 20; x++)
		{
			for (int y = -20; y < 20; y++) {
				//ABGR
				WattyColor col = Color::random();
				Sprite* sprite = new Sprite(col);
				GameObject* tmp = Instantiate::Create<GameObject>({ x,y }, { .8,.8 });
				tmp->addComponent(sprite);
				allSprites.push_back(sprite);
				allObjects2.push_back(tmp);
				allObjectPos.push_back({ x,y });
			}

		}

	}

	void tick() override {
		LETC::tick();
		fpsLabel->setText(std::string("FPS: ") + std::to_string(Stats::getFramesPerSecond()));
		upsLabel->setText(std::string("UPS: ") + std::to_string(Stats::getUpdatesPerSecond()));
	}
	void update() override{
		
		if (Input::keyWasPressed(GLFW_KEY_SPACE)) testDir *= -1;
		sceneCamera->setSize( glm::vec2(	
					sceneCamera->getSize().x - (100.0f*window->getAspectRatio().x  * Input::getScrollAmountThisFrameY())*Timer::delta,
					sceneCamera->getSize().y - (100.0f*window->getAspectRatio().y * Input::getScrollAmountThisFrameY())*Timer::delta
				));

		float r = Random::range(-1,1);
		float tFact = sin(Timer::elapsed());
		for (GameObject* go : allObjects)
		{
			pattern1(tFact, r, go);
		}
		for (GameObject* go : allObjects2)
		{
			pattern1(tFact*-1, r*2, go);
		}

		testMotion();

		LETC::update();
	}
	float totalDistKinematic = 0;
	float totalDistPhysical = 0;
	glm::vec2 startPosPhysical = {0,0};
	void testMotion() {
		int intTime = (int)Timer::elapsed();
		if (intTime != countedTime && intTime % 10 == 0) {
			testDir *= 0;
			countedTime = intTime;
			testBody->getBody()->SetLinearVelocity({0,0});
		}
		float fact = sin(Timer::elapsed());
		if (fact < 0) fact = -1;
		if (fact > 0) fact = 1;
		float speed = 1;
		totalDistKinematic += Timer::delta * testDir * speed;

		totalDistPhysical = glm::distance(testBody->getBodyPosition(), startPosPhysical);
		testTransform->translate({ Timer::delta * testDir * speed,0 });
	}
	void pattern1(float tFact, float r, GameObject* go) {
		tFact *= -.4f;
		float x = abs(go->transform->getPosition().x);
		float y = abs(go->transform->getPosition().y);

		go->transform->translate({ (y * tFact / (10.0f + x + y)),  x * (tFact) / (8.0f + pow(y + 2 * x,1)) });

		//go->transform->translate({sin( pow( sin(x * Timer::elapsed()),2) / 10), pow(cos(y * Timer::elapsed()),3) / (x+1) });

		//go->transform->rotate(Timer::delta * tan(.25f + x * r * tFact / 100.0f));
	}
	float testDir = 1;
	float maxTestX= -100000;
	float countedTime = 0;
	void OnGui() override{
		ImGui::Begin("debug info");
		ImGui::Text("%d seconds ", (int)Timer::elapsed());
		ImGui::Separator();
		float currentX = testTransform->getPosition().x;
		if (currentX > maxTestX) maxTestX = currentX;
		ImGui::Text("current X: %f | max: %f",currentX, maxTestX);
		ImGui::Separator();
		ImGui::Text("Distance Kinematic Sum:	  %f", totalDistKinematic);
		ImGui::Text("Distance Physical:           %f", totalDistPhysical);
		ImGui::End();
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






