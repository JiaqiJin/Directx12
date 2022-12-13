#version 430 core

uniform sampler2D DiffuseTexture;

uniform sampler2D ShadowMap;

uniform int VoxelDimensions;
uniform layout(RGBA8) image3D VoxelTexture;

in Vertex_GS
{
	vec2 TexCoord;
	flat int axis;
	vec4 DepthCoord;
} gs;

float PCF_Shadow_Mapping(float bias)
{
	float shadow = 0.0;
	vec2 ShadowMapTexSize = 1.0 / texture(shadowMap, 0);

	// 0 - 1
	float currentDepth = gs.DepthCoord.z / gs.DepthCoord.w;

	int radius = 1;
	for(int x = -radius; x <= radius; ++x )
	{
		for(int y = -radius; y <= radius; ++y)
		{
			float pcfDepth = texture(shadowMap, gs.DepthCoord.xy + vec2(x, y) * ShadowMapTexSize).r;
			shadow += currentDepth - bias < pcfDepth ? 0.0 : 1.0;
		}
	}

	shadow /= 9.0;

	if(gs.DepthCoord.z > 0)
		shadow = 0.0;

	return shadow;
}

void main()
{
	vec4 color = texture(DiffuseTexture, gs.TexCoord);

	ivec3 camPos = ivec3(gl_FragCoord.x, gl_FragCoord.y, VoxelDimensions * gl_FragCoord.z);

	ivec3 voxelPos;

	if(gs.axis == 1) 
	{
	    voxelPos.x = VoxelDimensions - 1 - camPos.z;
		voxelPos.z = VoxelDimensions - 1 - camPos.x;
		voxelPos.y = camPos.y;
	}
	else if(gs.axis == 2) 
	{
	    voxelPos.z = VoxelDimensions - 1 - camPos.y;
		voxelPos.y = VoxelDimensions - 1 - camPos.z;
		voxelPos.x = camPos.x;
	} 
	else 
	{
	    voxelPos = camPos;
		voxelPos.z = VoxelDimensions - 1 - camPos.z;
	}

	imageStore(VoxelTexture, voxelPos, vec4(color.rgb * PCF_Shadow_Mapping(0.002), 1.0f));
}