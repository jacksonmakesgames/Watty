#include "..\graphics\window.h"
#include "../math/math.h"
#include "../math/matrix4.h"

#define LOG(x) std::cout << x<< std::endl;


int start_game() {
	using namespace letc;
	using namespace graphics;
	using namespace math;

	Window window("This little engine could", 800, 600);
	glClearColor(.69f, 0.0f, .99f, 1.0f);
	Vector2 squareScale(0.1f, 0.1f);

	float x2 = squareScale.x;
	float x1 = -squareScale.x;
	float y2 = squareScale.y;
	float y1 = -squareScale.y;



	while (!window.closed()) {
		window.clear();


		if (window.keyPressed(GLFW_KEY_UP)) {
			y1 += .001f;
			y2 += .001f;
		}
		if (window.keyPressed(GLFW_KEY_DOWN)) {
			y1 -= .001f;
			y2 -= .001f;
		}
		if (window.keyPressed(GLFW_KEY_LEFT)) {
			x1 -= .001f;
			x2 -= .001f;
		}
		if (window.keyPressed(GLFW_KEY_RIGHT)) {
			x1 += .001f;
			x2 += .001f;
		}

		if (window.mouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
			double x, y;
			window.getMousePos(x, y);
			x1 = x / window.getWidth() - squareScale.x;
			y1 = y / window.getHeight() - squareScale.y;
			x2 = x / window.getWidth() + squareScale.x;
			y2 = y / window.getHeight() + squareScale.y;
		}
		glBegin(GL_QUADS);
		glVertex2f(x1, y1);
		glVertex2f(x1, y2);
		glVertex2f(x2, y2);
		glVertex2f(x2, y1);
		glEnd();
		window.update();
	}
	return 0;
}
