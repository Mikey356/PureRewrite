#pragma once
#include "Types/Types.h"
#include <string>
#include <vector>
#include <glad/glad.h>

struct Mesh
{
public:
	
	Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices);

	void Draw();

private:
	GLuint m_vao = 0; 
	GLuint m_vbo = 0;
	GLuint m_ebo = 0;
	std::vector<Vertex> m_vertices;
	std::vector<uint32_t> m_indices;

	void SetupMesh();
};