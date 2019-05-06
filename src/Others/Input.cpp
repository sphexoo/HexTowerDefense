
#include <iostream>

#include "Input.h"

bool Input::keyPressed[10];
float Input::mX;
float Input::mY;
bool Input::mouseLock;
int Input::scroll;


Input::Input()
{
	/* Intilalise key states and callback functions */
	for (int i = 0; i < 10; i++)
	{
		keyPressed[i] = false;
	}

	mouseLock = true;
	scroll = 0;
}

void Input::SetWindowCallback(GLFWwindow* window)
{
	/* setting up callback functions */
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_click_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Input::mouse_click_callback(GLFWwindow* window, int button, int action, int mods)
{
	/* handles mouse button presses and releases */
	if (button == 0 && action == 1)
	{
		keyPressed[MOUSE_1] = true; 
	}
	else if (button == 0 && action == 0)
	{
		keyPressed[MOUSE_1] = false;
	}

	if (button == 1 && action == 1)
	{
		keyPressed[MOUSE_2] = true;
	}
	else if (button == 1 && action == 0)
	{
		keyPressed[MOUSE_2] = false;
	}
}

void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	/* handles key presses and releases */
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		keyPressed[KEY_W] = true;
	}
	else if (key == GLFW_KEY_W && action == GLFW_RELEASE)
	{
		keyPressed[KEY_W] = false;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		keyPressed[KEY_S] = true;
	}
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
	{
		keyPressed[KEY_S] = false;
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		keyPressed[KEY_A] = true;
	}
	else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
	{
		keyPressed[KEY_A] = false;
	}
	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		keyPressed[KEY_D] = true;
	}
	else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
	{
		keyPressed[KEY_D] = false;
	}
	else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)
	{
		keyPressed[KEY_SHIFT] = true;
	}
	else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE)
	{
		keyPressed[KEY_SHIFT] = false;
	}
	else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		keyPressed[KEY_SPACE] = true;
	}
	else if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
	{
		keyPressed[KEY_SPACE] = false;
	}
	else if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		if (!mouseLock)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		mouseLock = !mouseLock;
	}
	else if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{

		keyPressed[KEY_R] = true;

	}
	else if (key == GLFW_KEY_R && action == GLFW_RELEASE)
	{

		keyPressed[KEY_R] = false;

	}
}

void Input::cursor_pos_callback(GLFWwindow* window, double x, double y)
{
	/* handles mouse cursor movement if mouse lock is enabled */
	mX = (float)x;
	mY = (float)y;
}

void Input::scroll_callback(GLFWwindow* window, double a, double b)
{

	scroll = (int)b;
}

bool Input::IsPressed(KeyName key)
{
	return keyPressed[key];
}