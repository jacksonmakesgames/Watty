#include "../math/math.h"
#include "../math/matrix4.h"
		  
#include "../graphics/window.h"
#include "../graphics/shader.h"
#include "../graphics/buffers/indexbuffer.h"
#include "../graphics/buffers/vertexarray.h"
#include "../graphics/simple2drenderer.h"
#include "../graphics/batchrenderer2d.h"
#include "../graphics/sprite.h"
#include "../graphics/layers/tilelayer.h"
#include "../graphics/layers/group.h"
		  
#include "../utils/timer.h"

#include <vector>

#include <time.h>

#define LOG(x) std::cout << x<< std::endl;

#define WHITE 0xffffffff


int test() {
	using namespace letc;
	using namespace graphics;
	using namespace math;

	Window window("This little engine could", 1280, 720);
	//glClearColor(.99f, .99f, .99f, 1.0f);

	Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader& shader = *s;

	Shader* s2 = new Shader("src/shaders/basic.vert", "src/shaders/basic_unlit.frag");
	Shader& shader2 = *s2;

	Shader* s3 = new Shader("src/shaders/basic.vert", "src/shaders/basic_unlit.frag");
	Shader& shader3 = *s3;

	TileLayer layer(&shader);
	TileLayer layer2(&shader2);

	TileLayer layer3(&shader3);


	srand(time(NULL));
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

	Timer time;
	float timer = 0.0f;

	unsigned int frames = 0;
	while (!window.closed()) {
		window.clear();
		double x, y;
		window.getMousePos(x, y);

		float xScreen = x * 32.0f / window.getWidth() - 16.0f;
		float yScreen = 9.0f - y * 18.0f / window.getHeight();

		Matrix4 mat = Matrix4::rotation(time.elapsed() * 20, Vector3(0.1f, -0.1f, 1));
		Matrix4 mat3 = Matrix4::rotation(time.elapsed() * 20, Vector3(0.1f, -0.1f, -1));

		shader.enable();
		shader.setUniform2f("light_pos", Vector2(xScreen, yScreen));
		shader2.enable();
		shader2.setUniformMat4("ml_matrix", mat);

		shader3.enable();
		shader3.setUniformMat4("ml_matrix", mat3);
		layer.draw();
		layer2.draw();
		layer3.draw();

		window.update();

		frames++;
		if ((time.elapsed() - timer) > 1.0f) {
			timer += 1.0f;
			printf(" [%d FPS] [%f MSPF] \r", frames, 1000.0 / (double)frames);
			frames = 0;
		}
	}
	return 0;
}
