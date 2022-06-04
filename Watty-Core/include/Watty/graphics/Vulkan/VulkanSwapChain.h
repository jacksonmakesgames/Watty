#pragma once
#include <ext/vulkan/include/vulkan.h>
#include <vector>
#include "vulkanphysicaldevice.h"
#include "vulkandevice.h"
#include "initializers.h"

namespace watty { namespace graphics {
	class VulkanSwapChain {
	private:
		VkSwapchainKHR m_swapChain;

		std::vector<VkImage> m_swapChainImages;
		std::vector<VkImageView> m_swapChainImageViews;

		VulkanDevice m_device;
		VkSurfaceKHR m_surface;
		SwapChainSupportDetails m_supportDetails;

		VkFormat m_swapChainImageFormat;
		VkExtent2D m_swapChainExtent;
		float m_width;
		float m_height;

	public:
		VulkanSwapChain(const VulkanDevice & device, const VkSurfaceKHR & surface, const VulkanPhysicalDevice& physicalDevice, float width, float height);
		VulkanSwapChain() {}
		

		inline VkSwapchainKHR& getSwapChain() { return m_swapChain; }
		inline VkExtent2D& getSwapChainExtent() { return m_swapChainExtent; }
		inline VkFormat& getSwapChainImageFormatExtent() { return m_swapChainImageFormat; }
		inline std::vector<VkImage>& getSwapChainImages(){ return m_swapChainImages; }
		const inline std::vector<VkImageView>& getSwapChainImageViews() { return m_swapChainImageViews; }

		static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, float width, float height);



		
		~VulkanSwapChain();
	private:
		void init(const VkPhysicalDevice& physicalDevice, QueueFamilyIndices indices);
		void createImageViews();
	};


} }