#include <graphics/window.h>
namespace watty {namespace graphics {
	void window_resize_callback(GLFWwindow* window, int width, int height);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


	bool Window::allowMultipleSubWindows = true;

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
			std::cout << "GLFW failed to initialize, terminating. Check your video drivers." << std::endl;
			return;
		}

		
		

		FontManager::init(m_Width / (getAspectRatio().x * 2),
			m_Height / (getAspectRatio().y * 2));

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
		if (firstInit) {
			if (!glfwInit()) {
				std::cout << "Failed to initialize GLFW" << std::endl;
				return false;
			}
		}
		else {
			glfwDestroyWindow(m_Window);
			glfwWaitEvents();
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

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		if(isResizeable) glfwSetFramebufferSizeCallback(m_Window, window_resize_callback);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		glfwSetScrollCallback(m_Window, scroll_callback);
		//glfwSetWindowCloseCallback(m_Window, window_close_callback);
		glfwSwapInterval(useVSync);

#ifndef WATTY_EMSCRIPTEN
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cout << "Failed to initialize GLAD" << std::endl;
				return -1;
			}
#endif
		if (firstInit) {
			std::cout << "Watty{} Version: " << WATTY_VERSION << std::endl;
			std::cout << " OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
		}
#ifndef WATTY_EMSCRIPTEN
			GLint flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
			if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
				glEnable(GL_DEBUG_OUTPUT);
				glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
				glDebugMessageCallback(openglCallbackFunction, nullptr);
				glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

			}
#endif // !WATTY_EMSCRIPTEN

			glClearColor(0, 0, 0, 1); // Default
			glEnable(GL_BLEND);

			//#ifdef WATTY_EMSCRIPTEN
					//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
			//#else
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			//#endif


		initImGUI();
		firstInit = false;
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

	glm::i8vec2 Window::getAspectRatio()
	{
		int outNum = mWidth;
		int outDen = mHeight;

		for (int i = outDen * outNum; i > 1; i--) {
			if ((outDen % i == 0) && (outNum % i == 0)) {
				outDen /= i;
				outNum /= i;
			}
		}
		return glm::i8vec2(outNum, outDen);
	}

	void Window::clear() const {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::clear(float r, float g, float b, float a, bool enableDepth, bool clearImGui) const
	{
		glClearColor(r,g,b,a);
		
		if (clearImGui) {
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}
		if (enableDepth) {
			//enable the GL_DEPTH_TEST to be able to see 3D object correctly
			glEnable(GL_DEPTH_TEST);
			//clear both the color buffer bit and the depth buffer bit
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		else {
			//clear just the color buffer bit
			glClear(GL_COLOR_BUFFER_BIT);
		}
	}
	void Window::clear(WattyColor clearColor, bool enableDepth, bool clearImGui) const {
		std::cout << "Error: Not Implemented, use clear(float, float, float, float, ...) instead" << std::endl;
		throw NotImplemented();
		glClearColor(clearColor.rgba.r/255.0f, clearColor.rgba.g/255.0f, clearColor.rgba.b/255.0f, clearColor.rgba.a/255.0f);
		//glClearColor(clearColor.asFloat[0], clearColor.asFloat[1], clearColor.asFloat[2], clearColor.asFloat[3]);
		//glClearColor(clearColor.rgba.b, clearColor.rgba.g, clearColor.rgba.r, clearColor.rgba.a);
		//glClearColor(clearColor.abgr.r, clearColor.abgr.g, clearColor.abgr.b, clearColor.abgr.a);

		if (clearImGui){
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}
		if (enableDepth){
			//enable the GL_DEPTH_TEST to be able to see 3D object correctly
			glEnable(GL_DEPTH_TEST);
			//clear both the color buffer bit and the depth buffer bit
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		else{
			//clear just the color buffer bit
			glClear(GL_COLOR_BUFFER_BIT);
		}
	}

	void Window::update() {
		//scrolledThisFrameY = 0;
		//Input::resetScroll();
		endImGuiFrame();
		glfwPollEvents();
		glfwSwapBuffers(mGLFWWindow);
	}

	void Window::endImGuiFrame() {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		if (Window::allowMultipleSubWindows) {
			// ImGui Multiple Viewports:
			if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}
		}
	}

	glm::vec3 Window::viewportToWorld(glm::vec2 position, const Camera& cam){
		glm::vec2 pointScreenRatio = glm::vec2();
		pointScreenRatio.x = position.x / getWidth();
		pointScreenRatio.y = (getHeight() -position.y) / getHeight();

		glm::vec2 pointWorldRatio = pointScreenRatio * cam.getSize();

		//pointWorldRatio.x -= (.5f * cam.getSize().x);
		//pointWorldRatio.y -= (.5f * cam.getSize().y);
		pointWorldRatio.x -= (.5f * cam.getViewportSize().x);
		pointWorldRatio.y -= (.5f * cam.getViewportSize().y);

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
		glScissor(0, 0, width,height);
		glEnable(GL_SCISSOR_TEST);
		win->m_Width = width;
		win->m_Height = height;
		
		for (size_t i = 0; i < Camera::allCameras.size(); i++)
		{
			if (Camera::allCameras[i]->isEditorCamera) continue; // TODO improve perf
			Camera::allCameras[i]->setWindowSize(glm::vec2(2 * (width / win->PIXEL_TO_METER_RATIO), 2 * (height / win->PIXEL_TO_METER_RATIO)));
		}



	}

	void window_close_callback(GLFWwindow* window)
	{
		glfwSetWindowShouldClose(window, GLFW_FALSE);
	}



	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Input::setKeyThisFrame(key, action != GLFW_RELEASE);
	}


	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
		Input::setButtonThisFrame(button, action != GLFW_RELEASE);
	}


	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
		Input::updateMousePos(xpos, ypos);
	}


	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
		Input::scrolledThisFrameY = yoffset;
	}

	//TODO: not sure why this is static
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