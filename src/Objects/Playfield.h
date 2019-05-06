#pragma once
#include <vector>

#include "Renderer.h"

class Hexagon;

class Playfield
{
private:
	std::vector<Hexagon> tiles;

public:
	int iTilesX = 20;
	int iTilesY = 20;

public:
	Playfield();
	~Playfield();

	void Draw(Renderer& renderer, Shader& shader, glm::mat4 viewMatrix);
	void Change();
	void Update(glm::vec3& pos);
	Hexagon* GetTile(glm::vec3& pos);
};