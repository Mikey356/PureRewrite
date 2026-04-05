#include "AssetLoader.h"
#include <vector>
#include <iostream>

namespace AssetManager {
    std::vector<OpenGLTexture> g_textures;

    void Init() {
        g_textures.emplace_back("Resources/Assets/backpack/diffuse.jpg");
        g_textures.emplace_back("Resources/Assets/backpack/normal.png");
        g_textures.emplace_back("Resources/Assets/backpack/roughness.jpg");
        g_textures.emplace_back("Resources/Assets/backpack/specular.jpg");

        
    }

    OpenGLTexture* GetTextureByName(const std::string& name) {
       
        for (auto& texture : g_textures)
        {
            if (texture.GetName() == name)
                return &texture;
        }

        return nullptr;
    }

    OpenGLTexture* GetTextureByIndex(int index) {

        if (index >= 0 && index < g_textures.size())
            return &g_textures[index];
        else
            std::cout << "ERROR::INVALID_OR_OUT_OF_RANGE_INDEX: " << index << std::endl;
    }
}