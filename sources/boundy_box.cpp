#include <boundy_box.hpp>

BoundyBox::BoundyBox(glm::vec2 position, glm::vec2 halfSize) : m_position{position}, m_halfSize{halfSize} {}

bool BoundyBox::containsPoint(glm::vec2 point)
{
    float left = m_position.x - m_halfSize.x;
    float right = m_position.x + m_halfSize.x;
    float top = m_position.y - m_halfSize.y;
    float bottom = m_position.y + m_halfSize.y;
    return inRange(left, right, point.x) && inRange(top, bottom, point.y);
}

bool BoundyBox::intersectBoundyBox(BoundyBox boundyBox)
{
    float left = m_position.x - m_halfSize.x;
    float right = m_position.x + m_halfSize.x;
    float top = m_position.y - m_halfSize.y;
    float bottom = m_position.y + m_halfSize.y;
    float otherLeft = boundyBox.m_position.x - boundyBox.m_halfSize.x;
    float otherRight = boundyBox.m_position.x + boundyBox.m_halfSize.x;
    float otherTop = boundyBox.m_position.y - boundyBox.m_halfSize.y;
    float otherBottom = boundyBox.m_position.y + boundyBox.m_halfSize.y;
    return inRange(left, right, otherLeft) || inRange(left, right, otherRight) || inRange(top, bottom, otherTop) || inRange(top, bottom, otherBottom);
}

bool BoundyBox::inRange(float min, float max, float value)
{
    return value > min && value < max;
}