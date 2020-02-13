#include <Watty.h>

#define SHADERVERT "J:/OneDrive/Projects/Game_Development/Watty/Sandbox/res/shaders/basic.vert"
#define SHADERFRAG "J:/OneDrive/Projects/Game_Development/Watty/Sandbox/res/shaders/basic_unlit.frag"
#define TESTTEXTURE "J:/OneDrive/Projects/Game_Development/Watty/Sandbox/res/textures/test.png"

using namespace letc;
using namespace graphics;
using namespace glm;



class Sandbox : public LETC {
private:
	Window* m_window;
	ParticleSystem* ps;
	ParticleProperties particleProps;
	bool debugPhysics = false;
	GameObject* particleGameObject;
	float beginColor[4]	=	{0, 0, 0, 0};
	float endColor[4]	=	{0, 0, 0, 0};
	int particleRate = 2;
	int maxParticles = 2200;

	GameObject* testSprite;
	GridLayer* gridLayer;
public:
	void init() override{
		// Create window
		m_window = createWindow("Watty {} Sandbox", 1600,900);
		m_window->setVSync(true);
		glClearColor(1,1,1,1);

		// Dear IMGUI:
		ImGui::CreateContext();

		sceneCamera->setSize(vec2(32.0f,18.0f));
		sceneCamera->setDepth(10.0f);
		sceneCamera->position = glm::vec3(0, 0, -2.0f);
		// Layers
		Layer* sandboxLayer = new Layer("Sandbox", new BatchRenderer2D(), new Shader(SHADERVERT, SHADERFRAG));
		layers.push_back(sandboxLayer);
		Layer* testLayer = new Layer("Test", new BatchRenderer2D(), new Shader(SHADERVERT, SHADERFRAG));
		layers.push_back(testLayer);


		gridLayer = new GridLayer(new Shader(SHADERVERT, SHADERFRAG), *sceneCamera, *m_window);
		layers.push_back(gridLayer);

		EngineControlLayer * engineControlLayer = new EngineControlLayer("Watty {} Layer", debugPhysics, resetFlag, &Window::useVSync, layers, new Shader(VERTPATH, FRAGUNLITPATH));
		layers.push_back(engineControlLayer);
		engineControlLayer->disable();

		//Gameobjects
		//particles
		{
			ps = new ParticleSystem(maxParticles);

			particleGameObject = new GameObject(vec2(0, 0), vec2(2, 2), ps);
			particleGameObject->setTag("Particles");
			sandboxLayer->add(particleGameObject);

			particleProps.position = particleGameObject->transform->getPosition();
			particleProps.colorBegin.c = 0xffffff80;
			particleProps.colorEnd.c = 0xff00ff00;
			particleProps.lifeTime = 2.0f;
			particleProps.sizeBegin = 2.0f;
			particleProps.sizeEnd = 0.0f;
			particleProps.sizeVariation = 0.0f;
			particleProps.velocityVariation = vec3(1.0, 2.0f, 0);
			particleProps.velocity = vec3(0, 0.0f, 0);
			particleProps.rotationSpeed = .5f;

			beginColor[0] = particleProps.colorBegin.rgba.a / 255.0f;
			beginColor[1] = particleProps.colorBegin.rgba.b / 255.0f;
			beginColor[2] = particleProps.colorBegin.rgba.g / 255.0f;
			beginColor[3] = particleProps.colorBegin.rgba.r / 255.0f;

			endColor[0] = particleProps.colorEnd.rgba.a / 255.0f;
			endColor[1] = particleProps.colorEnd.rgba.b / 255.0f;
			endColor[2] = particleProps.colorEnd.rgba.g / 255.0f;
			endColor[3] = particleProps.colorEnd.rgba.r / 255.0f;
		}
	

		testSprite = new GameObject(vec2(0, 0.0f), vec2(2,2),new Sprite(new Texture(TESTTEXTURE))); // parent
		testSprite->setTag("Test Parent");
		testLayer->add(testSprite);

		GameObject* childTest = new GameObject(glm::vec2(0,0), {.2,.2}, new Sprite(Color::orange));
		testSprite->transform->addChild(childTest->transform);

		/*testLayer->add(testSprite);  
		testLayer->add(new GameObject(vec2(-8, 0), vec2(1.0f), new Sprite(Color::blue)));*/

		testLayer->add(new GameObject({ 0,0 }, {.1,.1},new Sprite(0x80808080))); // greyboi
		testLayer->add(new GameObject({ 1,1 }, {.1,.1},new Sprite(0x80808080))); // greyboi
		testLayer->add(new GameObject({ -1,1 }, {.1,.1},new Sprite(0x80808080))); // greyboi
		testLayer->add(new GameObject({ 1,-1 }, {.1,.1},new Sprite(0x80808080))); // greyboi
		testLayer->add(new GameObject({ -1,-1 }, {.1,.1},new Sprite(0x80808080))); // greyboi
		testLayer->add(new GameObject({ -2,-2 }, {.1,.1},new Sprite(0x80808080))); // greyboi
	}

	void tick() override {
		LETC::tick();
	}
	void update() override{

		LETC::update();
		ps->update(gameTimer->delta);
		getInput();
	}

