#include "window.h"
namespace letc {namespace graphics {
	static void window_resize_callback(GLFWwindow* window, int width, int height);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	Window::Window(const char* title, int width, int height) {
		m_Title = title;
		m_Width = width;
		m_Height = height;
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
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);
#endif
		if (!m_Window) {
			glfwTerminate();
			std::cout << "Failed to create window" << std::endl;
			return false;
		}

		//TODO: VK CODE
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

		initVulkan();

	/*	glfwMakeContextCurrent(m_Window);
		
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetFramebufferSizeCallback(m_Window, window_resize_callback);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		glfwSwapInterval(0);*/


		
#if 0
		// TODO: OPENGL CODE
		GLint flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(openglCallbackFunction, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}

		// choose how textures render on top of one another
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		// add error texture to TextureManager
		//TextureManager::errorTexture = new Texture("J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/res/error_texture.png");
#endif
		return true;

	}

	void Window::initVulkan(){
		

		VulkanConfig vulkanConfig;
		vulkanConfig.applicationName = "LETC";
		vulkanConfig.applicationVersion = VK_MAKE_VERSION(0, 0, 1);

		m_vkInstance = new VulkanInstance(vulkanConfig, getRequiredExtensions());
	

		VkResult res = glfwCreateWindowSurface(m_vkInstance->getInstance(), m_Window, nullptr, &m_vkSurface);

		if (res != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface!");
		}

		physicalDevice = VulkanPhysicalDevice::GetPhysicalDevice(m_vkInstance, m_vkSurface);
		device = new VulkanDevice(m_vkInstance, physicalDevice);

		// init swapchain
		// TODO:: THESE SHOULD NOT BE MEMBERS OF PHYSICAL DEVICE, WE SHOULD MAKE A SWAP CHAIN CLASS!!
		SwapChainSupportDetails swapChainSupport = VulkanPhysicalDevice::querySwapChainSupport(physicalDevice->GetPhysicalDevice(), m_vkSurface);

		VkSurfaceFormatKHR surfaceFormat = VulkanPhysicalDevice::chooseSwapSurfaceFormat(swapChainSupport.formats);
		VkPresentModeKHR presentMode = VulkanPhysicalDevice::chooseSwapPresentMode(swapChainSupport.presentModes);
		VkExtent2D extent = VulkanPhysicalDevice::chooseSwapExtent(swapChainSupport.capabilities);

		uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
		if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
			imageCount = swapChainSupport.capabilities.maxImageCount;
		}

		// SHOULD PUT THIS IN INITIALIZERS
		VkSwapchainCreateInfoKHR createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = m_vkSurface;
		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		QueueFamilyIndices indices = physicalDevice->GetQueueFamilyIndices();
		uint32_t queueFamilyIndices[] = { indices.graphics_indices/*, indices.presentFamily*/};

		//if (indices.graphicsFamily != indices.presentFamily) {
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		//}
		//else {
			//createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			//createInfo.queueFamilyIndexCount = 0; // Optional
			//createInfo.pQueueFamilyIndices = nullptr; // Optional
		//}
		createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;
		createInfo.oldSwapchain = VK_NULL_HANDLE;
		VkSwapchainKHR swapChain;
		res = vkCreateSwapchainKHR(*(device->getDevice()), &createInfo, nullptr, &swapChain);
		if (res != VK_SUCCESS) {
			throw std::runtime_error("failed to create swap chain!");
		}

		// TODO: LEFT OFF RIGHT BEFORE "Retrieving the swap chain images"
	}

	void Window::cleanupVulkan(){
		vkDestroySurfaceKHR(m_vkInstance->getInstance(), m_vkSurface, nullptr);
		vkDestroyInstance(m_vkInstance->getInstance(), nullptr);
		// TODO destroy swapchain
	}

	std::vector<const char*>  Window::getRequiredExtensions()
	{
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		if (true) {
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}
		return extensions;
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


	void Window::clear() const {
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // opengl
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
		glfwSwapBuffers(m_Window);

		//audio:
		audio::AudioManager::update(); // TODO: TEST PERMORMANCE
	}

	bool Window::closed() const {
		return glfwWindowShouldClose(m_Window) == 1;
	}


	void window_resize_callback(GLFWwindow* window, int width, int height){
		//glViewport(0, 0, width, height);
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_Width = width;
		win->m_Height = height;
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

#if 0
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

#endif

	
}}