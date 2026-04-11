#pragma once

#include <glad/glad.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Renderer/Types/Mesh.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

struct Model
{
public:
	
	
	Model() = default;

	Model(const std::string& path);

	void Draw();

	const std::string GetName() const { return m_name; }
private:
	void LoadModel(const std::string& path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	std::string m_name;
	std::vector<Mesh> m_meshes;
	std::string m_directory;

};