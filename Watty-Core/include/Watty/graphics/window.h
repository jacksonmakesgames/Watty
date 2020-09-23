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


#include "Camera.h"
#include "font/fontmanager.h"
#include "../audio/audiomanager.h"
#include <input/Input.h>

namespace letc {namespace graphics {
	class Window {
	protected:
		bool isResizeable;
		bool isFullScreen;
	public:
		float PIXEL_TO_METER_RATIO = 100.0f;

		static bool useVSync;
		static Window* Instance;
		static bool allowMultipleSubWindows;
	private:
		friend struct GLFWwindow;
		const char* m_Title;
		int m_Width, m_Height;
		GLFWwindow *m_Window;
		bool m_Closed;
		bool firstInit = true;
		int m_refreshRate;

	public:
		Window(const char *title, int width, int height, bool resizeable, bool fullscreen=false);
		~Window();
		bool closed() const;
		void update();
		void clear() const;
		void clear(WattyColor clearColor, bool enableDepth, bool clearImGui) const;
		void clear(float r, float g, float b, float a, bool enableDepth, bool clearImGui) const;

		inline int getWidth() const { return Window::m_Width; };
		inline int getHeight() const { return Window::m_Height; };
		inline void setTitle(const char* newTitle) {
			m_Title = newTitle;
			glfwSetWindowTitle(m_Window,newTitle); 
		};
		inline void setSize(glm::vec2 newSize) {
			window_resize_callback(m_Window, (int)newSize.x, (int)newSize.y);
			glfwGetFramebufferSize(m_Window, (int*)&newSize.x, (int*)&newSize.y);
			glViewport(0, 0, newSize.x, newSize.y);
			init();

		};


		inline int getRefreshRate() { return m_refreshRate; };
		glm::i8vec2 getAspectRatio();
		static void toggleVSync();
		static void setVSync(bool state);

		glm::vec3 viewportToWorld(glm::vec2 position, const Camera& cam = *Camera::allCameras[0]);
		
	private:
		bool init();
		bool initImGUI();
		void endImGuiFrame();

		friend void window_resize_callback(GLFWwindow* window, int width, int height);
		friend void window_close_callback(GLFWwindow* window);
		
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
	//TODO move to Util
	class NotImplemented : public std::logic_error
	{
	public:
		NotImplemented() : std::logic_error("Function not yet implemented") { };
	};
}}
