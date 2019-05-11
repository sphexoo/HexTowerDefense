#pragma once
#include <vector>
#define _USE_MATH_DEFINES 
#include <math.h>
#include "Renderer.h"

class Cursor;

class Playfield
{
private:

	struct Tile
	{
		int x, y;
		glm::vec3 pos;
		bool selected;

		Tile(bool selected, int x, int y, glm::vec3 pos) : selected(selected), x(x), y(y), pos(pos) {}
	};

	glm::mat4 modelMatrix = glm::mat4(1.0f);

	std::vector<Tile> tiles;

	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	
	std::vector<float> vertex = { 0.0f,					  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
								cos((float)M_PI / 6.0f),  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
								0.0f,					  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
							   -cos((float)M_PI / 6.0f),  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
							   -cos((float)M_PI / 6.0f), -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
								0.0f,					 -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
								cos((float)M_PI / 6.0f), -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};

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
	int iTilesX = 25;
	int iTilesY = 25;

public:
	Playfield();
	~Playfield();

	void Draw(Renderer& renderer, Shader& shader, glm::mat4 viewMatrix);
	std::vector<float> GetVertexPositions(float x, float y, float z);
	std::vector<unsigned int> GetIndexValues(int shift);
	void GenerateMesh();
	void SetColor(int x, int y, float r, float g, float b, float a);
	void Update(glm::vec3& pos);
	Tile* GetTile(glm::vec3& pos);
};