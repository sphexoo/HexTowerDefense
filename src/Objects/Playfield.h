#pragma once
#include <vector>

#include "Renderer.h"

class Hexagon;

class Playfield
{
private:
	int iTilesX = 25;
	int iTilesY = 20;

	std::vector<Hexagon> tiles;

public:
	Playfield();
	~Playfield();

	void Draw(Renderer& renderer, Shader& shader, glm::mat4 viewMatrix);
};