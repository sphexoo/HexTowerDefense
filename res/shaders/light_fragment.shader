#version 330 core
layout(location = 0) out vec4 color;

uniform vec4 u_Color;
in vec3 v_Normal;

void main()
{
	float lightning_factor = (v_Normal.z + 1.0f) * 0.5f;
	vec4 targetColor = u_Color;
	targetColor.xyz = u_Color.xyz * lightning_factor;
	color = targetColor;
};