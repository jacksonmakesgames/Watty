#include <graphics/Vulkan/vulkanphysicaldevice.h>
namespace letc {namespace graphics {

	VulkanPhysicalDevice::VulkanPhysicalDevice(VkInstance& instance, const VkSurfaceKHR& surface){
		

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
					m_physicalDevice = device;
					m_indices = queueFamily;
				}
				else {
					secondaryDevice = device;
					secondaryQueue = queueFamily;
				}
			}
		}
		if (secondaryDevice == VK_NULL_HANDLE)
			return;
		else if(m_physicalDevice == VK_NULL_HANDLE){
			m_physicalDevice = secondaryDevice;
			m_indices = secondaryQueue;

		}
		// we never found a suitable device, todo log error
		if (m_physicalDevice == VK_NULL_HANDLE) 
			return;
		
		vkGetPhysicalDeviceProperties(
			m_physicalDevice,
			&m_physicalDeviceProperties
		);
		vkGetPhysicalDeviceMemoryProperties(
			m_physicalDevice,
			&m_physicalDeviceMemoryProperties
		);
		vkGetPhysicalDeviceFeatures(
			m_physicalDevice,
			&m_physicalDeviceFeatures
		);


	}

	std::vector<VkPhysicalDevice> VulkanPhysicalDevice::GetAvailablePhysicalDevices(VkInstance& instance)
	{
		uint32_t deviceCount = 0;

		vkEnumeratePhysicalDevices(
			instance,
			&deviceCount,
			nullptr
		);

		std::vector<VkPhysicalDevice> devices(deviceCount);

		vkEnumeratePhysicalDevices(
			instance,
			&deviceCount,
			devices.data()
		);


		return devices;
	}

	bool VulkanPhysicalDevice::PhysicalDeviceSupported(const VkInstance& instance, const VkPhysicalDevice& device, QueueFamilyIndices& queueFamily, const VkSurfaceKHR& surface){
		bool deviceSupported = IsDeviceSuitable(device, queueFamily, surface);

		bool extensionsSupported = checkDeviceExtensionSupport(device);
		bool swapChainAdequate = false;
		if (extensionsSupported) {
			SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device, surface);
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
		}
		return deviceSupported && extensionsSupported && swapChainAdequate;
	}

	bool VulkanPhysicalDevice::checkDeviceExtensionSupport(const VkPhysicalDevice& device) {
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


	bool VulkanPhysicalDevice::IsDeviceSuitable(const VkPhysicalDevice& device, QueueFamilyIndices& familyIndices, const VkSurfaceKHR& surface){
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
					familyIndices.present_indices = i;
				vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &familyIndices.supports_surfaceKHR);

			}
			if (familyIndices.graphics_indices < UINT32_MAX && familyIndices.present_indices < UINT32_MAX && familyIndices.supports_surfaceKHR == VK_TRUE)
				return true;
			i++;
		}
		return false;
	}



	VulkanPhysicalDevice::~VulkanPhysicalDevice() {
	
	}

	SwapChainSupportDetails VulkanPhysicalDevice::querySwapChainSupport(const VkPhysicalDevice& device, const VkSurfaceKHR& surface){
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

}}