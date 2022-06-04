#pragma once
#include <set>
#include <string>
#include <cstdint>
#include <algorithm>
#include "queuefamilyindices.h"
#include "SwapChainSupportDetails.h"


namespace watty { namespace graphics {
	
	const static std::vector<const char*> desiredDeviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	class VulkanPhysicalDevice {

	private:
		VkPhysicalDevice m_physicalDevice;
		QueueFamilyIndices m_indices;
		VkPhysicalDeviceProperties m_physicalDeviceProperties;
		VkPhysicalDeviceFeatures m_physicalDeviceFeatures;
		VkPhysicalDeviceMemoryProperties m_physicalDeviceMemoryProperties;
	
	public:
		VulkanPhysicalDevice(VkInstance& instance, const VkSurfaceKHR& surface);
		VulkanPhysicalDevice() {}

		inline const VkPhysicalDevice& GetThisPhysicalDevice()const { return m_physicalDevice; }

		inline const QueueFamilyIndices& GetQueueFamilyIndices() const { return m_indices; }
		inline const VkPhysicalDeviceFeatures& GetPhysicalDeviceFeatures() { return m_physicalDeviceFeatures; }
		inline const VkPhysicalDeviceProperties& GetPhysicalDeviceProperties() { return m_physicalDeviceProperties; }
		inline const VkPhysicalDeviceMemoryProperties& GetPhysicalDeviceMemoryProperties() const { return m_physicalDeviceMemoryProperties; }

		static SwapChainSupportDetails querySwapChainSupport(const VkPhysicalDevice& device, const VkSurfaceKHR& surface);

		~VulkanPhysicalDevice();
	public:
	private:
		static std::vector<VkPhysicalDevice> GetAvailablePhysicalDevices(VkInstance& instance);
		static bool PhysicalDeviceSupported(const VkInstance& instance, const VkPhysicalDevice& device, QueueFamilyIndices& queueFamily,const VkSurfaceKHR& surface);
		static bool IsDeviceSuitable(const VkPhysicalDevice& device, QueueFamilyIndices& familyIndices, const VkSurfaceKHR& surface);
		static bool checkDeviceExtensionSupport(const VkPhysicalDevice& device);
	
	};



} }