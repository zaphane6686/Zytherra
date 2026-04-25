#include <Vulkan/Graphics/GraphicsEngine.h>
#include <Vulkan/Graphics/RenderSystem.h>

lumina::GraphicsEngine::GraphicsEngine(const GraphicsEngineDesc& desc) :Base(desc.base)
{
	m_renderSystem = std::make_unique<RenderSystem>(RenderSystemDesc{m_logger});
}

lumina::GraphicsEngine::~GraphicsEngine()
{}
