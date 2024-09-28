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
        m_logger.set_level((spdlog::level::level_enum)SPDLOG_ACTIVE_LEVEL);
        m_logger.info("Renderer initialized");
    }

    void OglRenderer::onWindowResize(int width, int height)
    {
        m_logger.trace("Framebuffer resized: [{}, {}]", width, height);
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

    Shader& OglRenderer::createShader(const Text& vertexCode, const Text& fragmentCode)
    {
        ID shaderID = xg::newGuid().str();
        m_shaders.emplace(shaderID, OglShader{vertexCode, fragmentCode, shaderID});
        return m_shaders[shaderID];
    }

	Texture& OglRenderer::createTexture(const Image& image)
	{
		ID textureID = xg::newGuid().str();
		m_textures.emplace(textureID, OglTexture{image, textureID});
		return m_textures[textureID];
	}

    void OglRenderer::drawTestTriangle(Shader& shader)
    {
        float vertices[] = 
		{
			-0.5f, 0.5f, 0.0f, 0.0f,
			0.5f, -0.5f, 1.0f, 1.0f,
			0.5f, 0.5f, 1.0f, 0.0f,
			-0.5f, 0.5f, 0.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 1.0f,
			0.5f, -0.5f, 1.0f, 1.0f,
		};
		GLuint vbo, vao;

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);

		shader.bind();
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}