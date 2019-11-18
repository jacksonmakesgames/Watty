#include "vulkanphysicaldevice.h"
namespace letc {namespace graphics {

	VulkanPhysicalDevice::VulkanPhysicalDevice(VulkanInstance* instance, VkPhysicalDevice device, QueueFamilyIndices indices){
		m_instance = instance;
		m_device = device;
		m_indices = indices;
		
		
		vkGetPhysicalDeviceProperties(
			m_device,
			&m_physicalDeviceProperties
		);
		vkGetPhysicalDeviceMemoryProperties(
			m_device,
			&m_physicalDeviceMemoryProperties
		);
		vkGetPhysicalDeviceFeatures(
			m_device,
			&m_physicalDeviceFeatures
		);
	}

	std::vector<VkPhysicalDevice> VulkanPhysicalDevice::GetAvailablePhysicalDevices(VulkanInstance* instance)
	{
		uint32_t deviceCount = 0;

		vkEnumeratePhysicalDevices(
			instance->getInstance(),
			&deviceCount,
			nullptr
		);

		std::vector<VkPhysicalDevice> devices(deviceCount);

		vkEnumeratePhysicalDevices(
			instance->getInstance(),
			&deviceCount,
			devices.data()
		);


		return devices;
	}

	bool VulkanPhysicalDevice::PhysicalDeviceSupported(VulkanInstance* instance, VkPhysicalDevice& device, QueueFamilyIndices& queueFamily, VkSurfaceKHR& surface){
		bool deviceSupported = IsDeviceSuitable(device, queueFamily, surface);

		bool extensionsSupported = checkDeviceExtensionSupport(device);
		bool swapChainAdequate = false;
		if (extensionsSupported) {
			SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device, surface);
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
		}
		return deviceSupported && extensionsSupported && swapChainAdequate;
	}

	bool VulkanPhysicalDevice::checkDeviceExtensionSupport(VkPhysicalDevice& device) {
		uint32_t extensionCount;

		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());
		std::set<std::string> requiredExtensions(desiredDeviceExtensions.begin(), desiredDeviceExtensions.end());

		for (const auto& extension : availableExtensions) {
			requiredExtensions.erase(extension.extensionName);
		}
		return requiredExtensions.empty();
	}


	bool VulkanPhysicalDevice::IsDeviceSuitable(VkPhysicalDevice& device, QueueFamilyIndices& familyIndices, VkSurfaceKHR& surface){
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(
			device,
			&queueFamilyCount,
			nullptr
		);
		
		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);

		vkGetPhysicalDeviceQueueFamilyProperties(
			device,
			&queueFamilyCount,
			queueFamilies.data()
		);
	
		uint32_t i = 0;
		for(auto&queueFamily: queueFamilies){
			VkBool32  presentSupport;
			if (queueFamily.queueCount > 0) {
				if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
					familyIndices.graphics_indices = i;
				if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
					familyIndices.compute_indices = i;
				vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &familyIndices.supports_surfaceKHR);

			}
			if (familyIndices.graphics_indices < UINT32_MAX && familyIndices.compute_indices < UINT32_MAX && familyIndices.supports_surfaceKHR == VK_TRUE)
				return true;
			i++;
		}
		return false;
	}

	VulkanPhysicalDevice* VulkanPhysicalDevice::GetPhysicalDevice(VulkanInstance* instance, VkSurfaceKHR& surface){
		std::vector<VkPhysicalDevice> devices = GetAvailablePhysicalDevices(instance); 

		VkPhysicalDevice secondaryDevice = VK_NULL_HANDLE;
		QueueFamilyIndices secondaryQueue; 
		for (auto& device : devices) {
			QueueFamilyIndices queueFamily;
			if (PhysicalDeviceSupported(instance, device, queueFamily, surface)) {
				VkPhysicalDeviceProperties physicalDeviceProperties;
				vkGetPhysicalDeviceProperties(
					device,
					&physicalDeviceProperties
				);
				if (physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
					return new VulkanPhysicalDevice(instance, device,  queueFamily);

				}
				else {
					secondaryDevice = device;
					secondaryQueue = queueFamily;
				}
			}
		}
		if (secondaryDevice == VK_NULL_HANDLE)
			return nullptr;
		else {
			return new VulkanPhysicalDevice(instance, secondaryDevice, secondaryQueue);

		}

		return nullptr;
	}

	SwapChainSupportDetails VulkanPhysicalDevice::querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR& surface) {
		SwapChainSupportDetails details;

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

		if (formatCount != 0) {
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
		}

		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

		if (presentModeCount != 0) {
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
		}

		return details;
	}

	VkSurfaceFormatKHR VulkanPhysicalDevice::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
		for (const auto& availableFormat : availableFormats) {
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
				return availableFormat;
			}
		}

		return availableFormats[0];
	}

	VkPresentModeKHR VulkanPhysicalDevice::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) {
		for (const auto& availablePresentMode : availablePresentModes) {
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
				return availablePresentMode;
			}
		}

		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D VulkanPhysicalDevice::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
		if (capabilities.currentExtent.width != UINT32_MAX) {
			return capabilities.currentExtent;
		}
		else {
			//VkExtent2D actualExtent = { WIDTH, HEIGHT };
			VkExtent2D actualExtent = { 1600, 900 };

			actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
			actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

			return actualExtent;
		}
	}


	VulkanPhysicalDevice::~VulkanPhysicalDevice() {
	
	}


}}