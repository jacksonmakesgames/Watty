#include "window.h"
namespace letc {namespace graphics {
	static void window_resize_callback(GLFWwindow* window, int width, int height);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	Window::Window(const char* title, int width, int height) {
		m_title = title;
		m_width = width;
		m_height = height;
		if (!init())
			glfwTerminate();
		
		//FontManager::add(new Font("default", "Fonts/Roboto-Regular.ttf", 15)); // TODO: WE SHOULD DO THIS AT SOME POINT
		audio::AudioManager::init();

		for (int i = 0; i < MAX_KEYS; i++) {
			m_keysThisFrame[i]		=	false;
			m_keysLastFrame[i]	=	false;
			m_keysDown[i]	=	false;
		}
		for (int i = 0; i < MAX_BUTTONS; i++) {
			m_buttonsThisFrame[i]		=	 false;
			m_buttonsLastFrame[i]		=	 false;
			m_buttonsDown[i]			=	 false;
		}
	}	

	Window::~Window() {
		glfwTerminate();
		//FontManager::clean();
		audio::AudioManager::clean();


	}

	bool Window::init() {
		if (!glfwInit()){
			std::cout << "Failed to initialize GLFW" << std::endl;
			return false;
		}
		// TELL GLFW that we aren't using opengl
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

#if 0 // fullscreen
		m_Width = 1920;
		m_Height = 1080;
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, glfwGetPrimaryMonitor(), NULL); // fullscreen

#else
		m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
#endif
		if (!m_window) {
			glfwTerminate();
			std::cout << "Failed to create window" << std::endl;
			return false;
		}

		glfwMakeContextCurrent(m_window);

		glfwSetWindowUserPointer(m_window, this);
		glfwSetFramebufferSizeCallback(m_window, window_resize_callback);
		glfwSetKeyCallback(m_window, key_callback);
		glfwSetMouseButtonCallback(m_window, mouse_button_callback);
		glfwSetCursorPosCallback(m_window, cursor_position_callback);


		m_vkInstance = new VulkanInstance(m_width, m_height, m_window);

		return true;
	}


	bool Window::keyPressed(unsigned int keycode) const {
		if (keycode >= MAX_KEYS) {
		// TODO: log an error
			return false;
		}
		return m_keysThisFrame[keycode];
	}
	bool Window::keyDown(unsigned int keycode) const {
		if (keycode >= MAX_KEYS) {
		// TODO: log an error
			return false;
		}
		return m_keysDown[keycode];
	}

	bool Window::mouseButtonDown(unsigned int button) const {
		if (button >= MAX_BUTTONS) {
		// TODO: log an error
			return false;
		}
		return m_buttonsDown[button];
	}
	bool Window::mouseButtonPressed(unsigned int button) const {
		if (button >= MAX_BUTTONS) {
		// TODO: log an error
			return false;
		}
		return m_buttonsThisFrame[button];
	}

	void Window::getMousePos(double& x, double& y) const {
		x = mx;
		y = my;
	}

	void Window::waitForNotMinimized()
	{
		
	}

	void Window::update() {
		// handle input:
		for (size_t i = 0; i < MAX_KEYS; i++){
			m_keysDown[i] = m_keysThisFrame[i] && !m_keysLastFrame[i];
		}
		memcpy(&m_keysLastFrame, m_keysThisFrame, sizeof(bool)*MAX_KEYS);

		for (size_t i = 0; i < MAX_BUTTONS; i++){
			m_buttonsDown[i] = m_buttonsThisFrame[i] && !m_buttonsLastFrame[i];
		}
		memcpy(&m_buttonsLastFrame, m_buttonsThisFrame, sizeof(bool)*MAX_BUTTONS);

		glfwPollEvents();

		m_vkInstance->drawVulkanFrame();

		//audio:
		audio::AudioManager::update(); 
	}

	bool Window::closed() const {
		return glfwWindowShouldClose(m_window) == 1;
	}


	void window_resize_callback(GLFWwindow* window, int width, int height){
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_width = width;
		win->m_height = height;
		while (win->m_height == 0 || win->m_width == 0) {
			glfwGetFramebufferSize(win->getGLFWWindow(), &win->m_width, &win->m_height);
			glfwWaitEvents();
		}
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Window * win = (Window*) glfwGetWindowUserPointer(window);
		win->m_keysThisFrame[key] = action != GLFW_RELEASE;

	}
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
		Window * win = (Window*) glfwGetWindowUserPointer(window);
		win->m_buttonsThisFrame[button] = action != GLFW_RELEASE;

	}
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->mx = xpos;
		win->my = ypos;

	}

	
}}