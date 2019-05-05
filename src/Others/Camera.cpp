#include <iostream>

#include "Camera.h"
#include "Input.h"
#include "gtx/rotate_vector.hpp"

extern Input input;

Camera::Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up, float fWidth, float fHeight)
	: pos(pos), dir(dir), up(up), fWidth(fWidth), fHeight(fHeight)
{
	viewMatrix = glm::lookAt(pos, dir, up);

	ResetView();
}

Camera::~Camera()
{

}

void Camera::Update()
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

	// up down movement and tilt
	if (Input::scroll != 0)
	{
		fZoomTarget -= Input::scroll * 10;
		if (fZoomTarget > 90)
		{
			fZoomTarget = 90;
		}
		else if (fZoomTarget < 10)
		{
			fZoomTarget = 10;
		}
		Input::scroll = 0;
	}

	AnimateMovement();

	// check for camera reset
	if (input.IsPressed(Input::KEY_R))
	{
		ResetView();
	}

	// updating view matrix
	viewMatrix = glm::lookAt(pos, pos + dir, up);
}

void Camera::ResetView()
{
	/* sets camera view to initial position */
	fZoomTarget = 50;
	dir = rotateX(glm::vec3(0.0f, 1.0f, 0.0f), -3.14159f * 0.5f * fZoom * 0.01f);
	pos = glm::vec3(0.0f, -25.0f, fMaxHeight * fZoom * 0.01f);
}

void Camera::AnimateMovement()
{
	if ((int)fZoom > fZoomTarget)
	{
		fZoom -= 1.0f;
	}
	else if ((int)fZoom < fZoomTarget)
	{
		fZoom += 1.0f;
	}

	dir = rotateX(glm::vec3(0.0f, 1.0f, 0.0f), -3.14159f * 0.5f * fZoom * 0.01f);
	pos.z = fMaxHeight * fZoom * 0.01f;
}