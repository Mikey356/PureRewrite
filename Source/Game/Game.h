#pragma once
#include "Types/Player.h"
namespace Game
{
	void Init();
	void Update();
	float GetDeltaTime();
	Player& GetPlayer();
}