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
		void setMousePos(int mouseX, int mouseY);

    private:
        KeyCode translateKey(uint32_t glfwKeyCode);
        void notifyKeyCode(KeyCode keyCode, bool state);

    private:
        std::array<bool, KEYCODES_COUNT> m_keyStates;
		spdlog::logger m_logger;
    };
}
