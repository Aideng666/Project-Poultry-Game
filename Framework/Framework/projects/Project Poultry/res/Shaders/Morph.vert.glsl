#version 410

layout(location = 0) in vec3 inPos1;
layout(location = 1) in vec3 inCol;
layout(location = 2) in vec2 inUV;
layout(location = 3) in vec3 inNorm1;
layout(location = 4) in vec3 inPos2;
layout(location = 5) in vec3 inNorm2;

layout(location = 0) out vec3 outPos;
layout(location = 1) out vec3 outCol;
layout(location = 2) out vec3 outUV;
layout(location = 3) out vec3 outNorm;

uniform mat4 Model;
uniform mat3 Normal;
uniform mat4 ViewProjection;
uniform float MorphT;

void main()
{

	outPos = Model * mix(inPos1, inPos2, t);

	outNorm = Normal * mix(inNorm1, inNorm2, t);
	
	gl_Position = ViewProjection * outPos;

}
