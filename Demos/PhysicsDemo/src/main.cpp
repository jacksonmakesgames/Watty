
#include "../../L_ETC-core/src/letc.h"

#define LOG(x) std::cout << x << std::endl;
//#define __BUTTERFLY 1
#define __SOUND 1W

#define VERTPATH "J:/OneDrive/Projects/Game_Development/L_ETC/Demos/res/shaders/basic.vert"
#define FRAGLITPATH "J:/OneDrive/Projects/Game_Development/L_ETC/Demos/res/shaders/basic_lit.frag"
#define FRAGUNLITPATH "J:/OneDrive/Projects/Game_Development/L_ETC/Demos/res/shaders/basic_unlit.frag"
#define FONTPATH "J:/OneDrive/Projects/Game_Development/L_ETC/Demos/res/fonts/Roboto-Regular.ttf"
#define FONTITALICPATH "J:/OneDrive/Projects/Game_Development/L_ETC/Demos/res/fonts/Roboto-Italic.ttf"


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
class SimpleGame : public LETC {
	private:
		Window* m_window;
		GUILayer* m_engineControlLayer;
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

	public:
		SimpleGame() {}
		~SimpleGame() {

		}

		void init() override {
			m_window = createWindow("This little engine could", 1280, 720);
			m_window->setVSync(true);
			Vector2 fontScale = Vector2(m_window->getWidth() / 32.0f, m_window->getHeight() / 18.0f);
			math::Matrix4 ortho = math::Matrix4::orthographic(-16, 16, -9, 9, -10, 10);
			letc::physics::PhysicsWorld2D::setDebugDraw();

			Shader* shader0 = new Shader(VERTPATH,FRAGLITPATH);
			shader0->setUniform3f("light_pos", Vector3(16,16,0));
			shader0->setUniform1f("light_radius", 250.0f);
			shader0->setUniform1f("light_intensity", 1.1f);


			Layer* layer0 = new Layer("Ball Layer", new BatchRenderer2D(), shader0, ortho);
			layers.push_back(layer0);

			Layer* uiLayer = new Layer("UI Layer", new BatchRenderer2D(), new Shader(VERTPATH, FRAGUNLITPATH), math::Matrix4::orthographic(-16, 16, -9, 9, -10, 10));
			layers.push_back(uiLayer);
			
			FontManager::add(new Font("Roboto", FONTPATH, 10, fontScale)); 


			layer0->add(
				new GameObject(
					Vector3(-16, -9, 0),
					Vector2(32, 18),
					new Sprite(0xffF5F0F0)
				)
			);

			Vector3 playerPos(-2, -2, 0);
			Vector2 playerSize(2, 2);
			player = new GameObject(
				playerPos,
				playerSize,
				new Sprite(new Texture("J:/OneDrive/Projects/Game_Development/L_ETC/Demos/res/textures/Player.png")));

			player->addComponent(new PhysicsBody2D(
				physics::BodyShapes::circle,
				playerPos.x, playerPos.y,
				playerSize.x, playerSize.y,
				b2_dynamicBody, 0.6f, 0.5f));
			player->setTag("Player");
			layer0->add(player);

			boxTexture = new Texture("J:/OneDrive/Projects/Game_Development/L_ETC/Demos/res/textures/box.png");
			Texture* floorTexture = new Texture("J:/OneDrive/Projects/Game_Development/L_ETC/Demos/res/textures/floor.png");


			Vector3 floorPos(-16.0f,-9.0f,0);
			Vector2 floorSize(32, 2);
			GameObject* floor = new GameObject(floorPos, floorSize);
			floor->addComponent(new Sprite(floorPos.x, floorPos.y, floorSize.x, floorSize.y, floorTexture));
			floor->addComponent(new physics::PhysicsBody2D(physics::BodyShapes::box, floorPos.x, floorPos.y, floorSize.x, floorSize.y, b2_staticBody));
			//TODO BUG, physics bodies are still enabled even if the object is not in a layer
			layer0->add(floor);
			
			Vector3 floorPosL(-18.0f,-7.0f,0);
			Vector2 floorSizeL(2, 18);
			GameObject* floorL = new GameObject(floorPosL, floorSizeL);
			floorL->addComponent(new Sprite(floorPosL.x, floorPosL.y, floorSizeL.x, floorSizeL.y, floorTexture));
			floorL->addComponent(new physics::PhysicsBody2D(physics::BodyShapes::box, floorPosL.x, floorPosL.y, floorSizeL.x, floorSizeL.y, b2_staticBody));
			//TODO BUG, physics bodies are still enabled even if the object is not in a layer
			layer0->add(floorL);
			
			Vector3 floorPosR(16.0f,-7.0f,0);
			Vector2 floorSizeR(2, 18);
			GameObject* floorR = new GameObject(floorPosR, floorSizeR);
			floorR->addComponent(new Sprite(floorPosR.x, floorPosR.y, floorSizeR.x, floorSizeR.y, floorTexture));
			floorR->addComponent(new physics::PhysicsBody2D(physics::BodyShapes::box, floorPosR.x, floorPosR.y, floorSizeR.x, floorSizeR.y, b2_staticBody));
			//TODO BUG, physics bodies are still enabled even if the object is not in a layer
			layer0->add(floorR);

			math::Vector2 screenScale = math::Vector2(m_window->getWidth() / 32, m_window->getHeight() / 18);

			//TODO for now, it's best to keep the creation of textures close to where they get added to the layer. This is because if a texture is used in two separate draw calls, things won't show up properly
			FontManager::add(new Font("Roboto", "J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/res/fonts/Roboto-Regular.ttf", 16, screenScale));
			FontManager::add(new Font("Roboto", "J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/res/fonts/Roboto-Italic.ttf", 14, screenScale));

			Group* profileGroup = new Group(math::Matrix4::translation(Vector3(-15.5, 6.8, 0)));
			profileGroup->add(new GameObject(Vector3(0, 0, 0), Vector2(4.5f, 1.8), new Sprite(0x80808080)));
			fpsLabel = new Label("", "Roboto", 16, 0xffffffff);
			upsLabel = new Label("", "Roboto", 14, 0xffffffff);
			mpsLabel = new Label("", "Roboto", 14, 0xffffffff);
			profileGroup->add(new GameObject(Vector3(.3f, 1.2f, 0), fpsLabel));
			profileGroup->add(new GameObject(Vector3(.3f, .8f, 0), upsLabel));
			profileGroup->add(new GameObject(Vector3(.3f, .4f, 0), mpsLabel));
			uiLayer->add(profileGroup);

			AudioClip* clip = new AudioClip("slow_motion", "J:/OneDrive/Projects/Game_Development/L_ETC/Demos/res/sounds/slow_motion.ogg");
			AudioManager::addClip(clip);
			AudioManager::getClip("slow_motion")->play(true);
			AudioManager::getClip("slow_motion")->setGain(m_gain);

			GridLayer* gridLayer = new GridLayer(new Shader(VERTPATH, FRAGUNLITPATH), -16, 16, -9, 9, -10, 10);
			layers.push_back(gridLayer);
			gridLayer->disable();

			EngineControlLayer* engineControlLayer = new EngineControlLayer("LETC GUI Layer", debugPhysics, resetFlag, layers, new Shader(VERTPATH, FRAGUNLITPATH), ortho);
			layers.push_back(engineControlLayer);
			engineControlLayer->disable();

		}

