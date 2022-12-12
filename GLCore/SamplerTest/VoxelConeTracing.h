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

		VoxelizeShader = new Shader("Resource/Shader/VCT/Voxelization.vs", "Resource/Shader/VCT/Voxelization.fs", "Resource/Shader/VCT/Voxelization.gs");
	/*	ShadowShader = new Shader("", "");
		VoxelConeTracingShader = new Shader("", "");*/
		model = new Model("Resource/Model/sponza.obj");

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

	}

	void Init()
	{
		GenerateDepthTexture();
		GenerateVoxelTexture();
	}

	void Render()
	{

	}

	void GenerateDepthTexture()
	{

	}

	void GenerateVoxelTexture()
	{

	}
public:
	glm::vec3 lightDirection = glm::vec3(0.0f, 1.0f, 0.25f);

	GLFWwindow* window;

	int screen_width = 1280;
	int screen_height = 720;

	//Shader
	Shader* VoxelizeShader;
	//Shader* ShadowShader;
	//Shader* VoxelConeTracingShader;

	// Shadow
	GLuint Depth_FBO;
	GLuint Depth_Texture;
	GLuint ShadowMapSize = 4096;

	//Model
	Model* model;

};