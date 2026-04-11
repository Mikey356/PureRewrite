#include "Game.h"
#include "Backend/Backend.h"
namespace Game
{
	Player g_player;
	float g_deltaTime = 0.0f;
	float g_timeFrame = 0.0f;
	float g_PreviousTimeFrame = 0.0f;

	void Init() {
		glm::vec3 position(0.0f, 0.0f, 3.0f);
		glm::vec3 rotation(0.0f, 0.0f, 0.0f);
		g_player.Init(position, rotation);
	}
	void Update() 
	{
		g_timeFrame = static_cast<float>(Backend::GetGlfwTime());
		g_deltaTime = g_timeFrame- g_PreviousTimeFrame;
		g_PreviousTimeFrame = g_timeFrame;

		g_player.Update(g_deltaTime);
	}
				
	Player& GetPlayer()	{
		return g_player;
	}

	float GetDeltaTime() {
		return g_deltaTime;
	}
}