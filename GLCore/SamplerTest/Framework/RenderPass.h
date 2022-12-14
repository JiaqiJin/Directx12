#pragma once
#include<iostream>

#include "Shader.h"

class RenderPass
{
public:

	RenderPass(std::string name, const char* vspath, const char* fspath, const char* geometryPath = nullptr)
		: passName(name)
	{
		
	}
	
	std::string passName;
	Shader shader;

	virtual void init() = 0;
	virtual void update() = 0;

};