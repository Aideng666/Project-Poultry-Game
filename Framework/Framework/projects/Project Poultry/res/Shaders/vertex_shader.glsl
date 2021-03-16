#version 410

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inUV;
layout(location = 3) in vec3 inNormal;

layout(location = 0) out vec3 outPosition;
layout(location = 1) out vec3 outColor;
layout(location = 2) out vec2 outUV;
layout(location = 3) out vec3 outNormal;
layout(location = 4) out vec4 outFragPosLightSpace;

uniform mat4 u_ModelViewProjection;
uniform mat4 u_View;
uniform mat4 u_Projection;
uniform mat4 u_Model;
uniform mat3 u_ModelRotation;
uniform vec3 u_LightPos;
uniform mat4 u_LightSpaceMatrix;

void main() {

	gl_Position = u_ModelViewProjection * vec4(inPosition, 1.0);

	// Lecture 5
	// Pass vertex pos in world space to frag shader
	outPosition = (u_Model * vec4(inPosition, 1.0)).xyz;

	outUV = inUV;

	//pass out the light space fragment pos
	outFragPosLightSpace = u_LightSpaceMatrix * vec4(outPosition, 1.0);

	// Normals
	outNormal = u_ModelRotation * inNormal;

	///////////
	outColor = inColor;
}