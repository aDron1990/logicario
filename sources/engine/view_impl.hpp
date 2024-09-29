#pragma once

#include <engine/types.hpp>

#include <glm/glm.hpp>

namespace logicario::engine
{
    class ViewImpl
    {
    public:
		virtual ~ViewImpl() = default;
        virtual void bind() = 0;
        virtual void setRect(Rect viewRect) = 0;
		virtual Rect getRect() = 0;
		virtual glm::vec2 getSize() = 0;
		virtual void onRendererResize(int width, int height) = 0;

    };
}