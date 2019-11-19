#pragma once
#include <vulkan/vulkan.h>
#include < stdexcept >
#include <vector>

namespace letc { namespace graphics {

	class VulkanRenderPass {
	private:
		VkDevice* m_device;
		VkRenderPass m_renderPass;
	public:
		VulkanRenderPass(VkDevice* device, VkFormat swapChainImageFormat);

		void startRenderPass(VkExtent2D swapChainExtent, std::vector<VkFramebuffer>& frameBuffers, std::vector<VkCommandBuffer>& commandBuffers, VkPipeline& graphicsPipeline);

		inline VkRenderPass* getRenderPass() { return &m_renderPass; }

		~VulkanRenderPass();
	};

} }