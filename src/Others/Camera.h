#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"


class Camera
{
private:
	glm::vec3 pos;
	glm::vec3 dir;
	glm::vec3 up;
public: 
	glm::mat4 viewMatrix;

public: 
	Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up);
	~Camera();

	void Update();
};