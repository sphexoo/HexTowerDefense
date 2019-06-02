#include <GL/glew.h>
#include <iostream>
#include <gtx/rotate_vector.hpp>

#include "Playfield.h"
#include "VertexBuffer.h"
#include "VertexAttributes.h"
#include "IndexBuffer.h"
#include "Tower.h"
#include "Enemy.h"
#include "EnvObj.h"

#include "Input.h"

extern Input input;

Playfield::Playfield()
{
	/* creates playfield mesh */
	GenerateMesh();

	vb = new VertexBuffer(&vertices[0], sizeof(float) * vertices.size());
	ib = new IndexBuffer(&indices[0], indices.size());
	va = new VertexAttributes(true, 3, true, 4, false, 0);

	GenerateEnvironment(5, 8, 7);
}

Playfield::~Playfield()
{
	/* deletes all heap allocated objects */
	delete vb;
	delete va;
	delete ib;

	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		delete enemies[i];
	}

	for (unsigned int i = 0; i < towers.size(); i++)
	{
		delete towers[i];
	}

	for (unsigned int i = 0; i < envobjects.size(); i++)
	{
		delete envobjects[i];
	}
}

void Playfield::Draw(Renderer& renderer, Shader& shader, glm::mat4 viewMatrix)
{
	/* draws playfield */
	renderer.Draw3Dbasic(*vb, *va, *ib, shader, viewMatrix, modelMatrix);
}

void Playfield::DrawEntities(Renderer& renderer, Shader& shader, glm::mat4 viewMatrix)
{
	/* draws entities */
	// draw enemies
	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Draw(renderer, shader, viewMatrix);
	}

	// draw towers
	for (unsigned int i = 0; i < towers.size(); i++)
	{
		towers[i]->Draw(renderer, shader, viewMatrix);
	}

	// draw environmental objects
	for (unsigned int i = 0; i < envobjects.size(); i++)
	{
		envobjects[i]->Draw(renderer, shader, viewMatrix);
	}
}

std::vector<float> Playfield::GetVertexPositions(float x, float y, float z)
{
	/* creates vertex positions for mesh building */
	std::vector<float> out = vertex;

	for (unsigned int i = 0; i < vertex.size(); i = i + 7)
	{
		out[i]     += x;
		out[i + 1] += y;
		out[i + 2] += z;
	}

	return out;
}

std::vector<unsigned int> Playfield::GetIndexValues(int shift)
{
	/* creates indices for mesh building */
	std::vector<unsigned int> out = index;

	for (unsigned int i = 0; i < index.size(); i++)
	{
		out[i] += shift;
	}

	return out;
}

void Playfield::SetColor(int x, int y, float r, float g, float b, float a)
{
	/* changes vertices color to custom color attribute of hexagon at position x, y */
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
	/* changes vertices color tile color attribute of hexagon at position x, y */
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
	/* generate playfield mesh */
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


void Playfield::Update(glm::mat4& viewMatrix, glm::mat4& projMatrix, float fWidth, float fHeight)
{
	/* updates playfield colors based in mouse input */
	if (input.IsPressed(Input::MOUSE_1))
	{
		glm::vec3 cursor_pos = Input::GetObjectSpaceCoords(viewMatrix, projMatrix, fWidth, fHeight);
		Tile* selected_tile = GetTile(cursor_pos);
		if (selected_tile != nullptr && selected_tile->type != Tile::ENVOBJ)
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
		glm::vec3 cursor_pos = Input::GetObjectSpaceCoords(viewMatrix, projMatrix, fWidth, fHeight);
		Tile* selected_tile = GetTile(cursor_pos);
		if (selected_tile != nullptr)
		{
			selected_tile->type = Tile::BUILD;
			SetColor(selected_tile->x, selected_tile->y, selected_tile->type);
		}
	}
}

void Playfield::Update2(glm::mat4& viewMatrix, glm::mat4& projMatrix, float fWidth, float fHeight)
{
	/* updates playfield entities based on mouse input */
	if (input.IsPressed(Input::MOUSE_1))
	{
		glm::vec3 cursor_pos = Input::GetObjectSpaceCoords(viewMatrix, projMatrix, fWidth, fHeight);
		Tile* selected_tile = GetTile(cursor_pos);
		if (selected_tile != nullptr && selected_tile->type == Tile::BUILD)
		{
			if (selected_tile->tower == nullptr)
			{
				// create tower
				towers.push_back(new Tower(this, selected_tile->pos));
				selected_tile->tower = towers.back();
			}
			else
			{
				// destroy tower
				delete selected_tile->tower;

				for (unsigned int i = 0; i < towers.size(); i++)
				{
					if (selected_tile->tower == towers[i])
					{
						towers.erase(towers.begin() + i);
						break;
					}
				}

				selected_tile->tower = nullptr;
			}
		}
	}
}

void Playfield::UpdateEntities()
{
	/* call update method for all entites */
	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Update();
	}

	for (unsigned int i = 0; i < towers.size(); i++)
	{
		towers[i]->Update();
	}
}

