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
	int32_t g_currentWindowWidth = 0;
	int32_t g_currentWindowHeight = 0;
	bool Init(const std::string& title, int32_t width, int32_t height)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		g_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (g_window == NULL)
		{
			std::cout << "Failed to create window" << std::endl;
			return false;
		}
		glfwMakeContextCurrent(g_window);
		glfwSetFramebufferSizeCallback(g_window, Framebuffer_SizeCallBack);


		glfwSetInputMode(g_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		
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
		g_currentWindowWidth  = width;
		g_currentWindowHeight = height;
		return true;
	}

	float GetGlfwTime()
	{
		return (float)glfwGetTime();
	}
	void CleanUp() {
		glfwTerminate();
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