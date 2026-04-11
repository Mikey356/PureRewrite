#include "Renderer.h"

#include "AssetManager/AssetManager.h"
#include "Backend/Backend.h"
#include "Game/Game.h"
#include "OpenGL/Types/GL_shader.h"
#include "Renderer/Types/Model.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <unordered_map>

namespace Renderer
{
	Shader g_backpackShader;
	//Model g_backpack;

	void Init()
	{
		g_backpackShader.Load("Resources/OpenGL/GL_backpack.vert", "Resources/OpenGL/GL_backpack.frag");
		//g_backpack = Model("Resources/Models/backpack.obj");
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

		// Model matrix
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));

		g_backpackShader.Bind();
		g_backpackShader.SetMat4("projection", projection);
		g_backpackShader.SetMat4("view", camera.GetViewMatrix());
		g_backpackShader.SetMat4("model", model);

		OpenGLTexture* texture = AssetManager::GetTextureByName("diffuse");
		if (texture)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture->GetHandle());
		}
		Model* testModel = AssetManager::GetModelByName("backpack");
		if (testModel) {
			testModel->Draw();
		}
	}
	void HotloadShaders()
	{
		g_backpackShader.Hotload();
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