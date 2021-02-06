#version 420

layout(location = 0) in vec2 inUV;

out vec4 frag_color;

layout (binding = 0) uniform sampler2D s_screenTex;
layout (binding = 30) uniform sampler3D u_TexColorGrade;

//Affects the Color Correction
//Lower the number, closer we are to regular
uniform float u_Intensity = 1.0;

void main() 
{

	vec4 source = texture(s_screenTex, inUV);

	vec4 colorCube = texture(u_TexColorGrade, source.rgb);

	frag_color.rgb = mix(source.rgb, colorCube.rgb, u_Intensity);
    frag_color.a = mix(source.a, colorCube.a, u_Intensity);
}