#pragma once

#include <engine/ui/view_controller.hpp>

namespace logicario::engine::ui
{
    class MainView : public ViewController
    {
    public:
        MainView(ViewControllerPtr nextController = nullptr) : ViewController{std::move(nextController)} {};
        ~MainView() override = default;
        Rect transformRect(Rect rect, int rendererWidth, int rendererHeight) override
        {
            rect.left = 0;
            rect.right = rendererWidth;
            rect.top = 0;
            rect.bottom = rendererHeight;
            return rect;
        }
    };
}