#pragma once
#include "Types/Player.h"
#include "Types/GameObject.h"

namespace Game
{
	void Init();
	void Update();
	float GetDeltaTime();
	Player& GetPlayer();
	std::vector<GameObject>& GetGameObjects();
}