#version 330 core
layout(location = 0) out vec4 color;

uniform vec4 u_Color;
in vec3 v_Normal;

void main()
{
	float val = (v_Normal.z + 1.0f) * 0.5f;
	color = vec4(val, val, val, 1.0f);
};