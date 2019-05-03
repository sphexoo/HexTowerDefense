#include "MyImGui.h"

MyImGui::MyImGui(GLFWwindow* window)
{
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();
}

MyImGui::~MyImGui()
{
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
}

void MyImGui::Draw()
{
	ImGui_ImplGlfwGL3_NewFrame();

	/*
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("angHor: %.3f", angHor);
	ImGui::Text("angVert: %.3f", angVert);
	ImGui::Text("X: %.3f", viewPos.x);
	ImGui::Text("Y: %.3f", viewPos.y);
	ImGui::Text("Z: %.3f", viewPos.z);
	*/

	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}