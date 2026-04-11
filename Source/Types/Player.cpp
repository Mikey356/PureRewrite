#include "Player.h"
#include "Input/Input.h"
void Player::Init(const glm::vec3& initialPosition, const glm::vec3& initialRotation)
{
	SetPosition(initialPosition);
	m_camera.SetRotation(initialRotation);
}
void Player::Update(float deltaTime)
{
	// Movement
	float velocity = m_movementSpeed * deltaTime;

	// Compute front vector to restrict player move at ground level (XZ plane)
	glm::vec3 front = glm::normalize(m_camera.GetForward() * glm::vec3(1.0f, 0.0f, 1.0f)); 
	if(Input::KeyDown(PURE_KEY_W)) m_position += (front * velocity);
	if(Input::KeyDown(PURE_KEY_S)) m_position -= (front * velocity);
	if(Input::KeyDown(PURE_KEY_A)) m_position -= (m_camera.GetRight() * velocity);
	if(Input::KeyDown(PURE_KEY_D)) m_position += (m_camera.GetRight() * velocity);
	
	float m_mouseSensititvity = 0.002f;
	m_rotation.x += (float)Input::GetMouseOffsetPosY() * m_mouseSensititvity;
	m_rotation.y += (float)-Input::GetMouseOffsetPosX() * m_mouseSensititvity;

	// Restrict pitch
	m_rotation.x = glm::clamp(m_rotation.x, -1.5f, 1.5f);
	//Camera
	m_camera.SetPosition(m_position);
	m_camera.SetRotation(m_rotation);
	m_camera.Update();
}

void Player::SetPosition(const glm::vec3& positon) {
	m_position = positon;
}