#pragma once
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include "glm.hpp"

class MyImGui
{
public:
	float dX = 0.0f;
	float dY = 0.0f;
	float dZ = 0.0f;
	float AH = 0.0f;
	float AV = 0.0f;
public:
	MyImGui(GLFWwindow* window);
	~MyImGui();
	void Draw(float fZoom, float fZoomTarget, float fAngle);
};