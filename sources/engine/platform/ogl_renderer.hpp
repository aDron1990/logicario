#include <engine/renderer.hpp>
#include <engine/action.hpp>
#include <engine/platform/ogl_shader.hpp>
#include <engine/platform/ogl_texture.hpp>
#include <engine/platform/ogl_view_impl.hpp>

#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <GL/glew.h>

#include <functional>
#include <unordered_map>

namespace logicario::engine::platform
{
    class OglRenderer : public Renderer
    {
    public:
        OglRenderer(std::function<void()> swapCallback, std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> loggerSink);
        void onWindowResize(int width, int height);
        void swap() override;
        void clear(const glm::vec4& color) override;
        void drawTest(Shader& shader) override;
		void drawBackground(View& view, Shader& shader, glm::vec4 color) override;
		void draw(View& view, Sprite& sprite, Shader& shader) override;

    public:
        Shader& createShader(const Text& vertexCode, const Text& fragmentCode) override;
        Texture& createTexture(const Image& image) override;
		View& createView(ViewImpl::Rect viewRect) override;

    private:
        spdlog::logger m_logger;
        std::function<void()> m_swapCallback;
        std::unordered_map<ID, OglShader> m_shaders;
        std::unordered_map<ID, OglTexture> m_textures;
		std::unordered_map<ID, View> m_views;
		glm::ivec2 m_framebufferSize;
		float m_aspect;
    };
}