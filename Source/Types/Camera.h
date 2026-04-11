#pragma once
#include <glm/glm.hpp>

struct Camera
{
	Camera() = default;
	void Update();
	void SetPosition(const glm::vec3& position);
	void SetRotation(const glm::vec3& rotation);
	const glm::mat4& GetViewMatrix() const		  { return m_viewMatrix; }
	const glm::mat4& GetInverseViewMatrix() const { return m_inverseViewMatrix; }
	const glm::vec3& GetForward() const			  { return m_forward; }
	const glm::vec3& GetRight() const			  { return m_right; }
	const glm::vec3& GetUp() const				  { return m_up; }
	const glm::vec3& GetPosition() const		  { return m_position; }
	const glm::vec3& GetRotation() const		  { return m_rotation;  }
private:
	glm::vec3 m_position = glm::vec3(0.0f);
	glm::vec3 m_rotation = glm::vec3(0.0f); // X is pitch. Y is yaw.
	glm::mat4 m_viewMatrix = glm::mat4(1.0f);	
	glm::mat4 m_inverseViewMatrix = glm::mat4(1.0f);
	glm::vec3 m_forward = glm::vec3(0.0f);
	glm::vec3 m_right = glm::vec3(0.0f);
	glm::vec3 m_up = glm::vec3(0.0f);
};