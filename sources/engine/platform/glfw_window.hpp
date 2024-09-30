#pragma once

#include <engine/window.hpp>
#include <engine/platform/glfw_input.hpp>
#include <engine/platform/Ogl_renderer.hpp>

#include <GLFW/glfw3.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <memory>

namespace logicario::engine::platform
{
    struct GlfwWindowParams
    {
        std::string_view title;
        int width;
        int height;
        std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> loggerSink;
    };

    class GlfwWindow : public Window
    {
    public:
        GlfwWindow(const GlfwWindowParams& params);
        void update() override;
        Input& getInput() override;
        Renderer& getRenderer() override;

    private:
        using WindowHandleDeleter = void (*)(GLFWwindow*);
        using WindowHandle = std::unique_ptr<GLFWwindow, WindowHandleDeleter>;

    private:
        void initGlfw();
        void createWindow(const GlfwWindowParams& params);
        void setCallbacks();
        void swap();

    private:
        static void windowCloseCallback(GLFWwindow* window);
        static void windowKeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
		static void windowMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
		static void cursorPosCallback(GLFWwindow* window, double mouseX, double mouseY);

    private:
        WindowHandle m_windowHandle;
        spdlog::logger m_logger;
        std::unique_ptr<GlfwInput> m_input;
        std::unique_ptr<OglRenderer> m_renderer;
        ActionSubscribe m_resizedActionSubForRenderer;
    };
}