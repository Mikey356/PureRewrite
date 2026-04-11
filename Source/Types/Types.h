#pragma once
#include <glm/common.hpp>

struct Vertex {
	glm::vec3 Position = glm::vec3(0.0f);
	glm::vec3 Normal = glm::vec3(0.0f);
	glm::vec2 UV = glm::vec2(0.0f);
	glm::vec3 Tangent = glm::vec3(0.0f);
};