#include <engine/platform/glfw_window.hpp>

namespace logicario::engine::platform
{
    GlfwWindow::GlfwWindow(const GlfwWindowParams& params) : m_windowHandle{nullptr, nullptr}, m_input{params.loggerSink}, m_logger{"window", {params.loggerSink}}
    {
        initGlfw();
        createWindow(params);
		setCallbacks();
        m_logger.info("Window initialized");
    }

    void GlfwWindow::initGlfw()
    {
        auto result = glfwInit();
        if (!result)
        {
            m_logger.critical("Failed to init glfw");
            throw std::runtime_error{"Failed to init glfw"};
        }
    }

    void GlfwWindow::createWindow(const GlfwWindowParams& params)
    {
        auto windowPtr = glfwCreateWindow(params.width, params.height, params.title.data(), nullptr, nullptr);
        if (windowPtr == nullptr)
        {
            m_logger.critical("Failed to create window");
            glfwTerminate();
            throw std::runtime_error{"Failed to create window"};
        }
        m_windowHandle = WindowHandle{windowPtr, [](GLFWwindow* wnd)
        {
            glfwDestroyWindow(wnd);
            glfwTerminate();
        }};
    }

	void GlfwWindow::setCallbacks()
	{
		glfwSetWindowUserPointer(m_windowHandle.get(), this);
        glfwSetWindowCloseCallback(m_windowHandle.get(), windowCloseCallback);
        glfwSetKeyCallback(m_windowHandle.get(), windowKeyCallback);
	}

    void GlfwWindow::update()
    {
        glfwPollEvents();
    }

    Input& GlfwWindow::getInput()
    {
        return m_input;
    }

    void GlfwWindow::windowCloseCallback(GLFWwindow* window)
    {
        GlfwWindow* wnd = (GlfwWindow*)glfwGetWindowUserPointer(window);
        wnd->Closed.notify();
    }

    void GlfwWindow::windowKeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
    {
        if (action == GLFW_REPEAT) return;
        GlfwWindow* wnd = (GlfwWindow*)glfwGetWindowUserPointer(window);
        wnd->m_input.setKey(key, action);
    }
}