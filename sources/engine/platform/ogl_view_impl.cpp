#include <engine/platform/ogl_view_impl.hpp>

#include <GL/glew.h>

namespace logicario::engine::platform
{
    OglViewImpl::OglViewImpl(glm::vec2 rendererSize) : m_viewRect{0, 0, 0, 0}, m_rendererSize{rendererSize} {}

    void OglViewImpl::bind()
    {
        glm::vec4 viewport = {m_viewRect.left, m_viewRect.top, m_viewRect.right, m_viewRect.bottom};
		glViewport(viewport.x, m_rendererSize.y - viewport.w, viewport.z - viewport.x, (m_rendererSize.y - viewport.y) - (m_rendererSize.y - viewport.w));
    }

    void OglViewImpl::setRect(Rect viewRect)
    {
        m_viewRect = viewRect;
    }

	glm::vec2 OglViewImpl::getSize()
	{
		return {m_viewRect.right - m_viewRect.left, m_viewRect.bottom - m_viewRect.top};
	}

    void OglViewImpl::onRendererResize(int width, int height)
    {
        m_rendererSize = {width, height};
    }
}