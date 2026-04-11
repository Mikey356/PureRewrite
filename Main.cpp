#include "Types/Camera.h"
#include "AssetManager/AssetManager.h"
#include "Backend/Backend.h"
#include "Input/Input.h"
#include "Game/Game.h"
#include "Renderer/Renderer.h"
#include <iostream>


void LazyKeyPresses();

auto main() -> int
{
	std::cout << "\x1B[2J\x1B[HI did!\n";
	Backend::Init("PureBranch", 1280, 720);
	AssetManager::Init();
	Game::Init();
	Renderer::Init();
	Input::SetMousePosition(Backend::GetCurrentWindowWidth() / 2, Backend::GetCurrentWindowHeight() / 2);

	

	while (!Backend::WindowShouldClose())
	{
		LazyKeyPresses();
		Renderer::RenderFrame();
		Input::Update();
		Game::Update();

		Backend::SwapBuffersPollEvents();
	}

	Backend::CleanUp();
	return 0;
}

void LazyKeyPresses()
{
	if (Input::KeyPressed(PURE_KEY_ESCAPE)) Backend::ForceCloseWindow();
	if (Input::KeyPressed(PURE_KEY_H))		Renderer::HotloadShaders();
	if (Input::KeyDown(PURE_KEY_Q))			Renderer::EnableXRAY();
	if (Input::KeyDown(PURE_KEY_TAB))	    Renderer::DisableXRAY();
}
