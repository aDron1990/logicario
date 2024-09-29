#pragma once

#include <glm/glm.hpp>

namespace logicario::engine
{
    class Transform
    {
    public:
        Transform();
        void setPosition(glm::vec2 position);
        void setScale(glm::vec2 scale);
        glm::vec2 getPosition() const;
        glm::vec2 getScale() const;
        glm::mat4 getMatrix() const;

    private:
        void updateMatrix();

    private:
        glm::mat4 m_matrix;
        glm::vec2 m_position;
        glm::vec2 m_scale;
    };
}