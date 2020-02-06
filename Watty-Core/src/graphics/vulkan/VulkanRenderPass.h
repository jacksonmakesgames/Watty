#pragma once
#include <ext/vulkan/include/vulkan.h>
#include < stdexcept >
#include <vector>

namespace letc { namespace graphics {

	class VulkanRenderPass {
	private:
		VkDevice m_device;
		VkRenderPass m_renderPass;
	public:
		VulkanRenderPass(const VkDevice& device, const VkFormat& swapChainImageFormat);
		VulkanRenderPass() {}

		void startRenderPass(const VkExtent2D & swapChainExtent, const std::vector<VkFramebuffer>& frameBuffers, const std::vector<VkCommandBuffer>& commandBuffers, const VkPipeline & graphicsPipeline);

		inline VkRenderPass& getRenderPass() { return m_renderPass; }

		~VulkanRenderPass();
	};

} }