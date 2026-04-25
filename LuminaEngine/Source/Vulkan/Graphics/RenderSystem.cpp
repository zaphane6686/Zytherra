#include <Vulkan/Graphics/RenderSystem.h>
#include <vector>
#include <stdexcept>

lumina::RenderSystem::RenderSystem(const RenderSystemDesc& desc) : Base(desc.base), m_vkInstance(VK_NULL_HANDLE), m_logicalDevice(VK_NULL_HANDLE)
{
	try
	{
		initializeInstance();
		selectPhysicalDevice();
		createLogicalDevice();
	}
	catch (const std::exception& e)
	{
		getLogger().log(Logger::LogLevel::Error, e.what());
		cleanup();
		throw;
	}
}

void lumina::RenderSystem::initializeInstance()
{
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Zytherra";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "LuminaEngine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

	VkInstanceCreateInfo instanceCreateInfo{};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.pApplicationInfo = &appInfo;
	instanceCreateInfo.enabledLayerCount = validationLayers.size();
	instanceCreateInfo.ppEnabledLayerNames = validationLayers.data();

	VkResult result = vkCreateInstance(&instanceCreateInfo, nullptr, &m_vkInstance);
	if (result != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create Vulkan instance.");
	}
}

void lumina::RenderSystem::selectPhysicalDevice()
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(m_vkInstance, &deviceCount, nullptr);

	if (deviceCount == 0)
	{
		throw std::runtime_error("No Vulkan-capable devices found.");
	}

	std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
	vkEnumeratePhysicalDevices(m_vkInstance, &deviceCount, physicalDevices.data());

	VkPhysicalDevice fallbackDevice = VK_NULL_HANDLE;
	for (VkPhysicalDevice device : physicalDevices)
	{
		VkPhysicalDeviceProperties deviceProperties;
		vkGetPhysicalDeviceProperties(device, &deviceProperties);

		if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		{
			bestDevice = device;
			return;
		}

		if (fallbackDevice == VK_NULL_HANDLE)
		{
			fallbackDevice = device;
		}
	}
	if (fallbackDevice != VK_NULL_HANDLE)
	{
		bestDevice = fallbackDevice;
		getLogger().log(Logger::LogLevel::Warning, "No discrete GPU found. Using integrated GPU.");
		return;
	}

	throw std::runtime_error("No suitable physical device found.");
}

void lumina::RenderSystem::createLogicalDevice()
{
	vkGetPhysicalDeviceQueueFamilyProperties(bestDevice, &queueFamilyCount, nullptr);
	if (queueFamilyCount == 0)
	{
		throw std::runtime_error("No queue families found on physical device.");
	}
	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(bestDevice, &queueFamilyCount, queueFamilies.data());

	graphicsFamily = -1;
	for (uint32_t i = 0; i < queueFamilies.size(); i++)
	{
		if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			graphicsFamily = i;
			break;
		}
	}

	if (graphicsFamily == -1)
	{
		throw std::runtime_error("No graphics queue family found.");
	}

	VkDeviceQueueCreateInfo deviceQueueCreateInfo{};
	deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	deviceQueueCreateInfo.queueFamilyIndex = graphicsFamily;
	deviceQueueCreateInfo.queueCount = 1;
	deviceQueueCreateInfo.pQueuePriorities = &queuePriority;

	VkDeviceCreateInfo deviceCreateInfo{};
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.queueCreateInfoCount = 1;
	deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;

	VkResult result = vkCreateDevice(bestDevice, &deviceCreateInfo, nullptr, &m_logicalDevice);
	if (result != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create logical device.");
	}

	vkGetDeviceQueue(m_logicalDevice, graphicsFamily, 0, &m_graphicsQueue);
}

void lumina::RenderSystem::cleanup()
{
	if (m_logicalDevice != VK_NULL_HANDLE)
	{
		vkDestroyDevice(m_logicalDevice, nullptr);
		m_logicalDevice = VK_NULL_HANDLE;
	}

	if (m_vkInstance != VK_NULL_HANDLE)
	{
		vkDestroyInstance(m_vkInstance, nullptr);
		m_vkInstance = VK_NULL_HANDLE;
	}
}

lumina::RenderSystem::~RenderSystem()
{
	cleanup();
}
