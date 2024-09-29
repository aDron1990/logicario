#pragma once

#include <engine/view_impl.hpp>
#include <engine/action.hpp>

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
        void onRendererResize(int width, int height) override;

    private:
        ViewImpl::Rect m_viewRect;
        glm::vec2 m_rendererSize;
    };
}