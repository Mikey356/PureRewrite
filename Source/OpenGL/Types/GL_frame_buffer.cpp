#include "GL_frame_buffer.h"
#include <glad/glad.h>
#include <iostream>

OpenGLFrameBuffer::OpenGLFrameBuffer(const std::string& name, uint32_t width, uint32_t height)
{
	glCreateFramebuffers(1, &m_handle);
	m_name = name;
	m_width = width;
	m_height = height;
}

void OpenGLFrameBuffer::BindFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
}

void OpenGLFrameBuffer::CreateColorAttachment(const std::string& name, uint32_t internalFormat)
{
	ColorAttachment& colorAttachment = m_colorAttachments.emplace_back();
	colorAttachment.m_name = name;
	colorAttachment.m_levels = 1;

	// Create OpenGL handle(ID)
	glCreateTextures(GL_TEXTURE_2D, 1, &colorAttachment.m_handle);

	// Allocate GPU memory
	glTextureStorage2D(colorAttachment.m_handle, colorAttachment.m_levels, internalFormat, m_width, m_height);

	// Set texture paramters
	glTextureParameteri(colorAttachment.m_handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(colorAttachment.m_handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(colorAttachment.m_handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(colorAttachment.m_handle, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Bind texture to framebuffer
	GLenum attachment = GL_COLOR_ATTACHMENT0 + (GLenum)(m_colorAttachments.size() - 1);
	glNamedFramebufferTexture(m_handle, attachment, colorAttachment.m_handle, 0);	
}

void OpenGLFrameBuffer::CreateDepthAttachment()
{
	m_depthAttachment.m_levels = 1;
	// Create OpenGL handle(ID)
	glCreateTextures(GL_TEXTURE_2D, 1, &m_depthAttachment.m_handle);
	
	// Allocate GPU memory
	glTextureStorage2D(m_depthAttachment.m_handle, m_depthAttachment.m_levels, GL_DEPTH32F_STENCIL8, m_width, m_height);
	
	// Set texture paramters
	glTextureParameteri(m_depthAttachment.m_handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_depthAttachment.m_handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(m_depthAttachment.m_handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_depthAttachment.m_handle, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glNamedFramebufferTexture(m_handle, GL_DEPTH_ATTACHMENT, m_depthAttachment.m_handle, 0);
}
void OpenGLFrameBuffer::CheckForErrors()
{
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "Framebuffer '" << m_name << "'failed.\n";
	}

	else {
		std::cout << "Framebuffer '" << m_name << "'succeeded.\n";
	}
}

void OpenGLFrameBuffer::Clear(const std::string& name, float r, float g, float b, float a)
{
	uint32_t  attachmentSlot = GetColorAttachmentSlot(name);
	if (attachmentSlot != 0) {
		glDrawBuffer(GetColorAttachmentSlot(name));
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	else {
		std::cout << "OpenGLFrameBuffer::Clear(..) failed'" << name << "'not found in framebuffer '" << m_name << "'\n";
	}
}

void OpenGLFrameBuffer::ClearDepth()
{
	glClear(GL_DEPTH_BUFFER_BIT);
}

void OpenGLFrameBuffer::SetViewport()
{
	glViewport(0, 0, m_width, m_height);
}


void OpenGLFrameBuffer::SetDrawBuffer(const std::string& name)
{
	uint32_t  attachmentSlot = GetColorAttachmentSlot(name);
	if (attachmentSlot != 0){
		glDrawBuffer(GetColorAttachmentSlot(name));
	}
	else {
		std::cout << "OpenGLFrameBuffer::SetDrawBuffer(..) failed'" << name << "'not found in framebuffer '" << m_name << "'\n";
	}
}

uint32_t OpenGLFrameBuffer::GetColorAttachmentHandle(const std::string& name)
{
	for (auto& attachment : m_colorAttachments)
	{
		if (name == attachment.m_name)
			return attachment.m_handle;
	}

	std::cout << "OpenGLFrameBuffer::GetColorAttachmentHandle(..) failed'" << name << "'not found in framebuffer '" << m_name << "'\n";
	return 0;
}
			
uint32_t OpenGLFrameBuffer::GetColorAttachmentSlot(const std::string& name)
{
	for (int i = 0; i < m_colorAttachments.size(); i++)
	{
		if (name == m_colorAttachments[i].m_name)
			return GL_COLOR_ATTACHMENT0 + i;
	}

	std::cout << "OpenGLFrameBuffer::GetColorAttachmentIndex(..) failed'" << name << "'not found in framebuffer '" << m_name << "'\n";
	return 0;
}
