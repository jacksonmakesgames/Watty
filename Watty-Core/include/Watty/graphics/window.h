#pragma once
#include <iostream>
#include <tuple>
#ifdef WATTY_VULKAN
//#include <src/graphics/vulkan/initializers.h>
//#include <src/graphics/vulkan/vulkaninstance.h>
#include <ext/imgui/include/imgui/imgui.h>
#include "imgui/imgui_impl_glfw.h"
#include <ext/GLFW/include/GLFW/glfw3.h>
#endif // WATTY_VULKAN


#ifdef WATTY_EMSCRIPTEN
#include <emscripten.h>
#include <GLES3/gl32.h>
#else
#include <glad/glad.h>	
#endif

#include <imgui.h>
#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <graphics/Camera.h>
#include <graphics/font/fontmanager.h>
#include <audio/audiomanager.h>


namespace letc {namespace graphics {
#define MAX_KEYS 1024
#define MAX_BUTTONS 32

	class Window {
	protected:
		bool isResizeable;
		bool isFullScreen;
	public:
		static bool useVSync;
		static Window* Instance;
	private:
		friend struct GLFWwindow;
		const char* mTitle;
		int mWidth, mHeight;
		GLFWwindow *mGLFWWindow;
		bool mClosed;


		bool mKeysThisFrame[MAX_KEYS];
		bool mKeysLastFrame[MAX_KEYS];
		bool mKeysFirstFrameDown[MAX_KEYS];
		bool mButtonsThisFrame[MAX_BUTTONS];
		bool mButtonsLastFrame[MAX_BUTTONS];
		bool mButtonsFirstFrameDown[MAX_BUTTONS];
		double mMouseX, mMouseY;
		double mScrolledThisFrameY = 0;

		int mRefreshRate;




	public:
		Window(const char *title, int width, int height, bool resizeable, bool fullscreen=false);
		~Window();
		bool closed() const;
		void update();
		void listenForInput();
		void clear() const;

		inline int getWidth() const { return Window::mWidth; };
		inline int getHeight() const { return Window::mHeight; };



		bool keyWasPressed(unsigned int keycode) const;
		bool keyIsDown(unsigned int keycode) const;
		bool keyWasReleased(unsigned int keycode) const;
		bool mouseButtonWasPressed(unsigned int button) const;
		bool mouseButtonIsDown(unsigned int button) const;
		bool mouseButtonWasReleased(unsigned int button) const;
		void getMousePos(double& x, double& y) const;
		std::tuple<int, int> getAspectRatio();
		static void toggleVSync();
		static void setVSync(bool state);

		inline double getScrollAmountThisFrameY() { return mScrolledThisFrameY; };
		inline int getRefreshRate() { return mRefreshRate; };

		glm::vec3 viewportToWorld(glm::vec2 position, const Camera& cam = *Camera::allCameras[0]);

		
	private:
		bool init();
		bool initImGUI();

		friend void window_resize_callback(GLFWwindow* window, int width, int height);
		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		friend void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	};

#ifdef WATTY_OPENGL
	static void GLAPIENTRY openglCallbackFunction(GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam);

#endif
}}
