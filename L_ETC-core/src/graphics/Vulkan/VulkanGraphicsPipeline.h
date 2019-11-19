#pragma once
#include <vulkan/vulkan.h>
#include "../../utils/file_utils.h"
#include "VulkanDevice.h"
#include <vector>

namespace letc { namespace graphics{
	class VulkanGraphicsPipeline {
	private:
		VulkanDevice* m_device;
	public:
		VulkanGraphicsPipeline(VulkanDevice* device);
		

		
		~VulkanGraphicsPipeline();

	private:
		void createGraphicsPipeline();
		VkShaderModule createShaderModule(const std::vector<char>& code);
			
	};


} }