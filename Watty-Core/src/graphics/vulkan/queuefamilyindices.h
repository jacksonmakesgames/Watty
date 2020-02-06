#pragma once
#include <stdint.h>
#include <ext/vulkan/include/vulkan.h>
namespace letc { namespace graphics{
	struct QueueFamilyIndices{
		uint32_t graphics_indices = UINT32_MAX;
		uint32_t present_indices = UINT32_MAX;
		VkBool32 supports_surfaceKHR;
	};


} }