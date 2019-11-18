#include "VulkanSwapChain.h"
namespace letc { namespace graphics {

	VulkanSwapChain::VulkanSwapChain(VulkanDevice* device, VkSurfaceKHR* surface, VulkanPhysicalDevice* physicalDevice){
		m_device = device;
		m_surface = surface;
		m_physicalDevice = physicalDevice;
		init();
		
	}




	VkSurfaceFormatKHR VulkanSwapChain::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> & availableFormats) {
		for (const auto& availableFormat : availableFormats) {
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
				return availableFormat;
			}
		}

		return availableFormats[0];
	}

	VkPresentModeKHR VulkanSwapChain::chooseSwapPresentMode(const std::vector<VkPresentModeKHR> & availablePresentModes) {
		for (const auto& availablePresentMode : availablePresentModes) {
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
				return availablePresentMode;
			}
		}

		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D VulkanSwapChain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR & capabilities) {
		if (capabilities.currentExtent.width != UINT32_MAX) {
			return capabilities.currentExtent;
		}
		else {
			//VkExtent2D actualExtent = { WIDTH, HEIGHT };
			VkExtent2D actualExtent = { 1600, 900 };

			actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
			actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

			return actualExtent;
		}
	}

	void VulkanSwapChain::init()
	{
		SwapChainSupportDetails swapChainSupport = VulkanPhysicalDevice::querySwapChainSupport(m_physicalDevice->GetPhysicalDevice(), *m_surface);

		VkSurfaceFormatKHR surfaceFormat = graphics::VulkanSwapChain::chooseSwapSurfaceFormat(swapChainSupport.formats);
		VkPresentModeKHR presentMode = graphics::VulkanSwapChain::chooseSwapPresentMode(swapChainSupport.presentModes);
		VkExtent2D extent = graphics::VulkanSwapChain::chooseSwapExtent(swapChainSupport.capabilities);

		uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
		if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
			imageCount = swapChainSupport.capabilities.maxImageCount;
		}

		QueueFamilyIndices indices = m_physicalDevice->GetQueueFamilyIndices();

		uint32_t queueFamilyIndices[] = {indices.graphics_indices, indices.compute_indices };


		VkSwapchainCreateInfoKHR createInfo = initializers::SwapChainCreateInfo(*m_surface, m_physicalDevice->GetPhysicalDevice(), queueFamilyIndices, swapChainSupport, presentMode);

		VkResult res = vkCreateSwapchainKHR(*(m_device->getDevice()), &createInfo, nullptr, m_swapChain);
		if (res != VK_SUCCESS) {
			throw std::runtime_error("failed to create swap chain!");
		}
	}

} }

