#pragma once
#include <stdint.h>

namespace letc { namespace graphics{
	struct QueueFamilyIndices{
		uint32_t graphics_indices = UINT32_MAX;
		uint32_t compute_indices = UINT32_MAX;
		VkBool32 supports_surfaceKHR;
	};


} }