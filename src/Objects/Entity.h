#pragma once
#include "Renderer.h"
#include "Model.h"

class Entity
{
public:
	int x, y;
	Model model;
	glm::mat4 modelMatrix;

public:
	Entity();
	~Entity();
	void Draw(Renderer& renderer, Shader& shader, glm::mat4& viewMatrix);
	virtual void Update() = 0;
};