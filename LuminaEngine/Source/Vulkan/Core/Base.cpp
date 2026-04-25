#include <Vulkan/Core/Base.h>

using namespace lumina;

lumina::Base::Base(const BaseDesc& desc) : m_logger(desc.logger)
{
	
}

lumina::Base::~Base()
{
	
}

Logger& lumina::Base::getLogger() const noexcept
{
	return m_logger;
}
