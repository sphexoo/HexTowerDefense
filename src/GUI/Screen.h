#pragma once
#include <vector>


#include "ScreenElement.h"

#include "Renderer.h"
#include "Logger.h"

typedef void(*fcnPtr)(int state);

class Screen
{
public:
	float fWidth;
	float fHeight;
	std::string name;
	std::vector<ScreenElement*> elements;

public:
	Screen(std::string name, float fWidth, float fHeight);
	~Screen();
	ScreenElement* AddImageBox(float fPosX, float fPosY, float fScale, std::string path);
	void AddButtonBox(float fPosX, float fPosY, std::string path, fcnPtr handlerFcn, int handleToValue = 0);
	void AddTextBox(float fPosX, float fPosY, float charSize, std::string text, int* handle = nullptr);
	void Draw(Renderer& renderer);
	void CheckHover();
	void Update();
};