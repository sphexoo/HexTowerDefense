#pragma once
#include "Renderer.h"
#include "Model.h"

class Entity
{
public:
	int x, y;
	glm::vec3 pos;
	glm::vec3 pos_model;
	glm::mat4 modelMatrix;

	Model model;

public:
	Entity();
	~Entity();
	void Draw(Renderer& renderer, glm::mat4& viewMatrix);
	void DrawDepth(Renderer& renderer, glm::mat4& viewMatrix);
	virtual void Update() = 0;
};