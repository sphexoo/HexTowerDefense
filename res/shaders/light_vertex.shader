#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;

uniform mat4 u_MVP;
out vec3 v_Normal;
out vec3 v_Color;

void main()
{
	gl_Position = u_MVP * position;
	v_Normal = normal;
	v_Color = color;
};