#pragma once

#include "Mesh.h"

#include <stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>


class Model
{
public:
	

	std::vector<Mesh> m_meshes;
	std::string m_directory;
	bool m_gammaCorrection;

	Model(std::string const& path, bool gamma = false) : m_gammaCorrection(gamma)
	{
		LoadModel(path);
	}

	void Draw(Shader& shader)
	{
		for (unsigned int i = 0; i < m_meshes.size(); i++)
			m_meshes[i].Draw(shader);
	}

private:

	// loads a model and stores the model's meshes in the meshes vector.
	void LoadModel(std::string const& path)
	{
		// read file through ASSIMP
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
			return;
		}
		// get the directory path of the file path
		m_directory = path.substr(0, path.find_last_of('/'));

		// process ASSIMP's root node recursively
		ProcessNode(scene->mRootNode, scene);
	}

	
	void ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_meshes.push_back(ProcessMesh(mesh, scene));
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		// data
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		

		// iterate through each of the mesh's vertices
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			glm::vec3 vector;
			// position
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.m_position = vector;

			// normals
			if (mesh->HasNormals())
			{
				vector.x = mesh->mNormals[i].x;
				vector.y = mesh->mNormals[i].y;
				vector.z = mesh->mNormals[i].z;
				vertex.m_normal = vector;
			}

			// texture coordinates
			if (mesh->mTextureCoords[0])
			{
				glm::vec2 vec;


				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.m_texCoords = vec;

				vector.x = mesh->mTangents[i].x;
				vector.y = mesh->mTangents[i].y;
				vector.z = mesh->mTangents[i].z;
				vertex.m_tangent = vector;

				vector.x = mesh->mBitangents[i].x;
				vector.y = mesh->mBitangents[i].y;
				vector.z = mesh->mBitangents[i].z;
				vertex.m_Bitangent = vector;
			}
			else
				vertex.m_texCoords = glm::vec2(0.0f, 0.0f);

			vertices.push_back(vertex);
		}

		// iterate through each of the mesh's faces and get the vertex indices of each face
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			// get all indices of face and store them in the indices vector
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}


	

		

		// return a mesh object created from the mesh data 
		return Mesh(vertices, indices);
	}


	
};