
#pragma once
#include "OpenGL/Types/Texture.h"
#include <string>

namespace AssetManager {
    void Init();
    OpenGLTexture* GetTextureByName(const std::string& name);
    OpenGLTexture* GetTextureByIndex(int index);
}