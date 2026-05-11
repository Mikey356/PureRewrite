#include "Renderer.h"

#include "AssetManager/AssetManager.h"
#include "Backend/Backend.h"
#include "Game/Game.h"
#include "OpenGL/Types/GL_shader.h"
#include "Renderer/Types/Model.h"
#include "Types/Types.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <unordered_map>

namespace Renderer
{
	Shader g_shader;

	void Init()
	{
		g_shader.Load("Resources/OpenGL/GL_backpack.vert", "Resources/OpenGL/GL_backpack.frag");
	}
	void RenderFrame()
	{
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.412, 0.565, 0.800, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, Backend::GetCurrentWindowWidth(), Backend::GetCurrentWindowHeight());

		Player& player = Game::GetPlayer();
		Camera& camera = player.GetCamera();
		// Projection and view matrices
		glm::mat4 projection = glm::perspective(glm::radians(100.0f), (float)Backend::GetCurrentWindowWidth() / (float)Backend::GetCurrentWindowHeight(), 0.1f, 1000.0f);
		glm::mat4 view = camera.GetViewMatrix();

		g_shader.Bind();
		g_shader.SetMat4("projection", projection);
		g_shader.SetMat4("view", camera.GetViewMatrix());

		// Render game objects
		for(GameObject& gameObject : Game::GetGameObjects())
		{
			g_shader.SetMat4("model", gameObject.GetModelMatrix());
			
			Model* model = gameObject.GetModel();
			OpenGLTexture* texture = gameObject.GetTexture();

			if (texture)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texture->GetHandle());
			}

			if (model) {
				model->Draw();
			}
		}
		
	}

	void HotloadShaders()
	{
		g_shader.Hotload();
		std::cout << "Hotloaded shaders\n";
	}

	void EnableXRAY()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	}
	void DisableXRAY()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}