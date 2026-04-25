#pragma once
#include <Vulkan/Core/Common.h>
#include <Vulkan/Core/Base.h>
#include <vulkan/vulkan.h>

namespace lumina
{
	class RenderSystem final : public Base
	{
	public:
		explicit RenderSystem(const RenderSystemDesc& desc);
		virtual ~RenderSystem() override;

	private:	
		void initializeInstance();
		void selectPhysicalDevice();
		void createLogicalDevice();
		void cleanup();

		VkInstance m_vkInstance = VK_NULL_HANDLE;
		VkPhysicalDevice bestDevice = VK_NULL_HANDLE;
		uint32_t graphicsFamily = -1;
		uint32_t queueFamilyCount = 0;
		float queuePriority = 1.0f;
		VkDevice m_logicalDevice = VK_NULL_HANDLE;
		VkQueue m_graphicsQueue = VK_NULL_HANDLE;
	};
}