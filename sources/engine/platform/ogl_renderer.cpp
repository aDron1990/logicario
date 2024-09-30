#include <engine/platform/Ogl_renderer.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace logicario::engine::platform
{
    OglRenderer::OglRenderer(std::function<void()> swapCallback, std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> loggerSink) : m_swapCallback{swapCallback}, m_logger{"renderer", {loggerSink}}, m_framebufferSize{0, 0}, m_aspect{0}
    {
        glewExperimental = true;
		m_logger.set_level((spdlog::level::level_enum)SPDLOG_ACTIVE_LEVEL);
        if (glewInit() != GLEW_OK)
        {
            m_logger.critical("Failed to init OpeGL context");
            throw std::runtime_error{"Failed to init OpeGL context"};
        }
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

	View& OglRenderer::createView(View::ViewControllerPtr viewController)
	{
		ID viewID = xg::newGuid().str();
		View::ViewImplPtr viewImpl = std::make_unique<OglViewImpl>(m_framebufferSize);
		m_views.emplace(viewID, View{std::move(viewImpl), std::move(viewController), viewID});
		m_views[viewID].onRendererResize(m_framebufferSize.x, m_framebufferSize.y);
		return m_views[viewID];
	}

	void OglRenderer::draw(View& view, Sprite& sprite, Shader& shader)
	{
		auto spriteRegion = sprite.getTextureRegion();
		auto& spriteTexture = sprite.getTexture();
		glm::fvec2 spriteSize = {spriteRegion.right - spriteRegion.left, spriteRegion.bottom - spriteRegion.top};
		glm::fvec2 textureSize = spriteTexture.getSize();

		glm::mat4 model = sprite.getMatrix();
		glm::mat4 viewMatrix = view.getViewMatrix();
		glm::mat4 projection = glm::scale(glm::mat4{1.0f}, glm::vec3{1.0f, 1.0f, 1.0f});

		GLuint vbo, vao, ebo;

		float vertices[] = 
		{
			-(spriteSize.x / 2.0f), (spriteSize.y / 2.0f), 		spriteRegion.left / textureSize.x, spriteRegion.top / textureSize.y,
			(spriteSize.x / 2.0f), -(spriteSize.y / 2.0f), 		spriteRegion.right / textureSize.x, spriteRegion.bottom / textureSize.y,
			(spriteSize.x / 2.0f), (spriteSize.y / 2.0f), 		spriteRegion.right / textureSize.x, spriteRegion.top / textureSize.y,
			-(spriteSize.x / 2.0f), -(spriteSize.y / 2.0f), 	spriteRegion.left / textureSize.x, spriteRegion.bottom / textureSize.y,
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

		view.bind();
		shader.bind();
		shader.set(model, "model");
		shader.set(viewMatrix, "view");
		shader.set(projection, "projection");
		spriteTexture.bind();
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ebo);
		glDeleteVertexArrays(1, &vao);
	}

	void OglRenderer::draw(View& view, Rect& rect, Shader& shader, glm::vec4 color)
	{
		glm::mat4 viewMatrix = view.getViewMatrix();
		//glm::mat4 viewMatrix{1.0f};

		GLuint vbo, vao, ebo;

		float vertices[] = 
		{
			rect.left, rect.top,
			rect.right, rect.bottom,
			rect.right, rect.top,
			rect.left, rect.bottom,
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
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);

		view.bind();
		shader.bind();

		shader.set(color, "color");
		shader.set(viewMatrix, "view");
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

		shader.bind();
		shader.set(color, "color");
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
	}
}