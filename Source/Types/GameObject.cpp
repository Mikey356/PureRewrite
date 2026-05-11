#include "GameObject.h"
#include "AssetManager/AssetManager.h"

void GameObject::Update(float deltaTime)
{
	m_modelMatrix = m_transform.ToMat4();
}

void GameObject::SetModel(const std::string& modelName)
{
	Model* model = AssetManager::GetModelByName(modelName);
	if (!model)
	{
		std::cout << "GameObject::SetModel(..) failed because'" << modelName << "'not found\n";
		return;
	}
	m_model = model;
}

void GameObject::SetTexture(const std::string& textureName)
{
	OpenGLTexture* texture = AssetManager::GetTextureByName(textureName);
	if (!texture)
	{
		std::cout << "GameObject::SetTexture(..) failed because'" << textureName << "'not found\n";
		return;
	}
	m_texture = texture;
}