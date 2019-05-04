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

void Camera::Move()
{
	// forward backward movement
	if (input.IsPressed(Input::KEY_W))
	{
		pos.x += dir.x * fSpeed;
		pos.y += dir.y * fSpeed;
	}
	else if (input.IsPressed(Input::KEY_S))
	{
		pos.x -= dir.x * fSpeed;
		pos.y -= dir.y * fSpeed;
	}

	// left right movement
	if (input.IsPressed(Input::KEY_A))
	{
		glm::vec3 tmp_dir = glm::rotate(dir, 3.14159f * 0.5f, up);
		pos.x += tmp_dir.x * fSpeed;
		pos.y += tmp_dir.y * fSpeed;
	}
	else if (input.IsPressed(Input::KEY_D))
	{
		glm::vec3 tmp_dir = glm::rotate(dir, -3.14159f * 0.5f, up);
		pos.x += tmp_dir.x * fSpeed;
		pos.y += tmp_dir.y * fSpeed;
	}

	// up down movement
	if (Input::scroll != 0)
	{
		fZoom -= Input::scroll * 0.05f;
		if (fZoom > 0.9f)
		{
			fZoom = 0.9f;
		}
		else if (fZoom < 0.1)
		{
			fZoom = 0.1;
		}
		pos.z = fMaxHeight * fZoom;
		Input::scroll = 0;
	}
}

void Camera::Rotate()
{
	if (Input::mouseX != prevMouseX)
	{
		fAngle += (prevMouseX - Input::mouseX) * fAngSpeed;
		if (abs(fAngle) > 360 * 3.1415926 / 180)
		{
			fAngle = 0.0f;
		}
		prevMouseX = Input::mouseX;
	}

	dir = rotateX(glm::vec3(0.0f, 1.0f, 0.0f), -3.14159f * 0.5f * fZoom);
	dir = glm::rotateZ(dir, fAngle);
}

void Camera::Update()
{
	Move();
	Rotate();
	
	viewMatrix = glm::lookAt(pos, pos + dir, up);
}