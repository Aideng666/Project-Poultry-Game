#version 410

layout (location = 0) in vec3 inPosition;

//Out Lightspace matrix
uniform mat4 u_LightSpaceMatrix;
uniform mat4 u_Model;

void main()
{ 
	//Lightspace matrix is the viewProj matric from the lights perspective
	gl_Position = u_LightSpaceMatrix * u_Model * vec4(inPosition, 1.0);
}