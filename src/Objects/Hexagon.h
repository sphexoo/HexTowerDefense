#pragma once
#include <vector>
#define _USE_MATH_DEFINES 
#include <math.h>

#include "Renderer.h"

class Hexagon
{
private:
	glm::vec4 color;
	glm::vec4 colorSelected = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

	float fRadius;
	float fHeight;

	glm::mat4 modelMatrix;

	float vertices[21] = {   0.0f,					   0.0f, 0.0f,
							 cos((float)M_PI / 6.0f),  0.5f, 0.0f,
					    	 0.0f,					   1.0f, 0.0f,
					    	-cos((float)M_PI / 6.0f),  0.5f, 0.0f,
							-cos((float)M_PI / 6.0f), -0.5f, 0.0f,
							 0.0f,					  -1.0f, 0.0f,
							 cos((float)M_PI / 6.0f), -0.5f, 0.0f };

	unsigned int indices[18] = { 0, 1, 2,
								 0, 2, 3,
								 0, 3, 4,
								 0, 4, 5, 
								 0, 5, 6,
								 0, 6, 1 };

	VertexBuffer* vb;
	IndexBuffer* ib;
	VertexAttributes* va; 

public:
	glm::vec3 pos;
	bool selected = false;

public:
	Hexagon(float x, float y, float z, glm::vec4 color);
	~Hexagon();

	void Draw(Renderer& renderer, Shader& shader, glm::mat4 viewMatrix);
	void SetColor(float r, float g, float b, float a); 
};