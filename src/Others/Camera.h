#pragma once
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

class Camera
{
private:
	float fSpeed = 0.25f;
	float fAngSpeed = 0.005f;

	glm::vec3 pos;
	glm::vec3 dir;
	glm::vec3 up;

	glm::vec3 vel;

	float fMaxHeight = 20.0f;
	float fZoom = 0.5f;
	float fAngle = 0.0f;

	float prevMouseX = 0.0f;
	float prevMouseY = 0.0f;

	float fWidth;
	float fHeight;

public: 
	glm::mat4 viewMatrix;

public: 
	Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up, float fWidth, float fHeight);
	~Camera();

	void Update();
};