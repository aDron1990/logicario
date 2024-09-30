#pragma once

#include <glm/glm.hpp>

#include <memory.h>

class BoundyBox
{
public:
    BoundyBox(glm::vec2 position, glm::vec2 halfSize);
    bool containsPoint(glm::vec2 point);
    bool intersectBoundyBox(BoundyBox boundyBox);

	glm::vec2 m_position;
    glm::vec2 m_halfSize;

private:
    bool inRange(float min, float max, float value);

};