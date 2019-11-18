
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
#include "src/graphics/layers/group.h"
#include "src/graphics/texture.h"
#include "src/graphics/font/label.h"
#include "src/graphics/font/fontmanager.h"
#include "src/utils/timer.h"

#include <vector>
#include <stdio.h>
#include <time.h>


#define LOG(x) std::cout << x << std::endl;

// NOTE: COLORS ARE ABGR
#define WHITE 0xFFFFFFFF
#define BLUE 0xFFFF0000
#define PINK 0xFFFF80FF
#define BLACK 0xFF000000
#define GREY 0xFF808080

//#define __BUTTERFLY 1
#define __SOUND 1


int main() {
	
	using namespace letc;
	using namespace graphics;
	using namespace math;
	using namespace audio;
	Window window("This little engine could", 1280, 720);
	//glClearColor(1.0f,1.0f,1.0f,1.0f);
	//glClearColor(.5,.5,.5,1.0f);

	math::Matrix4 ortho = math::Matrix4::orthographic(-16,16,-9,9,-10,10);

	Shader* shader0 = new Shader("src/shaders/basic.vert", "src/shaders/basic_unlit.frag");
	Layer layer0(new BatchRenderer2D(), shader0, ortho);
	
	Shader* shader1= new Shader("src/shaders/basic.vert", "src/shaders/basic_unlit.frag");
	Layer layer1(new BatchRenderer2D(), shader1, ortho);


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

	//test textures
	Texture* texture = new Texture("J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/examples/SimpleGame/res/test2.png");
	layer0.add(new Sprite(-6, 0, 4, 4, texture));
	Texture* texture2 = new Texture("J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/examples/SimpleGame/res/Alien.png");
	layer0.add(new Sprite(2, 0, 4, 4, texture2));
	
#endif
	Vector2 fontScale = Vector2(window.getWidth() / 32.0f, window.getHeight() / 18.0f);
	//draw fps label
	FontManager::add(new Font("Roboto", "Fonts/Roboto-Regular.ttf", 16, fontScale));
	FontManager::add(new Font("Roboto", "Fonts/Roboto-Italic.ttf", 14, fontScale));

	Group* fpsGroup = new Group(Matrix4::translation(Vector3(-15.5,7.5,0)));
	fpsGroup->add(new Sprite(0, 0, 2.8f, 1, 0x80808080));
	Label* mspf = new Label("", .3f, .55f, "Roboto", 16, WHITE);
	Label* fps = new Label("", .3f, .15f, "Roboto", 14, WHITE);
	fpsGroup->add(mspf);
	fpsGroup->add(fps);
	layer0.add(fpsGroup);


#ifdef __SOUND
	AudioClip* clip = new AudioClip("sci_fi", "J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/examples/SimpleGame/res/sci_fi.ogg");
	AudioManager::addClip(clip);
	float gain = 0.5f;
	AudioManager::getClip("sci_fi")->play(false);
	AudioManager::getClip("sci_fi")->setGain(gain);

#endif

	srand(time(NULL));
	Timer time;
	float timer = 0.0f;
	unsigned int frames = 0;
	float t = 0;

	/********************************************************************************************************************
	*********GAME LOOP***************************************************************************************************
	*********************************************************************************************************************/
	while (!window.closed()) {
		t += 0.001f;
		window.clear();
		double x, y;
		window.getMousePos(x, y);

		if (window.keyPressed(GLFW_KEY_SPACE)) {
			time.reset();
			t = 0.0f;
		};

		float xScreenMousePos = x * 32.0f / window.getWidth() - 16.0f;
		float yScreenMousePos = 9.0f - y * 18.0f / window.getHeight();


#ifdef __BUTTERFLY
		Matrix4 mat = Matrix4::rotation(time.elapsed() * 30, Vector3(0.1f, -0.1f, 1));
		Matrix4 mat2 = Matrix4::scale(Vector3(30/time.elapsed(),30/time.elapsed(),30/time.elapsed()));
		Matrix4 fallingMat = Matrix4::scale(Vector3(time.elapsed() / 300,time.elapsed() / 300,time.elapsed() / 300));
		Matrix4 mat3 = Matrix4::rotation(time.elapsed() * 20, Vector3(0.1f, -0.1f, -1));
		Matrix4 rotmat4 = Matrix4::rotation(sin(t) * 20, Vector3(0.1f, -0.1f, -1));
		Matrix4 transmat4 = Matrix4::translation(Vector3(sin(t/t/t) * 16.0f, sin(t/t/t) * 9.0f, 0));

		
		const std::vector<Renderable2D*> renderables = layer.getRenderables();
		
		for (size_t i = 0; i < renderables.size(); i++){
			float c = sin(t)/2 + .5f;
			renderables[i]->setColor(Vector4(c, rand() % 1000 / 1000.0f, (renderables[i]->getPosition().x + 16.0f) / 32.0f, 1));
		}
		const std::vector<Renderable2D*> renderables4 = layer4.getRenderables();

		for (size_t i = 0; i < renderables4.size(); i++){
			float c = sin(t) / 2 + .5f;
			renderables4[i]->setColor(Vector4(c, .05f, 1-c, 1.0f));
		}

		litShader.enable();
		litShader.setUniform2f("light_pos", Vector2(xScreenMousePos, yScreenMousePos));
		
		shader2.enable();
		shader2.setUniformMat4("ml_matrix", mat);

		shader3.enable();
		shader3.setUniformMat4("ml_matrix", mat3);
		
		shader4.enable();
		shader4.setUniform2f("light_pos", Vector2(xScreenMousePos, yScreenMousePos));
		shader4.setUniformMat4("ml_matrix", transmat4*rotmat4);
		
		layer.draw();
		layer2.draw();
		layer3.draw();
		layer4.draw();
#endif

		layer0.draw();
		window.update();
		
#ifdef __SOUND
		if (window.keyPressed(GLFW_KEY_LEFT)) {
			gain -= 0.005f;
			AudioManager::getClip("sci_fi")->setGain(gain);

		}
		else if (window.keyPressed(GLFW_KEY_RIGHT)) {
			gain += 0.005f;
			AudioManager::getClip("sci_fi")->setGain(gain);
		}
		else if (window.keyDown(GLFW_KEY_P)) {
			AudioManager::getClip("sci_fi")->pause();
		}
		else if (window.keyDown(GLFW_KEY_R)) {
			AudioManager::getClip("sci_fi")->resume();
			AudioManager::getClip("sci_fi")->setGain(gain);
		}
		else if (window.keyDown(GLFW_KEY_S)) {
			AudioManager::getClip("sci_fi")->stop();
		}

#endif // __SOUND


		frames++;
		if ((time.elapsed() - timer) > 1.0f) {
			timer+=1.0f;
			mspf->text = std::to_string(1000.0 / (double)frames).substr(0, 5) + " mspf";
			fps->text = std::to_string(frames) + " fps";
			printf(" [%4d FPS] [%4.3f MSPF] \r", frames, 1000.0 / (double)frames);
			frames = 0;
		}
	}
	/********************************************************************************************************************
	*********GAME LOOP***************************************************************************************************
	*********************************************************************************************************************/

	return 0;
}






