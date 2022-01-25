#pragma once
#include <assert.h>
#include <vector>
#include "initializers.h"
#include <ext/vulkan/include/vulkan.h>
#include "VulkanDevice.h"
#include"VulkanError.h"


namespace watty { namespace graphics {

	class VulkanBuffer {
	private:
		VulkanDevice m_device;
		void* m_ptr;
		void* m_mappedMemory;
		unsigned int m_elementSize;
		unsigned int m_count = 1;
		VkDeviceSize m_totalSize;
		VkBuffer m_buffer;


		VkDeviceMemory m_deviceMemory;

	public:
		VulkanBuffer(const VulkanDevice& device, void* ptr, unsigned int elementSize, unsigned int count = 1);

		void CreateBuffer();
		uint32_t FindMemoryType(VkMemoryPropertyFlags props, uint32_t type_filter);
		virtual void setData();
		virtual void setData(unsigned int count);
		virtual void setData(unsigned int startIndex, unsigned int count);
		
		~VulkanBuffer();



	};



} }