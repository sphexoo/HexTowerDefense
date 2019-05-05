#include <iostream>

#include "Camera.h"
#include "Input.h"
#include "gtx/rotate_vector.hpp"

extern Input input;

Camera::Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up, float fWidth, float fHeight)
	: pos(pos), dir(dir), up(up), fWidth(fWidth), fHeight(fHeight)
{
	/* initial creaton of camera object. view matrix is initialized */
	viewMatrix = glm::lookAt(pos, dir, up);
}

Camera::~Camera()
{

}

void Camera::Update(float cursorX, float cursorY)
{
	if (cursorY < pos.y - 5.0f)
	{
		pos.y -= fSpeed;
	}
	else if (cursorY > pos.y + 25.0f)
	{
		pos.y += fSpeed;
	}

	if (cursorX < pos.x - 25.0f)
	{
		pos.x -= fSpeed;
	}
	else if (cursorX > pos.x + 25.0f)
	{
		pos.x += fSpeed;
	}


	// up down movement and tilt (Animated by setting a target value and changing fZoom towards that target every frame)
	if (Input::scroll != 0)
	{
		iZoomTarget -= Input::scroll * 10;
		if (iZoomTarget > 90)
		{
			iZoomTarget = 90;
		}
		else if (iZoomTarget < 10)
		{
			iZoomTarget = 10;
		}
		Input::scroll = 0;
	}

	// animation of camera view. each frame pos and dir are changed towards their defined target values
	Animate();

	// check for camera reset
	if (input.IsPressed(Input::KEY_R))
	{
		reset = true;
		iZoomTarget = 50;
		iPosXTarget = 0;
		iPosYTarget = -25;
	}

	// updating view matrix
	viewMatrix = glm::lookAt(pos, pos + dir, up);
}

void Camera::Animate()
{
	// automated animation of zoom factor is happening every frame
	if ((int)fZoom > iZoomTarget)
	{
		fZoom -= 1.0f;
	}
	else if ((int)fZoom < iZoomTarget)
	{
		fZoom += 1.0f;
	}

	// automated animation of position only happens during reset of camera view
	if (reset)
	{
		pos.z = fMaxHeight * fZoom * 0.01f;

		// vatiables wich keep track if x and y resets are finished
		bool x_reset = false;
		bool y_reset = false;

		if ((int)pos.x > iPosXTarget)
		{
			pos.x -= fSpeed;
		}
		else if ((int)pos.x < iPosXTarget)
		{
			pos.x += fSpeed;
		}
		else
		{
			x_reset = true;
		}

		if ((int)pos.y > iPosYTarget)
		{
			pos.y -= fSpeed;
		}
		else if ((int)pos.y < iPosYTarget)
		{
			pos.y += fSpeed;
		}
		else
		{
			y_reset = true;
		}

		// if x and y reset are finished, reset is set to false (it is not performed until next reset event)
		if (x_reset && y_reset)
		{
			reset = false;
		}
	}

	// setting animated dir and pos values
	dir = rotateX(glm::vec3(0.0f, 1.0f, 0.0f), -3.14159f * 0.5f * fZoom * 0.01f);
	pos.z = fMaxHeight * fZoom * 0.01f;
}