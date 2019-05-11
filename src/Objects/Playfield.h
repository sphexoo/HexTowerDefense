#pragma once
#include <vector>
#define _USE_MATH_DEFINES 
#include <math.h>
#include "Renderer.h"

class Hexagon;

class Playfield
{
private:
	glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 modelMatrix = glm::mat4(1.0f);

	std::vector<Hexagon> tiles;

	std::vector<float> vertices;

	std::vector<unsigned int> indices;

	std::vector<float> vertex = { 0.0f,					  0.0f, 0.0f,
								cos((float)M_PI / 6.0f),  0.5f, 0.0f,
								0.0f,					  1.0f, 0.0f,
							   -cos((float)M_PI / 6.0f),  0.5f, 0.0f,
							   -cos((float)M_PI / 6.0f), -0.5f, 0.0f,
								0.0f,					 -1.0f, 0.0f,
								cos((float)M_PI / 6.0f), -0.5f, 0.0f };

	std::vector<unsigned int> index = { 0, 1, 2,
										0, 2, 3,
										0, 3, 4,
										0, 4, 5,
										0, 5, 6,
										0, 6, 1 };

	VertexBuffer* vb;
	IndexBuffer* ib;
	VertexAttributes* va;

public:
	int iTilesX = 20;
	int iTilesY = 20;

public:
	Playfield();
	~Playfield();

	void Draw(Renderer& renderer, Shader& shader, glm::mat4 viewMatrix);
	std::vector<float> GetVertexPositions(float x, float y, float z);
	std::vector<unsigned int> GetIndexValues(int shift);
	void Update(glm::vec3& pos);
	Hexagon* GetTile(glm::vec3& pos);
};