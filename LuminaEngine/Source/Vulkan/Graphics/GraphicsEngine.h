#pragma once
#include <Vulkan/Core/Core.h>
#include <Vulkan/Core/Base.h>

namespace lumina
{
	class GraphicsEngine final: public Base
	{
	public:
		explicit GraphicsEngine(const GraphicsEngineDesc& desc);
		virtual ~GraphicsEngine() override;

	private:
		std::unique_ptr<RenderSystem> m_renderSystem{};
	};

}
