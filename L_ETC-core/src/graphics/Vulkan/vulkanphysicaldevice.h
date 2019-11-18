#pragma once
#include <set>
#include <cstdint>
#include <algorithm>
#include "vulkaninstance.h"
#include "queuefamilyindices.h"
#include "SwapChainSupportDetails.h"


namespace letc { namespace graphics {
	
	const static std::vector<const char*> desiredDeviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	class VulkanPhysicalDevice {

	private:
		VulkanInstance* m_instance;
		VkPhysicalDevice m_device;
		QueueFamilyIndices m_indices;
		VkPhysicalDeviceProperties m_physicalDeviceProperties;
		VkPhysicalDeviceFeatures m_physicalDeviceFeatures;
		VkPhysicalDeviceMemoryProperties m_physicalDeviceMemoryProperties;
	
	public:
		inline VkPhysicalDevice& GetPhysicalDevice() { return m_device; }
		inline QueueFamilyIndices& GetQueueFamilyIndices() { return m_indices; }
		inline VkPhysicalDeviceFeatures& GetPhysicalDeviceFeatures() { return m_physicalDeviceFeatures; }
		inline VkPhysicalDeviceProperties& GetPhysicalDeviceProperties() { return m_physicalDeviceProperties; }
		inline VkPhysicalDeviceMemoryProperties& GetPhysicalDeviceMemoryProperties() { return m_physicalDeviceMemoryProperties; }

		static VulkanPhysicalDevice* GetPhysicalDevice(VulkanInstance* instance, VkSurfaceKHR& surface);
		static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice& device, VkSurfaceKHR& surface);

	public:
		~VulkanPhysicalDevice();



	private:
		VulkanPhysicalDevice(VulkanInstance* instance, VkPhysicalDevice device, QueueFamilyIndices indices);
		static std::vector<VkPhysicalDevice> GetAvailablePhysicalDevices(VulkanInstance* instance);
		static bool PhysicalDeviceSupported(VulkanInstance* instance, VkPhysicalDevice& device, QueueFamilyIndices& queueFamily, VkSurfaceKHR& surface);
		static bool IsDeviceSuitable( VkPhysicalDevice& device, QueueFamilyIndices& queueFamily, VkSurfaceKHR& surface);
		static bool checkDeviceExtensionSupport(VkPhysicalDevice& device);

		
		
	
	};



} }