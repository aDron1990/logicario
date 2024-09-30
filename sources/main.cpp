#include <fmt/ranges.h>

#include <engine/platform/glfw_window.hpp>
#include <engine/platform/std_filesystem.hpp>
#include <engine/ui/main_view.hpp>
#include <engine/ui/corner_view.hpp>
#include <engine/ui/bordered_view.hpp>
#include <engine/ui/rect_view.hpp>

#include <quadtree.hpp>

#include <GLFW/glfw3.h>
#include <crossguid/guid.hpp>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

int main()
{
	srand(time(NULL));
    auto stdoutSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    spdlog::logger logger{"main", {stdoutSink}};
    logger.set_level((spdlog::level::level_enum)SPDLOG_ACTIVE_LEVEL);
    logger.info("{:-^80}", "Starting");
    try
    {
        logicario::engine::platform::StdFilesystem filesystem{stdoutSink};
        logicario::engine::platform::GlfwWindow window{{"logicario", 1024, 1024, stdoutSink}};
        bool run = true;
        auto windowClosedActionSub = window.Closed.add([&run]() { run = false; });
        auto& input = window.getInput();
        auto& renderer = window.getRenderer();

        auto keyDownedActionSub = input.KeyDowned.add(
            [&run](logicario::engine::KeyCode key)
            {
                if (key == logicario::engine::KeyCode::Esc) run = false;
            });

        auto vertex = filesystem.loadText("resources/shaders/sprite/vertex.glsl").value();
        auto fragment = filesystem.loadText("resources/shaders/sprite/fragment.glsl").value();
        auto& shader = renderer.createShader(vertex, fragment);

        auto b_vertex = filesystem.loadText("resources/shaders/background/vertex.glsl").value();
        auto b_fragment = filesystem.loadText("resources/shaders/background/fragment.glsl").value();
        auto& backgroundShader = renderer.createShader(b_vertex, b_fragment);

        auto r_vertex = filesystem.loadText("resources/shaders/rect/vertex.glsl").value();
        auto r_fragment = filesystem.loadText("resources/shaders/rect/fragment.glsl").value();
        auto& rectShader = renderer.createShader(r_vertex, r_fragment);

        auto atlasImage = filesystem.loadImage("resources/images/atlas.png").value();
        auto& atlasTexture = renderer.createTexture(atlasImage);
        logicario::engine::Sprite emptySprite{atlasTexture, {0, 32, 0, 32}};

        auto viewController = std::make_unique<logicario::engine::ui::MainView>();
        auto& view = renderer.createView(std::move(viewController));

        std::vector<logicario::engine::Sprite> sprites;
        emptySprite.setScale({0.2f, 0.2f});

        QuadTree qtree{BoundyBox{{0, 0}, {1024, 1024}}};
        std::function<void(QuadTree&)> renderQuadTree = [&](QuadTree& tree) -> void
        {
            auto aabb = tree.getAABB();
            logicario::engine::Rect rect = {aabb.m_position.x - aabb.m_halfSize.x, aabb.m_position.x + aabb.m_halfSize.x, aabb.m_position.y - aabb.m_halfSize.y, aabb.m_position.y + aabb.m_halfSize.y};
            renderer.draw(view, rect, rectShader, tree.color);
            QuadTree* subTree;
            subTree = tree.getChild(QuadTree::SubTreeType::LeftBottom);
            if (subTree) renderQuadTree(*subTree);
            subTree = tree.getChild(QuadTree::SubTreeType::LeftTop);
            if (subTree) renderQuadTree(*subTree);
            subTree = tree.getChild(QuadTree::SubTreeType::RightTop);
            if (subTree) renderQuadTree(*subTree);
            subTree = tree.getChild(QuadTree::SubTreeType::RightBottom);
            if (subTree) renderQuadTree(*subTree);
        };

        auto ac2 = input.MouseButtonDowned.add(
            [&](logicario::engine::MouseButton button)
            {
                auto mousePos = input.getMousePos();
                if (button == logicario::engine::MouseButton::Left && view.isMouseHover(mousePos.x, mousePos.y))
                {
                    auto viewPos = view.screenToViewCoords({mousePos.x, mousePos.y});
                    emptySprite.setPosition(viewPos);
                    sprites.push_back(emptySprite);
                    logger.debug("set sprite at: [{}, {}]", viewPos.x, viewPos.y);

                    qtree.insert(viewPos);

                    return;
                }
            });

        while (run)
        {
            window.update();
            renderer.clear({0.2, 0.2, 0.2, 1.0});
            renderer.drawBackground(view, backgroundShader, {0.7f, 0.7f, 0.7f, 1.0f});
            logicario::engine::Rect rect{0, 512, 0, 512};
            renderQuadTree(qtree);
            for (auto&& sprite : sprites)
            {
                renderer.draw(view, sprite, shader);
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
