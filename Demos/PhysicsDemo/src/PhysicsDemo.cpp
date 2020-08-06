
#include <Watty.h>
#include <res.h>

#define LOG(x) std::cout << x << std::endl;
//#define __BUTTERFLY 1
#define __SOUND 1

#define FRAGLITPATH  "shaders/basic_lit.frag"
#define FONTPATH  "fonts/Roboto-Regular.ttf"
#define FONTITALICPATH  "fonts/Roboto-Italic.ttf"
#define FLOORTEXTUREPATH  "textures/floor.png"
#define MUSICPATH  "sounds/slow_motion.ogg"

using namespace letc;
using namespace graphics;
using namespace math;
using namespace audio;
using namespace physics;

namespace letc {
	namespace physics {
		DebugPhysics* PhysicsWorld2D::debugDraw = new DebugPhysics();
		b2World* PhysicsWorld2D::box2DWorld = new b2World(b2Vec2(0.0f, -20.0f));

	}
}
class PhysicsDemo : public LETC {
	private:
		Label* fpsLabel;
		Label* upsLabel;
		Label* mpsLabel;
		std::vector<GameObject*> boxes;
		float m_gain = 0.5f;

		float playerSpeed = 70;
		float playerAcceleration = .9f;
		float playerJumpForce = 35;


		float m_lastMouseX;
		float m_lastMouseY;
		std::vector<float> m_lastXs;
		std::vector<float> m_lastYs;

		float time = 0.0f;

		GameObject* player;

		Texture* boxTexture;

		GameObject* m_grabbedBox = nullptr;
		Shader* shader0;
		
		//Camera* m_camera;

	public:
		PhysicsDemo() {}
		~PhysicsDemo() {

		}

