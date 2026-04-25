#include <Vulkan/All.h>

int main() 
{
    try
    {
        lumina::Game game({lumina::Logger::LogLevel::Info});
        game.run();
    }
    catch (const std::runtime_error&)
    {
       return EXIT_FAILURE;
	}
    catch (const std::exception&)
    {
        return EXIT_FAILURE;
    }
    catch (...)
    {
        return EXIT_FAILURE;
    }

   

    return 0;
}