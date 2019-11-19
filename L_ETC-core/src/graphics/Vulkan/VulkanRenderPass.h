#pragma once
#include <vulkan/vulkan.h>
#include < stdexcept >

namespace letc { namespace graphics {

	class VulkanRenderPass {
	private:
		VkDevice* m_device;
		VkRenderPass m_renderPass;
	public:
		VulkanRenderPass(VkDevice* device, VkFormat swapChainImageFormat);

		inline VkRenderPass* getRenderPass() { return &m_renderPass; }

		~VulkanRenderPass();
	};

} }