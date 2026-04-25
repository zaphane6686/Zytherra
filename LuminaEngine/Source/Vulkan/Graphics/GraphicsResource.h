#pragma once
#include <Vulkan/Core/Common.h>
#include <Vulkan/Core/Base.h>
#include <Vulkan/vulkan.h>

namespace lumina
{
	struct GraphicsResourceDesc
	{
		BaseDesc base;
		VkInstance& vkInstance;
		VkDevice& logicalDevice;
		VkQueue& graphicsQueue;
	};

	class GraphicsResource : public Base
	{
	public:
		explicit GraphicsResource(const GraphicsResourceDesc& desc):
			Base(desc.base),
			m_vkInstance(desc.vkInstance),
			m_logicalDevice(desc.logicalDevice),
			m_graphicsQueue(desc.graphicsQueue)
		{
		}
	protected:
		VkInstance& m_vkInstance;
		VkDevice& m_logicalDevice;
		VkQueue& m_graphicsQueue;
	};
}