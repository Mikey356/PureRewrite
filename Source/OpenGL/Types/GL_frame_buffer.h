#pragma once
#include <cstdint>
#include <string>
#include <vector>

struct ColorAttachment
{
	uint32_t m_handle = 0;
	uint32_t m_levels = 0;
	std::string m_name;
};
struct DepthAttachment
{
	uint32_t m_handle = 0;
	uint32_t m_levels = 0;
};

struct OpenGLFrameBuffer
{
	OpenGLFrameBuffer() = default;
	OpenGLFrameBuffer(const std::string& name, uint32_t width, uint32_t height);
	
	void BindFrameBuffer();
	void CreateColorAttachment(const std::string& name, uint32_t format);
	void CreateDepthAttachment();
	void Clear(const std::string& name, float r, float g, float b, float a);
	void ClearDepth();
	void SetViewport();
	void SetDrawBuffer(const std::string& name);
	void CheckForErrors();
	
	uint32_t GetColorAttachmentHandle(const std::string& name);
	uint32_t GetColorAttachmentSlot(const std::string& name);

	uint32_t GetHandle() const { return m_handle; }
	uint32_t GetWidth() const { return m_width; }
	uint32_t GetHeight() const { return m_height; }
	
private:
	std::string m_name;
	uint32_t m_handle = 0;
	uint32_t m_width = 0;
	uint32_t m_height = 0;
	std::vector<ColorAttachment> m_colorAttachments;
	DepthAttachment m_depthAttachment;
};