		void update() override {
		
			getInput();
			PhysicsWorld2D::step(gameTimer->delta);
			LETC::update();
		}

		void render() override {

			LETC::render();
			if (debugPhysics) PhysicsWorld2D::box2DWorld->DrawDebugData();

		}

		void tick() override {

			fpsLabel->text = std::to_string(getFramesPerSecond()) + " frames / second";
			upsLabel->text = std::to_string(getUpdatesPerSecond()) + " updates / second";
			mpsLabel->text = std::to_string(getMSPerFrame()).substr(0, 5) + "ms / frame";
			LETC::tick();
		}

		void reset() override{
			for (size_t i = 0; i < boxes.size(); i++)
			{
				getLayerByName("Ball Layer")->remove(boxes[i]);
			}
		}

		void getInput() {
			// SOUND
			if (m_window->keyIsDown(GLFW_KEY_LEFT_BRACKET)) {
				m_gain -= 0.005f;
				AudioManager::getClip("slow_motion")->setGain(m_gain);

			}
			else if (m_window->keyIsDown(GLFW_KEY_RIGHT_BRACKET)) {
				m_gain += 0.005f;
				AudioManager::getClip("slow_motion")->setGain(m_gain);
			}
			else if (m_window->keyWasPressed(GLFW_KEY_P)) {
				AudioManager::getClip("slow_motion")->pause();
			}
			else if (m_window->keyWasPressed(GLFW_KEY_R)) {
				AudioManager::getClip("slow_motion")->resume();
				AudioManager::getClip("slow_motion")->setGain(m_gain);
			}

			// ENGINE
			if (m_window->keyWasPressed(GLFW_KEY_GRAVE_ACCENT))
				getLayerByName("LETC GUI Layer")->enabled = !getLayerByName("LETC GUI Layer")->enabled;

			// PLAYER
			float horizontal = -1*(float)(m_window->keyIsDown(GLFW_KEY_A) || m_window->keyIsDown(GLFW_KEY_LEFT)) + (float)(m_window->keyIsDown(GLFW_KEY_D) || m_window->keyIsDown(GLFW_KEY_RIGHT));
			//float vertical = (float)(m_window->keyIsDown(GLFW_KEY_W) || m_window->keyIsDown(GLFW_KEY_UP)) + -1*(float)(m_window->keyIsDown(GLFW_KEY_S) || m_window->keyIsDown(GLFW_KEY_DOWN));
			if (m_window->keyWasPressed(GLFW_KEY_SPACE))
				player->getPhysicsBody2D()->addImpulse(Vector2(0,1), playerJumpForce);

			player->getPhysicsBody2D()->addImpulse(Vector2(1, 0), horizontal * playerSpeed * gameTimer->delta);
			//player->position.x += playerSpeed * horizontal * (float)gameTimer->delta;
			
			if (player->position.y < -10.0f) {
				player->position.y = 10.0f;
				player->getPhysicsBody2D()->getBody()->SetTransform(b2Vec2(0,0), 0.0f);
				player->getPhysicsBody2D()->zeroVelocity();
			}

			// BOXES:
			double x, y;
			m_window->getMousePos(x, y);
			float xScreenMousePos = x * 32.0f / m_window->getWidth() - 16.0f;
			float yScreenMousePos = 9.0f - y * 18.0f / m_window->getHeight();
			//if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) {

			if (m_window->mouseButtonWasPressed(GLFW_MOUSE_BUTTON_LEFT)) {

				QueryAABBCallback* callback = new QueryAABBCallback(getLayerByName("Ball Layer"));
				b2AABB* aabb = new b2AABB();
				aabb->lowerBound = b2Vec2(xScreenMousePos - .01f, yScreenMousePos - .01f);
				aabb->upperBound = b2Vec2(xScreenMousePos + .01f, yScreenMousePos + .01f);

				PhysicsWorld2D::box2DWorld->QueryAABB(callback, *aabb);


				if (!callback->hit){
					m_grabbedBox = addBox();
					m_grabbedBox->getPhysicsBody2D()->setLinearVelocity(Vector2(0, 0));
					m_grabbedBox->getPhysicsBody2D()->getBody()->SetTransform(b2Vec2(xScreenMousePos, yScreenMousePos), m_grabbedBox->getPhysicsBody2D()->getBody()->GetAngle());

				}
				else {
					m_grabbedBox = callback->gameObjects[0];
				}
			}
			else if (m_window->mouseButtonWasReleased(GLFW_MOUSE_BUTTON_LEFT)) {
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

					m_grabbedBox->getPhysicsBody2D()->setLinearVelocity(Vector2(4*xDiff, 4*yDiff));
					m_grabbedBox = nullptr;
				}

			}


