#pragma once

#include <engine/ui/view_controller.hpp>

namespace logicario::engine::ui
{
    class CornerStick : public ViewController
    {
    public:
        CornerStick(int border, int width, int height) : m_border{border}, m_width{width}, m_height{height} {};
        ~CornerStick() override = default;
        Rect createRect(int rendererWidth, int rendererHeight) override
        {
            Rect rect{};
            rect.left = rendererWidth - (m_width + m_border);
            rect.right = rendererWidth - m_border;
            rect.top = m_border;
            rect.bottom = m_height + m_border;
            return rect;
        }

    private:
        int m_border;
		int m_width;
		int m_height;
    };
}