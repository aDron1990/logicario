#pragma once

#include <engine/action.hpp>
#include <engine/input.hpp>
#include <engine/renderer.hpp>

namespace logicario::engine
{
    class Window
    {
    public:
        virtual void update() = 0;
        virtual Input& getInput() = 0;
		virtual Renderer& getRenderer() = 0;

    public:
        Action<> Closed;

    protected:
        ~Window() = default;
    };
}