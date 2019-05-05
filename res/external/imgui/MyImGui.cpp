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

void MyImGui::Draw(float fZoom, float fZoomTarget, float fAngle)
{
	ImGui_ImplGlfwGL3_NewFrame();

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("fZoom %.5f ", fZoom);
	ImGui::Text("fZoomTarget %.5f ", fZoomTarget);
	ImGui::Text("fAngle %.5f ", fAngle);

	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}