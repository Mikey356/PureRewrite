#include "Input.h"
#include "Backend/Backend.h"
#include <glad/glad.h>
#include <glfw3.h>
namespace Input 
{
	bool g_keyDown[348];
	bool g_keyDownPrevious[348];
	bool g_leftMouseDownPrevious = false;
	bool g_leftMouseDown = false;
	bool g_rightMouseDownPrevious= false;
	bool g_rightMouseDown = false;
	double g_mousePosX = 0;
	double g_mousePosY = 0;
	double g_mousePreviousPosX = 0;
	double g_mousePreviousPosY = 0;
	double g_mousePosOffsetX = 0;
	double g_mousePosOffsetY = 0;
	void Update()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Backend::GetWindowPtr());
		if (!window) return;

		// Keyboard
		for (int i = 32; i < 348; ++i)
		{
			g_keyDownPrevious[i] = g_keyDown[i];
			g_keyDown[i] = glfwGetKey(window, i) == GLFW_PRESS;
		}
		
		//Mouse buttons
		g_leftMouseDownPrevious = g_leftMouseDown;
		g_leftMouseDown = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);
		g_rightMouseDownPrevious = g_rightMouseDown;
		g_rightMouseDown = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS);
	
		
		
		// Mouse/Cursor position coordinates
		g_mousePreviousPosX = g_mousePosX;
		g_mousePreviousPosY = g_mousePosY;
		glfwGetCursorPos(window, &g_mousePosX, &g_mousePosY);
		
		// Mouse offset
		g_mousePosOffsetX = g_mousePosX - g_mousePreviousPosX;
		g_mousePosOffsetY = g_mousePreviousPosY - g_mousePosY;
	}
	
	void SetMousePosition(int x, int y)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Backend::GetWindowPtr());
		glfwSetCursorPos(window, (double)x, (double)y);
		g_mousePosX = (double)x;
		g_mousePosY = (double)y;
		g_mousePreviousPosX = (double)x;
		g_mousePreviousPosY = (double)y;
		g_mousePosOffsetX = 0;
		g_mousePosOffsetY = 0;
	}
	bool KeyDown(int keyCode) {
		return g_keyDown[keyCode];
	}
	
	bool KeyPressed(int keyCode) {
		return g_keyDown[keyCode] && !g_keyDownPrevious[keyCode];
	}
	
	bool LeftMouseDown() {
		return g_leftMouseDown;
	}
	
	bool LeftMousePressed() {
		return g_leftMouseDown && !g_leftMouseDownPrevious;
	}
	bool RightMouseDown() {
		return g_rightMouseDown;
	}
	
	bool RightMousePressed() {
		return g_rightMouseDown && !g_rightMouseDownPrevious;
	}

	int GetMousePosX() {
		return (int)g_mousePosX;
	}

	int GetMousePosY() {
		return (int)g_mousePosY;
	}
	int GetMouseOffsetPosX() {
		return (int)g_mousePosOffsetX;
	}

	int GetMouseOffsetPosY() {
		return (int)g_mousePosOffsetY;
	}
}