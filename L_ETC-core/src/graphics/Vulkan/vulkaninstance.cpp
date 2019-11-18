#include "vulkaninstance.h"

namespace letc {namespace graphics {
	VulkanInstance::VulkanInstance(VulkanConfig& config, std::vector<const char*> exts) {

		m_layers.push_back("VK_LAYER_LUNARG_standard_validation");
		m_extensions.push_back("VK_EXT_debug_report");

		for (size_t i = 0; i < exts.size(); i++)
		{
			m_extensions.push_back(exts[i]);
		}

		VkApplicationInfo appInfo = initializers::ApplicationInfo(config);
		VkInstanceCreateInfo instanceInfo = initializers::InstanceCreateInfo(appInfo, m_layers, m_extensions);


		VkResult result = vkCreateInstance(&instanceInfo, nullptr, &m_instance);

		if (result != VK_SUCCESS) {
			std::cout << "FAILED TO INIT VULKAN WITH ERROR: " << result << std::endl;
			return;
		}

	}
	VulkanInstance::~VulkanInstance(){
		vkDestroyInstance(m_instance, nullptr);
	}
	
}}