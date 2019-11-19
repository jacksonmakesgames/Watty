#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include < stdexcept >


namespace letc { namespace graphics{

	class VulkanFrameBuffer {
	private:
		std::vector<VkFramebuffer> m_swapChainFramebuffers;
		VkDevice* m_device;
	public:
		VulkanFrameBuffer(VkDevice* device, std::vector<VkImageView>* swapChainImageViews, VkRenderPass* renderPass, VkExtent2D* swapChainExtent);



		~VulkanFrameBuffer();
	private:



	};

} }