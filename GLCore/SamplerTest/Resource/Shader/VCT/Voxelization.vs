#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec3 aTex;

uniform mat4 DepthModelViewProjectionMatrix;
uniform mat4 ModelMatrix;

out Vertex
{
	vec2 TexCoord;
	vec4 DepthCoord;
};

void main()
{
	TexCoord = aTex;

	// Calculate depth coord
	DepthCoord = DepthModelViewProjectionMatrix * vec4(aPos, 1.0);
	DepthCoord.xyz =  DepthCoord.xyz * 0.5 + vec3(0.5);

	gl_Position = ModelMatrix * vec4(aPos, 1.0f);
}