#include <engine/window.hpp>
#include <engine/platform/glfw_window.hpp>

#include <GLFW/glfw3.h>
#include <crossguid/guid.hpp>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <memory>

int main()
{
    auto stdoutSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    spdlog::logger logger{"main", {stdoutSink}};
    logger.info("{:-^80}", "Starting");
    try
    {
        logicario::engine::platform::GlfwWindow window{{"logicario", 800, 600, stdoutSink}};
        bool run = true;
        auto as = window.Closed.add([&]() { run = false; });
        while (run)
            window.update();
    }
    catch (const std::exception& e)
    {
        logger.critical("{}; Closing...", e.what());
    }
	logger.info("{:-^80}", "Shutdown");
	return 0;
}