		void init() override {
			RawResources::Init();
			window->setTitle("This Little Engine Could");
			window->setSize({1290, 720});
			glm::vec2 fontScale = glm::vec2(window->getWidth() / 32.0f, window->getHeight() / 18.0f);

#ifdef WATTY_EMSCRIPTEN
			shader0 = new Shader(); // Can't use OGL4 shaders on WebGL2
#else
			shader0 = new Shader(DEFAULT_SHADER_VERT_PATH, FRAGLITPATH);
			shader0->setUniform3f("light_pos", glm::vec3(16,16,0));
			shader0->setUniform1f("light_radius", 250.0f);
			shader0->setUniform1f("light_intensity", 1.1f);

#endif

			Layer* layer0 = new Layer("Ball Layer", new BatchRenderer2D(), shader0);
			Layer* floorLayer = new Layer("Floor Layer", new BatchRenderer2D(), shader0);
			Layer* uiLayer = new Layer("UI Layer");
			
			//FontManager::add(new Font("Roboto", FONTPATH, 10, fontScale)); 

			// background
			layer0->add(
				new GameObject(
					glm::vec3(0, 0, 0),
					glm::vec2(32, 18),
					new Sprite(0xffF5F0F0)
				)
			);

			glm::vec3 playerPos(0, 2, 0);
			glm::vec2 playerSize(2, 2);
			player = new GameObject(
				playerPos,
				playerSize,
				new Sprite(new Texture( "textures/Player.png")));

			player->addComponent(new PhysicsBody2D(PhysicsBody2DParams(
				physics::BodyShapes::circle,
				playerPos,
				playerSize,
				b2_dynamicBody,
				false,
				glm::vec2(),
				0.6f, 0.5f)));

			player->setTag("Player");
			layer0->add(player);

			boxTexture = new Texture( "textures/box.png");
			Texture* floorTexture = new Texture(FLOORTEXTUREPATH);

			glm::vec3 floorPos(0,-9.0f,0);
			glm::vec2 floorSize(32, 2);

			PhysicsBody2DParams wallParams = PhysicsBody2DParams(physics::BodyShapes::box, floorPos, floorSize, b2_staticBody);

			GameObject* floor = new GameObject(floorPos, floorSize);
			floor->addComponent(new Sprite(floorPos.x, floorPos.y, floorSize.x, floorSize.y, floorTexture));
			floor->addComponent(new physics::PhysicsBody2D(wallParams));
			//TODO BUG, physics bodies are still enabled even if the object is not in a layer
			floorLayer->add(floor);
			
			glm::vec3 floorPosL(-17.0f,0,0);
			glm::vec2 floorSizeL(2, 18);
			wallParams.size = floorSizeL;
			GameObject* floorL = new GameObject(floorPosL, floorSizeL);
			floorL->addComponent(new Sprite(floorPosL.x, floorPosL.y, floorSizeL.x, floorSizeL.y, floorTexture));
			floorL->addComponent(new physics::PhysicsBody2D(wallParams));
			//TODO BUG, physics bodies are still enabled even if the object is not in a layer
			floorLayer->add(floorL);
			
			glm::vec3 floorPosR(17.0f,0,0);
			glm::vec2 floorSizeR(2, 18);
			GameObject* floorR = new GameObject(floorPosR, floorSizeR);
			floorR->addComponent(new Sprite(floorPosR.x, floorPosR.y, floorSizeR.x, floorSizeR.y, floorTexture));
			floorR->addComponent(new physics::PhysicsBody2D(wallParams));
			//TODO BUG, physics bodies are still enabled even if the object is not in a layer
			floorLayer->add(floorR);

			glm::vec2 screenScale = glm::vec2(window->getWidth() / 32, window->getHeight() / 18);
			
			//FONTS:
			/*
			//TODO for now, it's best to keep the creation of textures close to where they get added to the layer. This is because if a texture is used in two separate draw calls, things won't show up properly
			FontManager::add(new Font("Roboto",FONTPATH, 16, screenScale));
			FontManager::add(new Font("Roboto", FONTITALICPATH, 14, screenScale));

			// PROFILING
			GameObject* profileGroup = new GameObject({ -14, 8, 0 }, { 4.0f,2.0f }, new Sprite(Color::pink));
			GameObject* bkg = new GameObject(glm::vec3(0, 0, 0), {1.0f,1.0f}, new Sprite(0x80808080));
			fpsLabel = new Label("", "Roboto", 16, 0xffffffff); GameObject* fpsGO = new GameObject(glm::vec3(0, 1.f, 0), {.5f,.5f}, fpsLabel);
			upsLabel = new Label("", "Roboto", 14, 0xffffffff);	GameObject* upsGO = new GameObject(glm::vec3(.3f, .8f, 0), upsLabel);
			mpsLabel = new Label("", "Roboto", 14, 0xffffffff);	GameObject* mpsGO = new GameObject(glm::vec3(.3f, .4f, 0), mpsLabel);
			profileGroup->transform->addChild(bkg->transform);
			profileGroup->transform->addChild(fpsGO->transform);
			profileGroup->transform->addChild(upsGO->transform);
			profileGroup->transform->addChild(mpsGO->transform);
			uiLayer->add(profileGroup);
			*/
			AudioManager::addClip("slow_motion", MUSICPATH);
			AudioManager::getClip("slow_motion")->play(true);
			AudioManager::getClip("slow_motion")->setGain(m_gain);

			// TODO: crashes in fullscreen
			//GridLayer* gridLayer = new GridLayer(new Shader(VERTPATH, FRAGUNLITPATH), sceneCamera->position, 32, glm::vec2(m_window->getWidth(), m_window->getHeight()));
			//layers.push_back(gridLayer);
			//gridLayer->disable();


			//m_camera = new Camera(&layers, glm::vec3(0, 0, -1), glm::vec2(32.0f, 18.0f), 20, CameraMode::orthographic);

	}

		void update() override {
		
			getInput();
			checkBoxes();
			LETC::update();

		}

		void render() override {
			LETC::render();
		}

		void tick() override {
			//fpsLabel->text = std::to_string(getFramesPerSecond()) + " frames / second";
			//upsLabel->text = std::to_string(getUpdatesPerSecond()) + " updates / second";
			//mpsLabel->text = std::to_string(getMSPerFrame()).substr(0, 5) + "ms / frame";
			LETC::tick();
		}

