#include "Playfield.h"
#include "Hexagon.h"
#include "VertexBuffer.h"
#include "VertexAttributes.h"
#include "IndexBuffer.h"

Playfield::Playfield()
{
	tiles.reserve(iTilesX * iTilesY);

	for (int x = -iTilesX / 2; x < iTilesX / 2; x++)
	{
		for (int y = -iTilesY / 2; y < iTilesY / 2; y++)
		{
			float posX = 2.0f * cos((float)M_PI / 6.0f);
			float posY = 3.0f * sin((float)M_PI / 6.0f);

			float c = (float)((double)rand() / (RAND_MAX));

			glm::vec4 color = glm::vec4(c, c, c, 1.0f);

			if (y % 2 == 0)
			{
				//tiles.emplace_back(x * posX, y * posY, 0.0f, color);
				std::vector<float> tile = GetVertexPositions(x * posX, y * posY, 0.0f);
				vertices.insert(vertices.end(), tile.begin(), tile.end());

				std::vector<unsigned int> ind = GetIndexValues(vertices.size() / 3);
				indices.insert(indices.end(), ind.begin(), ind.end());
			}
			else
			{
				//tiles.emplace_back(x * posX + cos((float)M_PI / 6.0f), y * posY, 0.0f, color);
				std::vector<float> tile = GetVertexPositions(x * posX + cos((float)M_PI / 6.0f), y * posY, 0.0f);
				vertices.insert(vertices.end(), tile.begin(), tile.end());

				std::vector<unsigned int> ind = GetIndexValues(vertices.size() / 3);
				indices.insert(indices.end(), ind.begin(), ind.end());
			}
		}
	}

	vb = new VertexBuffer(&vertices[0], sizeof(float) * vertices.size());
	ib = new IndexBuffer(&indices[0], indices.size());
	va = new VertexAttributes(true, 3, false, 0);
}

Playfield::~Playfield()
{
	delete vb;
	delete va;
	delete ib;
}

void Playfield::Draw(Renderer& renderer, Shader& shader, glm::mat4 viewMatrix)
{
	renderer.Draw3Dbasic(*vb, *va, *ib, shader, viewMatrix, modelMatrix, color);
}

std::vector<float> Playfield::GetVertexPositions(float x, float y, float z)
{
	std::vector<float> out = vertex;

	for (int i = 0; i < vertex.size(); i = i + 3)
	{
		out[i]     += x;
		out[i + 1] += y;
		out[i + 2] += z;
	}

	return out;
}

std::vector<unsigned int> Playfield::GetIndexValues(int shift)
{
	std::vector<unsigned int> out = index;

	for (int i = 0; i < index.size(); i++)
	{
		out[i] += shift;
	}

	return out;
}

void Playfield::Update(glm::vec3& pos)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i].selected = false;
	}
	Hexagon* tile = GetTile(pos);
	if (tile != nullptr)
	{
		tile->selected = true;
	}
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
	return nullptr; 
}