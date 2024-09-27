#include <engine/platform/glfw_window.hpp>

#include <functional>

namespace logicario::engine::platform
{
    GlfwWindow::GlfwWindow(const GlfwWindowParams& params) : m_windowHandle{nullptr, nullptr}, m_logger{"window", {params.loggerSink}}
    {
        initGlfw();
        createWindow(params);
        setCallbacks();
        m_logger.info("Window initialized");
		glfwMakeContextCurrent(m_windowHandle.get());
		m_renderer = std::move(std::make_unique<OglRenderer>(std::bind(&GlfwWindow::swap, this), params.loggerSink));
		m_input = std::move(std::make_unique<GlfwInput>(params.loggerSink));
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

	void GlfwWindow::swap()
	{
		glfwSwapBuffers(m_windowHandle.get());
	}

    Input& GlfwWindow::getInput()
    {
        return *m_input;
    }

	Renderer& GlfwWindow::getRenderer()
	{
		return *m_renderer;
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
        wnd->m_input->setKey(key, action);
    }
}