		void reset() override{
			for (size_t i = 0; i < boxes.size(); i++)
			{
				Destroy(boxes[i]);
				//Layer::getLayerByName("Ball Layer")->remove(boxes[i]);
			}
			boxes.clear();
		}

		void checkBoxes() {
			boxes.clear();
			for (size_t bI = 0; bI < Layer::getLayerByName("Ball Layer")->getGameObjects().size(); bI++){
				if(Layer::getLayerByName("Ball Layer")->getGameObjects()[bI]->getTag() == "Box")
					boxes.push_back(Layer::getLayerByName("Ball Layer")->getGameObjects()[bI]);
			}
			
			for (size_t i = 0; i < boxes.size(); i++)
			{
			if (boxes[i]->transform->getPosition().y < -10 && m_grabbedBox != boxes[i]) {
				Layer::getLayerByName("Ball Layer")->remove(boxes[i]);
			}
			}

		}

		void getInput() {
			if (Input::keyWasPressed(GLFW_KEY_V)) {
				Window::setVSync(!Window::useVSync);
			}
			// SOUND
			if (Input::keyIsDown(GLFW_KEY_LEFT_BRACKET)) {
				m_gain -= 0.005f;
				AudioManager::getClip("slow_motion")->setGain(m_gain);

			}
			else if (Input::keyIsDown(GLFW_KEY_RIGHT_BRACKET)) {
				m_gain += 0.005f;
				AudioManager::getClip("slow_motion")->setGain(m_gain);
			}
			else if (Input::keyWasPressed(GLFW_KEY_P)) {
				AudioManager::getClip("slow_motion")->pause();
			}
			else if (Input::keyWasPressed(GLFW_KEY_R)) {
				AudioManager::getClip("slow_motion")->resume();
				AudioManager::getClip("slow_motion")->setGain(m_gain);
			}

			// PLAYER
			float horizontal = -1*(float)(Input::keyIsDown(GLFW_KEY_A) || Input::keyIsDown(GLFW_KEY_LEFT)) + (float)(Input::keyIsDown(GLFW_KEY_D) || Input::keyIsDown(GLFW_KEY_RIGHT));
			//float vertical = (float)(Input::keyIsDown(GLFW_KEY_W) || Input::keyIsDown(GLFW_KEY_UP)) + -1*(float)(Input::keyIsDown(GLFW_KEY_S) || Input::keyIsDown(GLFW_KEY_DOWN));
			if (Input::keyWasPressed(GLFW_KEY_SPACE))
				player->getPhysicsBody2D()->addImpulse(glm::vec2(0,1), playerJumpForce);

			player->getPhysicsBody2D()->addImpulse(glm::vec2(1, 0), horizontal * playerSpeed * Timer::delta);

			//player->position.x += playerSpeed * horizontal * (float)Timer::delta;
			glm::vec2 playerPos = player->transform->getPosition();
			if (playerPos.y < -10.0f) {
				player->transform->setPosition({ 0, 10 });
				player->getPhysicsBody2D()->getBody()->SetTransform(b2Vec2(0,0), 0.0f);
				player->getPhysicsBody2D()->zeroVelocity();
			}

			// BOXES:
			double x, y;
			Input::getMousePos(x, y);
			float xScreenMousePos = x * 32.0f / window->getWidth() - 16.0f;
			float yScreenMousePos = 9.0f - y * 18.0f / window->getHeight();

			if (Input::mouseButtonWasPressed(GLFW_MOUSE_BUTTON_LEFT) && (!ImGui::GetIO().WantCaptureMouse)) {

				QueryAABBCallback* callback = new QueryAABBCallback(Layer::getLayerByName("Ball Layer"));
				b2AABB* aabb = new b2AABB();
				aabb->lowerBound = b2Vec2(xScreenMousePos - .01f, yScreenMousePos - .01f);
				aabb->upperBound = b2Vec2(xScreenMousePos + .01f, yScreenMousePos + .01f);

				PhysicsWorld2D::box2DWorld->QueryAABB(callback, *aabb);


				if (!callback->hit){
					m_grabbedBox = addBox();
					m_grabbedBox->getPhysicsBody2D()->setLinearVelocity(glm::vec2(0, 0));
					m_grabbedBox->getPhysicsBody2D()->getBody()->SetTransform(b2Vec2(xScreenMousePos, yScreenMousePos), m_grabbedBox->getPhysicsBody2D()->getBody()->GetAngle());

				}
				else
					m_grabbedBox = callback->gameObjects[0];
				
			}
			else if (Input::mouseButtonWasReleased(GLFW_MOUSE_BUTTON_LEFT) && (!ImGui::GetIO().WantCaptureMouse)) {
				if (m_grabbedBox) {
					float xSum = 0;
					for (size_t i = 0; i < m_lastXs.size(); i++)
					{
						xSum+=(m_lastXs[i]);
					}
						float ySum = 0;
					for (size_t i = 0; i < m_lastYs.size(); i++)
					{
						ySum+=m_lastYs[i];
					}

					float xAvg = xSum / 30;
					float yAvg = ySum / 30;

					float xDiff = xScreenMousePos - xAvg;
					float yDiff = yScreenMousePos - yAvg;

					m_grabbedBox->getPhysicsBody2D()->setLinearVelocity(glm::vec2(4*xDiff, 4*yDiff));
					m_grabbedBox = nullptr;
				}

			}


			else if (Input::mouseButtonWasPressed(GLFW_MOUSE_BUTTON_RIGHT) && (!ImGui::GetIO().WantCaptureMouse)) {

				QueryAABBCallback* callback = new QueryAABBCallback(Layer::getLayerByName("Ball Layer"));
				b2AABB* aabb = new b2AABB();
				aabb->lowerBound = b2Vec2(xScreenMousePos - .01f, yScreenMousePos - .01f);
				aabb->upperBound = b2Vec2(xScreenMousePos + .01f, yScreenMousePos + .01f);

				PhysicsWorld2D::box2DWorld->QueryAABB(callback, *aabb);
				if (callback->hit) {
					if (callback->gameObjects[0]->getTag() == "Box") {
						Layer::getLayerByName("Ball Layer")->remove(callback->gameObjects[0]);
					}
				}
			}

			else if (Input::mouseButtonIsDown(GLFW_MOUSE_BUTTON_LEFT) && (!ImGui::GetIO().WantCaptureMouse)) {
				if (m_grabbedBox != nullptr) {
					m_grabbedBox->getPhysicsBody2D()->setLinearVelocity(glm::vec2(0,0));
					m_grabbedBox->getPhysicsBody2D()->getBody()->SetTransform(b2Vec2(xScreenMousePos, yScreenMousePos), m_grabbedBox->getPhysicsBody2D()->getBody()->GetAngle());
				}

			}
			m_lastXs.push_back(xScreenMousePos);
			m_lastYs.push_back(yScreenMousePos);
			if (m_lastYs.size() > 30) {
				m_lastXs.erase(m_lastXs.begin());
				m_lastYs.erase(m_lastYs.begin());
				m_lastXs.shrink_to_fit();
				m_lastYs.shrink_to_fit();
			}
		}

		GameObject* addBox() {
			double x, y;
			Input::getMousePos(x, y);
			float xScreenMousePos = x * 32.0f / window->getWidth() - 16.0f;
			float yScreenMousePos = 9.0f - y * 18.0f / window->getHeight();
			
			glm::vec2 boxSize(2, 2);
			glm::vec3 boxPos(xScreenMousePos, yScreenMousePos, 0);
			GameObject* box = Instantiate<GameObject>(boxPos, boxSize,"Ball Layer");
			box->addComponent(new Sprite(boxPos.x, boxPos.y, boxSize.x, boxSize.y, boxTexture));
			box->addComponent(new physics::PhysicsBody2D(
				PhysicsBody2DParams(
					physics::BodyShapes::box,
					boxPos,
					boxSize,
					b2_dynamicBody))
			);
			box->setTag("Box");
			boxes.push_back(box);
			return box;
		}
};



int main() {
	PhysicsDemo game;
	game.start();
	return 0;

}





