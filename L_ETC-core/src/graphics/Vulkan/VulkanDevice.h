#pragma once
#include <iostream>
#include "vulkaninstance.h"
#include "vulkanphysicaldevice.h"

namespace letc { namespace graphics {
	class VulkanDevice {
	private:
		VulkanInstance* m_instance;
		VkDevice m_device;
		VulkanPhysicalDevice* m_physicalDevice;
		VkQueue m_presentQueue;
		VkQueue m_graphicsQueue;
		VkCommandPool m_graphicsCommandPool;

	public:
		VulkanDevice(VulkanInstance* instance, VulkanPhysicalDevice* physical_device, std::vector<const char*>& layers);
		~VulkanDevice();

		inline VulkanInstance* getInstance() { return m_instance; }
		inline VulkanPhysicalDevice* getPhysicalDevice() { return m_physicalDevice; }
		inline VkQueue* getGraphicsQueue() { return &m_graphicsQueue; }
		inline VkQueue* getPresentQueue() { return &m_presentQueue; }
		inline VkDevice* getDevice() { return &m_device; }
		inline VkCommandPool& getComputeCommndPool() { return m_graphicsCommandPool; }

		void getGraphicsCommandBuffers(std::vector<VkCommandBuffer>& buffers);
		void freeGraphicsCommandPool(VkCommandBuffer* buffers, uint32_t count);


	};


} }