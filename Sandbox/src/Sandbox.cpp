#include <Watty.h>

#define SHADERVERT "J:/OneDrive/Projects/Game_Development/Watty/Sandbox/res/shaders/simple.vert"
#define SHADERFRAG "J:/OneDrive/Projects/Game_Development/Watty/Sandbox/res/shaders/simple.frag"

using namespace letc;
using namespace graphics;
using namespace glm;



class Sandbox : public LETC {
private:
	Window* m_window;
	ParticleSystem* ps;
public:
	void init() override{
		// Create window
		m_window = createWindow("Watty {} Sandbox", 1600,900);

		for (size_t i = 0; i < 100; i++)
		{
			std::cout<<Random::range(10,20)<<std::endl<<std::endl;
		}

		sceneCamera->setSize(vec2(16.0f,9.0f));
		sceneCamera->position = glm::vec3(8.0f, 4.5f, 0);
		// Layers
		Layer* sandboxLayer = new Layer("Sandbox", new BatchRenderer2D(), new Shader(SHADERVERT, SHADERFRAG));
		layers.push_back(sandboxLayer);

		//Gameobjects
		 ps = new ParticleSystem(100);

		 GameObject* particleGameObject = new GameObject(vec2(-1, -1), vec2(2, 2), ps);
		 sandboxLayer->add(particleGameObject);
	}

	void update() override{
		LETC::update();

		sceneCamera->position += 1.0f;
	}

	~Sandbox() {
		delete(ps);
	}

};


int main() {
	Sandbox* sandbox = new Sandbox();
	sandbox->start();
	return 0;
}