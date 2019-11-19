#include "initializers.h"
namespace letc {namespace initializers {

	VkApplicationInfo ApplicationInfo(graphics::VulkanConfig& config)
	{
		VkApplicationInfo info = {};
		info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		info.apiVersion = config.apiVersion;
		info.applicationVersion = config.applicationVersion;
		info.engineVersion = config.engine_version;
		info.pApplicationName = config.applicationName;
		info.pEngineName = config.engine_name;
		return info;
	}
	VkInstanceCreateInfo InstanceCreateInfo(VkApplicationInfo& appInfo, std::vector<const char*>& layers, std::vector<const char*>& extensions){
		VkInstanceCreateInfo info = {};
		info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		info.pApplicationInfo = &appInfo;

		info.enabledLayerCount = layers.size();
		info.enabledExtensionCount = extensions.size();

		info.ppEnabledLayerNames = layers.data();
		info.ppEnabledExtensionNames = extensions.data();

		return info;
	}
	VkDeviceCreateInfo DeviceCreateInfo(std::vector<VkDeviceQueueCreateInfo>& queueCreateInfos, VkPhysicalDeviceFeatures& features, std::vector<const char*>& layers, std::vector<const char*>& deviceExtensions){
		VkDeviceCreateInfo info = {};
		info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		info.queueCreateInfoCount = static_cast<uint32_t>( queueCreateInfos.size());
		info.pQueueCreateInfos = queueCreateInfos.data();
		info.pEnabledFeatures = &features;
		info.enabledLayerCount = static_cast<uint32_t>(layers.size());
		info.ppEnabledLayerNames = layers.data();
		info.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
		info.ppEnabledExtensionNames = deviceExtensions.data();
		
		return info;

	}

	VkDeviceQueueCreateInfo DeviceQueueCreate(uint32_t queueFamilyIndex, float& priority){
		VkDeviceQueueCreateInfo info = {};
		info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		info.queueFamilyIndex = queueFamilyIndex;
		info.queueCount = 1;
		info.pQueuePriorities = &priority;
		return info;
	}
	VkCommandPoolCreateInfo CommandPoolCreateInfo(uint32_t queueFamilyIndex, VkCommandPoolCreateFlags flags){
		VkCommandPoolCreateInfo info = {};
		info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		info.queueFamilyIndex = queueFamilyIndex;
		info.flags = flags;
		return info;
	}
	VkCommandBufferAllocateInfo CommandBufferAllocateInfo(VkCommandPool pool, std::vector<VkCommandBuffer>& buffers)
	{
		VkCommandBufferAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = pool;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = (uint32_t)buffers.size();
		return allocInfo;
	}

	VkBufferCreateInfo BufferCreateInfo(VkDeviceSize size, VkBufferUsageFlags usage){
		VkBufferCreateInfo info = {};
		info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		info.size = size;
		info.usage = usage;
		return info;
	
	}

	VkMemoryAllocateInfo MemoryAllocateInfo(VkDeviceSize size, uint32_t memoryTypeIndex)
	{
		VkMemoryAllocateInfo info = {};
		info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		info.allocationSize = size;
		info.memoryTypeIndex = memoryTypeIndex;
		return info;
	}

	VkSwapchainCreateInfoKHR SwapChainCreateInfo(VkSurfaceKHR& surface, VkPhysicalDevice& physicalDevice, VkExtent2D extent, uint32_t imageCount, VkSurfaceFormatKHR surfaceFormat, uint32_t queueFamilyIndices[], graphics::SwapChainSupportDetails swapChainSupport, VkPresentModeKHR presentMode)
	{
		VkSwapchainCreateInfoKHR createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = surface;
		createInfo.pNext = nullptr;
		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		if (queueFamilyIndices[0] != queueFamilyIndices[1]) {
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else {
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.queueFamilyIndexCount = 0; // 

			createInfo.pQueueFamilyIndices = nullptr; // Optional
		}
		createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;
		createInfo.oldSwapchain = VK_NULL_HANDLE;

		return createInfo;

	}
	
	VkImageViewCreateInfo ImageViewCreateInfo(VkImage swapChainImage, VkFormat swapChainImageFormat)
	{
		VkImageViewCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = swapChainImage;

		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = swapChainImageFormat;

		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;
		return createInfo;
	}
	VkShaderModuleCreateInfo ShaderCreateInfo(const std::vector<char>& code)
	{
		VkShaderModuleCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = code.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());
		return createInfo;
	}

	VkPipelineShaderStageCreateInfo ShaderStageCreateInfo(VkShaderModule module, VkShaderStageFlagBits stage){
		VkPipelineShaderStageCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		createInfo.stage = stage;
		createInfo.module = module;
		createInfo.pName = "main";
		return createInfo;
		
	}

	VkPipelineVertexInputStateCreateInfo PipelineVertexInputStateCreateInfo()
	{

		VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputInfo.vertexBindingDescriptionCount = 0;
		vertexInputInfo.pVertexBindingDescriptions = nullptr; // Optional
		vertexInputInfo.vertexAttributeDescriptionCount = 0;
		vertexInputInfo.pVertexAttributeDescriptions = nullptr; // Optional

		return vertexInputInfo;

	}

	VkPipelineInputAssemblyStateCreateInfo PipelineInputAssemblyStateCreateInfo()
	{
		VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
		inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		inputAssembly.primitiveRestartEnable = VK_FALSE;
		return inputAssembly;
	}

	VkPipelineViewportStateCreateInfo PipelineViewportStateCreateInfo(VkViewport* viewport, VkRect2D* scissor) {
		VkPipelineViewportStateCreateInfo viewportState = {};
		viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportState.viewportCount = 1;
		viewportState.pViewports = viewport;
		viewportState.scissorCount = 1;
		viewportState.pScissors = scissor;
		return viewportState;
	}


}}