#include <quadtree.hpp>

QuadTree::QuadTree(BoundyBox boundyBox) : m_aabb{boundyBox}, color{(float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1.0f} {}

bool QuadTree::insert(glm::vec2 point)
{
    if (!m_aabb.containsPoint(point)) return false;
    if (!m_point && !m_leftBottom)
    {
        m_point = point;
        return true;
    }
    if (!m_leftBottom)
    {
        subdivide();
        m_leftBottom->insert(m_point.value());
        m_leftTop->insert(m_point.value());
        m_rightTop->insert(m_point.value());
        m_rightBottom->insert(m_point.value());
        m_point = std::nullopt;
    }
    if (m_leftBottom->insert(point)) return true;
    if (m_leftTop->insert(point)) return true;
    if (m_rightTop->insert(point)) return true;
    if (m_rightBottom->insert(point)) return true;
}

void QuadTree::subdivide()
{
    glm::vec2 leftBottomPos{m_aabb.m_position.x - m_aabb.m_halfSize.x / 2, m_aabb.m_position.y - m_aabb.m_halfSize.y / 2};
    glm::vec2 leftTopPos{m_aabb.m_position.x - m_aabb.m_halfSize.x / 2, m_aabb.m_position.y + m_aabb.m_halfSize.y / 2};
    glm::vec2 rightTopPos{m_aabb.m_position.x + m_aabb.m_halfSize.x / 2, m_aabb.m_position.y + m_aabb.m_halfSize.y / 2};
    glm::vec2 rightBottomPos{m_aabb.m_position.x + m_aabb.m_halfSize.x / 2, m_aabb.m_position.y - m_aabb.m_halfSize.y / 2};
    m_leftBottom = std::make_unique<QuadTree>(BoundyBox{leftBottomPos, m_aabb.m_halfSize / 2.0f});
    m_leftTop = std::make_unique<QuadTree>(BoundyBox{leftTopPos, m_aabb.m_halfSize / 2.0f});
    m_rightTop = std::make_unique<QuadTree>(BoundyBox{rightTopPos, m_aabb.m_halfSize / 2.0f});
    m_rightBottom = std::make_unique<QuadTree>(BoundyBox{rightBottomPos, m_aabb.m_halfSize / 2.0f});
}

QuadTree* QuadTree::getChild(SubTreeType type)
{
    if (!m_leftBottom) return nullptr;
    switch (type)
    {
        case SubTreeType::LeftBottom: return m_leftBottom.get();
        case SubTreeType::LeftTop: return m_leftTop.get();
        case SubTreeType::RightTop: return m_rightTop.get();
        case SubTreeType::RightBottom: return m_rightBottom.get();
    }
}

BoundyBox QuadTree::getAABB()
{
    return m_aabb;
}