
#include "src/math/math.h"
#include "src/math/matrix4.h"

#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"
#include "src/graphics/simple2drenderer.h"
#include "src/graphics/batchrenderer2d.h"
#include "src/graphics/sprite.h"
#include "src/graphics/layers/layer.h"
#include "src/graphics/layers/GridLayer.h"
#include "src/graphics/layers/GUILayer.h"
#include "src/graphics/layers/group.h"
#include "src/graphics/texture.h"
#include "src/graphics/font/label.h"
#include "src/graphics/font/fontmanager.h"
#include "src/utils/timer.h"
//#include "src/GameObject.h"
#include "ext/Box2D/Box2D.h"
#include "src/physics/PhysicsWorld2D.h"
#include "src/physics/DebugPhysics.h"

#include <vector>
#include <stdio.h>
#include <time.h>

#include <imgui/imgui.h>
#include "src/graphics/imgui/imgui_impl_glfw.h"
#include "src/graphics/imgui/imgui_impl_opengl3.h"



#define LOG(x) std::cout << x << std::endl;

// NOTE: COLORS ARE ABGR
#define WHITE 0xFFFFFFFF
#define BLUE 0xFFFF0000
#define PINK 0xFFFF80FF
#define BLACK 0xFF000000
#define GREY 0xFF808080

//#define __BUTTERFLY 1
#define __SOUND 1

b2World* letc::physics::PhysicsWorld2D::box2DWorld = new b2World(b2Vec2(0.0f, -10.0f));

letc::physics::DebugPhysics* letc::physics::PhysicsWorld2D::debugDraw = new letc::physics::DebugPhysics();

#include "src/letc.h"
using namespace letc;
using namespace graphics;
using namespace math;
using namespace audio;
class SimpleGame : public LETC {
	private:
		Window* m_window;
		GUILayer* m_guiLayer;
		Label* fpsLabel;
		Label* upsLabel;
		Label* mpsLabel;

		float m_gain = 0.5f;

		float playerSpeed = 5000;
		float playerAcceleration = .9f;

		float time = 0.0f;

		GameObject* player;

	public:
		SimpleGame() {}
		~SimpleGame() {

		}