			else if (m_window->mouseButtonWasPressed(GLFW_MOUSE_BUTTON_RIGHT)) {

				QueryAABBCallback* callback = new QueryAABBCallback(getLayerByName("Ball Layer"));
				b2AABB* aabb = new b2AABB();
				aabb->lowerBound = b2Vec2(xScreenMousePos - .01f, yScreenMousePos - .01f);
				aabb->upperBound = b2Vec2(xScreenMousePos + .01f, yScreenMousePos + .01f);

				PhysicsWorld2D::box2DWorld->QueryAABB(callback, *aabb);
				if (callback->hit) {
					if (callback->gameObjects[0]->getTag() == "Box")
						getLayerByName("Ball Layer")->remove(callback->gameObjects[0]);
				}
			}

			else if (m_window->mouseButtonIsDown(GLFW_MOUSE_BUTTON_LEFT)) {
				if (m_grabbedBox != nullptr) {
					m_grabbedBox->getPhysicsBody2D()->setLinearVelocity(Vector2(0,0));
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
			m_window->getMousePos(x, y);
			float xScreenMousePos = x * 32.0f / m_window->getWidth() - 16.0f;
			float yScreenMousePos = 9.0f - y * 18.0f / m_window->getHeight();
			
			Vector2 boxSize(2, 2);
			Vector3 boxPos(xScreenMousePos-boxSize.x/2.0f, yScreenMousePos-boxSize.y/2.0f, 0);
			GameObject* box = new GameObject(boxPos, boxSize);
			box->addComponent(new Sprite(boxPos.x, boxPos.y, boxSize.x, boxSize.y, boxTexture));
			box->addComponent(new physics::PhysicsBody2D(physics::BodyShapes::box, boxPos.x, boxPos.y, boxSize.x, boxSize.y, b2_dynamicBody));
			box->setTag("Box");
			for (size_t i = 0; i < layers.size(); i++)
			{
				if (layers[i]->name == "Ball Layer") {
					layers[i]->add(box);
					boxes.push_back(box);
					return box;
				}
			}
			return nullptr;
		}
};



int main() {
	SimpleGame game;
	game.start();
	return 0;

}





