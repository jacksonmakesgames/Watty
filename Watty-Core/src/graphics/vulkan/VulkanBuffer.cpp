#include <graphics/Vulkan/VulkanBuffer.h>
namespace letc {namespace graphics {
	
	VulkanBuffer::VulkanBuffer(const VulkanDevice& device, void* ptr, unsigned int elementSize, unsigned int count)
	{
		m_device = device;
		m_ptr = ptr;
		m_elementSize = elementSize;
		m_count = count;
		m_totalSize = m_elementSize * m_count;
		CreateBuffer();
	}

	void VulkanBuffer::CreateBuffer(){
		VkBufferCreateInfo bufferInfo = initializers::BufferCreateInfo(m_totalSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);

		CheckForVulkanError(vkCreateBuffer(
			m_device.getDevice(),
			&bufferInfo,
			nullptr,
			&m_buffer));

		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(
			m_device.getDevice(),
			m_buffer,
			&memRequirements
		);

		VkMemoryAllocateInfo allocInfo = initializers::MemoryAllocateInfo(memRequirements.size, FindMemoryType(
																								VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
																								memRequirements.memoryTypeBits));
		CheckForVulkanError(vkAllocateMemory(
			m_device.getDevice(),
			&allocInfo,
			nullptr,
			&m_deviceMemory
		));

		CheckForVulkanError(vkBindBufferMemory(
			m_device.getDevice(),
			m_buffer,
			m_deviceMemory,
			0
		));

		vkMapMemory(
			m_device.getDevice(),
			m_deviceMemory,
			0,
			memRequirements.size,
			0,
			&m_mappedMemory

		);

	}

	uint32_t VulkanBuffer::FindMemoryType(VkMemoryPropertyFlags props, uint32_t type_filter){

		for (uint32_t i = 0; i < m_device.getPhysicalDevice().GetPhysicalDeviceMemoryProperties().memoryTypeCount; i++){
			if ((type_filter & (1 << i)) && (m_device.getPhysicalDevice().GetPhysicalDeviceMemoryProperties().memoryTypes[i].propertyFlags & props) == props) {
				return i;
			}

		}
		assert(0 && "No Available Memory Props");
		return -1;
	}

	void VulkanBuffer::setData(){
		memcpy(m_mappedMemory, m_ptr, (unsigned int) m_totalSize);
	}
	
	void VulkanBuffer::setData(unsigned int count){
		memcpy(m_mappedMemory, m_ptr, (unsigned int) m_elementSize * count);
	}

	void VulkanBuffer::setData(unsigned int startIndex, unsigned int count){
		memcpy(
			((char*) m_mappedMemory) + (startIndex * m_elementSize), 
			((char*) m_ptr) + (startIndex * m_elementSize),
			(unsigned int) m_totalSize
		);
	}

	VulkanBuffer::~VulkanBuffer(){
		vkUnmapMemory(
			m_device.getDevice(),
			m_deviceMemory	
		);

		vkDestroyBuffer(
			m_device.getDevice(),
			m_buffer,
			nullptr
		);

		vkFreeMemory(
			m_device.getDevice(),
			m_deviceMemory,
			nullptr
		);
	
	}
}}