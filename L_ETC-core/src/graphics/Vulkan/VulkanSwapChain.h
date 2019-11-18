#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "vulkanphysicaldevice.h"
#include "vulkandevice.h"
#include "../../initializers.h"

namespace letc { namespace graphics {
	class VulkanSwapChain {
	private:
		VulkanPhysicalDevice* m_physicalDevice;
		VulkanDevice* m_device;
		VkSurfaceKHR* m_surface;
		VkSwapchainKHR* m_swapChain;
		SwapChainSupportDetails m_supportDetails;


	public:
		VulkanSwapChain(VulkanDevice* device, VkSurfaceKHR* surface, VulkanPhysicalDevice* physicalDevice);
		

		static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR& surface);
		static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

		
		~VulkanSwapChain();
	private:
		void init();
	};


} }