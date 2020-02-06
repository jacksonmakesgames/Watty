#pragma once
#include <iostream>
#include <ext/vulkan/include/vulkan.h>
#include "initializers.h"
#include "VulkanPhysicalDevice.h"

namespace letc { namespace graphics {
	class VulkanDevice {
	private:
		VkDevice m_device;
		VulkanPhysicalDevice m_physicalDevice;
		VkQueue m_presentQueue;
		VkQueue m_graphicsQueue;
		VkCommandPool m_graphicsCommandPool;

	public:
		VulkanDevice(const VulkanPhysicalDevice& physical_device, const std::vector<const char*>& layers);
		VulkanDevice() {}

		inline const VulkanPhysicalDevice& getPhysicalDevice() const{ return m_physicalDevice; }
		inline const VkQueue& getGraphicsQueue() { return m_graphicsQueue; }
		inline const VkQueue& getPresentQueue() { return m_presentQueue; }
		inline const VkDevice& getDevice() { return m_device; }
		inline const VkCommandPool& getCommandPool() { return m_graphicsCommandPool; }

		void getGraphicsCommandBuffers(std::vector<VkCommandBuffer>& buffers);
		void freeGraphicsCommandPool(VkCommandBuffer* buffers, uint32_t count);

		~VulkanDevice();

	};


} }