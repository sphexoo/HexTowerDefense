#include "Camera.h"
#include "Input.h"
#include "gtx/rotate_vector.hpp"

extern Input input;

Camera::Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up)
	: pos(pos), dir(dir), up(up)
{
	viewMatrix = glm::lookAt(pos, dir, up);
}

Camera::~Camera()
{

}

void Camera::Update()
{
	// forward backward movement
	if (input.IsPressed(Input::KEY_W))
	{
		pos += dir * fSpeed;
	}
	else if (input.IsPressed(Input::KEY_S))
	{
		pos -= dir * fSpeed;
	}
	// left right movement
	if (input.IsPressed(Input::KEY_A))
	{
		pos += glm::rotate(dir, 3.14159f * 0.5f, up) * fSpeed;
	}
	else if (input.IsPressed(Input::KEY_D))
	{
		pos += glm::rotate(dir, -3.14159f * 0.5f, up) * fSpeed;
	}

	float dX = prevMouseX - Input::mouseX;
	if (dX != 0.0f)
	{
		dir = glm::rotate(dir, dX * fAngSpeed, up);
		prevMouseX = Input::mouseX;
	}

	float dY = prevMouseY - Input::mouseY;
	if (Input::mouseY != prevMouseY)
	{
		//dir = glm::rotate(dir, dX * fAngSpeed, glm::rotate(up, 3.14159f * 0.5f, dir));
		prevMouseY = Input::mouseY;
	}

	viewMatrix = glm::lookAt(pos, pos + dir, up);
}