#include <fmt/ranges.h>

#include <engine/platform/glfw_window.hpp>
#include <engine/platform/std_filesystem.hpp>
#include <engine/ui/main_view.hpp>
#include <engine/ui/corner_view.hpp>
#include <engine/ui/bordered_view.hpp>

#include <GLFW/glfw3.h>
#include <crossguid/guid.hpp>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <glm/gtc/matrix_transform.hpp>

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
        auto windowClosedActionSub = window.Closed.add([&run]() { run = false; });
        auto& input = window.getInput();
        auto& renderer = window.getRenderer();

        auto keyDownedActionSub = input.KeyDowned.add(
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

        auto atlasImage = filesystem.loadImage("resources/images/atlas.png").value();
        auto& atlasTexture = renderer.createTexture(atlasImage);
        logicario::engine::Sprite emptySprite{atlasTexture, {0, 32, 0, 32}};

        auto mainViewController = std::make_unique<logicario::engine::ui::MainView>(std::make_unique<logicario::engine::ui::BorderedView>(50));
        auto& mainView = renderer.createView(std::move(mainViewController));

        auto ac = input.MouseMoved.add(
            [&](int x, int y)
            {
                if (mainView.isMouseHover(x, y))
                {
                    auto viewPos = mainView.screenToViewCoords({x, y});
                    logger.debug("view:  [{}, {}]", viewPos.x, viewPos.y);
                    return;
                }
                logger.debug("mouse: [{}, {}]", x, y);
            });

        mainView.setZoom(6);
        std::vector<logicario::engine::Sprite> sprites;
        sprites.push_back(emptySprite);
        emptySprite.setPosition({32, 0});
        //sprites.push_back(emptySprite);

        while (run)
        {
            window.update();
            renderer.clear({0.2, 0.2, 0.2, 1.0});
            renderer.drawBackground(mainView, backgroundShader, {0.8f, 0.8f, 0.8f, 1.0f});
            for (auto&& sprite : sprites)
            {
                renderer.draw(mainView, sprite, shader);
            }
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
