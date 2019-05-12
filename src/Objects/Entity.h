#pragma once
#include "Renderer.h"
#include "Model.h"

class Entity
{
public:
	int x, y;
	glm::vec3 pos;
	glm::mat4 modelMatrix;

	Model model;

public:
	Entity();
	~Entity();
	void Draw(Renderer& renderer, Shader& shader, glm::mat4& viewMatrix);
	virtual void Update() = 0;
};