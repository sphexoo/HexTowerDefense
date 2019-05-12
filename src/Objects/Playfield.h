#pragma once
#include <vector>
#define _USE_MATH_DEFINES 
#include <math.h>
#include "Renderer.h"

class Cursor;
class Entity;

class Playfield
{
public:
	struct Tile
	{
		enum TYPE
		{
			PATH = 0,
			SPAWN = 1,
			TARGET = 2,
			BUILD = 3
		};
		int x, y;
		int type;
		glm::vec3 pos;

		Tile(int type, int x, int y, glm::vec3 pos) : type(type), x(x), y(y), pos(pos) {}
	};

	std::vector<Tile*> path;

	int iTilesX = 11;
	int iTilesY = 11;

private:
	std::vector<float> fTileColors = {  0.0f, 0.8f, 0.0f, 1.0f,	    // Path
										0.8f, 0.0f, 0.0f, 1.0f,	    // Spawn
										1.0f, 0.8f, 0.0f, 1.0f,		// Target
										0.5f, 0.5f, 0.5f, 1.0f, };	// Build

	glm::mat4 modelMatrix = glm::mat4(1.0f);

	std::vector<Tile> tiles;
	std::vector<Entity*> entities;

	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	
	std::vector<float> vertex = { 0.0f,					  0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f,
								cos((float)M_PI / 6.0f),  0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f,
								0.0f,					  1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f,
							   -cos((float)M_PI / 6.0f),  0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f,
							   -cos((float)M_PI / 6.0f), -0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f,
								0.0f,					 -1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f,
								cos((float)M_PI / 6.0f), -0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f};

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
	Playfield();
	~Playfield();

	void Draw(Renderer& renderer, Shader& shader, glm::mat4 viewMatrix);
	void DrawEntities(Renderer& renderer, Shader& shader, glm::mat4 viewMatrix);
	void Update(glm::vec3& cursor_pos);
	void UpdateEntities();
	std::vector<float> GetVertexPositions(float x, float y, float z);
	std::vector<unsigned int> GetIndexValues(int shift);
	void GenerateMesh();
	void SetColor(int x, int y, float r, float g, float b, float a);
	void SetColor(int x, int y, int type);
	Tile* GetPath(int n);
	void ClearEntities();
	Tile* GetTile(glm::vec3& pos);
	bool GeneratePath();
};