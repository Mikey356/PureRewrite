#include "AssetLoader/Model.h"
#include "AssetLoader/AssetLoader.h"`
#include "Camera/Camera.h"
#include "Backend/Backend.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void ProcessInput();

const uint32_t SCR_WIDTH = 800;
const uint32_t SCR_HEIGHT = 600;

// cam
Camera g_cam(glm::vec3(0.0f, 0.0f, 3.0f));
float g_last_X = SCR_WIDTH / 2.0f;
float g_last_Y = SCR_WIDTH / 2.0f;
bool g_cursrEntrScrn = true;

// time
float g_deltaTime = 0.0f;
float g_lastFrame = 0.0f;

auto main() -> int
{
	Backend::Init("PureBranch", SCR_WIDTH, SCR_HEIGHT);
	AssetManager::Init();

	Shader backpackShader("Resources/OpenGL/GL_backpack.vert","Resources/OpenGL/GL_backpack.frag");

	Model backpack("Resources/Assets/backpack/backpack.obj");

	backpackShader.Use();

		
	while (!Backend::WindowShouldClose())
	{
		// timing calculation
		float currentFrame = static_cast<float>(glfwGetTime());
		g_deltaTime = currentFrame - g_lastFrame;
		g_lastFrame = currentFrame;

		ProcessInput();
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.412, 0.565, 0.800, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Projection and view matrices
		glm::mat4 projection = glm::perspective(glm::radians(g_cam.m_zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
		glm::mat4 view = g_cam.GetViewMatrix();	
		
		// Model matrix
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		
		backpackShader.Use();
		backpackShader.SetMat4("projection", projection);
		backpackShader.SetMat4("view", view);
		backpackShader.SetMat4("model", model);

		backpack.Draw(backpackShader);

		Backend::SwapBuffersPollEvents();
	}

	Backend::CleanUp();
	return 0;
}

void ProcessInput()
{
	GLFWwindow* window = Backend::GetWindowPtr();

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		g_cam.ProcessKeyboard(FORWARD, g_deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		g_cam.ProcessKeyboard(BACKWARD, g_deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		g_cam.ProcessKeyboard(LEFT, g_deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		g_cam.ProcessKeyboard(RIGHT, g_deltaTime);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		g_cam.ProcessKeyboard(FORWARD, g_deltaTime);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		g_cam.ProcessKeyboard(BACKWARD, g_deltaTime);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		g_cam.ProcessKeyboard(RIGHT, g_deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		g_cam.ProcessKeyboard(LEFT, g_deltaTime);

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}