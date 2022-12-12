#version 430 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform mat4 ProjX;
uniform mat4 ProjY;
uniform mat4 ProjZ;

in Vertex
{
	vec2 TexCoord;
	vec4 DepthCoord;
} vertices[];

out Vertex_GS
{
	vec2 TexCoord;
	vec4 DepthCoord;
	float axis;
};

void main()
{
	//calculate edge vectors in voxel coordinate space
	vec3 edge1 = gl_in[0].gl_Position.xyz-gl_in[1].gl_Position.xyz;

	vec3 edge2 = gl_in[2].gl_Position.xyz-gl_in[0].gl_Position.xyz;

	vec3 normal = abs(cross(edge1, edge2)); 

	if(normal.x >= normal.y && normal.x >= normal.z)
        axis = 1;
    else if (normal.y >= normal.x  && normal.y >= normal.z)
        axis = 2;
    else
        axis = 3;
}