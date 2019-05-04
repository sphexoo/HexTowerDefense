#include <iostream>

#include "Camera.h"
#include "Input.h"
#include "gtx/rotate_vector.hpp"

extern Input input;

Camera::Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up, float fWidth, float fHeight)
	: pos(pos), dir(dir), up(up), fWidth(fWidth), fHeight(fHeight)
{
	viewMatrix = glm::lookAt(pos, dir, up);
}

Camera::~Camera()
{

}

void Camera::Move()
{
	// left right movement (camera pans when cursor is close to window edge)
	if (Input::mX < fWidth * 0.1f)
	{
		pos.x -= fSpeed;
	}
	else if (Input::mX > fWidth * 0.9f)
	{
		pos.x += fSpeed;
	}

	// forward backward movement (camera pans when cursor is close to window edge)
	if (Input::mY < fHeight * 0.1f)
	{
		pos.y += fSpeed;
	}
	else if (Input::mY > fHeight * 0.9f)
	{
		pos.y -= fSpeed;
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
	dir = rotateX(glm::vec3(0.0f, 1.0f, 0.0f), -3.14159f * 0.5f * fZoom);
}

void Camera::Update()
{
	Move();
	Rotate();
	viewMatrix = glm::lookAt(pos, pos + dir, up);
}