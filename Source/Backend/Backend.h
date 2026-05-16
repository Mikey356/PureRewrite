#pragma once
#include <string>

enum struct WindowMode
{
	WINDOWED, 
	FULLSCREEN
};

namespace Backend
{
	bool Init(const std::string& title, int32_t width, int32_t height);
	void CleanUp();

	void ForceCloseWindow();
	void ToggleFullScreen();
	void SetWindowMode(WindowMode mode);
	void SwapBuffersPollEvents();
	
	bool WindowShouldClose();
	float GetGlfwTime();
	void* GetWindowPtr();
	int32_t GetCurrentWindowWidth();
	int32_t GetCurrentWindowHeight();	
}