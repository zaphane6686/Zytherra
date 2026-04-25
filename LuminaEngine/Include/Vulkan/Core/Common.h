#pragma once
#include <Vulkan/Core/Core.h>
#include <Vulkan/Core/Logger.h>

namespace lumina
{
	struct BaseDesc
	{
		Logger& logger;
	};

	struct WindowDesc
	{
		BaseDesc base;
	};

	struct GraphicsEngineDesc
	{
		BaseDesc base;
	};

	struct RenderSystemDesc
	{
		BaseDesc base;
	};

	struct GameDesc
	{
		Logger::LogLevel logLevel = Logger::LogLevel::Error;
	};

	struct SurfaceDesc
	{
		BaseDesc base;
	};

}