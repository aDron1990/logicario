#pragma once

#include <engine/ui/view_controller.hpp>

#include <functional>

namespace logicario::engine::ui
{
    class CornerView : public ViewController
    {
    public:
        enum class Corner
        {
            RightTop,
            RightBottom,
            LeftTop,
            LeftBottom
        };

    private:
        std::function<Rect(Rect, int, int)> m_transformRect;

    public:
        CornerView(Corner corner, int width, int height, ViewControllerPtr nextController = nullptr)
            : ViewController{std::move(nextController)}, m_transformRect{nullptr}, m_width{width}, m_height{height}
        {
            using namespace std::placeholders;
            switch (corner)
            {
                case Corner::RightTop: m_transformRect = [this](Rect rect, int rendererWidth, int rendererHeight) { return rightTopCorner(rect, rendererWidth, rendererHeight); }; break;
                case Corner::RightBottom: m_transformRect = [this](Rect rect, int rendererWidth, int rendererHeight) { return rightBottomCorner(rect, rendererWidth, rendererHeight); }; break;
                case Corner::LeftTop: m_transformRect = [this](Rect rect, int rendererWidth, int rendererHeight) { return leftTopCorner(rect, rendererWidth, rendererHeight); }; break;
                case Corner::LeftBottom: m_transformRect = [this](Rect rect, int rendererWidth, int rendererHeight) { return leftBottomCorner(rect, rendererWidth, rendererHeight); }; break;
                default: assert(false); break;
            }
        };
        ~CornerView() override = default;
        Rect transformRect(Rect rect, int rendererWidth, int rendererHeight) override { return m_transformRect(rect, rendererWidth, rendererHeight); }

    private:
        Rect rightTopCorner(Rect rect, int rendererWidth, int rendererHeight)
        {
            rect.left = rendererWidth - m_width;
            rect.right = rendererWidth;
            rect.top = 0;
            rect.bottom = m_height;
            return rect;
        };

        Rect rightBottomCorner(Rect rect, int rendererWidth, int rendererHeight)
        {
            rect.left = rendererWidth - m_width;
            rect.right = rendererWidth;
            rect.top = rendererHeight - m_height;
            rect.bottom = rendererHeight;
            return rect;
        };

        Rect leftTopCorner(Rect rect, int rendererWidth, int rendererHeight)
        {
            rect.left = 0;
            rect.right = m_width;
            rect.top = 0;
            rect.bottom = m_height;
            return rect;
        };

        Rect leftBottomCorner(Rect rect, int rendererWidth, int rendererHeight)
        {
            rect.left = 0;
            rect.right = m_width;
            rect.top = rendererHeight - m_height;
            rect.bottom = rendererHeight;
            return rect;
        };

    private:
        int m_width;
        int m_height;
    };
}