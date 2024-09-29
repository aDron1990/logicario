#pragma once

#include <engine/types.hpp>

#include <memory>

namespace logicario::engine::ui
{
    class ViewController
    {
    public:
        using ViewControllerPtr = std::unique_ptr<ViewController>;
        ViewController() : m_nextViewController{nullptr} {};
        ViewController(ViewControllerPtr nextViewController) : m_nextViewController{std::move(nextViewController)} {};
        virtual ~ViewController() = default;
        Rect createRect(int rendererWidth, int rendererHeight)
        {
            Rect rect = transformRect({0, rendererWidth, 0, rendererHeight}, rendererWidth, rendererHeight);
            if (m_nextViewController) rect = m_nextViewController->transformRect(rect, rendererWidth, rendererHeight);
            return rect;
        };
        virtual Rect transformRect(Rect rect, int rendererWidth, int rendererHeight) = 0;

    private:
        ViewControllerPtr m_nextViewController;
    };
}
