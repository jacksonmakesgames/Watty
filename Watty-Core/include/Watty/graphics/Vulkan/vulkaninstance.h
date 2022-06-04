#pragma once

#define GLFW_INCLUDE_VULKAN
#include <ext/GLFW/include/GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <optional>
#include <set>

#include"initializers.h"

#include "vulkanconfig.h"
#include "VulkanDevice.h"
#include "VulkanGraphicsPipeline.h"
#include "vulkanphysicaldevice.h"
#include "VulkanSwapChain.h"
#include "VulkanRenderPass.h"
#include "VulkanFrameBuffer.h"

namespace watty { namespace graphics {

	class VulkanInstance {
	private:
		VkInstance m_instance;

		std::vector<const char*> m_layers;
		std::vector<const char*> m_extensions;

		VkSurfaceKHR m_vkSurface;
		VulkanPhysicalDevice m_vkPhysicalDevice;
		VulkanDevice m_vkLogicalDevice;
		VulkanSwapChain m_vkSwapChain;
		VulkanRenderPass m_vkRenderPass;
		VulkanGraphicsPipeline m_vkGraphicsPipeline;
		VulkanFrameBuffer m_vkFrameBuffers;

		std::vector<VkCommandBuffer> m_vkCommandBuffers;
		std::vector<VkSemaphore> m_imageAvailableSemaphores;
		std::vector<VkSemaphore> m_renderFinishedSemaphores;
		std::vector<VkFence> m_inFlightFences;
		std::vector<VkFence> m_imagesInFlight;
		size_t m_currentFrame = 0;

		float m_windowWidth;
		float m_windowHeight;
		GLFWwindow* m_glfwWindow;

	public:
		VulkanInstance(int initWidth, int initHeight, GLFWwindow* glfwWindow);

		void drawVulkanFrame();
		inline const VkInstance& getInstance(){ return m_instance; }
		inline const std::vector<const char*>& getLayers(){ return m_layers; }
		~VulkanInstance();


	private:
		void initVulkan();
		std::vector<const char*> getRequiredExtensions();
		void recreateSwapChain();
		void cleanupSwapChain();
		void cleanupVulkan();




	};


} }