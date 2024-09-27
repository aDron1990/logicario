#pragma once

#include <engine/action.hpp>
#include <engine/keycode.hpp>

namespace logicario::engine
{
    class Input
    {
    public:
        Action<KeyCode> KeyDowned;
        Action<KeyCode> KeyUpped;

    protected:
        ~Input() = default;
    };
}