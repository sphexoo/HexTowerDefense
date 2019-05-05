#pragma once
#include "Renderer.h"

class Cursor
{
private:
	float fSpeed = 0.05f;
	float fHover = 0.1f;
	

	float prevmX = 0.0f;
	float prevmY = 0.0f;

	float vertices[20] = { -0.5, -0.5, fHover, 0.0f, 0.0f, 
						    0.5, -0.5, fHover, 1.0f, 0.0f, 
						    0.5,  0.5, fHover, 1.0f, 1.0f, 
						   -0.5,  0.5, fHover, 0.0f, 1.0f };

	unsigned int indices[6] = { 0, 1, 2,
								2, 3, 0};

	glm::mat4 modelMatrix;

	VertexBuffer* vb;
	IndexBuffer* ib;
	VertexAttributes* va;

	Texture* texture;

public:
	glm::vec3 pos;

public:
	Cursor(glm::vec3 pos);
	~Cursor();

	void Draw(Renderer& renderer, Shader& shader, glm::mat4 viewMatrix);
	void Update();
};