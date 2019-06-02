#pragma once
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

class Cursor;

class Camera
{
private:
	glm::vec3 lookFrom;
	glm::vec3 lookTo;
	glm::vec3 lookUp;

	glm::vec3 lookFromDefault;
	glm::vec3 lookToDefault;

	int iCameraHeightTarget = 20;
	float fCameraHeight = 20.0f;

	float fSpeed = 0.2f;
	float fAngSpeed = 0.01f;
	float fMaxHeight = 20.0f;

	float fZoom = 50.0f;
	int iZoomTarget = 50;
	float fAngle = 0.0f;

	int iPosXTarget = 0;
	int iPosYTarget = -0;

	float fBorder = 75.0f;

	float fWidth;
	float fHeight;
	float iTilesX;
	float iTilesY;

	int iResetSteps = 0;
	glm::vec3 lookFromReset;
	glm::vec3 lookToReset;

public: 
	glm::mat4 viewMatrix;

public: 
	Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up, float fWidth, float fHeight);
	~Camera();

	void Animate();
	void Update();
};