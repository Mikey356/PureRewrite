#pragma once
#include <glad/glad.h>
#include <string>

struct OpenGLTexture {
	OpenGLTexture() = default;
	OpenGLTexture(const std::string& path);

	GLuint GetHandle() const { return m_handle; }
	GLint GetWidth() const { return m_width; }
	GLint GetHeight() const { return m_height; }
	GLint GetChannelCount() const { return m_channelCount; }
	const std::string& GetName() const { return m_name; }

private:
	GLuint m_handle = 0;
	GLint m_width = 0;
	GLint m_height = 0;
	GLint m_channelCount = 0;
	std::string m_name;

};