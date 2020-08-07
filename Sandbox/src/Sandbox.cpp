#include "Sandbox.h"

namespace letc {
	namespace physics {
		DebugPhysics* PhysicsWorld2D::debugDraw = new DebugPhysics();
		b2World* PhysicsWorld2D::box2DWorld = new b2World(b2Vec2(0.0f, 0.0f));
	}

	void Sandbox::init() {
		RawResources::Init(); //TODO
		window->setSize({ 1920,1080 });
		window->setTitle("{Watty Game Engine}");
		window->useVSync = false;
		glClearColor(.45, .23, .23, 1);

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

		particleProps= new ParticleProperties();
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


	void Sandbox::tick() {
		LETC::tick();
		fpsLabel->setText(std::string("FPS: ") + std::to_string(Stats::getFramesPerSecond()));
		upsLabel->setText(std::string("UPS: ") + std::to_string(Stats::getUpdatesPerSecond()));
	}
	void Sandbox::update(){
		
		sceneCamera->setSize(glm::vec2(
			sceneCamera->getSize().x - (10.0f * window->getAspectRatio().x * Input::getScrollAmountThisFrameY()) * Timer::delta,
			sceneCamera->getSize().y - (10.0f * window->getAspectRatio().y * Input::getScrollAmountThisFrameY()) * Timer::delta
		));

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

		testMotion();

		LETC::update();
	}
	void Sandbox::OnGui() {
		ImGui::Begin("debug info");
		ImGui::End();
	}
	void Sandbox::render() {

		LETC::render();
	}

}

int main() {
	Sandbox* sandbox = new Sandbox();
	sandbox->start();
	return 0;
}





