#include "Playfield.h"
#include "Hexagon.h"

Playfield::Playfield()
{
	tiles.reserve(iTilesX * iTilesY);

	for (int x = -iTilesX / 2; x < iTilesX / 2; x++)
	{
		for (int y = -iTilesY / 2; y < iTilesY / 2; y++)
		{
			float posX = 2.0f * cos((float)M_PI / 6.0f);
			float posY = 3.0f * sin((float)M_PI / 6.0f);

			float c = (double)rand() / (RAND_MAX);

			glm::vec4 color = glm::vec4(c, c, c, 1.0f);

			if (y % 2 == 0)
			{
				tiles.emplace_back(x * posX, y * posY, 0.0f, color);
			}
			else
			{
				tiles.emplace_back(x * posX + cos((float)M_PI / 6.0f), y * posY, 0.0f, color);
			}
		}
	}
}

Playfield::~Playfield()
{

}

void Playfield::Draw(Renderer& renderer, Shader& shader, glm::mat4 viewMatrix)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i].Draw(renderer, shader, viewMatrix);
	}
}

void Playfield::Change()
{
	int x = (int)((double)rand() / (RAND_MAX) * iTilesX);
	int y = (int)((double)rand() / (RAND_MAX)* iTilesY);

	tiles[x * iTilesX + y].SetColor((double)rand() / (RAND_MAX), (double)rand() / (RAND_MAX), (double)rand() / (RAND_MAX), (double)rand() / (RAND_MAX));
}

void Playfield::Update(glm::vec3& pos)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i].selected = false;
	}

	GetTile(pos)->selected = true;
}

Hexagon* Playfield::GetTile(glm::vec3& pos)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		float dist = glm::length(tiles[i].pos - pos);
		tiles[i].selected = false;
		if (dist < cos((float)M_PI / 6.0f))
		{
			return &tiles[i];
		}
	}
}