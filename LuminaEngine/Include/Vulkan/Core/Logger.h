#pragma once

namespace lumina
{
	class Logger final 
	{
	public:
		enum class LogLevel
		{
			Error = 0,
			Warning,
			Info
		};
		explicit Logger(LogLevel logLevel = LogLevel::Error);
		void log(LogLevel level, const char* message) const;

	private:
		LogLevel m_logLevel = LogLevel::Error;
	};

#define LuminaLogInfo(message) \
	getLogger().log((Logger::LogLevel::Info), message);

#define LuminaLogWarning(message) \
	getLogger().log((Logger::LogLevel::Warning), message);

#define LuminaLogError(message) \
	getLogger().log((Logger::LogLevel::Error), message);
	
#define LuminaLogErrorAndThrow(message) \
	{\
	LuminaLogError(message);\
	throw std::runtime_error(message);\
	}

}

