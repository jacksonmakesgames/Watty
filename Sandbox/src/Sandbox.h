#pragma once
#include <Watty.h>
#include <res.h>

using namespace letc;
using namespace graphics;
using namespace math;
using namespace audio;
using namespace physics;
using namespace glm;


namespace letc {
	class Sandbox : public LETC {
	public:
	private:
		std::vector<Sprite*> allSprites;
		std::vector <GameObject*> allObjects;
		std::vector<GameObject*> allObjects2;
		std::vector<glm::vec2> allObjectPos;
		ParticleSystem* s;
		GameObject* pg;
		Label* fpsLabel;
		Label* upsLabel;
		glm::vec2 startKinematic;
		Transform2D* testTransform;
		PhysicsBody2D* testBody;

		float totalDistKinematic = 0;
		float totalDistPhysical = 0;
		glm::vec2 startPosPhysical = { 0,0 };

		float testDir = 1;
		float maxTestX = -100000;
		float countedTime = 0;

		ParticleProperties* particleProps;

	public:
		void init() override;
		void tick() override;
		void update() override;
		void OnGui() override;
		void render() override;

	private:
		void sandboxInit() {
			RawResources::Init(); //TODO
			window->setSize({ 1920,1080 });
			window->setTitle("{Watty Game Engine}");
			window->useVSync = false;
			glClearColor(.45, .23, .23, 1);
			//basicSetup();
		};
		void TestECS();
		void TestRegular();

		void basicSetup() {

			Layer* guiLayer = new Layer("GUI");
			AudioManager::addClip("drums", "audio/drums.wav");
			AudioManager::getClip("drums")->play(true);
			AudioManager::getClip("drums")->setGain(.5f);

			FontManager::add("test", "fonts/Lobster.ttf", 100);
			LabelProperties labelProps;
			labelProps.charsPerLine = 30;
			labelProps.text = "";
			labelProps.font = FontManager::get("test");
			labelProps.color = Color::orange;
			labelProps.overflowMode = OverflowMode::Expand;
			fpsLabel = new Label(labelProps);
			labelProps.color = Color::white;
			upsLabel = new Label(labelProps);
			GameObject* fpsGO = Instantiate<GameObject>({ -14, 7 }, { 1,1 }, "GUI");
			GameObject* upsGO = Instantiate<GameObject>({ -14, 5 }, { .5,.4 }, "GUI");
			fpsGO->addComponent(fpsLabel);
			upsGO->addComponent(upsLabel);
			//setupSquares();

			particleProps = new ParticleProperties();
			particleProps->lifeTime = 1;
			particleProps->velocity = { -5,0 };
			particleProps->colorBegin = Color::white;
			particleProps->colorEnd = Color::transparent;
			particleProps->velocityVariation = { 0.2,0.2 };
			particleProps->position = { 0,0 };
			particleProps->rotationSpeed = 2;
			particleProps->rotationSpeedVariation = 100.0f;
			particleProps->sizeVariation = .5f;
			particleProps->sizeBegin = 1;
			particleProps->sizeEnd = 0;
			particleProps->maxParticles = 100;
			particleProps->texture = new Texture("textures/smoke.png");
			s = new ParticleSystem(particleProps);
			pg = new GameObject({ -.8f,0 }, { .5,.5 });
			pg->addComponent(s);
			setupMotionTest();
		}

		void setupMotionTest() {
			GameObject* go = Instantiate<GameObject>({ -10,2 }, { 2,2 });
			go->addComponent(new Sprite(0xffffffff));
			testTransform = go->transform;
			GameObject* child = Instantiate<GameObject>({ 0,0 }, { .1f,.1f }, "");
			child->addComponent(new Sprite(Color::orange));
			go->transform->addChild(child->transform);
			startKinematic = testTransform->getPosition();
			go->transform->addChild(pg->transform);
			GameObject* go2 = Instantiate<GameObject>({ -10,-2 }, { 2,2 });
			go2->addComponent(new Sprite(0xffffffff));
			GameObject* child2 = Instantiate<GameObject>({ 0,0 }, { .1f,.1f }, "");
			child2->addComponent(new Sprite(Color::blue));
			go2->addComponent(new PhysicsBody2D(PhysicsBody2DParams(BodyShapes::box, { -10,2 }, { 2,2 }, b2BodyType::b2_dynamicBody)));
			testBody = go2->getPhysicsBody2D();
			testBody->getBody()->SetLinearDamping(0.0f);
			testBody->getBody()->SetLinearVelocity({ 1,0 });
			testBody->addForce({ 1,0 }, 1);
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
					GameObject* tmp = Instantiate<GameObject>({ x,y }, { .8,.8 });
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
					GameObject* tmp = Instantiate<GameObject>({ x,y }, { .8,.8 });
					tmp->addComponent(sprite);
					allSprites.push_back(sprite);
					allObjects2.push_back(tmp);
					allObjectPos.push_back({ x,y });
				}

			}

		}

		void squaresUpdate() {
			float r = Random::range(-1, 1);
			float tFact = sin(Timer::elapsed());
			for (GameObject* go : allObjects)
			{
				squaresPattern1(tFact, r, go);
			}
			for (GameObject* go : allObjects2)
			{
				squaresPattern1(tFact * -1, r * 2, go);
			}

		}


		void testMotion() {
			int intTime = (int)Timer::elapsed();
			if (intTime != countedTime && intTime % 10 == 0) {
				testDir *= 0;
				countedTime = intTime;
				testBody->getBody()->SetLinearVelocity({ 0,0 });
			}
			float fact = sin(Timer::elapsed());
			if (fact < 0) fact = -1;
			if (fact > 0) fact = 1;
			float speed = 1;
			totalDistKinematic += Timer::delta * testDir * speed;

			totalDistPhysical = glm::distance(testBody->getBodyPosition(), startPosPhysical);
			testTransform->translate({ Timer::delta * testDir * speed,0 });
		}
		void squaresPattern1(float tFact, float r, GameObject* go) {
			tFact *= -.4f;
			float x = abs(go->transform->getPosition().x);
			float y = abs(go->transform->getPosition().y);
			go->transform->translate({ (y * tFact / (10.0f + x + y)),  x * (tFact) / (8.0f + pow(y + 2 * x,1)) });
			//go->transform->translate({sin( pow( sin(x * Timer::elapsed()),2) / 10), pow(cos(y * Timer::elapsed()),3) / (x+1) });
			//go->transform->rotate(Timer::delta * tan(.25f + x * r * tFact / 100.0f));
		}

		~Sandbox() {
		}

	};
}