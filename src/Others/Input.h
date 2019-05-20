#pragma once
#include <GLFW/glfw3.h>
#include "Renderer.h"

constexpr auto NUM_KEYS = 11;

class Input
{
	/*
	Class handles input from mouse and keyboard
	*/
private:
	static bool keyPressed[NUM_KEYS];

private:
	static void cursor_pos_callback(GLFWwindow* window, double x, double y);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_click_callback(GLFWwindow* window, int button, int action, int mods);
	static void scroll_callback(GLFWwindow* window, double a, double b);
	
public:
	enum KeyName
	{
		MOUSE_1	  = 0,
		MOUSE_2   = 1,
		MOUSE_3   = 2,
		KEY_SHIFT = 3,
		KEY_SPACE = 4,
		KEY_W     = 5, 
		KEY_S     = 6,
		KEY_A	  = 7,
		KEY_D	  = 8,
		KEY_R	  = 9,
		KEY_ESC	  = 10
	};

	static float mX;
	static float mY;
	static float prevmX;
	static float prevmY;
	static float dX;
	static float dY;
	static int scroll;
	static bool mouseLock;

	Input();

	bool IsPressed(KeyName key);
	bool IsHold(KeyName key);
	void SetWindowCallback(GLFWwindow* window);
	void ResetMouse();
	static glm::vec3 GetObjectSpaceCoords(glm::mat4& viewMatrix, glm::mat4& projMatrix, float fWidth, float fHeight);
};