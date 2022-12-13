#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Shader.h"
#include "Model.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

class Voxel_Cone_Tracing
{
public:
	Voxel_Cone_Tracing(int screen_width_, int screen_height_, GLFWwindow*& window_)
	{
		screen_width = screen_width_;
		screen_height = screen_height_;

		window = window_;

		//VoxelizeShader = new Shader("Resource/Shader/VCT/Voxelization.vs", "Resource/Shader/VCT/Voxelization.fs", "Resource/Shader/VCT/Voxelization.gs");
		ShadowShader = new Shader("Resource/Shader/VCT/Shadow.vs", "Resource/Shader/VCT/Shadow.fs");
		VoxelConeTracingShader = new Shader("Resource/Shader/VCT/VoxelConeTracingShader.vs", "Resource/Shader/VCT/VoxelConeTracingShader.fs"); 
		model = new Model("Resource/Model/Backpack/Survival_BackPack_2.fbx");
	}

	void Init()
	{
		// Depth FBO
		glGenFramebuffers(1, &Depth_FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, Depth_FBO);

		// Create depth texture
		glGenTextures(1, &Depth_Texture);
		glBindTexture(GL_TEXTURE_2D, Depth_Texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, ShadowMapSize, ShadowMapSize, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, Depth_Texture, 0);
		glDrawBuffer(GL_NONE);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			cout << "Error Creating Depth FrameBuffer\n";
			return;
		}

		// Voxelization Init
		glEnable(GL_TEXTURE_3D);

		glGenTextures(1, &VoxelTexture);
		glBindTexture(GL_TEXTURE_3D, VoxelTexture);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int numVoxels = VoxelDimensions * VoxelDimensions * VoxelDimensions;
		GLubyte* data = new GLubyte[4 * numVoxels];
		memset(data, 0, 4 * numVoxels);

		glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA8, VoxelDimensions, VoxelDimensions, VoxelDimensions, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		delete[] data;

		glGenerateMipmap(GL_TEXTURE_3D);

		float size = VoxelGridWorldSize;

		glm::mat4 projectMat = glm::ortho(-size * 0.5f, size * 0.5f, -size * 0.5f, size * 0.5f, size * 0.5f, size * 1.5f);

		ProjX = projectMat * glm::lookAt(glm::vec3(VoxelGridWorldSize, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		ProjY = projectMat * glm::lookAt(glm::vec3(0, VoxelGridWorldSize, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, -1));
		ProjZ = projectMat * glm::lookAt(glm::vec3(0, 0, VoxelGridWorldSize), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		//GenerateDepthTexture();
		//GenerateVoxelTexture();
	}

	void Render()
	{
		//Draw Scene
		glfwGetFramebufferSize(window, &screen_width, &screen_height);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, screen_width, screen_height);

		/*glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)screen_width / (float)screen_height, 0.1f, 1000.0f);
		glm::vec3 camera_Position = camera.Position;*/

		VoxelConeTracingShader->use();

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)screen_width / (float)screen_height, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		VoxelConeTracingShader->setMat4("projection", projection);
		VoxelConeTracingShader->setMat4("view", view);

		// render the loaded model
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		VoxelConeTracingShader->setMat4("model", modelMatrix);

		model->Draw(*VoxelConeTracingShader);
	}

	void GenerateDepthTexture()
	{
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		glBindFramebuffer(GL_FRAMEBUFFER, Depth_FBO);
		glViewport(0, 0, ShadowMapSize, ShadowMapSize);
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ShadowShader->use();

		glm::mat4 lightProjection, lightView;
		lightProjection = glm::ortho(-120, 120, -120, 120, -100, 100);
		lightView = glm::lookAt(lightDirection, glm::vec3(0.0), glm::vec3(0.0, 1.0, 0.0));
		DepthViewProjectionMatrix = lightProjection * lightView;

		glm::mat4 proj = glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(0.05f, 0.05f, 0.05f)), glm::vec3(0.0f, 0.0f, 0.0f));
		ShadowShader->setMat4("DepthViewProjectionMatrix", DepthViewProjectionMatrix * proj);

		model->Draw(*ShadowShader);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, screen_width, screen_height);
	}

	void GenerateVoxelTexture()
	{
		/*glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		glViewport(0, 0, VoxelDimensions, VoxelDimensions);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		VoxelizeShader->use();
		VoxelizeShader->setInt("VoxelDimensions", VoxelDimensions);
		VoxelizeShader->setMat4("ProjX", ProjX);
		VoxelizeShader->setMat4("ProjY", ProjY);
		VoxelizeShader->setMat4("ProjZ", ProjZ);

		glActiveTexture(GL_TEXTURE0 + 5);
		glBindTexture(GL_TEXTURE_2D, Depth_Texture);
		VoxelizeShader->setInt("ShadowMap", 5);

		glBindImageTexture(6, VoxelTexture, 0, GL_TRUE, 0, GL_WRITE_ONLY, GL_RGBA8);
		VoxelizeShader->setInt("VoxelTexture", 6);

		glm::mat4 mMat = glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(0.05f, 0.05f, 0.05f)), glm::vec3(0.0f, 0.0f, 0.0f));
		VoxelizeShader->setMat4("ModelMatrix", mMat);
		VoxelizeShader->setMat4("DepthModelViewProjectionMatrix", DepthViewProjectionMatrix * mMat);
		VoxelizeShader->setInt("ShadowMapSize", ShadowMapSize);

		model->Draw(*VoxelizeShader);
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_3D, VoxelTexture);
		glGenerateMipmap(GL_TEXTURE_3D);
		glViewport(0, 0, screen_width, screen_height);*/
	}

public:
	glm::vec3 lightDirection = glm::vec3(0.0f, 1.0f, 0.25f);

	GLFWwindow* window;

	int screen_width = 1280;
	int screen_height = 720;

	//Shader
	//Shader* VoxelizeShader;
	Shader* ShadowShader;
	Shader* VoxelConeTracingShader;

	// Voxel
	GLuint VoxelTexture;
	GLuint Texture3D_VAO;

	int VoxelDimensions = 128;
	const float VoxelGridWorldSize = 150.0f;

	// Shadow
	GLuint Depth_FBO;
	GLuint Depth_Texture;
	GLuint ShadowMapSize = 4096;

	//Model
	Model* model;

	// Matrix 
	glm::mat4 DepthViewProjectionMatrix;
	glm::mat4 ProjX;
	glm::mat4 ProjY;
	glm::mat4 ProjZ;
};