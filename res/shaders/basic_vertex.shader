#version 330 core
layout(location = 0) in vec4 position;

uniform mat4 u_ProjMat;
uniform mat4 u_TranslMat;

void main()
{
	gl_Position = u_ProjMat * u_TranslMat * position;
	//gl_Position = u_ProjMat * position;
};