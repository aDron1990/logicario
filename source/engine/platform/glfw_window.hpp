#pragma once

#include <engine/window.hpp>
#include <engine/platform/glfw_input.hpp>

#include <GLFW/glfw3.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <optional>
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

    private:
        using WindowHandleDeleter = void (*)(GLFWwindow*);
        using WindowHandle = std::unique_ptr<GLFWwindow, WindowHandleDeleter>;

    private:
        void initGlfw();
        void createWindow(const GlfwWindowParams& params);
		void setCallbacks();

	private:
		static void windowCloseCallback(GLFWwindow* window);
		static void windowKeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);

    private:
        WindowHandle m_windowHandle;
        GlfwInput m_input;
        spdlog::logger m_logger;
    };
}