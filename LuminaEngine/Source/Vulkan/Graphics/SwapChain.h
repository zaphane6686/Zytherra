#pragma once
#include <Vulkan/Graphics/GraphicsResource.h>

namespace lumina
{
	class SwapChain final : public GraphicsResource
	{
	public:
		SwapChain(const GraphicsResourceDesc& desc);
	};
}

