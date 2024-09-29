#pragma once

#include <glm/glm.hpp>

namespace logicario::engine
{
    class ViewImpl
    {
    public:
        struct Rect
        {
            int left, right, top, bottom;
        };

    public:
		virtual ~ViewImpl() = default;
        virtual void bind() = 0;
        virtual void setRect(Rect viewRect) = 0;
		virtual void onRendererResize(int width, int height) = 0;

    };
}