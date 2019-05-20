
#include <iostream>

#include "Input.h"

bool Input::keyPressed[NUM_KEYS];
float Input::mX;
float Input::mY;
float Input::prevmX;
float Input::prevmY;
float Input::dX;
float Input::dY;
bool Input::mouseLock;
int Input::scroll;

Input::Input()
{
	/* Intilalise key states and callback functions */
	for (int i = 0; i < NUM_KEYS; i++)
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

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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

	if (button == 2 && action == 1)
	{
		keyPressed[MOUSE_3] = true;
	}
	else if (button == 2 && action == 0)
	{
		keyPressed[MOUSE_3] = false;
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
	else if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		keyPressed[KEY_R] = true;
	}
	else if (key == GLFW_KEY_R && action == GLFW_RELEASE)
	{
		keyPressed[KEY_R] = false;
	}
	else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		keyPressed[KEY_ESC] = true;
	}
	else if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
	{
		keyPressed[KEY_ESC] = false;
	}
}

void Input::cursor_pos_callback(GLFWwindow* window, double x, double y)
{
	/* handles mouse cursor movement if mouse lock is enabled */
	mX = (float)x;
	mY = (float)y;
	dX = mX - prevmX;
	dY = mY - prevmY;
	prevmX = mX;
	prevmY = mY;
}

void Input::scroll_callback(GLFWwindow* window, double a, double b)
{

	scroll = (int)b;
}

bool Input::IsPressed(KeyName key)
{
	bool pressed = keyPressed[key];
	keyPressed[key] = false;
	return pressed;
}

bool Input::IsHold(KeyName key)
{
	return keyPressed[key];
}

void Input::ResetMouse()
{
	dX = 0.0f;
	dY = 0.0f;
}

glm::vec3 Input::GetObjectSpaceCoords(glm::mat4& viewMatrix, glm::mat4& projMatrix, float fWidth, float fHeight)
{
	/* returns vector to point in object space which has been clicked in window space */
	GLfloat depth;
	glReadPixels(Input::mX, fHeight - Input::mY - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

	glm::vec4 viewport = glm::vec4(0, 0, fWidth, fHeight);
	glm::vec3 wincoord = glm::vec3(Input::mX, fHeight - Input::mY - 1, depth);
	glm::vec3 objcoord = glm::unProject(wincoord, viewMatrix, projMatrix, viewport);

	return objcoord;
}