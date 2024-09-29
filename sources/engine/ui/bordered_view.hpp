#pragma once

#include <engine/ui/view_controller.hpp>

namespace logicario::engine::ui
{
    class BorderedView : public ViewController
    {
    public:
        BorderedView(int border) : m_border{border} {};
        ~BorderedView() override = default;
		Rect transformRect(Rect rect, int rendererWidth, int rendererHeight) override
		{
            rect.left += m_border;
            rect.right -= m_border;
            rect.top += m_border;
            rect.bottom -= m_border;
            return rect;
		}

    private:
        int m_border;
    };
}