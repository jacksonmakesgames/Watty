#include "src/math/math.h"
#include "src/math/matrix4.h"

#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"
#include "src/graphics/simple2drenderer.h"
#include "src/graphics/batchrenderer2d.h"
#include "src/graphics/sprite.h"
#include "src/graphics/layers/tilelayer.h"
#include "src/graphics/layers/group.h"
#include "src/graphics/texture.h"
#include "src/graphics/font/label.h"
#include "src/graphics/font/fontmanager.h"
#include "src/utils/timer.h"

#include <vector>
#include <stdio.h>
#include <time.h>
#include "gorilla/ga.h"
#include "gorilla/gau.h"


#include "ext/freetype-gl/font-manager.h"

#define LOG(x) std::cout << x << std::endl;
#define BLUE 0xFFFF0000
#define PINK 0xFFFF00FF
#define WHITE 0xFFFFFFFF
#define BLACK 0xFF000000
#define GREY 0xFF808080
// NOTE: COLORS ARE ABGR

#define __BUTTERFLY 1
//#define __SOUND 1

static void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context)
{
	gc_int32* flag = (gc_int32*)(in_context);
	*flag = 1;
	ga_handle_destroy(in_handle);
}



int main() {
	
	using namespace letc;
	using namespace graphics;
	using namespace math;
	Window window("This little engine could", 1280, 720);
	//glClearColor(1.0f,1.0f,1.0f,1.0f);

	Shader* s0 = new Shader("src/shaders/basic.vert", "src/shaders/basic_unlit.frag");
	Shader& shader0 = *s0;
	TileLayer layer0(&shader0);


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

	layer4.add(new Sprite(-12, -3, 6.0f, 6.0f, new Texture("J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/asterisk.png")));

	
#else
	// test colors
	layer0.add(new Sprite(15, 8,1.0f,1.0f, PINK));
	layer0.add(new Sprite(15, 7,1.0f,1.0f, BLUE));
	layer0.add(new Sprite(15, 6,1.0f,1.0f, WHITE));
	layer0.add(new Sprite(15, 5,1.0f,1.0f, GREY));

	//test textures
	Texture* texture = new Texture("J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/test2.png");
	layer0.add(new Sprite(-6, 0, 4, 4, texture));
	
	Texture* texture2 = new Texture("J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/Alien.png");
	layer0.add(new Sprite(2, 0, 4, 4, texture2));
	shader0.enable();
	GLint texIDs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	shader0.setUniform1iv("textures", texIDs, 10);

#endif


	//draw fps label
	ftgl::font_manager_t* ftglFontManager = ftgl::font_manager_new(512, 512, 2);
	ftgl::texture_font_t* ftFont = ftgl::font_manager_get_from_filename(ftglFontManager, "Fonts/Roboto-Regular.ttf", 22);
	Font* font = new Font(ftFont, ftglFontManager->atlas);

	FontManager::add(new Font("Roboto", "Fonts/Roboto-Regular.ttf", 16));
	FontManager::add(new Font("Roboto", "Fonts/Roboto-Italic.ttf", 14));


	Group* fpsGroup = new Group(Matrix4::translation(Vector3(-15.5,7.5,0)));
	fpsGroup->add(new Sprite(0, 0, 2.8f, 1, 0x80808080));
	Label* mspf = new Label("", .3f, .55f, "Roboto", 16, WHITE);
	Label* fps = new Label("", .3f, .15f, "Roboto", 14, WHITE);
	fpsGroup->add(mspf);
	fpsGroup->add(fps);
	layer0.add(fpsGroup);


#ifdef __SOUND
	gau_Manager* mgr;
	ga_Mixer* mixer;
	ga_StreamManager* streamMgr;
	ga_Handle* stream;
	gau_SampleSourceLoop* loopSrc = 0;
	gau_SampleSourceLoop** pLoopSrc = &loopSrc;
	gc_int32 loop = 1;
	gc_int32 quit = 0;

	/* Initialize library + manager */
	gc_initialize(0);
	mgr = gau_manager_create_custom(GA_DEVICE_TYPE_DEFAULT, GAU_THREAD_POLICY_SINGLE, 4, 512);
	mixer = gau_manager_mixer(mgr);
	streamMgr = gau_manager_streamManager(mgr);

	/* Create and play streaming audio */
	if (!loop)
		pLoopSrc = 0;
	stream = gau_create_handle_buffered_file(mixer, streamMgr, "gummy.ogg", "ogg",
		&setFlagAndDestroyOnFinish, &quit, pLoopSrc);
	ga_handle_play(stream);


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
		gau_manager_update(mgr);
		gc_thread_sleep(1);
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
	//delete texture;

#ifdef __SOUND

	/* Clean up library + manager */
	gau_manager_destroy(mgr);
	gc_shutdown();

	return 0;
#endif // __SOUND


	return 0;
}