Playfield::Tile* Playfield::GetTile(glm::vec3& pos)
{
	/* returns tile pointer if there is one within hexagon radius */
	for (unsigned int i = 0; i < tiles.size(); i++)
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
	/* generates path based on selected tile types.
	   returns true if paths is valid. */
	Tile* currentTile = nullptr;
	Tile* lastTile = nullptr;
	// find spawn
	for (unsigned int i = 0; i < tiles.size(); i++)
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
		for (unsigned int i = 0; i < neighbors.size(); i++)
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
		enemies.push_back(new Enemy(this));
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
	/* clears all entities */

	// clear enemies
	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		delete enemies[i];
	}
	enemies.clear();

	// clear towers
	for (unsigned int i = 0; i < towers.size(); i++)
	{
		delete towers[i];
	}
	towers.clear();

	// set tower pointers of all tiles to nullptr
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		tiles[i].tower = nullptr;
	}

	/*
	// clear environmental objects
	for (unsigned int i = 0; i < envobjects.size(); i++)
	{
		delete envobjects[i];
	}
	envobjects.clear();
	*/
}

void Playfield::ClearEnemies()
{
	/* clears only enemies */
	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		delete enemies[i];
	}
	enemies.clear();
}

void Playfield::ClearTowers()
{
	/* clears only towers */
	for (unsigned int i = 0; i < towers.size(); i++)
	{
		delete towers[i];
	}
	towers.clear();

	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		tiles[i].tower = nullptr;
	}
}

void Playfield::ClearEnvObjects()
{
	/* clears only enemies */
	for (unsigned int i = 0; i < envobjects.size(); i++)
	{
		delete envobjects[i];
	}
	envobjects.clear();
}


Enemy* Playfield::GetEnemy(unsigned int num)
{
	/* returns enemy pointer of nth enemy. returns nullptr if there are no enemies */
	if (enemies.size() > num)
	{
		return enemies[num];
	}
	return nullptr;
}

void Playfield::ClearEnemy(Enemy* enemy)
{
	/* deletes enemy pointed at */
	delete enemy;
	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i] == enemy)
		{
			enemies.erase(enemies.begin() + i);
			break;
		}
	}
}

void Playfield::SpawnEnemy()
{
	/* spawns a new enemy if there is a path specified */
	if (path.size() > 0)
	{
		enemies.push_back(new Enemy(this));
	}
}

void Playfield::GenerateEnvironment(int type1, int type2, int type3)
{
	// reset all tiles with current type ENVOBJ to BUILD
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i].type == Tile::ENVOBJ)
		{
			tiles[i].type = Tile::BUILD;
		}
	}

	// create vector to store tile pointers to tiles which get env objects
	std::vector<Tile*> tmpTiles;
	tmpTiles.reserve(type1 + type2 + type3);

	for (int i = 0; i < (type1 + type2 + type3); i++)
	{
		// randomize tile
		int iPosX = (int)(((double)rand() / RAND_MAX) * iTilesX);
		int iPosY = (int)(((double)rand() / RAND_MAX) * iTilesY);

		// check if random tile is free to build
		if (tiles[iPosX + iTilesY * iPosY].type == Tile::BUILD)
		{
			// add tile to tmp list and change type to ENVOBJ
			tmpTiles.push_back(&tiles[iPosX + iTilesY * iPosY]);
			tiles[iPosX + iTilesY * iPosY].type = Tile::ENVOBJ;
		}
		else
		{
			// repeat iteration of for loop
			i--;
		}
	}

	// Add enviromental objects
	for (unsigned int i = 0; i < tmpTiles.size(); i++)
	{
		// generating random offset from center of target tile (max distance from center is specified with parameter )
		float fOffset = (float)((double)rand() / RAND_MAX) * fMaxRadius;
		float fAngle = (float)((double)rand() / RAND_MAX) * 2.0f * (float)M_PI;

		glm::vec3 offset = glm::rotateZ(glm::vec3(fOffset, 0.0f, 0.0f), fAngle);
		glm::vec3 finalPos = glm::vec3(tmpTiles[i]->pos.x, tmpTiles[i]->pos.y, 0.0f) + offset;

		if (type1 > 0)
		{
			envobjects.push_back(new EnvObj(this, EnvObj::TREE, finalPos));
			type1--;
		}
		else if (type2 > 0)
		{
			envobjects.push_back(new EnvObj(this, EnvObj::GRASS, finalPos));
			type2--;
		}
		else if (type3 > 0)
		{
			envobjects.push_back(new EnvObj(this, EnvObj::STONE, finalPos));
			type3--;
		}
	}
}