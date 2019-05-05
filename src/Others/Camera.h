#pragma once
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

class Camera
{
private:
	glm::vec3 pos;
	glm::vec3 dir;
	glm::vec3 up;

	float fSpeed = 0.25f;
	float fMaxHeight = 40.0f;


	float prevMouseX = 0.0f;
	float prevMouseY = 0.0f;

	float fWidth;
	float fHeight;
	float iTilesX;
	float iTilesY;

public: 
	glm::mat4 viewMatrix;

	float fZoom = 50.0f;
	int fZoomTarget = 50;
	float fAngle = 0.0f;

public: 
	Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up, float fWidth, float fHeight);
	~Camera();

	void AnimateMovement();
	void Update();
	void ResetView();
};