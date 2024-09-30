#pragma once

#include <engine/action.hpp>
#include <engine/keycode.hpp>

#include <glm/glm.hpp>

namespace logicario::engine
{
    class Input
    {
    public:
        Action<KeyCode> KeyDowned;
        Action<KeyCode> KeyUpped;
		Action<int, int> MouseMoved;
		Action<MouseButton> MouseButtonDowned;
		Action<MouseButton> MouseButtonUpped;

	public:
		virtual glm::vec2 getMousePos() = 0;

    protected:
        ~Input() = default;
    };
}