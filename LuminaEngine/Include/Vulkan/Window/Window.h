#pragma once
#include <Vulkan/Core/Base.h>
#include <Vulkan/Core/Common.h>
#include <Windows.h>

namespace lumina
{
	class Window : public Base
	{
	public:
		explicit Window(const WindowDesc& desc);
		virtual ~Window() override;

	private:
		void* m_handle{};
	};
}


