#include <graphics/Vulkan/vulkaninstance.h>

namespace letc {namespace graphics {
	const int MAX_FRAMES_IN_FLIGHT = 2;

	const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif


	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
		}
		else {
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
		if (func != nullptr) {
			func(instance, debugMessenger, pAllocator);
		}
	}

	//Todo: this needs major cleanup
	VulkanInstance::VulkanInstance(int initWidth, int initHeight, GLFWwindow* glfwWindow){
		m_windowWidth = initWidth;
		m_windowHeight = initHeight;
		m_glfwWindow = glfwWindow;

		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		
		// Find out which extensions we will need
		std::vector<const char*> exts = getRequiredExtensions();

		for (size_t i = 0; i < exts.size(); i++)
		{
			m_extensions.push_back(exts[i]);
		}

		VulkanConfig config;
		config.applicationName = "LETC";
		config.applicationVersion = VK_MAKE_VERSION(0, 0, 1);


		VkApplicationInfo appInfo = initializers::ApplicationInfo(config);
		VkInstanceCreateInfo instanceInfo = initializers::InstanceCreateInfo(appInfo, m_layers, m_extensions);


		VkResult result = vkCreateInstance(&instanceInfo, nullptr, &m_instance);

		if (result != VK_SUCCESS) {
			std::cout << "FAILED TO INIT VULKAN WITH ERROR: " << result << std::endl;
			return;
		}

		initVulkan();
	}

