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

		// TODO: WE SHOULD NOT BE PASSING POINTERS, THESE SHOULD JUST BE OBJS PASSED BY REFERENCE

		// create physical device
		m_vkPhysicalDevice = VulkanPhysicalDevice::GetPhysicalDevice(m_vkInstance, m_vkSurface);
		
		// create logical device
		m_vkLogicalDevice = new VulkanDevice(m_vkInstance, m_vkPhysicalDevice, m_vkInstance->getLayers());

		// create swapchain/ swapchain images
		 m_vkSwapChain = new VulkanSwapChain(m_vkLogicalDevice, &m_vkSurface, m_vkPhysicalDevice);

		 // create render pass
		 m_vkRenderPass = new VulkanRenderPass(m_vkLogicalDevice->getDevice(), *m_vkSwapChain->getSwapChainImageFormatExtent());

		// create graphics pipeline
		 m_vkGraphicsPipeline = new VulkanGraphicsPipeline(m_vkLogicalDevice, m_vkSwapChain->getSwapChainExtent(), m_vkRenderPass->getRenderPass());

		 // create frame buffers
		 m_vkFrameBuffers = new VulkanFrameBuffer(m_vkLogicalDevice->getDevice(), m_vkSwapChain->getSwapChainImageViews(), m_vkRenderPass->getRenderPass(), m_vkSwapChain->getSwapChainExtent());

		 // allocate command buffers TODO: only three for now, we can make this more later
		 m_vkCommandBuffers.resize(m_vkFrameBuffers->getswapChainFramebuffers().size());
		 m_vkLogicalDevice->getGraphicsCommandBuffers(m_vkCommandBuffers);

		// start the renderpass
		 m_vkRenderPass->startRenderPass(m_vkSwapChain->getSwapChainExtent(), m_vkFrameBuffers->getswapChainFramebuffers(), m_vkCommandBuffers, m_vkGraphicsPipeline->getPipeline());

		 // create semaphores
		 //TODO: move these to initializers eventually
		 m_imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
		 m_renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
		 m_inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
		 m_imagesInFlight.resize(m_vkSwapChain->getSwapChainImages().size(), VK_NULL_HANDLE);

		 VkSemaphoreCreateInfo semaphoreInfo = {};
		 semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		 VkFenceCreateInfo fenceInfo = {};
		 fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		 fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		 for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			 if (vkCreateSemaphore(*m_vkLogicalDevice->getDevice(), &semaphoreInfo, nullptr, &m_imageAvailableSemaphores[i]) != VK_SUCCESS ||
				 vkCreateSemaphore(*m_vkLogicalDevice->getDevice(), &semaphoreInfo, nullptr, &m_renderFinishedSemaphores[i]) != VK_SUCCESS ||
				 vkCreateFence(*m_vkLogicalDevice->getDevice(), &fenceInfo, nullptr, &m_inFlightFences[i]) != VK_SUCCESS) {

				 throw std::runtime_error("failed to create synchronization objects for a frame!");
			 }
		 }

	}

	void Window::drawVulkanFrame() {
		uint32_t imageIndex;

		vkWaitForFences(*m_vkLogicalDevice->getDevice(), 1, &m_inFlightFences[m_currentFrame], VK_TRUE, UINT64_MAX);

		vkAcquireNextImageKHR(*m_vkLogicalDevice->getDevice(),*m_vkSwapChain->getSwapChain(), UINT64_MAX, m_imageAvailableSemaphores[m_currentFrame], VK_NULL_HANDLE, &imageIndex);
		// Check if a previous frame is using this image (i.e. there is its fence to wait on)
		if (m_imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
			vkWaitForFences(*m_vkLogicalDevice->getDevice(), 1, &m_imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
		}
		// Mark the image as now being in use by this frame
		m_imagesInFlight[imageIndex] = m_inFlightFences[m_currentFrame];


		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

		VkSemaphore waitSemaphores[] = { m_imageAvailableSemaphores[m_currentFrame] };
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &m_vkCommandBuffers[imageIndex];

		VkSemaphore signalSemaphores[] = { m_renderFinishedSemaphores[m_currentFrame] };
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;

		vkResetFences(*m_vkLogicalDevice->getDevice(), 1, &m_inFlightFences[m_currentFrame]);

		if (vkQueueSubmit(*m_vkLogicalDevice->getGraphicsQueue(), 1, &submitInfo, m_inFlightFences[m_currentFrame]) != VK_SUCCESS) {
			throw std::runtime_error("failed to submit draw command buffer!");
		}


		// presentation
		VkSwapchainKHR swapChains[] = {  *m_vkSwapChain->getSwapChain() };
		VkPresentInfoKHR presentInfo = {};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapChains;
		presentInfo.pImageIndices = &imageIndex;
		presentInfo.pResults = nullptr; // Optional

		vkQueuePresentKHR(*m_vkLogicalDevice->getGraphicsQueue(), &presentInfo);

		vkQueueWaitIdle(*m_vkLogicalDevice->getGraphicsQueue());

		m_currentFrame = (m_currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
	}

	void Window::cleanupVulkan(){
		vkDestroySurfaceKHR(m_vkInstance->getInstance(), m_vkSurface, nullptr);
		vkDestroyInstance(m_vkInstance->getInstance(), nullptr);
		vkDestroySwapchainKHR(*m_vkLogicalDevice->getDevice(), *m_vkSwapChain->getSwapChain(), nullptr);
		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			vkDestroySemaphore(*m_vkLogicalDevice->getDevice(), m_renderFinishedSemaphores[i], nullptr);
			vkDestroySemaphore(*m_vkLogicalDevice->getDevice(), m_imageAvailableSemaphores[i], nullptr);
			vkDestroyFence(*m_vkLogicalDevice->getDevice(), m_inFlightFences[i], nullptr);
		}

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
		//glfwSwapBuffers(m_Window); //OPENGL

		drawVulkanFrame();

		//audio:
		audio::AudioManager::update(); 
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