#pragma once

#include <engine/resource.hpp>
#include <engine/view_impl.hpp>
#include <engine/action.hpp>

#include <memory>

namespace logicario::engine
{
    class View : virtual public Resource
    {
    public:
        using ViewImplPtr = std::unique_ptr<ViewImpl>;
        View();
        View(ViewImplPtr viewImpl, const ID& resourceID);
        void onRendererResize(int width, int height);
        void bind();
		glm::vec2 getSize();

    public:
        bool operator==(const View& view) const noexcept;
        View(View&& view) noexcept;
        View& operator=(View&& view) noexcept;
        View(const View&) = delete;
        View& operator=(const View&) = delete;

    private:
        ViewImplPtr m_viewImpl;
    };
}