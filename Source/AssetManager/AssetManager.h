
#pragma once
#include "OpenGL/Types/GL_Texture.h"
#include "Renderer/Types/Model.h"
#include <string>

namespace AssetManager {
    void Init();
    OpenGLTexture* GetTextureByName(const std::string& name);
    OpenGLTexture* GetTextureByIndex(int index);
    Model* GetModelByName(const std::string& name);
    Model* GetModelByIndex(int index);
}