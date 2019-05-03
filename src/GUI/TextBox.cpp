#include "TextBox.h"

TextBox::TextBox(float x, float y, float charSize, std::string text)
{
	texture = new Texture("res/textures/char_map.png");
	this->fWidth = (float)texture->GetWidth();
	this->fHeight = (float)texture->GetHeight();
	this->charSize = charSize;
	this->scaleMax = 1.0f;
	this->scaleMin = 1.0f;

	pos = glm::vec3(x - fWidth / charCols * text.size() * charSize / 2.0f, y - fHeight / charRows * charSize / 2.0f, 0.0f);

	this->text = text;

	SetVertices();
	
	vb = new VertexBuffer(&verticesList[0], sizeof(float) * 20 * text.size());
	ib = new IndexBuffer(&indicesList[0], 6 * text.size());
	va = new VertexAttributes(true, 3, true, 2);

	modelMatrix = glm::translate(glm::mat4(1.0f), pos);
}

TextBox::~TextBox()
{
	delete vb;
	delete ib;
	delete va;
	delete texture;
}

void TextBox::SetVertices()
{
	int numChars = text.size();
	int countVerticesList = 0; 
	int countIndicesList = 0;
	for (int i = 0; i < numChars; i++)
	{
		int row;
		int n = text.at(i);
		if (n > 96 && n < 123) // n liegt zwischen a und z
		{
			n = n - 'a';
			row = 0;
		}
		else if (n > 64 && n < 91) // n liegt zwischen A und Z
		{
			n = n - 'A';
			row = 1;
		}
		else if (n > 47 && n < 58) // n liegt zwischen 0 und 9
		{
			n = n - '0';
			row = 2;
		}
		else
		{
			n = (int)charCols;
			row = (int)charRows;
		}
		
		verticesList.insert(verticesList.end(), vertices.begin(), vertices.end());
		countVerticesList += 20;
		for (int j = 0; j < 20; j = j + 5)
		{
			// x, y coordinates
			verticesList[countVerticesList - 20 + j + 0] = charSize * (verticesList[countVerticesList - 20 + j + 0] * fWidth / charCols + fWidth / charCols * i);
			verticesList[countVerticesList - 20 + j + 1] = charSize * (verticesList[countVerticesList - 20 + j + 1] * fHeight / charRows);
			// texture coordinates
			verticesList[countVerticesList - 20 + j + 3] = n / charCols + verticesList[countVerticesList - 20 + j + 3] / charCols;
			verticesList[countVerticesList - 20 + j + 4] = row / charRows + verticesList[countVerticesList - 20 + j + 4] / charRows;
			if (n == -65 && false)
			{
				//check for space
				verticesList[countVerticesList - 20 + j + 3] = 0.0f;
				verticesList[countVerticesList - 20 + j + 4] = 0.0f;
			}
		}
		
		indicesList.insert(indicesList.end(), indices.begin(), indices.end());
		countIndicesList += 6;
		for (int j = 0; j < 6; j++)
		{
			indicesList[countIndicesList - 6 + j] += i * 4;
		}
	}
}