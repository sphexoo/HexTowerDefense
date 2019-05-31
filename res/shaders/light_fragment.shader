#version 330 core
layout(location = 0) out vec4 color;

uniform vec4 u_Color;
in vec3 v_Normal;
in vec3 v_Color;

void main()
{
	float lightning_factor = (v_Normal.z + 1.0f) * 0.75f;
	vec4 targetColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	targetColor.xyz = v_Color.xyz * lightning_factor;
	color = targetColor;
};