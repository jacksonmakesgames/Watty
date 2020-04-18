#include <graphics/Vulkan/VulkanDevice.h>
namespace letc { namespace graphics {

	VulkanDevice::VulkanDevice(const VulkanPhysicalDevice& physical_device, const std::vector<const char*>& layers){
		m_physicalDevice = physical_device;
		VkPhysicalDeviceFeatures physicalDeviceFeatures = m_physicalDevice.GetPhysicalDeviceFeatures();
		std::vector<const char*> deviceLayers = layers;

		QueueFamilyIndices indices = m_physicalDevice.GetQueueFamilyIndices();

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos = std::vector<VkDeviceQueueCreateInfo>();
		float priority = 1.0f;
	

		//queueCreateInfos.push_back(initializers::DeviceQueueCreate(indices.present_indices, priority));
		queueCreateInfos.push_back(initializers::DeviceQueueCreate(indices.graphics_indices, priority));

		std::vector<const char*> extensions = desiredDeviceExtensions;

		VkDeviceCreateInfo createInfo = initializers::DeviceCreateInfo(queueCreateInfos, physicalDeviceFeatures, deviceLayers, extensions);
		
		//Logical Device
		if (vkCreateDevice(m_physicalDevice.GetThisPhysicalDevice(), &createInfo, nullptr, &m_device) != VK_SUCCESS) {
			throw std::runtime_error("failed to create logical device!");
		}

		// Device Queues
		vkGetDeviceQueue(m_device, indices.graphics_indices, 0, &m_graphicsQueue);
		//vkGetDeviceQueue(m_device, indices.present_indices, 0, &m_presentQueue);
	
		// Command Pool
		VkCommandPoolCreateInfo computePoolInfo = initializers::CommandPoolCreateInfo(m_physicalDevice.GetQueueFamilyIndices().graphics_indices);

		VkResult result = vkCreateCommandPool(
			m_device,
			&computePoolInfo,
			nullptr,
			&m_graphicsCommandPool
		);

		if (result != VK_SUCCESS) {
			std::cout << "ERROR CREATING COMMAND POOL: " << result << std::endl;
			return;
		}
	}

	VulkanDevice::~VulkanDevice(){
		vkDestroyCommandPool(m_device, m_graphicsCommandPool, nullptr);
		vkDestroyDevice(m_device, nullptr);
	}

	void VulkanDevice::getGraphicsCommandBuffers(std::vector<VkCommandBuffer>& buffers){
		VkCommandBufferAllocateInfo commandBufferAllocateInfo = initializers::CommandBufferAllocateInfo(m_graphicsCommandPool, buffers);

		if (vkAllocateCommandBuffers(m_device, &commandBufferAllocateInfo, buffers.data()) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate command buffers!");
		}

		for (size_t i = 0; i < buffers.size(); i++) {
			VkCommandBufferBeginInfo beginInfo = {};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags = 0; // Optional
			beginInfo.pInheritanceInfo = nullptr; // Optional

			if (vkBeginCommandBuffer(buffers[i], &beginInfo) != VK_SUCCESS) {
				throw std::runtime_error("failed to begin recording command buffer!");
			}
		}

	}

	void VulkanDevice::freeGraphicsCommandPool(VkCommandBuffer* buffers, uint32_t count){
		// not used right now
		vkFreeCommandBuffers(
			m_device,
			m_graphicsCommandPool,
			count,
			buffers
		);
	}

} }
