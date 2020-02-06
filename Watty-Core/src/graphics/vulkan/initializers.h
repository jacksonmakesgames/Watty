#pragma once
#include <vector>
#include <ext/vulkan/include/vulkan.h>
#include "vulkanconfig.h"
#include "SwapChainSupportDetails.h"


namespace letc { namespace initializers {

	VkApplicationInfo ApplicationInfo(const graphics::VulkanConfig& config);
	VkInstanceCreateInfo InstanceCreateInfo(const VkApplicationInfo& appInfo, const std::vector<const char*>& layers, const std::vector<const char*>& extensions);
	
	VkDeviceCreateInfo DeviceCreateInfo(std::vector<VkDeviceQueueCreateInfo>& queueCreateInfos, VkPhysicalDeviceFeatures& features, std::vector<const char*>& layers, std::vector<const char*>& deviceExtensions);
	
	VkDeviceQueueCreateInfo DeviceQueueCreate(const uint32_t queueFamilyIndex, const float & priority);

	VkCommandPoolCreateInfo CommandPoolCreateInfo(uint32_t queueFamilyIndex, VkCommandPoolCreateFlags flags = 0);

	VkCommandBufferAllocateInfo CommandBufferAllocateInfo(VkCommandPool pool, const std::vector<VkCommandBuffer>& buffers);
	VkBufferCreateInfo BufferCreateInfo(VkDeviceSize size,  VkBufferUsageFlags usage);

	VkMemoryAllocateInfo MemoryAllocateInfo(VkDeviceSize size,  uint32_t memoryTypeIndex);

	VkSwapchainCreateInfoKHR SwapChainCreateInfo(const VkSurfaceKHR& surface, const VkPhysicalDevice& physicalDevice, const VkExtent2D& extent, uint32_t imageCount, const VkSurfaceFormatKHR& surfaceFormat, uint32_t queueFamilyIndices[], const graphics::SwapChainSupportDetails& swapChainSupport, const VkPresentModeKHR& presentMode);
	VkImageViewCreateInfo ImageViewCreateInfo(const VkImage& swapChainImage, const VkFormat& swapChainImageFormat);
	
	VkShaderModuleCreateInfo ShaderCreateInfo(const std::vector<char>& code);

	VkPipelineShaderStageCreateInfo ShaderStageCreateInfo(VkShaderModule module, VkShaderStageFlagBits stage);
	VkPipelineVertexInputStateCreateInfo PipelineVertexInputStateCreateInfo();
	VkPipelineInputAssemblyStateCreateInfo PipelineInputAssemblyStateCreateInfo();

	VkPipelineViewportStateCreateInfo PipelineViewportStateCreateInfo(const VkViewport* viewport, const VkRect2D* scissor);

} }