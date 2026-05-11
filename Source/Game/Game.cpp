#include "Game.h"
#include "Backend/Backend.h"
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
		glm::vec3 position(0.0f, 0.0f, 3.0f);
		glm::vec3 rotation(0.0f, 0.0f, 0.0f);
		g_player.Init(position, rotation);
	
		GameObject& backpack = g_gameObjects.emplace_back();
		backpack.SetModel("backpack"); 
		backpack.SetTexture("diffuse");
		backpack.SetScale(1.0f);
		backpack.SetPosition(glm::vec3(0.0f, 0.0f, -2.0f));

		GameObject& gun = g_gameObjects.emplace_back();
		gun.SetModel("Smoking_gun");
		gun.SetTexture("wood");
		gun.SetTexture("wood rough");
		gun.SetTexture("wood nor");
		gun.SetTexture("other material");
		gun.SetTexture("other material rough");
		gun.SetTexture("other material nor");
		gun.SetTexture("internal_ground_ao_texture");
		gun.SetTexture("brass");
		gun.SetTexture("brass rough");
		gun.SetTexture("brass nor");
		gun.SetTexture("basic steel");
		gun.SetTexture("basic steel rough");
		gun.SetScale(0.1f);
		gun.SetPosition(glm::vec3(-10.0f, 0.0f, 0.0f));

		GameObject& house = g_gameObjects.emplace_back();
		house.SetModel("house");
		house.SetTexture("HouseLayout_CLR.tga");
		house.SetScale(0.01f);
		house.SetPosition(glm::vec3(-18.0f, -2.0f, 0.0f));

		
	}
	
	void Update() 
	{
		g_timeFrame = static_cast<float>(Backend::GetGlfwTime());
		g_deltaTime = g_timeFrame- g_PreviousTimeFrame;
		g_PreviousTimeFrame = g_timeFrame;

		g_player.Update(g_deltaTime);

		for (GameObject& gameObject : g_gameObjects){
			gameObject.Update(g_deltaTime);
		}
		
		for (GameObject& gameObject : g_gameObjects)
		{
			Model* model = gameObject.GetModel();
			if (!model) continue;

			if (model->GetName() == "Smoking_gun")
			{
				glm::vec3 rotation = gameObject.GetRotation();
				rotation.y += 4.0f * g_deltaTime;
				gameObject.SetRotation(rotation);
			}

			if (model->GetName() == "house")
			{
				glm::vec3 rotation = gameObject.GetRotation();
				rotation.x += 2.0f * g_deltaTime;
				gameObject.SetRotation(rotation);
			}

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