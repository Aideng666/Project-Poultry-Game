#version 410
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	float ambientStrength = 0.5;
	vec3 ambient = ambientStrength * lightColor;

	vec3 result = ambient * objectColor;

	FragColor = vec4(result, 1.0);//vec4(lightColor * objectColor, 1.0);
}