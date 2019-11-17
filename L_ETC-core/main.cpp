
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



int main() {
	using namespace letc;
	using namespace graphics;
	using namespace math;
	using namespace audio;
	Window window("This little engine could", 1280, 720);

	srand(time(NULL));
	Timer time;
	float timer = 0.0f;
	unsigned int frames = 0;
	float t = 0;


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

		window.update();

	}


	return 0;
}






