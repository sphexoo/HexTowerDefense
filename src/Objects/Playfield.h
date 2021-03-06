#pragma once
#include <vector>
#define _USE_MATH_DEFINES 
#include <math.h>
#include "Renderer.h"
#include "Entity.h"

class Cursor;
class Enemy;
class Tower;
class EnvObj;

class Playfield : public Entity
{
public:
	struct Tile
	{
		enum TYPE
		{
			PATH = 0,
			SPAWN = 1,
			TARGET = 2,
			BUILD = 3,
			ENVOBJ = 4
		};
		int x, y;
		int type;
		glm::vec3 pos;
		Tower* tower = nullptr;

		Tile(int type, int x, int y, glm::vec3 pos) : type(type), x(x), y(y), pos(pos) {}
	};

	std::vector<Tile*> path;

	int iTilesX = 11;
	int iTilesY = 11;

	glm::mat4 modelMatrix = glm::mat4(1.0f);

	std::vector<Enemy*> enemies;
	std::vector<Tower*> towers;
	std::vector<EnvObj*> envobjects;

private:
	std::vector<float> fTileColors = {  0.0f, 0.8f, 0.0f,		// Path
										0.8f, 0.0f, 0.0f,		// Spawn
										1.0f, 0.8f, 0.0f,		// Target
										0.5f, 0.5f, 0.5f  };	// Build

	std::vector<Tile> tiles;

	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	
	std::vector<float> vertex = { 0.0f,					  0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f,
								cos((float)M_PI / 6.0f),  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f,
								0.0f,					  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f,
							   -cos((float)M_PI / 6.0f),  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f,
							   -cos((float)M_PI / 6.0f), -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f,
								0.0f,					 -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f,
								cos((float)M_PI / 6.0f), -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f };

	std::vector<unsigned int> index = { 0, 1, 2,
										0, 2, 3,
										0, 3, 4,
										0, 4, 5,
										0, 5, 6,
										0, 6, 1 };

	float fMaxRadius = 0.25f;

public:
	Playfield();
	~Playfield();

	void Draw(Renderer& renderer, const glm::mat4 viewMatrix);
	void DrawEntities(Renderer& renderer, Shader& shader, glm::mat4 viewMatrix) const;
	void Update() override;
	void Update(glm::mat4& viewMatrix, glm::mat4& projMatrix, float fWidth, float fHeight);
	void Update2(glm::mat4& viewMatrix, glm::mat4& projMatrix, float fWidth, float fHeight);
	void UpdateEntities();
	std::vector<float> GetVertexPositions(float x, float y, float z);
	std::vector<unsigned int> GetIndexValues(int shift);
	void GenerateMesh();
	void SetColor(int x, int y, int type);
	Tile* GetPath(int n);
	void ClearEntities();
	void ClearEnemies();
	void ClearEnvObjects();
	void ClearEnemy(Enemy* enemy);
	void ClearTowers();
	Tile* GetTile(glm::vec3& pos);
	Enemy* GetEnemy(unsigned int num);
	bool GeneratePath();
	void SpawnEnemy();
	void GenerateEnvironment(int type1, int type2, int type3);
};