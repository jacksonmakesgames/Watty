#pragma once
#include <iostream>
#include <vulkan/vulkan.h>

namespace letc { namespace graphics{

	static bool CheckForVulkanError(VkResult result){
		if (result != VK_SUCCESS) {
			std::cout << "VULKAN ERROR: " << result << std::endl;
			return false;
		}
		return true;
	}



} }