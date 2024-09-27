#include <engine/renderer.hpp>
#include <engine/action.hpp>

#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <GL/glew.h>

#include <functional>

namespace logicario::engine::platform
{
    class OglRenderer : public Renderer
    {
    public:
        OglRenderer(std::function<void()> swapCallback, std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> loggerSink);
        void onWindowResize(int width, int height);
        void swap() override;
        void clear(const glm::vec4& color) override;
        void draw() override;

    private:
        spdlog::logger m_logger;
        std::function<void()> m_swapCallback;
    };
}