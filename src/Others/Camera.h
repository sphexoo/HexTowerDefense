#pragma once
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

class Cursor;

class Camera
{
private:
	glm::vec3 pos;
	glm::vec3 dir;
	glm::vec3 up;

	float fSpeed = 0.2f;
	float fMaxHeight = 30.0f;

	float fZoom = 50.0f;
	int iZoomTarget = 50;
	float fAngle = 0.0f;

	int iPosXTarget = 13;
	int iPosYTarget = -13;

	float fBorder = 75.0f;

	float fWidth;
	float fHeight;
	float iTilesX;
	float iTilesY;

	bool reset = false;

public: 
	glm::mat4 viewMatrix;

public: 
	Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up, float fWidth, float fHeight);
	~Camera();

	void Animate();
	void Update();
};