#pragma once
#include <vulkan/vulkan.h>
#include <vector>

namespace letc { namespace graphics{

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;

		
	};

} }