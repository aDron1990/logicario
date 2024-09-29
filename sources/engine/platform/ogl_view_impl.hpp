#pragma once

#include <engine/view_impl.hpp>
#include <engine/action.hpp>
#include <engine/types.hpp>

namespace logicario::engine::platform
{
    class OglViewImpl : public ViewImpl
    {
    public:
		OglViewImpl(glm::vec2 rendererSize);
		~OglViewImpl() override = default;

    public:
        void bind() override;
        void setRect(Rect viewRect) override;
		glm::vec2 getSize() override;
        void onRendererResize(int width, int height) override;

    private:
        Rect m_viewRect;
        glm::vec2 m_rendererSize;
    };
}