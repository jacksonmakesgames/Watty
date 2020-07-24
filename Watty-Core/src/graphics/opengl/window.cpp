#include <graphics/window.h>
namespace letc {namespace graphics {
	void window_resize_callback(GLFWwindow* window, int width, int height);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	Window* Window::Instance = nullptr;

	Window::Window(const char* title, int width, int height, bool resizeable, bool fullscreen) {
		if (Window::Instance != nullptr) {
			//TODO: log error
			std::cout << "Error: can only have one Window" << std::endl;
			exit(1);
		}
		else {
			Window::Instance = this;
		}

		mTitle = title;
		mWidth = width;
		mHeight = height;
		isResizeable = resizeable;
		isFullScreen = fullscreen;
		if (!init()) {
			glfwTerminate();
			std::cout << "GLFW failed to initialize, terminating." << std::endl;
			return;
		}

		for (int i = 0; i < MAX_KEYS; i++) {
			mKeysThisFrame[i]		=	false;
			mKeysLastFrame[i]	=	false;
			mKeysFirstFrameDown[i]	=	false;
		}
		for (int i = 0; i < MAX_BUTTONS; i++) {
			mButtonsThisFrame[i]		=	 false;
			mButtonsLastFrame[i]		=	 false;
			mButtonsFirstFrameDown[i]			=	 false;
		}

		FontManager::init(mWidth / (std::get<0>(getAspectRatio()) * 2),
			mHeight / (std::get<1>(getAspectRatio()) * 2));

	}	

	Window::~Window() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyPlatformWindows();
		ImGui::DestroyContext();

		glfwTerminate();

		//FontManager::clean(); //TODO
		audio::AudioManager::clean();
	}

	// TODO: NOT SURE, asks nvidia to use dedicated gpu
	/*extern "C" {
		_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
	}*/

	bool Window::init() {

		if (!glfwInit()){
			std::cout << "Failed to initialize GLFW" << std::endl;
			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

		glfwWindowHint(GLFW_RESIZABLE, isResizeable);

		if (isFullScreen) {
			const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			
			mWidth = mode->width;
			mHeight = mode->height;
			mGLFWWindow = glfwCreateWindow(mWidth, mHeight, mTitle, glfwGetPrimaryMonitor(), NULL); // fullscreen
		}
		else
			mGLFWWindow = glfwCreateWindow(mWidth, mHeight, mTitle, NULL, NULL);
		
		mRefreshRate = glfwGetVideoMode(glfwGetPrimaryMonitor())->refreshRate;
		if (!mGLFWWindow) {
			glfwTerminate();
			std::cout << "Failed to create window" << std::endl;
			return false;
		}

		glfwMakeContextCurrent(mGLFWWindow);
		glfwSetWindowUserPointer(mGLFWWindow, this);
		if(isResizeable) glfwSetFramebufferSizeCallback(mGLFWWindow, window_resize_callback);
		glfwSetKeyCallback(mGLFWWindow, key_callback);
		glfwSetMouseButtonCallback(mGLFWWindow, mouse_button_callback);
		glfwSetCursorPosCallback(mGLFWWindow, cursor_position_callback);
		glfwSetScrollCallback(mGLFWWindow, scroll_callback);
		glfwSwapInterval(useVSync);

#ifndef WATTY_EMSCRIPTEN
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}
#endif
		std::cout << "Watty{} Version: " << WATTY_VERSION << std::endl;
		std::cout << " OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

#ifndef WATTY_EMSCRIPTEN
		GLint flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT){
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(openglCallbackFunction, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

		}
#endif // !WATTY_EMSCRIPTEN

		glClearColor(0, 0, 0, 1); // Default
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		
		initImGUI();


		return true;
	}

	bool Window::initImGUI()
	{
		// imgui:
		IMGUI_CHECKVERSION();

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

#ifdef WATTY_EMSCRIPTEN
		const char* glsl_version = "#version 300 es";
#else
		const char* glsl_version = "#version 450";
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // enable multiple viewports
		io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;
#endif // WATTY_EMSCRIPTEN

		ImGui::GetStyle().WindowRounding = 0.0f;
		ImGui::GetStyle().ChildRounding = 0.0f;
		ImGui::GetStyle().FrameRounding = 0.0f;
		ImGui::GetStyle().GrabRounding = 0.0f;
		ImGui::GetStyle().PopupRounding = 0.0f;
		ImGui::GetStyle().ScrollbarRounding = 0.0f;
		ImGui::StyleColorsLight();

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(mGLFWWindow, true);
		ImGui_ImplOpenGL3_Init(glsl_version);

		io.DisplaySize = ImVec2(mWidth, mHeight);
		return true;
	}

