#pragma once
#include <GLFW/glfw3.h>

class Input
{
	/*
	Class handles input from mouse and keyboard
	*/
private:
	static bool mouseLock;
	static bool keyPressed[10];

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
		KEY_T	  = 9
	};


	static float mouseX;
	static float mouseY;
	static int scroll;

	Input();

	bool IsPressed(KeyName key);
	void SetWindowCallback(GLFWwindow* window);
};