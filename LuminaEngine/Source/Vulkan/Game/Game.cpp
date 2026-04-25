#include <Vulkan/Game/Game.h>
#include <Vulkan/Window/Window.h>
#include <Vulkan/Graphics/GraphicsEngine.h>
#include <Vulkan/Core/Logger.h>

lumina::Game::Game(const GameDesc& desc) :
	Base({ *std::make_unique<Logger>(desc.logLevel).release()}),
	m_loggerPtr(&m_logger)
{
	m_graphicsEngine = std::make_unique<GraphicsEngine>(GraphicsEngineDesc{m_logger});
	m_display = std::make_unique<Window>(WindowDesc{m_logger});

	m_loggerPtr->log(Logger::LogLevel::Info, "Game initialized.");
}

lumina::Game::~Game()
{
	m_loggerPtr->log(Logger::LogLevel::Info, "Game deallocation started.");
}


