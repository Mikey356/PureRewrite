#pragma once
#include "keycodes.h"
namespace Input
{
	void Update();
	void SetMousePosition(int x, int y);
	bool KeyDown(int keyCode);
	bool KeyPressed(int keyCode);	
	bool LeftMouseDown();
	bool LeftMousePressed();	
	bool RightMouseDown();
	bool RightMousePressed();	
	int GetMousePosX();
	int GetMousePosY();
	int GetMouseOffsetPosX();
	int GetMouseOffsetPosY();
}