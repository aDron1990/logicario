#pragma once

#include <engine/ui/view_controller.hpp>

namespace logicario::engine::ui
{
    class RectView : public ViewController
    {
    public:
        RectView(Rect rect, ViewControllerPtr nextController = nullptr) : ViewController{std::move(nextController)}, m_rect{rect} {};
        ~RectView() override = default;
        Rect transformRect(Rect rect, int rendererWidth, int rendererHeight) override
        {
            return m_rect;
        }

    private:
        Rect m_rect;
    };
}