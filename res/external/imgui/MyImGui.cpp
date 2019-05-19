#include "MyImGui.h"

#include "Cursor.h"

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

void MyImGui::Draw(Cursor& cursor, float mx, float my)
{
	ImGui_ImplGlfwGL3_NewFrame();

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("X: %.3f", cursor.pos.x);
	ImGui::Text("Y: %.3f", cursor.pos.y);
	ImGui::Text("prevX: %.3f", cursor.prevmX);
	ImGui::Text("prevY: %.3f", cursor.prevmY);
	ImGui::Text("MX: %.3f", mx);
	ImGui::Text("MY: %.3f", my);


	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}