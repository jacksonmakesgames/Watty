#pragma once
#include <ext/vulkan/include/vulkan.h>
#include <vector>
#include < stdexcept >


namespace letc { namespace graphics{

	class VulkanFrameBuffer {
	private:
		std::vector<VkFramebuffer> m_swapChainFramebuffers;
		VkDevice m_device;
	public:
		VulkanFrameBuffer(const VkDevice& device, const std::vector<VkImageView>& swapChainImageViews, const VkRenderPass& renderPass, const VkExtent2D& swapChainExtent);
		VulkanFrameBuffer() {}

		inline std::vector<VkFramebuffer>& getswapChainFramebuffers() { return m_swapChainFramebuffers; }

		~VulkanFrameBuffer();
	private:



	};

} }