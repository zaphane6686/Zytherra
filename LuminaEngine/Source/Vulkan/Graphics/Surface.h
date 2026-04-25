#pragma once
#include <Vulkan/Core/Base.h>

namespace lumina
{
	class Surface : public Base
	{
	public:
		Surface(const BaseDesc& desc);
		virtual ~Surface() override;
	};
}

