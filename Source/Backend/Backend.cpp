#include "Backend.h"
#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>

// Always select the dedicated GPU
extern "C" 
{
	__declspec(dllexport) unsigned __int32 AmdPowerXpressRequestHighPerformance = 0x1;
	__declspec(dllexport) unsigned __int32 NvOptimusEnablement = 0x1;
}
namespace Backend
{
	void Framebuffer_SizeCallBack(GLFWwindow* window, int width, int height);

	GLFWwindow* g_window = nullptr;
	GLFWmonitor* g_monitor = nullptr;
	const GLFWvidmode* g_mode = nullptr;
	int32_t g_currentWindowWidth = 0;
	int32_t g_currentWindowHeight = 0;
	int32_t g_fullscreenWidth = 0;
	int32_t g_fullscreenHeight = 0;
	int32_t g_windowedWidth = 0;
	int32_t g_windowedHeight = 0;
	WindowMode g_windowMode = WindowMode::WINDOWED;

	bool Init(const std::string& title, int32_t width, int32_t height)
	{
		glfwInit();

		g_monitor = glfwGetPrimaryMonitor();
		g_mode = glfwGetVideoMode(g_monitor);
		
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		glfwWindowHint(GLFW_RED_BITS, g_mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, g_mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, g_mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, g_mode->refreshRate);

		g_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (g_window == NULL)
		{
			std::cout << "Failed to create window" << std::endl;
			return false;
		}
		glfwMakeContextCurrent(g_window);
		glfwSetFramebufferSizeCallback(g_window, Framebuffer_SizeCallBack);


		glfwSetInputMode(g_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		
		g_fullscreenWidth = g_mode->width;
		g_fullscreenHeight = g_mode->height; 

		g_windowedWidth = width;
		g_windowedHeight = height;

		SetWindowMode(WindowMode::WINDOWED);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return false;
		}

		// print specs
		GLint major, minor;
		glGetIntegerv(GL_MAJOR_VERSION, &major);
		glGetIntegerv(GL_MINOR_VERSION, &minor);
		const GLubyte* vendor = glGetString(GL_VENDOR);
		const GLubyte* renderer = glGetString(GL_RENDERER);
		std::cout << "\nGPU: " << renderer << "\n";
		std::cout << "\nGL version: " << major << "." << minor << "\n";

		return true;
	}

	float GetGlfwTime()
	{
		return (float)glfwGetTime();
	}

	void CleanUp() {
		glfwTerminate();
	}
	
	void ToggleFullScreen()
	{
		if (g_windowMode == WindowMode::FULLSCREEN) {
			g_windowMode = WindowMode::WINDOWED;
		}
		else
			g_windowMode = WindowMode::FULLSCREEN;
	
		SetWindowMode(g_windowMode);
	}

	void SetWindowMode(WindowMode windowMode)
	{
		if (windowMode == WindowMode::FULLSCREEN) 
		{
			g_currentWindowWidth = g_fullscreenWidth;
			g_currentWindowHeight = g_fullscreenHeight;
		}
		else
		{
			g_currentWindowWidth = g_windowedWidth;
			g_currentWindowHeight = g_windowedHeight;
		}

		glfwSetWindowPos(g_window, 0, 0);
		glfwSetWindowMonitor(g_window, nullptr, 0, 0, g_currentWindowWidth, g_currentWindowHeight, g_mode->refreshRate);
	}
	bool WindowShouldClose() {
		return glfwWindowShouldClose(g_window);
	}

	void ForceCloseWindow()
	{
		glfwSetWindowShouldClose(g_window, true);
	}

	void SwapBuffersPollEvents()
	{
		glfwSwapBuffers(g_window);
		glfwPollEvents();
	}

	void* GetWindowPtr() {
		return g_window;
	}
	int32_t GetCurrentWindowWidth() {
		return g_currentWindowWidth;
	}
	int32_t GetCurrentWindowHeight() {
		return g_currentWindowHeight;
	}
	void Framebuffer_SizeCallBack(GLFWwindow* window, int width, int height)
	{
		g_currentWindowHeight = height;
		g_currentWindowWidth  = width;
	}


}