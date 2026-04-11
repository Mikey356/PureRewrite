#pragma once
#include "Camera.h"

struct Player
{
	Player() = default;
	void Init(const glm::vec3& initialPosition, const glm::vec3& initialRotation);
	void Update(float deltaTime);
	void SetPosition(const glm::vec3& positon);
	void SetRotation(const glm::vec3& rotation);

	const glm::vec3& GetPosition() { return m_position; }
	const glm::vec3& GetRotation() { return m_rotation; }
	Camera& GetCamera()  { return m_camera; }
private:
	Camera m_camera;
	glm::vec3 m_position = glm::vec3(0.0f);
	glm::vec3 m_rotation = glm::vec3(0.0f);
	float m_movementSpeed = 5.0f;
};