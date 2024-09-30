#pragma once

#include <engine/input.hpp>

#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <functional>
#include <array>

namespace logicario::engine::platform
{
    class GlfwInput : public Input
    {
    public:
        GlfwInput(std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> loggerSink);
        void setKey(uint32_t glfwKeyCode, bool state);
		void setMouseButton(uint32_t glfwButtonCode, bool state);
		void setMousePos(int mouseX, int mouseY);
		glm::vec2 getMousePos();

    private:
        KeyCode translateKey(uint32_t glfwKeyCode);
        void notifyKeyCode(KeyCode keyCode, bool state);
		MouseButton translateButton(uint32_t glfwButtonCode);
		void notifyButtonCode(MouseButton buttonCode, bool state);

    private:
        std::array<bool, KEYCODES_COUNT> m_keyStates;
		glm::vec2 m_mousePos;
		spdlog::logger m_logger;
    };
}