	void render() override {
		if (getLayerByName("Watty {} Layer")->enabled) {
			LETC::render();
			return;
		}
		beginColor[0]	= particleProps.colorBegin.rgba.a	/ 255.0f;
		beginColor[1]	= particleProps.colorBegin.rgba.b	/ 255.0f;
		beginColor[2]	= particleProps.colorBegin.rgba.g	/ 255.0f;
		beginColor[3]	= particleProps.colorBegin.rgba.r	/ 255.0f;

		endColor[0]		= particleProps.colorEnd.rgba.a		/ 255.0f;
		endColor[1]		= particleProps.colorEnd.rgba.b		/ 255.0f;
		endColor[2]		= particleProps.colorEnd.rgba.g		/ 255.0f;
		endColor[3]		= particleProps.colorEnd.rgba.r		/ 255.0f;

		// IMGUI
		// Start the Dear ImGui frame	
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		{
			ImGui::Begin("Particles");
			ImGui::PushItemWidth(180.0f);
			ImGui::SliderFloat(" | Life Time", &particleProps.lifeTime, 0.0f, 5.0f);
			ImGui::SliderInt(" | Rate", &particleRate, 1, 10);
			
			if (ImGui::DragInt("Max Particles", &maxParticles)) {
				if (maxParticles < 1) maxParticles = 1;
				ps->changeMaxParticles(maxParticles);
			};

			ImGui::PushID(0); 
			ImGui::ColorPicker4(" | Begin Color", beginColor, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs  | ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_PickerHueBar);
			ImGui::PopID(); 
			ImGui::PushID(1);
			ImGui::ColorPicker4("| End Color", endColor, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs  | ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_PickerHueBar);
			ImGui::PopID();

			ImGui::SliderFloat(" | Start Size", &particleProps.sizeBegin, 0.0f, 5.0f);
			ImGui::SliderFloat(" | End Size", &particleProps.sizeEnd, 0.0f, 5.0f);
			ImGui::SliderFloat(" | Rotation Speed", &particleProps.rotationSpeed, -5.0f, 5.0f);
			ImGui::SliderFloat2(" | Velocity", &particleProps.velocity.x, -10.0f, 10.0f);
			ImGui::SliderFloat2(" | Velocity Variation", &particleProps.velocityVariation.x, -10.0f, 10.0f);
			ImGui::PopItemWidth();

		}
			ImGui::End();
		
		LETC::render();

			
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		particleProps.colorBegin.rgba.a = beginColor[0]*255;
		particleProps.colorBegin.rgba.b = beginColor[1]*255;
		particleProps.colorBegin.rgba.g = beginColor[2]*255;
		particleProps.colorBegin.rgba.r = beginColor[3]*255;
		
		particleProps.colorEnd.rgba.a = endColor[0]*255;
		particleProps.colorEnd.rgba.b = endColor[1]*255;
		particleProps.colorEnd.rgba.g = endColor[2]*255;
		particleProps.colorEnd.rgba.r = endColor[3]*255;
	}


	bool heldMouse = false;
	void getInput() {
		//Engine Control Layer
		if (m_window->keyWasPressed(GLFW_KEY_GRAVE_ACCENT))
			getLayerByName("Watty {} Layer")->enabled ? getLayerByName("Watty {} Layer")->disable() : getLayerByName("Watty {} Layer")->enable();
		

		float horizontal = -1 * (float)(m_window->keyIsDown(GLFW_KEY_A) || m_window->keyIsDown(GLFW_KEY_LEFT)) + (float)(m_window->keyIsDown(GLFW_KEY_D) || m_window->keyIsDown(GLFW_KEY_RIGHT));
		float vertical = (float)(m_window->keyIsDown(GLFW_KEY_W) || m_window->keyIsDown(GLFW_KEY_UP)) + -1 * (float)(m_window->keyIsDown(GLFW_KEY_S) || m_window->keyIsDown(GLFW_KEY_DOWN));
		float mod = 1.0f;
		if (m_window->keyIsDown(GLFW_KEY_LEFT_SHIFT)) {
			mod = 5.0f;
		}
		
		sceneCamera->position.x += horizontal * gameTimer->delta * mod;
		sceneCamera->position.y += vertical   * gameTimer->delta * mod;

		sceneCamera->setSize(
			glm::vec2(
				sceneCamera->getSize().x - 4.0f * m_window->getScrollAmountThisFrameY() * gameTimer->delta * 10.0f * mod,
				sceneCamera->getSize().y - 2.25f * m_window->getScrollAmountThisFrameY() * gameTimer->delta* 10.0f * mod
			));
		

		//PARTICLES!
		if (m_window->mouseButtonWasPressed(GLFW_MOUSE_BUTTON_LEFT)&& !ImGui::GetIO().WantCaptureMouse) {
			heldMouse = true;
		}
		
		if (m_window->mouseButtonIsDown(GLFW_MOUSE_BUTTON_LEFT) &&!ImGui::GetIO().WantCaptureMouse) {
			double x, y;
			m_window->getMousePos(x, y);
			vec3 pos = m_window->viewportToWorld(vec2(x, y));
			particleGameObject->transform->setPosition(pos);
			particleProps.position = particleGameObject->transform->getPosition();
			if (heldMouse){
				for (size_t i = 0; i < particleRate; i++)
				{
					ps->emitOne(particleProps);
				}
			}

		}
		if (m_window->mouseButtonWasReleased(GLFW_MOUSE_BUTTON_LEFT)&& !ImGui::GetIO().WantCaptureMouse) {
			heldMouse = false;
		}
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