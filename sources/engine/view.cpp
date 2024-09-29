#include <engine/view.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace logicario::engine
{
    View::View() : m_viewImpl{nullptr}, m_viewController{nullptr} {}
    View::View(ViewImplPtr viewImpl, ViewControllerPtr viewController, const ID& resourceID) : Resource{resourceID}, m_viewImpl{std::move(viewImpl)}, m_viewController{std::move(viewController)} {}

    void View::onRendererResize(int width, int height)
    {
        auto rect = m_viewController->createRect(width, height);
        m_viewImpl->setRect(rect);
        m_viewImpl->onRendererResize(width, height);
    }

    void View::bind()
    {
        m_viewImpl->bind();
    }

    glm::vec2 View::getSize()
    {
        return m_viewImpl->getSize();
    }

    glm::mat4 View::getViewMatrix()
    {
        auto size = m_viewImpl->getSize();
		glm::mat4 matrix{1.0f};
        matrix = glm::scale(matrix, glm::vec3{1.0f / size.x, 1.0f / size.y, 1.0f});
        matrix = glm::scale(matrix, glm::vec3{m_zoom, m_zoom, 1.0f});
		return matrix;
    }

    void View::setZoom(float zoom) 
	{
		m_zoom = zoom;
	}

    View::View(View&& view) noexcept : m_viewImpl{std::move(view.m_viewImpl)}, m_viewController{std::move(view.m_viewController)}
    {
        setID(view.getID());
    }

    View& View::operator=(View&& view) noexcept
    {
        m_viewImpl = std::move(view.m_viewImpl);
        m_viewController = std::move(view.m_viewController);
        setID(view.getID());
        return *this;
    }

    bool View::operator==(const View& view) const noexcept
    {
        return Resource::operator==(view);
    }
}
