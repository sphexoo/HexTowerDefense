#include "Camera.h"
#include "Input.h"

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
	
	if (input.IsPressed(Input::KEY_W))
	{
		pos += dir;
	}
	else if (input.IsPressed(Input::KEY_S))
	{
		pos -= dir;
	}
	viewMatrix = glm::lookAt(pos, dir, up);
}