#include "Sandbox.h"

namespace letc {
	namespace physics {
		DebugPhysics* PhysicsWorld2D::debugDraw = new DebugPhysics();
		b2World* PhysicsWorld2D::box2DWorld = new b2World(b2Vec2(0.0f, 0.0f));
	}

	void Sandbox::init() {
		sandboxInit();
	}


	void Sandbox::tick() {
		LETC::tick();
		if(fpsLabel)
			fpsLabel->setText(std::string("FPS: ") + std::to_string(Stats::getFramesPerSecond()));
		if(upsLabel)
			upsLabel->setText(std::string("UPS: ") + std::to_string(Stats::getUpdatesPerSecond()));
	}
	void Sandbox::update(){
		
		sceneCamera->setSize(glm::vec2(
			sceneCamera->getSize().x - (10.0f * window->getAspectRatio().x * Input::getScrollAmountThisFrameY()) * Timer::delta,
			sceneCamera->getSize().y - (10.0f * window->getAspectRatio().y * Input::getScrollAmountThisFrameY()) * Timer::delta
		));

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





