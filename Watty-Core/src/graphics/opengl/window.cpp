#include <graphics/window.h>
namespace letc {namespace graphics {
	static void window_resize_callback(GLFWwindow* window, int width, int height);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	Window::Window(const char* title, int width, int height, bool resizeable, bool fullscreen) {
		m_Title = title;
		m_Width = width;
		m_Height = height;
		isResizeable = resizeable;
		isFullScreen = fullscreen;
		if (!init())
			glfwTerminate();
		
		//FontManager::add(new Font("default", "res/fonts/Roboto-Regular.ttf", 15)); 
		audio::AudioManager::init();

		for (int i = 0; i < MAX_KEYS; i++) {
			m_keysThisFrame[i]		=	false;
			m_keysLastFrame[i]	=	false;
			m_keysFirstFrameDown[i]	=	false;
		}
		for (int i = 0; i < MAX_BUTTONS; i++) {
			m_buttonsThisFrame[i]		=	 false;
			m_buttonsLastFrame[i]		=	 false;
			m_buttonsFirstFrameDown[i]			=	 false;
		}

		// imgui:
		 // Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		const char* glsl_version = "#version 450";
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsLight();
		//ImGui::StyleColorsClassic();

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
		ImGui_ImplOpenGL3_Init(glsl_version); // we might need this


	}	

	Window::~Window() {

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		glfwTerminate();
		FontManager::clean();
		audio::AudioManager::clean();
	}

	// TODO: NOT SURE, asks nvidia to use dedicate gpu
	/*extern "C" {
		_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
	}*/

	bool Window::init() {


		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

		if (!glfwInit()){
			std::cout << "Failed to initialize GLFW" << std::endl;
			return false;
		}
		glfwWindowHint(GLFW_RESIZABLE, isResizeable);

		if (isFullScreen) {
			const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			
			m_Width = mode->width;
			m_Height = mode->height;
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, glfwGetPrimaryMonitor(), NULL); // fullscreen
		}
		else
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		
		m_refreshRate = glfwGetVideoMode(glfwGetPrimaryMonitor())->refreshRate;
		if (!m_Window) {
			glfwTerminate();
			std::cout << "Failed to create window" << std::endl;
			return false;
		}

		glfwMakeContextCurrent(m_Window);
		
		glfwSetWindowUserPointer(m_Window, this);
		if(isResizeable) glfwSetFramebufferSizeCallback(m_Window, window_resize_callback);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		glfwSetScrollCallback(m_Window, scroll_callback);
		glfwSwapInterval(useVSync);


		//if (glewInit() != GLEW_OK) {
		//	std::cout << "Could not initialize GLEW" << std::endl;
		//	return false;

		//}	
		
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}

		std::cout << "Watty{} Version: " << WATTYVERSION << std::endl;
		std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

		GLint flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(openglCallbackFunction, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}

		glClearColor(0, 0, 0, 1);


		// choose how textures render on top of one another
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		// add error texture to TextureManager
		//TextureManager::errorTexture = new Texture("J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/res/error_texture.png");

		return true;

	}

	bool Window::keyIsDown(unsigned int keycode) const {
		// if the key is down this frame
		if (keycode >= MAX_KEYS) {
		// TODO: log an error
			return false;
		}
		return m_keysThisFrame[keycode];
	}

	bool Window::keyWasPressed(unsigned int keycode) const {
		// If this is the first frame a key is down
		if (keycode >= MAX_KEYS) {
		// TODO: log an error
			return false;
		}
		return m_keysFirstFrameDown[keycode];
	}

	bool Window::mouseButtonWasPressed(unsigned int button) const {
		if (button >= MAX_BUTTONS) {
		// TODO: log an error
			return false;
		}
		return m_buttonsFirstFrameDown[button];
	}
	bool Window::mouseButtonIsDown(unsigned int button) const {
		if (button >= MAX_BUTTONS) {
		// TODO: log an error
			return false;
		}
		return m_buttonsThisFrame[button];
	}

	bool Window::mouseButtonWasReleased(unsigned int button) const
	{
		if (button >= MAX_BUTTONS) {
			// TODO: log an error
			return false;
		}
		return (m_buttonsLastFrame[button] && !m_buttonsThisFrame[button]);
	}	
	
	bool Window::keyWasReleased(unsigned int key) const
	{
		if (key >= MAX_KEYS) {
			// TODO: log an error
			return false;
		}
		return  (m_keysLastFrame[key] && !m_keysThisFrame[key]);;
	}

	void Window::getMousePos(double& x, double& y) const {
		x = mx;
		y = my;
	}


	void Window::clear() const {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::update() {
		scrolledThisFrameY = 0;


		glfwPollEvents();
		glfwSwapBuffers(m_Window);

		//audio:
		audio::AudioManager::update(); // TODO: TEST PERMORMANCE


	}

	void Window::listenForInput()
	{
		
		for (int i = 0; i < MAX_KEYS; i++) {
			m_keysFirstFrameDown[i] = false;
		}
		// handle input:
		for (size_t i = 0; i < MAX_KEYS; i++) {
			m_keysFirstFrameDown[i] = m_keysThisFrame[i] && !m_keysLastFrame[i]; // first frame pressed
		}
		memcpy(&m_keysLastFrame, m_keysThisFrame, sizeof(bool) * MAX_KEYS);

		for (size_t i = 0; i < MAX_BUTTONS; i++) {
			m_buttonsFirstFrameDown[i] = m_buttonsThisFrame[i] && !m_buttonsLastFrame[i];
		}
		memcpy(&m_buttonsLastFrame, m_buttonsThisFrame, sizeof(bool) * MAX_BUTTONS);

	}

	bool Window::closed() const {
		return glfwWindowShouldClose(m_Window) == 1;
	}


	void window_resize_callback(GLFWwindow* window, int width, int height){
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		if (!win->isResizeable) { return;  }
		glViewport(0, 0, width, height);
		win->m_Width = width;
		win->m_Height = height;
		FontManager::remakeAllFonts(width/32.0f, height/16.0f); // NOTE: huge performance hit when resizing.. we should rethink this
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
	
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->scrolledThisFrameY = yoffset;
	}


	void Window::toggleVSync()
	{
		Window::useVSync = !Window::useVSync;
		glfwSwapInterval(Window::useVSync);
	}
	void Window::setVSync(bool state)
	{
		Window::useVSync = state;
		glfwSwapInterval(Window::useVSync);
	}

	static void GLAPIENTRY openglCallbackFunction(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam){
		return;
		std::cout << "---------------------opengl-callback-start------------" << std::endl;
		std::cout << "Message: " << message << std::endl;
		std::cout << "Type: ";
		switch (type) {
		case GL_DEBUG_TYPE_ERROR:
			std::cout << "ERROR";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			std::cout << "DEPRECATED_BEHAVIOR";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			std::cout << "UNDEFINED_BEHAVIOR";
			break;
		case GL_DEBUG_TYPE_PORTABILITY:
			std::cout << "PORTABILITY";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE:
			std::cout << "PERFORMANCE";
			break;
		case GL_DEBUG_TYPE_OTHER:
			std::cout << "OTHER";
			break;
		}
		std::cout << std::endl;

		std::cout << "id: " << id << std::endl;
		std::cout << "severity: ";
		switch (severity) {
		case GL_DEBUG_SEVERITY_LOW:
			std::cout << "LOW";
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			std::cout << "MEDIUM";
			break;
		case GL_DEBUG_SEVERITY_HIGH:
			std::cout << "HIGH";
			break;
		}
		std::cout << std::endl;
		std::cout << "---------------------opengl-callback-end--------------" << std::endl;
	}



	
}}