#pragma once
#include <string>

namespace Backend
{
	bool Init(const std::string& title, int32_t width, int32_t height);
	void CleanUp();
	bool WindowShouldClose();
	void ForceCloseWindow();
	void SwapBuffersPollEvents();
	float GetGlfwTime();
	void* GetWindowPtr();
	int32_t GetCurrentWindowWidth();
	int32_t GetCurrentWindowHeight();	
}