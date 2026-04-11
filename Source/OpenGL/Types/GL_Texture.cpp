#include "GL_Texture.h"
#include <stb_image.h>
#include <iostream>
#include <filesystem>
#include <fstream>
OpenGLTexture::OpenGLTexture(const std::string& path)
{
	stbi_set_flip_vertically_on_load(true);
	m_name = std::filesystem::path(path).stem().string();
	
	
	glGenTextures(1, &m_handle);


	unsigned char* data = stbi_load(path.c_str(), &m_width, &m_height, &m_channelCount, 0);
	if (data)
	{
		GLenum format;
		if (m_channelCount == 1)
			format = GL_RED;
		else if (m_channelCount == 3)
			format = GL_RGB;
		else if (m_channelCount == 4)
			format = GL_RGBA;
		glBindTexture(GL_TEXTURE_2D, m_handle);
		glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
		std::cout << "Loaded texture: " << path << std::endl;
		
	}
	else
	{
		std::cout << "Failed to load: " << path << std::endl;
		stbi_image_free(data);
	}

	
}

