#include <iostream>

#include "Camera.h"
#include "Input.h"
#include "gtx/rotate_vector.hpp"

extern Input input;

Camera::Camera(glm::vec3 lookFromDefault, glm::vec3 lookToDefault, glm::vec3 lookUp, float fWidth, float fHeight)
	: lookFromDefault(lookFromDefault), lookToDefault(lookToDefault), lookUp(lookUp), fWidth(fWidth), fHeight(fHeight)
{
	/* initial creaton of camera object. view matrix is initialized */
	lookFrom = lookFromDefault;
	lookTo = lookToDefault;

	// setting initial camera height depending on specified camera position
	fCameraHeight = lookFromDefault.z;
	iCameraHeightTarget = (int)fCameraHeight;
	
	// creating view matrix from camera position and direction
	viewMatrix = glm::lookAt(lookFrom, lookTo, lookUp);
}

Camera::~Camera()
{

}

void Camera::Update()
{
	// left-right movement
	if (Input::mX < fBorder)
	{
		glm::vec3 vel = lookTo - lookFrom;
		vel.z = 0.0f;
		vel = glm::normalize(vel);
		vel = glm::rotateZ(vel, 0.5f * 3.14159f);

		lookFrom += vel * fSpeed;
		lookTo += vel * fSpeed;
	}
	else if (Input::mX > fWidth - fBorder)
	{
		glm::vec3 vel = lookTo - lookFrom;
		vel.z = 0.0f;
		vel = glm::normalize(vel);
		vel = glm::rotateZ(vel, -0.5f * 3.14159f);

		lookFrom += vel * fSpeed;
		lookTo += vel * fSpeed;
	}

	// forward / backward movement
	if (Input::mY < fBorder)
	{
		glm::vec3 vel = lookTo - lookFrom;
		vel.z = 0.0f;
		vel = glm::normalize(vel);
		
		lookFrom += vel * fSpeed;
		lookTo += vel * fSpeed;
	}
	else if (Input::mY > fHeight - fBorder)
	{
		glm::vec3 vel = lookTo - lookFrom;
		vel.z = 0.0f;
		vel = glm::normalize(vel);
		
		lookFrom -= vel * fSpeed;
		lookTo -= vel * fSpeed;
	}

	// rotate around current lookTo
	if (input.IsHold(Input::MOUSE_3))
	{
		lookFrom = lookFrom - lookTo;
		lookFrom = glm::rotateZ(lookFrom, -Input::dX *fAngSpeed);
		lookFrom = lookFrom + lookTo;

		Input::dX = 0.0f;
	}

	// up down movement and tilt (Animated by setting a target value and changing fZoom towards that target every frame)
	if (Input::scroll != 0)
	{
		iCameraHeightTarget -= Input::scroll * 2;

		if (iCameraHeightTarget > 50)
		{
			iCameraHeightTarget = 50;
		}
		else if (iCameraHeightTarget < 0)
		{
			iCameraHeightTarget = 0;
		}

		Input::scroll = 0;
	}

	// animation of camera view. each frame pos and dir are changed towards their defined target values
	Animate();

	// check for camera reset
	if (input.IsPressed(Input::KEY_R))
	{
		// reset camera height values for zoom animation without reset
		iCameraHeightTarget = (int)lookFromDefault.z;
		fCameraHeight = lookFromDefault.z;
		// create vectors to change lookFrom and lookAt every frame to generate reset animation
		iResetSteps = 50;
		lookFromReset = (lookFromDefault - lookFrom) * 1.0f / (float)iResetSteps;
		lookToReset = (lookToDefault - lookTo) * 1.0f / (float)iResetSteps;
	}

	// updating view matrix
	viewMatrix = glm::lookAt(lookFrom, lookTo, lookUp);
}

void Camera::Animate()
{
	// automated animation of position only happens during reset of camera view
	if (iResetSteps > 0)
	{
		lookFrom += lookFromReset;
		lookTo += lookToReset;
		iResetSteps--;
	}
	// automated animation of zoom factor is happening every frame
	else if ((int)fCameraHeight < iCameraHeightTarget)
	{
		fCameraHeight += 0.25f;
		lookFrom.z = fCameraHeight;
	}
	else if ((int)fCameraHeight > iCameraHeightTarget)
	{
		fCameraHeight -= 0.25f;
		lookFrom.z = fCameraHeight;
	}
}