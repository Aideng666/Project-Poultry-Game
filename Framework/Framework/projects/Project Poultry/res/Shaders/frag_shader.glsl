#version 420
layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inUV;
layout(location = 3) in vec3 inNormal;
layout(location = 4) in vec4 inFragPosLightSpace;

layout (binding = 30) uniform sampler2D s_ShadowMap;

uniform sampler2D s_Diffuse;

uniform vec3  u_AmbientCol;
uniform float u_AmbientStrength;

uniform vec3  u_LightPos;
uniform vec3  u_LightDir;
uniform vec3  u_LightCol;
uniform float u_AmbientLightStrength;
uniform float u_AmbientLightStrength2;
uniform float u_SpecularLightStrength;
uniform float u_Shininess;
uniform float u_Time = 0.0f;
uniform vec3 u_Position;
uniform int u_LightNum;

uniform float u_LightAttenuationConstant;
uniform float u_LightAttenuationLinear;
uniform float u_LightAttenuationQuadratic;

uniform vec3  u_CamPos;

uniform int u_LightOn;

out vec4 frag_color;


struct DirectionalLight
{
	//Light direction (defaults to down, to the left, and a little forward)
	vec4 _lightDirection;

	//Generic Light controls
	vec4 _lightCol;

	//Ambience controls
	vec4 _ambientCol;
	float _ambientPow;
	
	//Power controls
	float _lightAmbientPow;
	float _lightSpecularPow;

	float _shadowBias;
};

layout (std140, binding = 0) uniform u_Lights
{
	DirectionalLight sun;
};

float ShadowCalculation(vec4 fragPosLightSpace)
{
	// Perspective Division
	vec3 projectionCoordinates = fragPosLightSpace.xyz / fragPosLightSpace.w;

	//Transform into a [0, 1] range
	projectionCoordinates = projectionCoordinates * 0.5 + 0.5;

	//Gets the closest depth value
	float closestDepth = texture(s_ShadowMap, projectionCoordinates.xy).r;

	//Gets current depth according to camera
	float currentDepth = projectionCoordinates.z;

	float shadow = 0.0;

	vec2 texelSize = 1.0 / textureSize(s_ShadowMap, 0);

	for(int x = -1; x <= 1; ++x)
	{
		for(int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(s_ShadowMap, projectionCoordinates.xy + vec2(x, y) * texelSize).r; 
			shadow += currentDepth - sun._shadowBias > pcfDepth ? 1.0 : 0.0;        
		}    
	}

	shadow /= 9.0;

	return shadow;
}

vec3 CreateSpotlight(vec3 pos, vec3 direction, float strength, float cutoff)
{
	vec3 lightDir = normalize(pos - inPos);

	vec3 ambient = ((u_AmbientLightStrength2 * u_LightCol) + (u_AmbientCol * u_AmbientStrength));

	float theta = dot(lightDir, normalize(-direction));

	if (theta > cutoff)
	{
		vec3 N = normalize(inNormal);

		
		float dif = max(dot(N, lightDir), 0.0);
		vec3 diffuse = dif * u_LightCol;// add diffuse intensity
		float dist = length(u_LightPos - inPos);
		diffuse = diffuse / dist; // (dist*dist)

		vec3 viewDir = normalize(u_CamPos - inPos);
		vec3 h		 = normalize(lightDir + viewDir);
		
		vec3 reflectDir = reflect(-lightDir, N);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Shininess);
		vec3 specular = strength * spec * u_LightCol; 

		return (vec3(ambient + diffuse + specular));
	}
	else
	{
		return ambient;
	}

}

vec3 CreateDirectionLight(vec3 pos, float strength)
{
	vec3 lightDir = normalize(pos - inPos);

	vec3 ambient = ((u_AmbientLightStrength * u_LightCol) + (u_AmbientCol * u_AmbientStrength));

	vec3 N = normalize(inNormal);

		
		float dif = max(dot(N, lightDir), 0.0);
		vec3 diffuse = dif * u_LightCol;// add diffuse intensity
		float dist = length(u_LightPos - inPos);
		diffuse = diffuse / dist; // (dist*dist)

		vec3 viewDir = normalize(u_CamPos - inPos);
		vec3 h		 = normalize(lightDir + viewDir);
		
		vec3 reflectDir = reflect(-lightDir, N);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Shininess);
		vec3 specular = strength * spec * u_LightCol; 

		return (vec3(ambient + diffuse + specular));
}

vec3 Lerp(vec3 p0, vec3 p1, float t)
{
	return (1.0f - t) * p0 + t * p1;
}


void main() { 

	vec4 textureColor = texture(s_Diffuse, inUV);

	float strength  = max(min(((2 * cos(u_Time * radians(180.0f))) + (4 * sin((u_Time * radians(180.0f)) / 4)) + (3 *cos(u_Time * radians(180.0f) * 3))) + (4 * sin(u_Time * radians(180.0f) * 3)), 1), 0);

	vec3 lightDir = normalize(-sun._lightDirection.xyz);

	vec3 ambient = ((/*u_AmbientLightStrength*/ strength * u_LightCol) + (u_AmbientCol * u_AmbientStrength));

	vec3 N = normalize(inNormal);

	
	float dif = max(dot(N, lightDir), 0.0);
	vec3 diffuse = dif * sun._lightCol.xyz;// add diffuse intensity
	float dist = length(u_LightPos - inPos);

	float attenuation = 1.0f / (
	u_LightAttenuationConstant + 
	u_LightAttenuationLinear * dist +
	u_LightAttenuationQuadratic * dist * dist);

	diffuse = diffuse / dist; // (dist*dist)

	vec3 viewDir = normalize(u_CamPos - inPos);
	vec3 h		 = normalize(lightDir + viewDir);
	
	vec3 reflectDir = reflect(-lightDir, N);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Shininess);
	vec3 specular = /*sun._lightSpecularPow*/ strength * spec * sun._lightCol.xyz; // Can also use a specular color

	float shadow = ShadowCalculation(inFragPosLightSpace);

	vec3 result = (
	(sun._ambientPow * sun._ambientCol.xyz) + // global ambient light
	(1.0 - shadow) * (diffuse + specular)/* * attenuation*/ // light factors from our single light
	) * inColor * textureColor.rgb; // Object color


	switch (u_LightOn)
	{
		case 2:
			frag_color = vec4(sun._ambientPow * 2.0 * inColor * textureColor.rgb, 1.0);
			break;
		case 1:
			frag_color = vec4(result, 1.0);
			break;
				
		case 0:
			frag_color = vec4(inColor * textureColor.rgb, 1.0);
			break;
	}

}