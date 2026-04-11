#include "AssetManager.h"
#include "Util/Util.h"
#include <vector>
#include <iostream>


namespace AssetManager 
{
    std::vector<OpenGLTexture> g_textures;
    std::vector<Model> g_models;

    void Init()
    {
        // Load models
        for (const std::string& filePath : Util::GetFilePaths("Resources/Models"))
        {
           
            g_models.emplace_back(filePath);
        }

        // Load textures
        for (const std::string& filePath : Util::GetFilePaths("Resources/Textures"))
        {
            g_textures.emplace_back(filePath);
        }

        
    }

    OpenGLTexture* GetTextureByName(const std::string& name)
    {
       
        for (auto& texture : g_textures)
        {
            if (texture.GetName() == name)
                return &texture;
        }

        return nullptr;
    }
    Model* GetModelByName(const std::string& name)
    {
       
        for (auto& model : g_models)
        {
            if (model.GetName() == name)
                return &model;
        }

        return nullptr;
    }

    Model* GetModelByIndex(int index)
    {
        // TO DO: check if this index is out of bounds
            return &g_models[index];
    }
    OpenGLTexture* GetTextureByIndex(int index)
    {
        // TO DO: check if this index is out of bounds
            return &g_textures[index];
    }


}