#include "Game.h"
#include "Backend/Backend.h"
#include "Types/Constants.h"
#include <vector>			

namespace Game
{
	Player g_player;
	float g_deltaTime = 0.0f;
	float g_timeFrame = 0.0f;
	float g_PreviousTimeFrame = 0.0f;

	std::vector<GameObject> g_gameObjects;

	void Init() 
	{
		glm::vec3 position(0.0f, 1.6f, 3.0f);
		glm::vec3 rotation(0.0f, 0.0f, 0.0f);
		g_player.Init(position, rotation);
	
		GameObject& backpack = g_gameObjects.emplace_back();
		backpack.SetModel("backpack"); 
		backpack.SetTexture("diffuse");
		backpack.SetScale(0.5f);
		backpack.SetPosition(glm::vec3(0.0f, 1.0f, 2.0f));
		backpack.SetRotation(glm::vec3(0.0f, PURE_PI, 0.0f));

		GameObject& gun = g_gameObjects.emplace_back();
		gun.SetModel("Smoking_gun");
		gun.SetTexture("internal_ground_ao_texture");
		gun.SetScale(0.02f);
		gun.SetPosition(glm::vec3(0.0f, 1.3f, -1.5f));

		GameObject& cube = g_gameObjects.emplace_back();
		cube.SetModel("Cube");
		cube.SetTexture("Default_Default_Roughness");
		cube.SetScale(glm::vec3(5.0f, 2.6f, 7.0f));
		cube.SetPosition(glm::vec3(0.0f, 1.2f, 0.0f));
		
	}
	
	void Update()
	{
		g_timeFrame = static_cast<float>(Backend::GetGlfwTime());
		g_deltaTime = g_timeFrame - g_PreviousTimeFrame;
		g_PreviousTimeFrame = g_timeFrame;

		g_player.Update(g_deltaTime);

		for (GameObject& gameObject : g_gameObjects) {
			gameObject.Update(g_deltaTime);
		}
		for (GameObject& gameObject : g_gameObjects) {
			Model* model = gameObject.GetModel();
			if (!model) continue;
			if (model->GetName() == "Smoking_gun")
			{
				glm::vec3 rotation = gameObject.GetRotation();
				rotation.y += 3.0f * g_deltaTime;
				gameObject.SetRotation(rotation);
			}
			gameObject.Update(g_deltaTime);
		}

	}
				
	Player& GetPlayer()	{
		return g_player;
	}

	float GetDeltaTime() {
		return g_deltaTime;
	}

	std::vector<GameObject>& GetGameObjects(){
		return g_gameObjects;
	}
}