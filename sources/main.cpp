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
	logger.set_level((spdlog::level::level_enum)SPDLOG_ACTIVE_LEVEL);
    logger.info("{:-^80}", "Starting");
    try
    {
        logicario::engine::platform::StdFilesystem filesystem{stdoutSink};
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


		auto vertex = filesystem.loadText("resources/shaders/main/vertex.glsl").value();
		auto fragment = filesystem.loadText("resources/shaders/main/fragment.glsl").value();
		auto& shader = renderer.createShader(vertex, fragment);

		auto b_vertex = filesystem.loadText("resources/shaders/background/vertex.glsl").value();
		auto b_fragment = filesystem.loadText("resources/shaders/background/fragment.glsl").value();
		auto& backgroundShader = renderer.createShader(b_vertex, b_fragment);

		auto image = filesystem.loadImage("resources/images/test.png").value();
		auto& texture = renderer.createTexture(image);

		auto& view = renderer.createView({0, 50, 0, 50});

		logger.debug("shader id is {}", shader.getID());
		logger.debug("texture id is {}", texture.getID());
		
		logicario::engine::Sprite sprite{texture, {1, 15, 4, 12}};

        while (run)
        {
            window.update();
            renderer.clear({0.2, 0.2, 0.2, 1.0});
			renderer.drawBackground(view, backgroundShader, glm::vec4{0.8f});
			//renderer.draw(sprite, shader);
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
