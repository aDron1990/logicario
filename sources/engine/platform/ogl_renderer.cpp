#include <engine/platform/Ogl_renderer.hpp>

namespace logicario::engine::platform
{
    OglRenderer::OglRenderer(std::function<void()> swapCallback, std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> loggerSink) : m_swapCallback{swapCallback}, m_logger{"renderer", {loggerSink}}
    {
        glewExperimental = true;
        if (glewInit() != GLEW_OK)
        {
            m_logger.critical("Failed to init OpeGL context");
            throw std::runtime_error{"Failed to init OpeGL context"};
        }
        m_logger.info("Renderer initialized");
    }

    void OglRenderer::onWindowResize(int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void OglRenderer::swap()
    {
        m_swapCallback();
    }

    void OglRenderer::clear(const glm::vec4& color)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OglRenderer::draw() {}

    Shader& OglRenderer::createShader(const Text& vertexCode, const Text& fragmentCode)
    {
		ID shaderID = xg::newGuid().str();
        m_shaders.emplace(shaderID, OglShader{vertexCode, fragmentCode, shaderID});
        return m_shaders[shaderID];
    }
}