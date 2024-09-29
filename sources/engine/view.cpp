#include <engine/view.hpp>

namespace logicario::engine
{
    View::View() : m_viewImpl{nullptr} {}
    View::View(ViewImplPtr viewImpl, const ID& resourceID) : Resource{resourceID}, m_viewImpl{std::move(viewImpl)} {}

    void View::onRendererResize(int width, int height)
    {
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

    View::View(View&& view) noexcept : m_viewImpl{std::move(view.m_viewImpl)}
    {
        setID(view.getID());
    }

    View& View::operator=(View&& view) noexcept
    {
        m_viewImpl = std::move(view.m_viewImpl);
        setID(view.getID());
        return *this;
    }

    bool View::operator==(const View& view) const noexcept
    {
        return Resource::operator==(view);
    }
}
