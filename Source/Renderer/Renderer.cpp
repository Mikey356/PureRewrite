#include "Renderer.h"

#include "AssetManager/AssetManager.h"
#include "Backend/Backend.h"
#include "Game/Game.h"
#include "OpenGL/Types/GL_frame_buffer.h"
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
	Shader g_lightingShader;
	Shader g_postProcessingShader;
	OpenGLFrameBuffer g_frameBuffer;
	void Init()
	{
		g_lightingShader.Load("Resources/GL_Shaders/shading.vert", "Resources/GL_Shaders/shading.frag");
		g_postProcessingShader.Load("Resources/GL_Shaders/post_processing.vert", "Resources/GL_Shaders/post_processing.frag");

		g_frameBuffer = OpenGLFrameBuffer("FBO", 1920 * 2, 1080 * 2);
		g_frameBuffer.CreateColorAttachment("Color", GL_RGBA16F);
		g_frameBuffer.CreateColorAttachment("PostProcessed", GL_RGBA16F);
		g_frameBuffer.CreateDepthAttachment();
		g_frameBuffer.CheckForErrors();
	}
	
	void ClearRenderTargetsPass();
	void ShadingPass();
	void PostProcessingPass();
	void BlitFinalImageToFrameBuffer();

	void RenderFrame()
	{
		ClearRenderTargetsPass();
		ShadingPass();
		PostProcessingPass();
		BlitFinalImageToFrameBuffer();
	}

	void ClearRenderTargetsPass()
	{
		g_frameBuffer.BindFrameBuffer();
		g_frameBuffer.Clear("Color", 0.412, 0.565, 0.800, 1);
		g_frameBuffer.Clear("PostProcessed", 0.0f, 0.0f, 1.0f, 1.0f);
		g_frameBuffer.ClearDepth();
	}

	void ShadingPass() 
	{
		// Bind FBO for drawing
		g_frameBuffer.BindFrameBuffer(); 
		g_frameBuffer.SetDrawBuffer("Color");
		g_frameBuffer.SetViewport();
		

		// Configure OpenGL state
		glEnable(GL_DEPTH_TEST);


		Player& player = Game::GetPlayer();
		Camera& camera = player.GetCamera();
		// Projection and view matrices
		glm::mat4 projection = glm::perspective(glm::radians(100.0f), (float)Backend::GetCurrentWindowWidth() / (float)Backend::GetCurrentWindowHeight(), 0.1f, 1000.0f);
		glm::mat4 view = camera.GetViewMatrix();

		g_lightingShader.Bind();
		g_lightingShader.SetMat4("u_projection", projection);
		g_lightingShader.SetMat4("u_view", camera.GetViewMatrix());
		g_lightingShader.SetVec3("u_viewPosition", camera.GetPosition());


		// Render game objects
		for (GameObject& gameObject : Game::GetGameObjects())
		{
			g_lightingShader.SetMat4("u_model", gameObject.GetModelMatrix());
			g_lightingShader.SetMat4("u_inverseModel", glm::inverse(gameObject.GetModelMatrix()));

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
	};
	
	void PostProcessingPass()
	{
		static uint32_t dummyVAO = 0;

		g_frameBuffer.BindFrameBuffer();
		g_frameBuffer.SetDrawBuffer("PostProcessed");
		g_frameBuffer.SetViewport();

		g_postProcessingShader.Bind();
		glBindTextureUnit(0, g_frameBuffer.GetColorAttachmentHandle("Color"));

		// Create VAO if it doesn't exist
		if (dummyVAO == 0){
			glGenVertexArrays(1, &dummyVAO);
		}
		
		//OpenGL state
		glDisable(GL_DEPTH_TEST);
		
		// Draw full screen triangle
		glBindVertexArray(dummyVAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	void BlitFinalImageToFrameBuffer() 
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
		GLuint srcX0 = 0;
		GLuint srcY0 = 0;
		GLuint srcX1 = g_frameBuffer.GetWidth();
		GLuint srcY1 = g_frameBuffer.GetHeight();

		GLuint dstX0 = 0;
		GLuint dstY0 = 0;
		GLuint dstX1 = Backend::GetCurrentWindowWidth();
		GLuint dstY1 = Backend::GetCurrentWindowHeight();

		glBindFramebuffer(GL_READ_FRAMEBUFFER, g_frameBuffer.GetHandle());
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

		glReadBuffer(g_frameBuffer.GetColorAttachmentSlot("PostProcessed"));
		glDrawBuffer(GL_BACK);

		glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	}

	void HotloadShaders()
	{
		g_lightingShader.Hotload();
		g_postProcessingShader.Hotload();
		std::cout << "Hotloaded shaders\n";
	}

	void EnableXRAY(){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void DisableXRAY(){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}