		void init() override {
			initPhysics();
			letc::physics::PhysicsWorld2D::setDebugDraw();

			m_window = createWindow("This little engine could", 1280, 720);
			m_window->setVSync(true);
			Vector2 fontScale = Vector2(m_window->getWidth() / 32.0f, m_window->getHeight() / 18.0f);
			math::Matrix4 ortho = math::Matrix4::orthographic(-16, 16, -9, 9, -10, 10);

			layers.push_back(new GridLayer(new Shader("src/shaders/basic.vert", "src/shaders/basic_unlit.frag"), -16, 16, -9, 9, -10, 10));

			Shader* guiShader = new Shader("src/shaders/basic.vert", "src/shaders/basic_unlit.frag");
			GUILayer* guiLayer = new GUILayer(*this, guiShader, ortho);
			layers.push_back(guiLayer);

			Shader* shader0 = new Shader("src/shaders/basic.vert", "src/shaders/basic_unlit.frag");
			Layer* layer0 = new Layer("Ball Layer", new BatchRenderer2D(), shader0, ortho);
			layers.push_back(layer0);

			Shader* shader1 = new Shader("src/shaders/basic.vert", "src/shaders/basic_unlit.frag");
			Layer* layer1 = new Layer("Layer1", new BatchRenderer2D(), shader1, ortho);
			layers.push_back(layer1);

			Layer* uiLayer = new Layer("UI Layer", new BatchRenderer2D(), new Shader("src/shaders/basic.vert", "src/shaders/basic_unlit.frag"), math::Matrix4::orthographic(-16, 16, -9, 9, -10, 10));
			layers.push_back(uiLayer);

#ifdef __BUTTERFLY

			Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic_lit.frag");
			Shader& litShader = *s;

			TileLayer layer(&litShader);

			Shader* s2 = new Shader("src/shaders/basic.vert", "src/shaders/basic_unlit.frag");
			Shader& shader2 = *s2;
			TileLayer layer2(&shader2);

			Shader* s3 = new Shader("src/shaders/basic.vert", "src/shaders/basic_unlit.frag");
			Shader& shader3 = *s3;
			TileLayer layer3(&shader3);

			Shader* s4 = new Shader("src/shaders/basic.vert", "src/shaders/basic_lit.frag");
			Shader& shader4 = *s4;
			TileLayer layer4(&shader4);

			for (float y = -9.0f; y < 9.0f; y += .25f) {
				for (float x = -16.0f; x < 16.0f; x += .25f) {
					Sprite* sprite = new Sprite(x, y, .095f, .095f, WHITE);
					sprite->setColor(Vector4((y + 9.0f) / 18.0f, rand() % 1000 / 1000.0f, (x + 16.0f) / 32.0f, 1));
					layer.add(sprite);
				}
			}
			for (float y = -9.0f; y < 9.0f; y += .25f) {
				for (float x = -16.0f; x < 16.0f; x += .25f) {
					Sprite* sprite = new Sprite(x, y, .095f, .095f, WHITE);
					sprite->setColor(Vector4((y + 9.0f) / 18.0f, rand() % 1000 / 1000.0f, (x + 16.0f) / 32.0f, 1));
					layer2.add(sprite);
				}
			}
			for (float y = -9.0f; y < 9.0f; y += .25f) {
				for (float x = -16.0f; x < 16.0f; x += .25f) {
					Sprite* sprite = new Sprite(x, y, .095f, .095f, WHITE);
					sprite->setColor(Vector4((y + 9.0f) / 18.0f, rand() % 1000 / 1000.0f, (x + 16.0f) / 32.0f, 1));
					layer3.add(sprite);
				}
			}

			layer4.add(new Sprite(-12, -3, 6.0f, 6.0f, new Texture("J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/examples/SimpleGame/res/asterisk.png")));

#else

			FontManager::add(new Font("Roboto", "Fonts/Roboto-Regular.ttf", 10, fontScale)); // breaks


			Vector3 playerPos(-2, -2, 0);
			Vector2 playerSize(2, 2);
			player = new GameObject(
				playerPos,
				playerSize,
				new Sprite(new Texture("J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/examples/SimpleGame/res/Player.png")));

			player->addComponent(new physics::PhysicsBody2D(
				playerPos.x, playerPos.y,
				playerSize.x, playerSize.y,
				b2_dynamicBody, 0.6f));

			layer0->add(player);

			
			Vector3 floorPos(-16.0f,-9.0f,0);
			Vector2 floorSize(32, 2);
			GameObject* floor = new GameObject(floorPos, floorSize);
			floor->addComponent(new Sprite(floorPos.x, floorPos.y, floorSize.x, floorSize.y, new Texture("J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/examples/SimpleGame/res/floor.png")));
			floor->addComponent(new physics::PhysicsBody2D(floorPos.x, floorPos.y, floorSize.x, floorSize.y, b2_staticBody));
			//TODO BUG, physics bodies are still enabled even if the object is not in a layer
			layer0->add(floor);
			
			Vector3 floorPosL(-18.0f,-9.0f,0);
			Vector2 floorSizeL(2, 18);
			GameObject* floorL = new GameObject(floorPosL, floorSizeL);
			floorL->addComponent(new Sprite(floorPosL.x, floorPosL.y, floorSizeL.x, floorSizeL.y, new Texture("J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/examples/SimpleGame/res/floor.png")));
			floorL->addComponent(new physics::PhysicsBody2D(floorPosL.x, floorPosL.y, floorSizeL.x, floorSizeL.y, b2_staticBody));
			//TODO BUG, physics bodies are still enabled even if the object is not in a layer
			layer0->add(floorL);
			
			Vector3 floorPosR(18.0f,-9.0f,0);
			Vector2 floorSizeR(2, 18);
			GameObject* floorR = new GameObject(floorPosR, floorSizeR);
			floorR->addComponent(new Sprite(floorPosR.x, floorPosR.y, floorSizeR.x, floorSizeR.y, new Texture("J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/examples/SimpleGame/res/floor.png")));
			floorR->addComponent(new physics::PhysicsBody2D(floorPosR.x, floorPosR.y, floorSizeR.x, floorSizeR.y, b2_staticBody));
			//TODO BUG, physics bodies are still enabled even if the object is not in a layer
			layer0->add(floorR);

			


#endif
			math::Vector2 screenScale = math::Vector2(m_window->getWidth() / 32, m_window->getHeight() / 18);

			//TODO for now, it's best to keep the creation of textures close to where they get added to the layer. This is because if a texture is used in two separate draw calls, things won't show up properly
			FontManager::add(new Font("Roboto", "J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/fonts/Roboto-Regular.ttf", 16, screenScale));
			FontManager::add(new Font("Roboto", "J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/fonts/Roboto-Italic.ttf", 14, screenScale));

			Group* profileGroup = new Group(math::Matrix4::translation(Vector3(-15.5, 6.8, 0)));
			profileGroup->add(new GameObject(Vector3(0, 0, 0), Vector2(4.5f, 1.8), new Sprite(0x80808080)));
			fpsLabel = new Label("", "Roboto", 16, 0xffffffff);
			upsLabel = new Label("", "Roboto", 14, 0xffffffff);
			mpsLabel = new Label("", "Roboto", 14, 0xffffffff);
			profileGroup->add(new GameObject(Vector3(.3f, 1.2f, 0), fpsLabel));
			profileGroup->add(new GameObject(Vector3(.3f, .8f, 0), upsLabel));
			profileGroup->add(new GameObject(Vector3(.3f, .4f, 0), mpsLabel));
			uiLayer->add(profileGroup);
			

#ifdef __SOUND
			AudioClip* clip = new AudioClip("slow_motion", "J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/examples/SimpleGame/res/slow_motion.ogg");
			AudioManager::addClip(clip);
			AudioManager::getClip("slow_motion")->play(true);
			AudioManager::getClip("slow_motion")->setGain(m_gain);

#endif
		}

