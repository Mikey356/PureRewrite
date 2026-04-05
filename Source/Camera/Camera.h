#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// Define movement states
enum Cam_Movement
{
	FORWARD, 
	BACKWARD,
	LEFT,
	RIGHT
};


const float g_YAW = -90.0f;
const float g_PITCH = 0.0f;
const float g_SPEED = 10.0f;
const float g_SENSITIVITY = 0.2f;
const float g_ZOOM = 90.0f;

// Camera class processes input and calculate its euler angles, vectors, and matrices
class Camera
{
public:
	// cam attributes
	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_worldUp;
	// euler angles
	float m_yaw;
	float m_pitch;
	// cam controls
	float m_movementSpeed;
	float m_mouseSensitivity;
	float m_zoom;

	// constructor for cam vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = g_YAW, float pitch = g_PITCH) : m_front(glm::vec3(0.0f, 0.0f, -1.0f)), m_movementSpeed(g_SPEED), m_mouseSensitivity(g_SENSITIVITY), m_zoom(g_ZOOM)
	{
		m_position = position;
		m_worldUp = up;
		m_yaw = yaw;
		m_pitch = pitch;
		UpdateCameraVectors();
	}
	
	// constructor for cam vectors scalar values
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : m_front(glm::vec3(0.0f, 0.0f, -1.0f)), m_movementSpeed(g_SPEED), m_mouseSensitivity(g_SENSITIVITY), m_zoom(g_ZOOM)
	{
		m_position = glm::vec3(posX, posY, posZ);
		m_worldUp = glm::vec3(upX, upY, upZ);
		m_yaw = yaw;
		m_pitch = pitch;
		UpdateCameraVectors();
	}

	//returns the view matrix
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(m_position, m_position + m_front, m_up);
	}

	void ProcessKeyboard(Cam_Movement direction, float deltaTime)
	{
		float velocity = m_movementSpeed * deltaTime;
		switch (direction) {
		case FORWARD:
			m_position += m_front * velocity;
			break;
		case BACKWARD:
			m_position -= m_front * velocity;
			break;
		case RIGHT:
			m_position += m_right * velocity;
			break;
		case LEFT:
			m_position -= m_right * velocity;
			break;
		}
	}
	void ProcessMouseMovement(float x_offset, float y_offset, GLboolean constrainPitch = true)
	{
		x_offset *= m_mouseSensitivity;
		y_offset *= m_mouseSensitivity;

		m_yaw += x_offset;
		m_pitch += y_offset;

		// make sure the pitch isn't out of bounds so the screen doesn't flip
		if (constrainPitch)
		{
			if (m_pitch > 89.0f)
				m_pitch = 89.0f;
			if (m_pitch < -89.0f)
				m_pitch = -89.0f;
		}

		// update cam vectors using the angles
		UpdateCameraVectors();
	}

	void ProcessMouseScroll(float y_offset)
	{
		m_zoom -= (float)y_offset;
		if (m_zoom < 1.0f)
			m_zoom = 1.0f;
		if (m_zoom > 90.0f)
			m_zoom = 90.0f;
	}

private:
	// calculate the front cam vector from the camera's updated angles
	void UpdateCameraVectors()
	{
		// calculate the new front vector
		glm::vec3 front;
		front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		front.y = sin(glm::radians(m_pitch));
		front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_front = glm::normalize(front);

		// recalculate the right and up vector
		m_right = glm::normalize(glm::cross(m_front, m_worldUp));
		m_up = glm::normalize(glm::cross(m_right, m_front));
	}
};