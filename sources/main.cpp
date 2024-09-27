#include <fmt/ranges.h>

#include <engine/platform/glfw_window.hpp>
#include <engine/platform/std_filesystem.hpp>

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
        auto windowClosedActionSubscribe = window.Closed.add([&run]() { run = false; });
        auto& input = window.getInput();
        auto& renderer = window.getRenderer();
        auto keyDownedActionSubscribe = input.KeyDowned.add(
            [&run](logicario::engine::KeyCode key)
        {
            if (key == logicario::engine::KeyCode::Esc) run = false;
        });

		logicario::engine::platform::StdFilesystem filesystem{stdoutSink};
		auto image = filesystem.loadImage("resources/images/test.png");

        while (run)
        {
            window.update();
            renderer.clear({0.5, 0.6, 0.7, 1.0});
            renderer.swap();
        }
    }
    catch (const std::exception& e)
    {
        logger.critical("{}; Closing...", e.what());
    }
    logger.info("{:-^80}", "Shutdown");
    return 0;
}
