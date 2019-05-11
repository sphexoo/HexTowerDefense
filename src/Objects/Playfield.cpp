#include <GL/glew.h>

#include "Playfield.h"
#include "Hexagon.h"
#include "VertexBuffer.h"
#include "VertexAttributes.h"
#include "IndexBuffer.h"

Playfield::Playfield()
{
	GenerateMesh();

	vb = new VertexBuffer(&vertices[0], sizeof(float) * vertices.size());
	ib = new IndexBuffer(&indices[0], indices.size());
	va = new VertexAttributes(true, 3, true, 4);

	SetColor(0, 0, 0.0f, 0.0f, 1.0f, 1.0f);
}

Playfield::~Playfield()
{
	delete vb;
	delete va;
	delete ib;
}

void Playfield::Draw(Renderer& renderer, Shader& shader, glm::mat4 viewMatrix)
{
	renderer.Draw3Dbasic(*vb, *va, *ib, shader, viewMatrix, modelMatrix);
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

			tiles.emplace_back(false, x, y, glm::vec3(x * distX + offset, y * distY, 0.0f));

			std::vector<float> tile = GetVertexPositions(x * distX + offset, y * distY, 0.0f);
			vertices.insert(vertices.end(), tile.begin(), tile.end());

			std::vector<unsigned int> ind = GetIndexValues(vertices.size() / 7 - 7);
			indices.insert(indices.end(), ind.begin(), ind.end());
		}
	}
}

void Playfield::Update(glm::vec3& pos)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i].selected = false;
	}
	Tile* selected_tile = GetTile(pos);
	if (selected_tile != nullptr)
	{
		SetColor(selected_tile->x, selected_tile->y, 0.0f, 1.0f, 0.0f, 1.0f);
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