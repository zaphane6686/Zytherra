#include <Vulkan/Core/Logger.h>
#include <iostream>

lumina::Logger::Logger(LogLevel logLevel) : m_logLevel(logLevel)
{
	std::clog << "Lumina Engine" << std::endl;
	std::clog << "-------------" << std::endl;
}

void lumina::Logger::log(LogLevel level, const char* message) const
{
	auto logLevelToString = [](LogLevel level) -> const char* 
	{
		switch (level)
		{
		case LogLevel::Info:return "INFO";
		case LogLevel::Warning:return "WARNING";
		case LogLevel::Error:return "ERROR";
		default:return "UNKNOWN";
		}
	};

	if (level > m_logLevel)return;
	std::clog << "[Lumina " << logLevelToString(level) << "] " << message << std::endl;
}
