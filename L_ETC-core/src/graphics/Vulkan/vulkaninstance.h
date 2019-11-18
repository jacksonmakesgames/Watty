#pragma once
#include<iostream>
#include <vulkan/vulkan.h>
#include <vector>
#include"../../initializers.h"
#include "vulkanconfig.h"


namespace letc { namespace graphics {
	class VulkanInstance {
	private:
		VkInstance m_instance;
		std::vector<const char*> m_layers;
		std::vector<const char*> m_extensions;


	public:
		VulkanInstance(VulkanConfig& config, std::vector<const char*> exts);
		~VulkanInstance();
		inline VkInstance& getInstance(){ return m_instance; }
		inline std::vector<const char*>& getLayers(){ return m_layers; }


	private:




	};


} }