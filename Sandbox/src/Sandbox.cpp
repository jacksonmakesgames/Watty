#include "Sandbox.h"

namespace letc {
	namespace physics {
		DebugPhysics* PhysicsWorld2D::debugDraw = new DebugPhysics();
		b2World* PhysicsWorld2D::box2DWorld = new b2World(b2Vec2(0.0f, 0.0f));
	}

	Sandbox* sandbox = new Sandbox();

	Sprite s = Sprite(Color::blue);


	class TestGameObject :public GameObject {
	public:
		TestGameObject(glm::vec2 position, glm::vec2 size):GameObject(position, size) {
		}

		void update() override {
			float horizontalAxis = -1 * (float)(Input::keyIsDown(GLFW_KEY_A) || Input::keyIsDown(GLFW_KEY_LEFT)) + (float)(Input::keyIsDown(GLFW_KEY_D) || Input::keyIsDown(GLFW_KEY_RIGHT));
			float verticalAxis = (float)(Input::keyIsDown(GLFW_KEY_W) || Input::keyIsDown(GLFW_KEY_UP)) + -1 * (float)(Input::keyIsDown(GLFW_KEY_S) || Input::keyIsDown(GLFW_KEY_DOWN));
			transform->translate({ horizontalAxis * 10.f * Timer::delta, verticalAxis * 10.f * Timer::delta });
			
			transform->rotate(Timer::delta);
			GameObject::update();
		}

	};

	struct Move2DComponent : public ECSComponent<Move2DComponent> {
		glm::vec2 movement = {0,0};
	};


	struct InputHandlerComponent : public ECSComponent<InputHandlerComponent> {
		double horizontalAxis =0;
		double verticalAxis = 0;
	};

	class InputHandlerSystem : public BaseECSSystem {
	public:
		InputHandlerSystem() {
			addComponentType(InputHandlerComponent::ID);
			addComponentType(Move2DComponent::ID);

		}
		virtual void updateComponents(float deltaTime, BaseECSComponent** components) override{
			InputHandlerComponent* input = (InputHandlerComponent*)components[0];
			input->horizontalAxis = -1 * (float)(Input::keyIsDown(GLFW_KEY_A) || Input::keyIsDown(GLFW_KEY_LEFT)) + (float)(Input::keyIsDown(GLFW_KEY_D) || Input::keyIsDown(GLFW_KEY_RIGHT));
			input->verticalAxis = (float)(Input::keyIsDown(GLFW_KEY_W) || Input::keyIsDown(GLFW_KEY_UP)) + -1 * (float)(Input::keyIsDown(GLFW_KEY_S) || Input::keyIsDown(GLFW_KEY_DOWN));

			Move2DComponent* move = (Move2DComponent*)components[1];
			move->movement = { input->horizontalAxis, input->verticalAxis };
		}
	};
	class MoveSystem : public BaseECSSystem {
	public:
		MoveSystem() {
			addComponentType(Transform2DComponent::ID);
			addComponentType(Move2DComponent::ID);
		}

		virtual void updateComponents(float deltaTime, BaseECSComponent** components) override {
			Transform2DComponent* transform = (Transform2DComponent*)components[0];
			Move2DComponent* move = (Move2DComponent*)components[1];
			glm::vec2 newPos = transform->position + move->movement * 10.0f * deltaTime;
			if (newPos != transform->position) {
				transform->position = newPos;
			}
			transform->rotation += deltaTime;
				transform->transformMatrix = calculateMatrix(transform->position, transform->size, transform->rotation);
		}

		glm::mat4 calculateMatrix(glm::vec2 position, glm::vec2 size, float rotation) {
			glm::mat4 transformMatrix = glm::mat4(1.0f);
			glm::vec3 drawPosition = {
				position.x,
				position.y,
				0.0f
			};

			//if (parent != nullptr)
			//	transformMatrix = glm::translate(transformMatrix, glm::vec3(0.25f * parent->getSize().x, 0.25f * parent->getSize().y, 0.0f));

			drawPosition.x -= .5f * size.x;
			drawPosition.y -= .5f * size.y;


			//Position
			transformMatrix = glm::translate(transformMatrix, drawPosition);										// Move to drawing position

			//Rotation
			transformMatrix = glm::translate(transformMatrix, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));	    // Offset for rotate
			transformMatrix = glm::rotate(transformMatrix, rotation, glm::vec3(0.0f, 0.0f, 1.0f));					// Rotate on Z
			transformMatrix = glm::translate(transformMatrix, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));     // Move back to draw position

			//Scale
			transformMatrix = glm::scale(transformMatrix, glm::vec3(size, 1.0f));									// Scale
			
			return transformMatrix;
		}
	};


	const unsigned int TEST_AMT = 6000;

	Transform2DComponent		*transformC		;
	MoveSystem					*moveSystem		;
	InputHandlerSystem			*inputSystem	;
	Move2DComponent				*moveC			;
	InputHandlerComponent		*inputC			;
	RenderableSpriteComponent	*renderableC	;
	WattyColor c = Color::white;
	void Sandbox::init() {
		sandboxInit();

		// ECS:
		//TestECS();
		//TestRegular();

		setupSquares();

	}

	void Sandbox::TestRegular() {
		new graphics::GridLayer(*sceneCamera, *window);

		Sprite* sr = new Sprite("textures/asterisk.png");
		for (size_t i = 0; i < TEST_AMT; i++) {
			TestGameObject* go = Instantiate<TestGameObject>({ Random::range(-16, 16), Random::range(-9, 9) }, {1,1});
			go->addComponent(sr);
		}	
	}

	void Sandbox::TestECS() {
		transformC = new Transform2DComponent();
		moveSystem = new MoveSystem();
		inputSystem = new InputHandlerSystem();
		moveC = new Move2DComponent();
		inputC = new InputHandlerComponent();
		renderableC = new RenderableSpriteComponent();

		renderableC->texture = Texture("textures/asterisk.png");

		for (size_t i = 0; i < TEST_AMT; i++){
			transformC->position = { Random::range(-16,16), Random::range(-9,9) };
			ecs.makeEntity(*transformC, *moveC, *inputC, *renderableC);
		}


		//Systems:
		mainSystems.addSystem(*inputSystem);
		mainSystems.addSystem(*moveSystem);

	}
	void Sandbox::tick() {
		LETC::tick();
		if(fpsLabel)
			fpsLabel->setText(std::string("FPS: ") + std::to_string(Stats::getFramesPerSecond()));
		if(upsLabel)
			upsLabel->setText(std::string("UPS: ") + std::to_string(Stats::getUpdatesPerSecond()));


	}
	void Sandbox::update(){
		//testMotion();	

		sceneCamera->setSize(glm::vec2(
			sceneCamera->getSize().x - (10.0f * window->getAspectRatio().x * Input::getScrollAmountThisFrameY()) * Timer::delta,
			sceneCamera->getSize().y - (10.0f * window->getAspectRatio().y * Input::getScrollAmountThisFrameY()) * Timer::delta
		));

		squaresUpdate();

		//LETC::update();
	}
	void Sandbox::OnGui() {
		//ImGui::Begin("debug info");
		//ImGui::End();
	}
	void Sandbox::render() {
		LETC::render();
	}
}

int main() {

	sandbox->start();
	return 0;
}





