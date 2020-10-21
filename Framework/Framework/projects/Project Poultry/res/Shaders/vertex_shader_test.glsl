#version 410
layout (location = 0) in vec3 aPos;

uniform mat4 u_ModelViewProjection;

void main()
{
	gl_Position = u_ModelViewProjection * vec4(aPos, 1.0);
}