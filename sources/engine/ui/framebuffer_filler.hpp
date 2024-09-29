#pragma once

#include <engine/ui/view_controller.hpp>

namespace logicario::engine::ui
{
    class FramebufferFiller : public ViewController
    {
    public:
        FramebufferFiller(int border) : m_border{border} {};
        ~FramebufferFiller() override = default;
        Rect createRect(int rendererWidth, int rendererHeight) override
        {
            Rect rect{};
            rect.left = m_border;
            rect.right = rendererWidth - m_border;
            rect.top = m_border;
            rect.bottom = rendererHeight - m_border;
            return rect;
        }

    private:
        int m_border;
    };
}