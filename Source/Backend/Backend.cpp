#include "Backend.h"
#include <iostream>

namespace Backend
{
	void Framebuffer_SizeCallBack(GLFWwindow* window, int width, int height);

	GLFWwindow* g_window = nullptr;
	bool Init(const std::string& title, int width, int height)
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

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return false;
		}

		return true;
	}
	void CleanUp()
	{
		glfwTerminate();
	}
	bool WindowShouldClose()
	{
		return glfwWindowShouldClose(g_window);
	}

	void SwapBuffersPollEvents()
	{
		glfwSwapBuffers(g_window);
		glfwPollEvents();
	}

	GLFWwindow* GetWindowPtr()
	{
		return g_window;
	}

	void Framebuffer_SizeCallBack(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}


}