	std::tuple<int, int> Window::getAspectRatio()
	{
		int outNum = mWidth;
		int outDen = mHeight;

		for (int i = outDen * outNum; i > 1; i--) {
			if ((outDen % i == 0) && (outNum % i == 0)) {
				outDen /= i;
				outNum /= i;
			}
		}
		return std::tuple<int, int>(outNum, outDen);
	}




	bool Window::keyIsDown(unsigned int keycode) const {
		// if the key is down this frame
		if (keycode >= MAX_KEYS) {
		// TODO: log an error
			return false;
		}
		return mKeysThisFrame[keycode];
	}



	bool Window::keyWasPressed(unsigned int keycode) const {
		// If this is the first frame a key is down
		if (keycode >= MAX_KEYS) {
		// TODO: log an error
			return false;
		}
		return mKeysFirstFrameDown[keycode];
	}


	bool Window::mouseButtonWasPressed(unsigned int button) const {
		if (button >= MAX_BUTTONS) {
		// TODO: log an error
			return false;
		}
		return mButtonsFirstFrameDown[button];
	}


	bool Window::mouseButtonIsDown(unsigned int button) const {
		if (button >= MAX_BUTTONS) {
		// TODO: log an error
			return false;
		}
		return mButtonsThisFrame[button];
	}


	bool Window::mouseButtonWasReleased(unsigned int button) const {
		if (button >= MAX_BUTTONS) {
			// TODO: log an error
			return false;
		}
		return (mButtonsLastFrame[button] && !mButtonsThisFrame[button]);
	}	
	

	bool Window::keyWasReleased(unsigned int key) const {
		if (key >= MAX_KEYS) {
			// TODO: log an error
			return false;
		}
		return  (mKeysLastFrame[key] && !mKeysThisFrame[key]);;
	}


	void Window::getMousePos(double& x, double& y) const {
		x = mMouseX;
		y = mMouseY;
	}


	void Window::clear() const {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}


	void Window::update() {
		mScrolledThisFrameY = 0;
		glfwPollEvents();
		glfwSwapBuffers(mGLFWWindow);
	}


	void Window::listenForInput(){
		
		for (int i = 0; i < MAX_KEYS; i++) {
			mKeysFirstFrameDown[i] = false;
		}
		// handle input:
		for (size_t i = 0; i < MAX_KEYS; i++) {
			mKeysFirstFrameDown[i] = mKeysThisFrame[i] && !mKeysLastFrame[i]; // first frame pressed
		}
		memcpy(&mKeysLastFrame, mKeysThisFrame, sizeof(bool) * MAX_KEYS);

		for (size_t i = 0; i < MAX_BUTTONS; i++) {
			mButtonsFirstFrameDown[i] = mButtonsThisFrame[i] && !mButtonsLastFrame[i];
		}
		memcpy(&mButtonsLastFrame, mButtonsThisFrame, sizeof(bool) * MAX_BUTTONS);
	}


	glm::vec3 Window::viewportToWorld(glm::vec2 position, const Camera& cam){
		glm::vec2 pointScreenRatio = glm::vec2();
		pointScreenRatio.x = position.x / getWidth();
		pointScreenRatio.y = (getHeight() -position.y) / getHeight();

		glm::vec2 pointWorldRatio = pointScreenRatio * cam.getSize();

		pointWorldRatio.x -= (.5f * cam.getSize().x);
		pointWorldRatio.y -= (.5f * cam.getSize().y);

		glm::vec3 worldPoint = glm::vec3(pointWorldRatio.x, pointWorldRatio.y, 0) + cam.position;
		return worldPoint;
	}
	

	bool Window::closed() const {
		return glfwWindowShouldClose(mGLFWWindow) == 1;
	}


	void window_resize_callback(GLFWwindow* window, int width, int height){
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		if (!win->isResizeable) { return;  }
		glViewport(0, 0, width, height);
		win->mWidth = width;
		win->mHeight = height;
		
		// NOTE: huge performance hit when resizing.. we should rethink this
		/*std::tuple aR = win->getAspectRatio();
		FontManager::remakeAllFonts(
			win->getWidth() / (std::get<0>(aR) * 2),
			win->getHeight() / (std::get<1>(aR) * 2));*/
	}


	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Window * win = (Window*) glfwGetWindowUserPointer(window);
		win->mKeysThisFrame[key] = action != GLFW_RELEASE;

	}


	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
		Window * win = (Window*) glfwGetWindowUserPointer(window);
		win->mButtonsThisFrame[button] = action != GLFW_RELEASE;

	}


	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->mMouseX = xpos;
		win->mMouseY = ypos;

	}
	

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->mScrolledThisFrameY = yoffset;
	}


	void Window::toggleVSync(){
		Window::useVSync = !Window::useVSync;
		glfwSwapInterval(Window::useVSync);
	}

	void Window::setVSync(bool state){
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