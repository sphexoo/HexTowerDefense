#pragma once
#include <string>

#include "ScreenElement.h"

class TextBox : public ScreenElement
{
private:
	std::string text;
	float charSize = 0.5f;
	float charCols = 26.0f;
	float charRows = 3.0f; 

	std::vector<float> verticesList;
	std::vector<unsigned int> indicesList;

public:
	TextBox(float x, float y, float charSize, std::string text);
	~TextBox();
	void SetVertices();
};