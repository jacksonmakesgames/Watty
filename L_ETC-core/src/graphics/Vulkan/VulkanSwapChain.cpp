#include "VulkanSwapChain.h"
namespace letc { namespace graphics {

	VulkanSwapChain::VulkanSwapChain(VulkanDevice* device, VkSurfaceKHR* surface, VulkanPhysicalDevice* physicalDevice, float width, float height){
		m_device = device;
		m_surface = surface;
		m_physicalDevice = physicalDevice;
		m_width = width;
		m_height = height;
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

	VkExtent2D VulkanSwapChain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR & capabilities, float width, float height) {
		if (capabilities.currentExtent.width != UINT32_MAX) {
			return capabilities.currentExtent;
		}
		else {

			VkExtent2D actualExtent = {
				static_cast<uint32_t>(width),
				static_cast<uint32_t>(height)
			};

			actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
			actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

			return actualExtent;
		}
	}

	VulkanSwapChain::~VulkanSwapChain(){
		for (auto imageView : m_swapChainImageViews) {
			vkDestroyImageView(*m_device->getDevice(), imageView, nullptr);
		}
	}

	void VulkanSwapChain::init()
	{
		SwapChainSupportDetails swapChainSupport = VulkanPhysicalDevice::querySwapChainSupport(m_physicalDevice->GetPhysicalDevice(), *m_surface);

		VkSurfaceFormatKHR surfaceFormat = graphics::VulkanSwapChain::chooseSwapSurfaceFormat(swapChainSupport.formats);

		m_swapChainImageFormat = surfaceFormat.format;

		VkPresentModeKHR presentMode = graphics::VulkanSwapChain::chooseSwapPresentMode(swapChainSupport.presentModes);
		m_swapChainExtent = graphics::VulkanSwapChain::chooseSwapExtent(swapChainSupport.capabilities, m_width, m_height);

		uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
		if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
			imageCount = swapChainSupport.capabilities.maxImageCount;
		}

		QueueFamilyIndices indices = m_physicalDevice->GetQueueFamilyIndices();

		uint32_t queueFamilyIndices[] = {indices.graphics_indices, indices.present_indices };


		VkSwapchainCreateInfoKHR createInfo = initializers::SwapChainCreateInfo(*m_surface, m_physicalDevice->GetPhysicalDevice(), m_swapChainExtent, imageCount, surfaceFormat, queueFamilyIndices, swapChainSupport, presentMode);

		VkDevice vkDevice = *m_device->getDevice();
		VkResult res = vkCreateSwapchainKHR(vkDevice, &createInfo, nullptr, &m_swapChain);
		if (res != VK_SUCCESS) {
			throw std::runtime_error("failed to create swap chain!");
		}

		//Swap chain Images:
		vkGetSwapchainImagesKHR(*m_device->getDevice(), m_swapChain, &imageCount, nullptr);
		m_swapChainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(*m_device->getDevice(), m_swapChain, &imageCount, m_swapChainImages.data());

		// Image views:
		createImageViews();


	}

	void VulkanSwapChain::createImageViews(){
		m_swapChainImageViews.resize(m_swapChainImages.size());
		for (size_t i = 0; i < m_swapChainImages.size(); i++) {
			VkImageViewCreateInfo createInfo = initializers::ImageViewCreateInfo(m_swapChainImages[i], m_swapChainImageFormat);
			if (vkCreateImageView(*m_device->getDevice(), &createInfo, nullptr, &m_swapChainImageViews[i]) != VK_SUCCESS) {
				throw std::runtime_error("failed to create image views!");
			}
		}
	}

} }