		void update() override {
			double x, y;
			m_window->getMousePos(x, y);
			float xScreenMousePos = x * 32.0f / m_window->getWidth() - 16.0f;
			float yScreenMousePos = 9.0f - y * 18.0f / m_window->getHeight();

			if (m_window->mouseButtonWasPressed(GLFW_MOUSE_BUTTON_LEFT)) {
				addBox();
			}

#ifdef __SOUND
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

#endif // __SOUND

#ifdef __BUTTERFLY
			Matrix4 mat = Matrix4::rotation(time.elapsed() * 30, Vector3(0.1f, -0.1f, 1));
			Matrix4 mat2 = Matrix4::scale(Vector3(30 / time.elapsed(), 30 / time.elapsed(), 30 / time.elapsed()));
			Matrix4 fallingMat = Matrix4::scale(Vector3(time.elapsed() / 300, time.elapsed() / 300, time.elapsed() / 300));
			Matrix4 mat3 = Matrix4::rotation(time.elapsed() * 20, Vector3(0.1f, -0.1f, -1));
			Matrix4 rotmat4 = Matrix4::rotation(sin(t) * 20, Vector3(0.1f, -0.1f, -1));
			Matrix4 transmat4 = Matrix4::translation(Vector3(sin(t / t / t) * 16.0f, sin(t / t / t) * 9.0f, 0));


			const std::vector<Renderable2D*> renderables = layer.getRenderables();

			for (size_t i = 0; i < renderables.size(); i++) {
				float c = sin(t) / 2 + .5f;
				renderables[i]->setColor(Vector4(c, rand() % 1000 / 1000.0f, (renderables[i]->getPosition().x + 16.0f) / 32.0f, 1));
			}
			const std::vector<Renderable2D*> renderables4 = layer4.getRenderables();

			for (size_t i = 0; i < renderables4.size(); i++) {
				float c = sin(t) / 2 + .5f;
				renderables4[i]->setColor(Vector4(c, .05f, 1 - c, 1.0f));
			}

			litShader.enable();
			litShader.setUniform2f("light_pos", Vector2(xScreenMousePos, yScreenMousePos));

			shader2.enable();
			shader2.setUniformMat4("ml_matrix", mat);

			shader3.enable();
			shader3.setUniformMat4("ml_matrix", mat3);

			shader4.enable();
			shader4.setUniform2f("light_pos", Vector2(xScreenMousePos, yScreenMousePos));
			shader4.setUniformMat4("ml_matrix", transmat4 * rotmat4);

			layer.draw();
			layer2.draw();
			layer3.draw();
			layer4.draw();
#endif
			getInput();
			if(debugPhysics) physics::PhysicsWorld2D::box2DWorld->DrawDebugData();
			physics::PhysicsWorld2D::step(gameTimer->delta);
			LETC::update();
		}

