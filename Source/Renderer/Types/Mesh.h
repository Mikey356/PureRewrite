#pragma once
#include "Types/Types.h"
#include <string>
#include <vector>
#include <glad/glad.h>

struct Mesh
{
public:
	
	Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

	void Draw();

private:
	GLuint m_vao = 0; 
	GLuint m_vbo = 0;
	GLuint m_ebo = 0;
	GLsizei m_vertexCount = 0;
	GLsizei m_indexCount = 0;
};