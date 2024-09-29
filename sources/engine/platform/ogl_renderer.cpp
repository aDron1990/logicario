#include <engine/platform/Ogl_renderer.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace logicario::engine::platform
{
    OglRenderer::OglRenderer(std::function<void()> swapCallback, std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> loggerSink) : m_swapCallback{swapCallback}, m_logger{"renderer", {loggerSink}}, m_framebufferSize{0, 0}, m_aspect{0}
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
		m_framebufferSize = {width, height};
		m_aspect = (float)height / width;
        glViewport(0, 0, width, height);
		for (auto&& view : m_views)
		{
			view.second.onRendererResize(width, height);
		}
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

	View& OglRenderer::createView(ViewImpl::Rect viewRect)
	{
		ID viewID = xg::newGuid().str();
		View::ViewImplPtr viewImpl = std::make_unique<OglViewImpl>(m_framebufferSize);
		viewImpl->setRect(viewRect);
		m_views.emplace(viewID, View{std::move(viewImpl), viewID});
		return m_views[viewID];
	}

    void OglRenderer::drawTest(Shader& shader)
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
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);

		shader.bind();
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
    }

	void OglRenderer::draw(View& view, Sprite& sprite, Shader& shader)
	{
		auto spriteRegion = sprite.getTextureRegion();
		auto& spriteTexture = sprite.getTexture();
		glm::fvec2 spriteSize = {spriteRegion.right - spriteRegion.left, spriteRegion.bottom - spriteRegion.top};
		glm::fvec2 textureSize = spriteTexture.getSize();
		float spriteAspect = spriteSize.x / spriteSize.y;
		//glm::mat4 model = glm::scale(glm::mat4{1.0f}, glm::vec3{(float)1.0f / textureSize.x, (float)1.0f / textureSize.y, 1.0f});
		float aspect = view.getSize().y / view.getSize().x;
		glm::mat4 model = glm::scale(glm::mat4{1.0f}, glm::vec3{1.0f * spriteAspect, 1.0f, 1.0f});
		glm::mat4 projection = glm::scale(glm::mat4{1.0f}, glm::vec3{1.0f * aspect, 1.0f, 1.0f});

		GLuint vbo, vao, ebo;
		float vertices[] = 
		{
			-0.5f, 0.5f, 	spriteRegion.left / textureSize.x, spriteRegion.top / textureSize.y,
			0.5f, -0.5f, 	spriteRegion.right / textureSize.x, spriteRegion.bottom / textureSize.y,
			0.5f, 0.5f, 	spriteRegion.right / textureSize.x, spriteRegion.top / textureSize.y,
			-0.5f, -0.5f, 	spriteRegion.left / textureSize.x, spriteRegion.bottom / textureSize.y,
		};

		unsigned int indices[] =
		{
			0, 1, 2,
			0, 3, 1
		};

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);

		shader.bind();
		shader.set(model, "model");
		shader.set(projection, "projection");
		spriteTexture.bind();
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ebo);
		glDeleteVertexArrays(1, &vao);
	}

	void OglRenderer::drawBackground(View& view, Shader& shader, glm::vec4 color)
	{
		float vertices[] = 
		{
			-1.0f, 1.0f,
			1.0f, -1.0f,
			1.0f, 1.0f,
			-1.0f, 1.0f,
			-1.0f, -1.0f,
			1.0f, -1.0f,
		};
		GLuint vbo, vao;

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		view.bind();

		//glm::vec4 viewport = {borderThick, borderThick, m_framebufferSize.x - borderThick, m_framebufferSize.y - borderThick};
		//glViewport(viewport.x, m_framebufferSize.y - viewport.w, viewport.z - viewport.x, (m_framebufferSize.y - viewport.y) - (m_framebufferSize.y - viewport.w));
		//glm::vec2 viewportSize = {viewport.z - viewport.x, viewport.w - viewport.y};

		//glm::vec2 newSize = {100, 100};
		//glm::vec2 pixelPos = {50, 50};
		//glm::vec2 a = {newSize.x / viewportSize.x, newSize.y / viewportSize.y};
		//pixelPos -= viewportSize / 2.0f;
		//pixelPos /= viewportSize / 2.0f;
		//pixelPos.y = -pixelPos.y;
		//glm::vec2 newPos = pixelPos;
		//glm::mat4 matrix{1.0f};
		//matrix = glm::translate(glm::mat4{1.0f}, {newPos, 0.0f});
		//matrix = glm::scale(matrix, glm::vec3{a, 1.0f});

		shader.bind();
		shader.set(glm::vec4{0.8f}, "color");
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
	}
}