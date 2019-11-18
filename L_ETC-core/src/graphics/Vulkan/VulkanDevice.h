#pragma once
#include <iostream>
#include "vulkaninstance.h"
#include"vulkanphysicaldevice.h"

namespace letc { namespace graphics {
	class VulkanDevice {
	private:
		VulkanInstance* m_instance;
		VkDevice m_device;
		VulkanPhysicalDevice* m_physicalDevice;
		VkQueue m_computeQueue;
		VkQueue m_graphicsQueue;
		VkCommandPool m_computeCommandPool;

	public:
		VulkanDevice(VulkanInstance* instance, VulkanPhysicalDevice* physical_device);
		~VulkanDevice();

		inline VulkanInstance* getInstance() { return m_instance; }
		inline VulkanPhysicalDevice* getPhysicalDevice() { return m_physicalDevice; }
		inline VkQueue* getQueue() { return &m_computeQueue; }
		inline VkDevice* getDevice() { return &m_device; }
		inline VkCommandPool& getComputeCommndPool() { return m_computeCommandPool; }

		void getComputeCommand(VkCommandBuffer* buffers, uint32_t count);
		void freeComputeCommand(VkCommandBuffer* buffers, uint32_t count);


	};


} }