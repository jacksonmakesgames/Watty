#pragma once
#include <vulkan.h>

namespace letc { namespace graphics{


	struct VulkanConfig {
		const char* applicationName = "Watty";
		uint32_t applicationVersion = VK_MAKE_VERSION(0,0,0);
		const char* engine_name = "The Little Engine that Could";
		const uint32_t engine_version = VK_MAKE_VERSION(0,0,0);
		const uint32_t apiVersion = VK_MAKE_VERSION(1, 1, 126);
	
	};

} }