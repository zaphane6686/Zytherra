#pragma once
#include <Vulkan/Core/Logger.h>

namespace lumina
{
#define LuminaGraphicsLogErrorAndThrow(hr, message) \
    {\
	auto _result = (hr);\
	if ((_result) != (VK_SUCCESS))LuminaLogErrorAndThrow(message);\
	}
}