	void VulkanInstance::initVulkan() {

		VkResult res = glfwCreateWindowSurface(m_instance, m_glfwWindow, nullptr, &m_vkSurface);
		if (res != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface!");
		}

		// create physical device
		m_vkPhysicalDevice = *new VulkanPhysicalDevice(m_instance, m_vkSurface);

		// create logical device
		m_vkLogicalDevice = *new VulkanDevice(m_vkPhysicalDevice, m_layers);

		// create swapchain / swapchain images
		m_vkSwapChain = *new VulkanSwapChain(m_vkLogicalDevice, m_vkSurface, m_vkPhysicalDevice, m_windowWidth, m_windowHeight);

		// create render pass
		m_vkRenderPass = *new VulkanRenderPass(m_vkLogicalDevice.getDevice(), m_vkSwapChain.getSwapChainImageFormatExtent());

		// create graphics pipeline
		m_vkGraphicsPipeline = *new VulkanGraphicsPipeline(m_vkLogicalDevice, m_vkSwapChain.getSwapChainExtent(), m_vkRenderPass.getRenderPass());

		// create frame buffers
		m_vkFrameBuffers = VulkanFrameBuffer(m_vkLogicalDevice.getDevice(), m_vkSwapChain.getSwapChainImageViews(), m_vkRenderPass.getRenderPass(), m_vkSwapChain.getSwapChainExtent());

		// allocate command buffers
		m_vkCommandBuffers.resize(m_vkFrameBuffers.getswapChainFramebuffers().size());
		m_vkLogicalDevice.getGraphicsCommandBuffers(m_vkCommandBuffers);

		// start the renderpass
		m_vkRenderPass.startRenderPass(m_vkSwapChain.getSwapChainExtent(), m_vkFrameBuffers.getswapChainFramebuffers(), m_vkCommandBuffers, m_vkGraphicsPipeline.getPipeline());

		// create semaphores
		m_imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
		m_renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
		m_inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
		m_imagesInFlight.resize(m_vkSwapChain.getSwapChainImages().size(), VK_NULL_HANDLE);

		//TODO: move these to initializers eventually
		VkSemaphoreCreateInfo semaphoreInfo = {};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkFenceCreateInfo fenceInfo = {};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			if (vkCreateSemaphore(m_vkLogicalDevice.getDevice(), &semaphoreInfo, nullptr, &m_imageAvailableSemaphores[i]) != VK_SUCCESS ||
				vkCreateSemaphore(m_vkLogicalDevice.getDevice(), &semaphoreInfo, nullptr, &m_renderFinishedSemaphores[i]) != VK_SUCCESS ||
				vkCreateFence(m_vkLogicalDevice.getDevice(), &fenceInfo, nullptr, &m_inFlightFences[i]) != VK_SUCCESS) {

				throw std::runtime_error("failed to create synchronization objects for a frame!");
			}
		}
	}

	void VulkanInstance::recreateSwapChain() {
		// TODO not sure everything is being cleaned up

		cleanupSwapChain();

		// create swapchain / swapchain images
		m_vkSwapChain = *new VulkanSwapChain(m_vkLogicalDevice, m_vkSurface, m_vkPhysicalDevice, m_windowWidth, m_windowHeight);

		// create render pass
		m_vkRenderPass = *new VulkanRenderPass(m_vkLogicalDevice.getDevice(), m_vkSwapChain.getSwapChainImageFormatExtent());

		// create graphics pipeline
		m_vkGraphicsPipeline = *new VulkanGraphicsPipeline(m_vkLogicalDevice, m_vkSwapChain.getSwapChainExtent(), m_vkRenderPass.getRenderPass());

		// create frame buffers
		m_vkFrameBuffers = *new VulkanFrameBuffer(m_vkLogicalDevice.getDevice(), m_vkSwapChain.getSwapChainImageViews(), m_vkRenderPass.getRenderPass(), m_vkSwapChain.getSwapChainExtent());

		// allocate command buffers 
		m_vkCommandBuffers.resize(m_vkFrameBuffers.getswapChainFramebuffers().size());
		m_vkLogicalDevice.getGraphicsCommandBuffers(m_vkCommandBuffers);
		m_vkRenderPass.startRenderPass(m_vkSwapChain.getSwapChainExtent(), m_vkFrameBuffers.getswapChainFramebuffers(), m_vkCommandBuffers, m_vkGraphicsPipeline.getPipeline());


	}

	void VulkanInstance::cleanupSwapChain() {
		vkDeviceWaitIdle(m_vkLogicalDevice.getDevice());

		for (size_t i = 0; i < m_vkFrameBuffers.getswapChainFramebuffers().size(); i++) {
			vkDestroyFramebuffer(m_vkLogicalDevice.getDevice(), m_vkFrameBuffers.getswapChainFramebuffers()[i], nullptr);
		}

		vkFreeCommandBuffers(m_vkLogicalDevice.getDevice(), m_vkLogicalDevice.getCommandPool(), static_cast<uint32_t>(m_vkCommandBuffers.size()), m_vkCommandBuffers.data());

		vkDestroyPipeline(m_vkLogicalDevice.getDevice(), m_vkGraphicsPipeline.getPipeline(), nullptr);
		vkDestroyPipelineLayout(m_vkLogicalDevice.getDevice(), m_vkGraphicsPipeline.getPipelineLayout(), nullptr);
		vkDestroyRenderPass(m_vkLogicalDevice.getDevice(), m_vkRenderPass.getRenderPass(), nullptr);

		for (size_t i = 0; i < m_vkSwapChain.getSwapChainImageViews().size(); i++) {
			vkDestroyImageView(m_vkLogicalDevice.getDevice(), m_vkSwapChain.getSwapChainImageViews()[i], nullptr);
		}

		vkDestroySwapchainKHR(m_vkLogicalDevice.getDevice(), m_vkSwapChain.getSwapChain(), nullptr);

	}

	void VulkanInstance::drawVulkanFrame() {
		uint32_t imageIndex;

		vkWaitForFences(m_vkLogicalDevice.getDevice(), 1, &m_inFlightFences[m_currentFrame], VK_TRUE, UINT64_MAX);

		VkResult result = vkAcquireNextImageKHR(m_vkLogicalDevice.getDevice(), m_vkSwapChain.getSwapChain(), UINT64_MAX, m_imageAvailableSemaphores[m_currentFrame], VK_NULL_HANDLE, &imageIndex);
		if (result == VK_ERROR_OUT_OF_DATE_KHR) {
			recreateSwapChain();
			return;
		}
		else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
			throw std::runtime_error("failed to acquire swap chain image!");
		}

		// Check if a previous frame is using this image (i.e. there is its fence to wait on)
		if (m_imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
			vkWaitForFences(m_vkLogicalDevice.getDevice(), 1, &m_imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
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

		vkResetFences(m_vkLogicalDevice.getDevice(), 1, &m_inFlightFences[m_currentFrame]);

		if (vkQueueSubmit(m_vkLogicalDevice.getGraphicsQueue(), 1, &submitInfo, m_inFlightFences[m_currentFrame]) != VK_SUCCESS) {
			throw std::runtime_error("failed to submit draw command buffer!");
		}

		// presentation
		VkSwapchainKHR swapChains[] = { m_vkSwapChain.getSwapChain() };
		VkPresentInfoKHR presentInfo = {};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapChains;
		presentInfo.pImageIndices = &imageIndex;
		presentInfo.pResults = nullptr; // Optional

		result = vkQueuePresentKHR(m_vkLogicalDevice.getGraphicsQueue(), &presentInfo);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
			recreateSwapChain();
		}
		else if (result != VK_SUCCESS) {
			throw std::runtime_error("failed to present swap chain image!");
		}


		vkQueueWaitIdle(m_vkLogicalDevice.getGraphicsQueue());

		m_currentFrame = (m_currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
	}

	void VulkanInstance::cleanupVulkan() {
		cleanupSwapChain();

		vkDestroySwapchainKHR(m_vkLogicalDevice.getDevice(), m_vkSwapChain.getSwapChain(), nullptr);
		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			vkDestroySemaphore(m_vkLogicalDevice.getDevice(), m_renderFinishedSemaphores[i], nullptr);
			vkDestroySemaphore(m_vkLogicalDevice.getDevice(), m_imageAvailableSemaphores[i], nullptr);
			vkDestroyFence(m_vkLogicalDevice.getDevice(), m_inFlightFences[i], nullptr);
		}
		vkDeviceWaitIdle(m_vkLogicalDevice.getDevice());


	}

	std::vector<const char*>  VulkanInstance::getRequiredExtensions()
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






	VulkanInstance::~VulkanInstance(){

		vkDestroyInstance(m_instance, nullptr);
	}
	
}}