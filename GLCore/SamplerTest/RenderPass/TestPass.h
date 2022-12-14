#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include"../Framework/RenderPass.h"
#include <iostream>
#include "../Framework/Camera.h"

class TestPass : public RenderPass
{
public:
	TestPass(std::string name, const char* vspath, const char* fspath, const char* gspath = nullptr)
		: RenderPass(name, vspath, fspath, gspath)
	{
		camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	}

	Camera* camera;

	virtual void init();

	virtual void update();
};

