#include "VulkanDevice.h"
namespace letc { namespace graphics {

	VulkanDevice::VulkanDevice(VulkanInstance* instance, VulkanPhysicalDevice* physical_device){
		m_instance = instance;
		m_physicalDevice = physical_device;

		QueueFamilyIndices indices = m_physicalDevice->GetQueueFamilyIndices();

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos = std::vector<VkDeviceQueueCreateInfo>();
		float priority = 1.0f;

		//queueCreateInfos.push_back(initializers::DeviceQueueCreate(indices.compute_indices, priority));
		queueCreateInfos.push_back(initializers::DeviceQueueCreate(indices.graphics_indices, priority));

		VkDeviceCreateInfo createInfo = initializers::DeviceCreateInfo(queueCreateInfos, m_physicalDevice->GetPhysicalDeviceFeatures());
		
		//TODO error checking
		
		VkResult result;
		result = vkCreateDevice(
			m_physicalDevice->GetPhysicalDevice(),
			&createInfo,
			nullptr,
			&m_device
		);
		if (result != VK_SUCCESS) {
			std::cout << "ERROR CREATING DEVICE: " << result << std::endl;
			return;
		}

		//vkGetDeviceQueue(
		//	m_device,
		//	indices.compute_indices,
		//	0,
		//	&m_computeQueue
		//);
		
		vkGetDeviceQueue(
			m_device,
			indices.graphics_indices,
			0,
			&m_graphicsQueue
		);
	
		VkCommandPoolCreateInfo computePoolInfo = initializers::CommandPoolCreateInfo(m_physicalDevice->GetQueueFamilyIndices().compute_indices);

		result = vkCreateCommandPool(
			m_device,
			&computePoolInfo,
			nullptr,
			&m_computeCommandPool
		);

		if (result != VK_SUCCESS) {
			std::cout << "ERROR CREATING COMMAND POOL: " << result << std::endl;
			return;
		}
	}

	VulkanDevice::~VulkanDevice(){
		vkDestroyCommandPool(m_device, m_computeCommandPool, nullptr);
		vkDestroyDevice(m_device, nullptr);
	}

	void VulkanDevice::getComputeCommand(VkCommandBuffer* buffers, uint32_t count){
		VkCommandBufferAllocateInfo commandBufferAllocateInfo = initializers::CommandBufferAllocateInfo(m_computeCommandPool, count);

		VkResult result = vkAllocateCommandBuffers(
			m_device,
			&commandBufferAllocateInfo,
			buffers
		);
		if (result != VK_SUCCESS) {
			std::cout << "ERROR GETTING COMPUTE COMMAND " << result << std::endl;
			return;
		}
	}

	void VulkanDevice::freeComputeCommand(VkCommandBuffer* buffers, uint32_t count){
		vkFreeCommandBuffers(
			m_device,
			m_computeCommandPool,
			count,
			buffers
		);
	}

} }
