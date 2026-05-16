#pragma once
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Constants.h"

struct Vertex {
	glm::vec3 Position = glm::vec3(0.0f);
	glm::vec3 Normal = glm::vec3(0.0f);
	glm::vec2 UV = glm::vec2(0.0f);
	glm::vec3 Tangent = glm::vec3(0.0f);
};


struct Transform
{
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 rotation = glm::vec3(0.0f);
	glm::vec3 scale	= glm::vec3(0.0f);


	glm::mat4 ToMat4()
	{
		glm::mat4 mat = glm::translate(glm::mat4(1.0f), position);
		mat *= glm::mat4_cast(glm::quat(rotation));
		mat = glm::scale(mat, scale);
		return mat;
	}
};