#include "VulkanGraphicsPipeline.h"
namespace letc { namespace graphics {
	VulkanGraphicsPipeline::VulkanGraphicsPipeline(VulkanDevice* device){
		m_device = device;
		createGraphicsPipeline();
	}
	void VulkanGraphicsPipeline::createGraphicsPipeline()
	{
		auto vertShaderCode = read_shader_file("J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/src/shaders/vert.spv");
		auto fragShaderCode = read_shader_file("J:/OneDrive/Projects/Game_Development/L_ETC/L_ETC-core/src/shaders/frag.spv");
		VkShaderModule vertShaderModule = createShaderModule(vertShaderCode);
		VkShaderModule fragShaderModule = createShaderModule(fragShaderCode);

		VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
		vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
		vertShaderStageInfo.module = vertShaderModule;
		vertShaderStageInfo.pName = "main";

		VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
		fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		fragShaderStageInfo.module = fragShaderModule;
		fragShaderStageInfo.pName = "main";


		VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

		vkDestroyShaderModule(*m_device->getDevice(), fragShaderModule, nullptr);
		vkDestroyShaderModule(*m_device->getDevice(), vertShaderModule, nullptr);
	}

	VkShaderModule VulkanGraphicsPipeline::createShaderModule(const std::vector<char>& code) {
		
		VkShaderModuleCreateInfo createInfo = initializers::ShaderCreateInfo(code);


		VkShaderModule shaderModule;

		if (vkCreateShaderModule(*m_device->getDevice(), &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
			throw std::runtime_error("failed to create shader module!");
		}

		return shaderModule;
	}

	VulkanGraphicsPipeline::~VulkanGraphicsPipeline(){
	
	}

} }

