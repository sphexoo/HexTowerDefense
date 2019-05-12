#include <GL/glew.h>

#include "Playfield.h"
#include "VertexBuffer.h"
#include "VertexAttributes.h"
#include "IndexBuffer.h"
#include "Entity.h"
#include "Enemy.h"

#include "Input.h"

extern Input input;

Playfield::Playfield()
{
	GenerateMesh();

	vb = new VertexBuffer(&vertices[0], sizeof(float) * vertices.size());
	ib = new IndexBuffer(&indices[0], indices.size());
	va = new VertexAttributes(true, 3, true, 4);
}

Playfield::~Playfield()
{
	delete vb;
	delete va;
	delete ib;

	for (int i = 0; i < entities.size(); i++)
	{
		delete entities[i];
	}
}

void Playfield::Draw(Renderer& renderer, Shader& shader, glm::mat4 viewMatrix)
{
	// draw playfield
	renderer.Draw3Dbasic(*vb, *va, *ib, shader, viewMatrix, modelMatrix);
}

void Playfield::DrawEntities(Renderer& renderer, Shader& shader, glm::mat4 viewMatrix)
{
	// draw entities
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->Draw(renderer, shader, viewMatrix);
	}
}

std::vector<float> Playfield::GetVertexPositions(float x, float y, float z)
{
	std::vector<float> out = vertex;

	for (int i = 0; i < vertex.size(); i = i + 7)
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

void Playfield::SetColor(int x, int y, float r, float g, float b, float a)
{
	int offset = x + y * iTilesY;

	for (int i = 0; i < 49; i = i + 7)
	{
		vertices[i + 49 * offset + 3] = r;
		vertices[i + 49 * offset + 4] = g;
		vertices[i + 49 * offset + 5] = b; 
		vertices[i + 49 * offset + 6] = a; 
	}
	vb->Bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);
}

void Playfield::SetColor(int x, int y, int type)
{
	int offset = x + y * iTilesY;

	for (int i = 0; i < 49; i = i + 7)
	{
		vertices[i + 49 * offset + 3] = fTileColors[type * 4 + 0];
		vertices[i + 49 * offset + 4] = fTileColors[type * 4 + 1];
		vertices[i + 49 * offset + 5] = fTileColors[type * 4 + 2];
		vertices[i + 49 * offset + 6] = fTileColors[type * 4 + 3];
	}
	vb->Bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);
}

void Playfield::GenerateMesh()
{
	float distX = 2.0f * cos((float)M_PI / 6.0f);
	float distY = 3.0f * sin((float)M_PI / 6.0f);

	for (int y = 0; y < iTilesY; y++)
	{
		for (int x = 0; x < iTilesX; x++)
		{
			float offset;
			if (y % 2 != 0)
			{
				offset = 0.0f;
			}
			else
			{
				offset = cos((float)M_PI / 6.0f);
			}

			tiles.emplace_back(3, x, y, glm::vec3(x * distX + offset, y * distY, 0.0f));

			std::vector<float> tile = GetVertexPositions(x * distX + offset, y * distY, 0.0f);
			vertices.insert(vertices.end(), tile.begin(), tile.end());

			std::vector<unsigned int> ind = GetIndexValues(vertices.size() / 7 - 7);
			indices.insert(indices.end(), ind.begin(), ind.end());
		}
	}
}

void Playfield::Update(glm::vec3& cursor_pos)
{
	if (input.IsPressed(Input::MOUSE_1))
	{
		Tile* selected_tile = GetTile(cursor_pos);
		if (selected_tile != nullptr)
		{
			selected_tile->type += 1;
			if (selected_tile->type > 2)
			{
				selected_tile->type = 0;
			}
			SetColor(selected_tile->x, selected_tile->y, selected_tile->type);
		}
	}
	else if (input.IsHold(Input::MOUSE_2))
	{
		Tile* selected_tile = GetTile(cursor_pos);
		if (selected_tile != nullptr)
		{
			selected_tile->type = Tile::BUILD;
			SetColor(selected_tile->x, selected_tile->y, selected_tile->type);
		}
	}
}

void Playfield::UpdateEntities()
{
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->Update();
	}
}

Playfield::Tile* Playfield::GetTile(glm::vec3& pos)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		float dist = glm::length(tiles[i].pos - pos);
		if (dist < cos((float)M_PI / 6.0f))
		{
			return &tiles[i];
		}
	}
	return nullptr;
}

bool Playfield::GeneratePath()
{
	Tile* currentTile = nullptr;
	Tile* lastTile = nullptr;
	// find spawn
	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i].type == Tile::SPAWN)
		{
			currentTile = &tiles[i];
			path.push_back(currentTile);
			break;
		}
	}

	// check if spawn was found
	if (currentTile == nullptr)
	{
		return false;
	}

	// find path from spawn to target
	std::vector<Tile*> neighbors;
	neighbors.reserve(6);
	int cnt = 100; // max number of iterations and max length of path

	while (currentTile->type != Tile::TARGET && cnt > 0)
	{
		int x = currentTile->x;
		int y = currentTile->y;
		cnt--;

		// left neighbor 
		if (x > 0)
		{
			neighbors.push_back(&tiles[(x - 1) + y * iTilesY]);
		}
		// right neighbor 
		if (x < iTilesX - 1)
		{
			neighbors.push_back(&tiles[(x + 1) + y * iTilesY]);
		}
		

		if (currentTile->y % 2 != 0)
		{	
			// bottom neighbors (if current row is odd)
			if (y > 0)
			{
				neighbors.push_back(&tiles[x + (y - 1) * iTilesY]);
				if (x > 0)
				{
					neighbors.push_back(&tiles[(x - 1) + (y - 1) * iTilesY]);
				}
			}
			// top neighbors (if current row is odd)
			if (y < iTilesY - 1)
			{
				neighbors.push_back(&tiles[x + (y + 1) * iTilesY]);
				if (x > 0)
				{
					neighbors.push_back(&tiles[(x - 1) + (y + 1) * iTilesY]);
				}
			}
		}
		else
		{
			// bottom neighbors (if current row is even)
			if (y > 0)
			{
				neighbors.push_back(&tiles[x + (y - 1) * iTilesY]);
				if (x < iTilesX - 1)
				{
					neighbors.push_back(&tiles[(x + 1) + (y - 1) * iTilesY]);
				}
			}
			// top neighbors (if current row is even)
			if (y < iTilesY - 1)
			{
				neighbors.push_back(&tiles[x + (y + 1) * iTilesY]);
				if (x < iTilesX - 1)
				{
					neighbors.push_back(&tiles[(x + 1) + (y + 1) * iTilesY]);
				}
			}
		}

		// find next tile
		for (int i = 0; i < neighbors.size(); i++)
		{
			if (neighbors[i] != lastTile && (neighbors[i]->type == Tile::PATH || neighbors[i]->type == Tile::TARGET))
			{
				lastTile = currentTile;
				currentTile = neighbors[i]; 
				path.push_back(currentTile);
				break; 
			}
		}
		neighbors.clear();
	}

	// check if path is valid (current tile is of type Tile::TARGET)
	if (currentTile->type == Tile::TARGET)
	{
		entities.push_back(new Enemy(this));
		return true;
	}
	return false;
}

Playfield::Tile* Playfield::GetPath(int n)
{
	/* returns nth tile in of path */
	return path[n];
}

void Playfield::ClearEntities()
{
	for (int i = 0; i < entities.size(); i++)
	{
		delete entities[i];
	}
	entities.clear();
}