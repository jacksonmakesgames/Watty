#pragma once
#include <ext/vulkan/include/vulkan.h>
#include <utils/file_utils.h>
#include "VulkanDevice.h"
#include <vector>

namespace letc { namespace graphics{
	class VulkanGraphicsPipeline {
	private:
		VkPipeline m_graphicsPipeline;
		VulkanDevice m_device;
		VkPipelineLayout m_pipelineLayout;
	public:
		VulkanGraphicsPipeline(VulkanDevice& device, VkExtent2D& swapChainExtent, VkRenderPass& renderPass);
		VulkanGraphicsPipeline() {}
		
		inline VkPipeline& getPipeline() { return m_graphicsPipeline; }
		inline VkPipelineLayout& getPipelineLayout() { return m_pipelineLayout; }
		
		~VulkanGraphicsPipeline();

	private:
		void createGraphicsPipeline(VkExtent2D& swapChainExtent, VkRenderPass& renderPass);
		VkShaderModule createShaderModule(const std::vector<char>& code);
			
	};


} }