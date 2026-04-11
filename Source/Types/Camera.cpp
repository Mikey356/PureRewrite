#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <iostream>
void Camera::Update()
{
	glm::mat4 m = glm::translate(glm::mat4(1.0f), m_position);

	m *= glm::mat4_cast(glm::quat(m_rotation));
	m_inverseViewMatrix = m;
	m_viewMatrix = glm::inverse(m_inverseViewMatrix);

	m_forward = -glm::vec3(m_inverseViewMatrix[2]);
	m_right = glm::vec3(m_inverseViewMatrix[0]);
	m_up = glm::vec3(m_inverseViewMatrix[1]);

}

void Camera::SetPosition(const glm::vec3& positon) {
	m_position = positon;
}
void Camera::SetRotation(const glm::vec3& rotation) {
	m_rotation = rotation;
}
