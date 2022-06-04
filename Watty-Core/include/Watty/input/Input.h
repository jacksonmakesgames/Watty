#pragma once
#include <memory>
#include <glfw/glfw3.h>

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

namespace watty {
	class Input {
	public:
		static bool keyIsDown(unsigned int keycode);
		static bool keyWasPressed(unsigned int keycode);
		static bool mouseButtonWasPressed(unsigned int button);
		static bool mouseButtonIsDown(unsigned int button);
		static bool mouseButtonWasReleased(unsigned int button);
		static bool keyWasReleased(unsigned int key);
		static void getMousePos(double& x, double& y);
		static void listenForInput();
		static void setKeyThisFrame(int key, bool down);
		static void setButtonThisFrame(int button, bool down);

		static void updateMousePos(double x, double y);

		//static void setKeyFirstFrameDown();
		//static void setKeyFirstFrameDown();
		//static void setButtonThisFrame();


		static inline double getScrollAmountThisFrameY() { return scrolledThisFrameY; };

		static void init();
		static void resetScroll();

		//Mouse
		static double scrolledThisFrameY;
		static double mx, my;

		//Keys/Buttons
		static bool m_keysThisFrame[MAX_KEYS];
		static bool m_keysLastFrame[MAX_KEYS];
		static bool m_keysFirstFrameDown[MAX_KEYS];
		static bool m_buttonsThisFrame[MAX_BUTTONS];
		static bool m_buttonsLastFrame[MAX_BUTTONS];
		static bool m_buttonsFirstFrameDown[MAX_BUTTONS];


		//friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		//friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		//friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		//friend void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	};

//#ifdef WATTY_OPENGL
//	static void GLAPIENTRY openglCallbackFunction(GLenum source,
//		GLenum type,
//		GLuint id,
//		GLenum severity,
//		GLsizei length,
//		const GLchar* message,
//		const void* userParam);
//
//#endif

}