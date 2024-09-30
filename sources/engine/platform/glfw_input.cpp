#include <engine/platform/glfw_input.hpp>

#include <GLFW/glfw3.h>

namespace logicario::engine::platform
{
    GlfwInput::GlfwInput(std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> loggerSink) : m_logger{"input", {loggerSink}}, m_keyStates{0}, m_mousePos{0.0f}
    {
        m_logger.set_level((spdlog::level::level_enum)SPDLOG_ACTIVE_LEVEL);
        m_logger.info("Input initialized");
    }

    void GlfwInput::setKey(uint32_t glfwKeyCode, bool state)
    {
        KeyCode keyCode = translateKey(glfwKeyCode);
        m_keyStates[(uint32_t)keyCode] = state;
        notifyKeyCode(keyCode, state);
    }

	void GlfwInput::setMouseButton(uint32_t glfwButtonCode, bool state)
	{
		MouseButton buttonCode = translateButton(glfwButtonCode);
		notifyButtonCode(buttonCode, state);
	}

    void GlfwInput::setMousePos(int mouseX, int mouseY)
    {
		m_mousePos = {mouseX, mouseY};
        MouseMoved.notify(mouseX, mouseY);
    }

	glm::vec2 GlfwInput::getMousePos()
	{
		return m_mousePos;
	}

    void GlfwInput::notifyKeyCode(KeyCode keyCode, bool state)
    {
        if (keyCode == KeyCode::None)
        {
            m_logger.debug("Unknown key. Can`t notify");
            return;
        }
        if (state)
            KeyDowned.notify(keyCode);
        else
            KeyUpped.notify(keyCode);
    }

    void GlfwInput::notifyButtonCode(MouseButton buttonCode, bool state)
    {
        if (buttonCode == MouseButton::None)
        {
            m_logger.debug("Unknown button. Can`t notify");
            return;
        }
		if (state)
            MouseButtonDowned.notify(buttonCode);
        else
            MouseButtonUpped.notify(buttonCode);
    }

    KeyCode GlfwInput::translateKey(uint32_t glfwKeyCode)
    {
        switch (glfwKeyCode)
        {
            case GLFW_KEY_ESCAPE: return KeyCode::Esc;
            case GLFW_KEY_SPACE: return KeyCode::Space;
            case GLFW_KEY_TAB: return KeyCode::Tab;
            case GLFW_KEY_CAPS_LOCK: return KeyCode::CapsLock;
            case GLFW_KEY_RIGHT_SHIFT: return KeyCode::RShift;
            case GLFW_KEY_LEFT_SHIFT: return KeyCode::LShift;
            case GLFW_KEY_RIGHT_CONTROL: return KeyCode::RCtrl;
            case GLFW_KEY_LEFT_CONTROL: return KeyCode::LCtrl;
            case GLFW_KEY_RIGHT_ALT: return KeyCode::RAlt;
            case GLFW_KEY_LEFT_ALT: return KeyCode::LAlt;
            case GLFW_KEY_RIGHT_SUPER: return KeyCode::RSuper;
            case GLFW_KEY_LEFT_SUPER: return KeyCode::LSuper;

            case GLFW_KEY_W: return KeyCode::W;
            case GLFW_KEY_A: return KeyCode::A;
            case GLFW_KEY_S: return KeyCode::S;
            case GLFW_KEY_D: return KeyCode::D;
            case GLFW_KEY_E: return KeyCode::E;
            case GLFW_KEY_Q: return KeyCode::Q;
            case GLFW_KEY_Z: return KeyCode::Z;
            case GLFW_KEY_X: return KeyCode::X;

            default: return KeyCode::None;
        }
    }

    MouseButton GlfwInput::translateButton(uint32_t glfwButtonCode)
    {
        switch (glfwButtonCode)
        {
            case GLFW_MOUSE_BUTTON_1: return MouseButton::Left;
            case GLFW_MOUSE_BUTTON_2: return MouseButton::Right;
            case GLFW_MOUSE_BUTTON_3: return MouseButton::Middle;
            default: return MouseButton::None;
        }
    }
}