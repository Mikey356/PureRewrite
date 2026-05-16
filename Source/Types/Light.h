#pragma once
#include <glm/glm.hpp>


struct Light
{
	Light() = default;
	void SetPosition(const glm::vec3& position) { m_position = position; }
	void SetColor(const glm::vec3& color)		{ m_color = color; }
	void SetRadius(float radius)				{ m_radius = radius; }
	void SetStrength(float strength)			{ m_strength = strength; }

	const glm::vec3& GetPosition() const		{ return m_position; }
	const glm::vec3& GetColor()	const			{ return m_color; }
	float GetRadius(float radius) const			{ return m_radius; }
	float GetStrength(float strength) const		{ return m_strength; }

private:
	glm::vec3 m_position = glm::vec3(0.0f);
	glm::vec3 m_color = glm::vec3(1.0f);
	float m_strength = 1.0f;
	float m_radius = 1.0f;
};