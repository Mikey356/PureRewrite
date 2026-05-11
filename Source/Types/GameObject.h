#pragma once
#include <string>
#include "Renderer/Types/Model.h"
#include "OpenGL/Types/GL_Texture.h"
#include "Types/Types.h"

struct GameObject
{
	void Update(float deltaTime);
	void SetModel(const std::string& modelName);
	void SetTexture(const std::string& textureName);

	void SetPosition(const glm::vec3& position) { m_transform.position = position; }
	void SetRotation(const glm::vec3& rotation) { m_transform.rotation = rotation; }
	void SetScale(const glm::vec3& scale)		{ m_transform.scale = scale; }
	void SetScale(float scale)					{ m_transform.scale = glm::vec3(scale); }


	Model* GetModel() const						{ return m_model; }
	OpenGLTexture* GetTexture() const			{ return m_texture; }
	const glm::vec3& GetPosition() const		{ return m_transform.position; }
	const glm::vec3& GetRotation() const		{ return m_transform.rotation; }
	const glm::vec3& GetScale() const			{ return m_transform.scale; }
	const glm::mat4& GetModelMatrix() const		{ return m_modelMatrix; }

private:
	Model* m_model = nullptr;
	OpenGLTexture* m_texture = nullptr;
	Transform m_transform;
	glm::mat4 m_modelMatrix= glm::mat4(1.0f);
};