#include <engine/platform/ogl_view_impl.hpp>

#include <GL/glew.h>

namespace logicario::engine::platform
{
    OglViewImpl::OglViewImpl(glm::vec2 rendererSize) : m_viewRect{0, 0, 0, 0}, m_rendererSize{rendererSize} {}

    void OglViewImpl::bind()
    {
        Rect viewport{};
        viewport.left = m_viewRect.left;
        viewport.bottom = m_rendererSize.y - m_viewRect.bottom;
        viewport.right = m_viewRect.right - viewport.left;
        viewport.top = (m_rendererSize.y - m_viewRect.top) - m_viewRect.bottom;
        glViewport(viewport.left, viewport.bottom, viewport.right, viewport.top);
    }

    void OglViewImpl::setRect(Rect viewRect)
    {
        m_viewRect = viewRect;
    }

    void OglViewImpl::onRendererResize(int width, int height)
    {
        m_rendererSize = {width, height};
    }
}