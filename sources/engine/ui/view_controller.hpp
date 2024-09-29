#pragma once

#include <engine/types.hpp>

namespace logicario::engine::ui
{
    class ViewController
    {
    public:
		virtual ~ViewController() = default;
        virtual Rect createRect(int rendererWidth, int rendererHeight) = 0;
    };
}
