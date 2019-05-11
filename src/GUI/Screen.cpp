#include <iostream>

#include "Screen.h"
#include "Input.h"

#include "ImageBox.h"
#include "ButtonBox.h"
#include "TextBox.h"

/* Access the logger object globally created in Application.cpp */
extern Logger logger;
extern Input input;

Screen::Screen(std::string name, float fWidth, float fHeight)
	: name(name), fWidth(fWidth), fHeight(fHeight)
{
}

Screen::~Screen()
{
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		delete elements[i];
	}
}

ScreenElement* Screen::AddImageBox(float fPosX, float fPosY, float fScale, std::string path)
{
	ScreenElement* tmp = new ImageBox(fPosX, fPosY, 0.01f * elements.size(), fScale, path);
	elements.push_back(tmp);
	return tmp;
}

void Screen::AddButtonBox(float fPosX, float fPosY, std::string path, fcnPtr handlerFcn, int handleToValue /*= 0*/)
{
	ScreenElement* tmp = new ButtonBox(fPosX, fPosY, path, handlerFcn, handleToValue);
	elements.push_back(tmp);
}

void Screen::AddTextBox(float fPosX, float fPosY, float charSize, std::string text, int* handle /*=nullptr*/)
{
	elements.push_back(new TextBox(fPosX, fPosY, charSize, text));

}

void Screen::Draw(Renderer& renderer, Shader& shader)
{
	for (auto element : elements)
	{
		element->Draw(renderer, shader);
	}
}

void Screen::CheckHover()
{
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		if (Input::mX > elements[i]->pos.x - elements[i]->fWidth * 0.5f &&
			Input::mX < elements[i]->pos.x + elements[i]->fWidth * 0.5f &&
			(fHeight - Input::mY) > elements[i]->pos.y - elements[i]->fHeight * 0.5f && 
			(fHeight - Input::mY) < elements[i]->pos.y + elements[i]->fHeight * 0.5f)
		{
			elements[i]->OnHover();

			if (input.IsPressed(Input::MOUSE_1))
			{
				elements[i]->OnClick();
			}
		}
		else
		{
			elements[i]->OnNoHover();
		}
	}
}

void Screen::Update()
{
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		delete elements[i];
	}
	elements.clear();
}