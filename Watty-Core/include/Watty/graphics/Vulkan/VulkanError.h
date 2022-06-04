#pragma once
#include <iostream>
#include <ext/vulkan/include/vulkan.h>

namespace watty { namespace graphics{

	static bool CheckForVulkanError(VkResult result){
		if (result != VK_SUCCESS) {
			std::cout << "VULKAN ERROR: " << result << std::endl;
			return false;
		}
		return true;
	}



} }