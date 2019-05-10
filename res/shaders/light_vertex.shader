#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;

uniform mat4 u_MVP;
out vec3 v_Normal;

void main()
{
	gl_Position = u_MVP * position;
	v_Normal = normal;
};