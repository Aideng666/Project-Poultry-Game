#version 410 core

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;

layout(location = 0) out vec3 outPos;
layout(location = 1) out vec3 outColor;
layout(location = 2) out vec3 outNormal;

uniform mat4 u_ModelViewProjection;
uniform mat4 u_View;
uniform mat4 u_Model;
uniform mat3 u_ModelRotation;
uniform vec3 u_LightPos;

void main()
{
	gl_Position = u_ModelViewProjection * vec4(inPosition, 1.0);

	outPos = (u_Model * vec4(inPosition, 1.0)).xyz;

	outNormal = u_ModelRotation * inNormal;

	outColor = inColor;
}