#pragma once

#include <boundy_box.hpp>

#include <optional>
#include <memory>

class QuadTree
{
public:
    enum class SubTreeType : size_t
    {
        LeftBottom,
        LeftTop,
        RightTop,
        RightBottom,
    };

public:
    QuadTree() = default;
    QuadTree(BoundyBox boundyBox);
    bool insert(glm::vec2 point);
    QuadTree* getChild(SubTreeType type);
    BoundyBox getAABB();

	glm::vec4 color;

private:
    void subdivide();

private:
    BoundyBox m_aabb;
    std::optional<glm::vec2> m_point;
    std::unique_ptr<QuadTree> m_leftBottom;
    std::unique_ptr<QuadTree> m_leftTop;
    std::unique_ptr<QuadTree> m_rightTop;
    std::unique_ptr<QuadTree> m_rightBottom;
};