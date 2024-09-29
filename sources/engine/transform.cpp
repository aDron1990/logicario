#include <engine/transform.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace logicario::engine
{
    Transform::Transform() : m_matrix{1.0f}, m_position{0.0f, 0.0f}, m_scale{1.0f, 1.0f} 
	{
		updateMatrix();
	}

	void Transform::updateMatrix()
	{
		m_matrix = glm::mat4{1.0f};
		m_matrix = glm::translate(m_matrix, glm::vec3{m_position, 0.0f});
		m_matrix = glm::scale(m_matrix, glm::vec3(m_scale, 1.0f));
	}

	void Transform::setPosition(glm::vec2 position)
	{
		m_position = position;
		updateMatrix(); 
	}

	void Transform::setScale(glm::vec2 scale)
	{
		m_scale = scale;
		updateMatrix(); 
	}

	glm::vec2 Transform::getPosition() const
	{
		return m_position;
	}

	glm::vec2 Transform::getScale() const
	{
		return m_scale;
	}

	glm::mat4 Transform::getMatrix() const
	{
		return m_matrix;
	}
}