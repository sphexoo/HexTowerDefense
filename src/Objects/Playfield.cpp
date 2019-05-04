#include "Playfield.h"
#include "Hexagon.h"

Playfield::Playfield()
{
	tiles.reserve(iTilesX * iTilesY);

	for (int x = 0; x < iTilesX; x++)
	{
		for (int y = 0; y < iTilesY; y++)
		{
			float posX = 3.0f * sin((float)M_PI / 6.0f);
			float posY = 2.0f * cos((float)M_PI / 6.0f);

			float color;
			if ((x + y) % 2 == 0)
			{
				color = 1.0f;
			}
			else
			{
				color = 0.0f;
			}

			if (x % 2 == 0)
			{
				tiles.emplace_back(x * posX, y * posY, (x + y) * 0.1f, color);
			}
			else
			{
				tiles.emplace_back(x * posX, y * posY + cos((float)M_PI / 6.0f), (x + y) * 0.1f, color);
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