		void render() override {

			LETC::render();
		}

		void tick() override {

			fpsLabel->text = std::to_string(getFramesPerSecond()) + " frames / second";
			upsLabel->text = std::to_string(getUpdatesPerSecond()) + " updates / second";
			mpsLabel->text = std::to_string(getMSPerFrame()).substr(0, 5) + "ms / frame";
			LETC::tick();
		}

		void getInput() {
			float horizontal = -1*(float)(m_window->keyIsDown(GLFW_KEY_A) || m_window->keyIsDown(GLFW_KEY_LEFT)) + (float)(m_window->keyIsDown(GLFW_KEY_D) || m_window->keyIsDown(GLFW_KEY_RIGHT));
			//float vertical = (float)(m_window->keyIsDown(GLFW_KEY_W) || m_window->keyIsDown(GLFW_KEY_UP)) + -1*(float)(m_window->keyIsDown(GLFW_KEY_S) || m_window->keyIsDown(GLFW_KEY_DOWN));
			if (m_window->keyWasPressed(GLFW_KEY_SPACE))
				player->getPhysicsBody2D()->addForce(Vector2(0,1), 1.0f);

			player->getPhysicsBody2D()->addForce(Vector2(horizontal, 0), playerAcceleration * playerSpeed * gameTimer->delta);
			//player->position.x += playerSpeed * horizontal * (float)gameTimer->delta;

			if (player->position.y < -10.0f) {
				player->position.y = 10.0f;
				player->getPhysicsBody2D()->getBody()->SetTransform(b2Vec2(0,0), 0.0f);
				player->getPhysicsBody2D()->zeroVelocity();
			}

		}

		void addBox() {
			// todo doesn't work
			double x, y;
			m_window->getMousePos(x, y);
			float xScreenMousePos = x * 32.0f / m_window->getWidth() - 16.0f;
			float yScreenMousePos = 9.0f - y * 18.0f / m_window->getHeight();

			Vector3 boxPos(x, y, 0);
			Vector2 boxSize(2, 2);
			GameObject* box = new GameObject(boxPos, boxSize);
			box->addComponent(new Sprite(boxPos.x, boxPos.y, boxSize.x, boxSize.y, new Texture("J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/examples/SimpleGame/res/floor.png")));
			box->addComponent(new physics::PhysicsBody2D(boxPos.x, boxPos.y, boxSize.x, boxSize.y, b2_dynamicBody));
			layers[1]->add(box);

		
		}
};



int main() {
	SimpleGame game;
	game.start();
	return 0;
}





