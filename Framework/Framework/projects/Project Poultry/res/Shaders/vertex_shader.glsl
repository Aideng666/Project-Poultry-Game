#version 410

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;

uniform mat4 u_ModelViewProjection;

void main()
{
	gl_Position = u_ModelViewProjection * vec4(inPos, 1.0);
}