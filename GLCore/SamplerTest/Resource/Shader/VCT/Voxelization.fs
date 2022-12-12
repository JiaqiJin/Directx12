#version 430 core

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

in Vertex_GS
{
	vec2 TexCoord;
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
	vec4 color = texture(diffuseTexture, )
}