#pragma once
#include <string>
#include <glad/glad.h>
#include <glfw3.h>
namespace Backend
{
	bool Init(const std::string& title, int width, int height);
	bool WindowShouldClose();
	void SwapBuffersPollEvents();
	void CleanUp();
	GLFWwindow* GetWindowPtr();
}