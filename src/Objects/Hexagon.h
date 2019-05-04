#pragma once
#include <vector>
#define _USE_MATH_DEFINES 
#include <math.h>

#include "Renderer.h"

class Hexagon
{
private:
	float fRadius;
	float fHeight;
	glm::mat4 modelMatrix;
	/*
	float vertices[35] = { 0.0f,  0.0f, 0.0f,						 0.5f, 0.5f,
							-0.5f, -cos((float)M_PI / 6.0f), 0.0f,	 sin((float)M_PI / 6.0f), 0.0f,
							 0.5f, -cos((float)M_PI / 6.0f), 0.0f,   0.5f + sin((float)M_PI / 6.0f), 0.0f,
							 1.0f,  0.0f, 0.0f,						 1.0f, 0.5f,
							 0.5f,  cos((float)M_PI / 6.0f), 0.0f,   sin((float)M_PI / 6.0f), 1.0f,
							-0.5f,  cos((float)M_PI / 6.0f), 0.0f,	 0.5f + sin((float)M_PI / 6.0f), 1.0f,
							-1.0f,  0.0f, 0.0f,						 0.0f, 0.5f };
							*/


	float vertices[21] = {   0.0f,  0.0f,					 0.0f,
							 1.0f,  0.0f,					 0.0f,
							 0.5f,  cos((float)M_PI / 6.0f), 0.0f,
							-0.5f,  cos((float)M_PI / 6.0f), 0.0f,
							-1.0f,  0.0f,					 0.0f,
							-0.5f, -cos((float)M_PI / 6.0f), 0.0f,
							 0.5f, -cos((float)M_PI / 6.0f), 0.0f  };

	unsigned int indices[18] = { 0, 1, 2,
								 0, 2, 3,
								 0, 3, 4,
								 0, 4, 5, 
								 0, 5, 6,
								 0, 6, 1 };


	VertexBuffer* vb;
	IndexBuffer* ib;
	VertexAttributes* va; 
	Texture* texture;

public:
	Hexagon();
	~Hexagon();

	void Draw(Renderer& renderer, Shader& shader, glm::mat4 viewMatrix);
	void Rotate();
};