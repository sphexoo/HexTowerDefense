#include "Playfield.h"
#include "Hexagon.h"

Playfield::Playfield()
{
	tiles.reserve(iTilesX * iTilesY);

	for (int x = -iTilesX / 2; x < iTilesX / 2; x++)
	{
		for (int y = -iTilesY / 2; y < iTilesY / 2; y++)
		{
			float posX = 3.0f * sin((float)M_PI / 6.0f);
			float posY = 2.0f * cos((float)M_PI / 6.0f);

			float color = ((double)rand() / (RAND_MAX));

			if (x % 2 == 0)
			{
				tiles.emplace_back(x * posX, y * posY, 0.0f, color);
			}
			else
			{
				tiles.emplace_back(x * posX, y * posY + cos((float)M_PI / 6.0f), 0.0f, color);
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