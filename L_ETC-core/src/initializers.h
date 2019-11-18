#pragma once
#include <vector>
#include <vulkan/vulkan.h>
#include "graphics/Vulkan/vulkanconfig.h"
#include "graphics/Vulkan/SwapChainSupportDetails.h"


namespace letc { namespace initializers {

	VkApplicationInfo ApplicationInfo(graphics::VulkanConfig& config);
	VkInstanceCreateInfo InstanceCreateInfo(VkApplicationInfo& appInfo, std::vector<const char*>& layers, std::vector<const char*>& extensions);
	
	VkDeviceCreateInfo DeviceCreateInfo(std::vector<VkDeviceQueueCreateInfo>& queueCreateInfos, VkPhysicalDeviceFeatures& features, std::vector<const char*>& layers, std::vector<const char*>& deviceExtensions);
	
	VkDeviceQueueCreateInfo DeviceQueueCreate(uint32_t queueFamilyIndex, float& priority);

	VkCommandPoolCreateInfo CommandPoolCreateInfo(uint32_t queueFamilyIndex, VkCommandPoolCreateFlags flags = 0);

	VkCommandBufferAllocateInfo CommandBufferAllocateInfo(VkCommandPool pool, uint32_t count);
	VkBufferCreateInfo BufferCreateInfo(VkDeviceSize size,  VkBufferUsageFlags usage);

	VkMemoryAllocateInfo MemoryAllocateInfo(VkDeviceSize size,  uint32_t memoryTypeIndex);

	VkSwapchainCreateInfoKHR SwapChainCreateInfo(VkSurfaceKHR& surface, VkPhysicalDevice& physicalDevice, VkExtent2D extent, uint32_t imageCount, VkSurfaceFormatKHR surfaceFormat, uint32_t queueFamilyIndices[], graphics::SwapChainSupportDetails swapChainSupport, VkPresentModeKHR presentMode);
	VkImageViewCreateInfo ImageViewCreateInfo(VkImage swapChainImage, VkFormat swapChainImageFormat);

} }