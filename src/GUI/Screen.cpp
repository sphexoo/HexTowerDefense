#include "Screen.h"

/* Access the logger object globally created in Application.cpp */
extern Logger logger;

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
	//elements.push_back(new ButtonBox(fPosX, fPosY, path, handlerFcn, handleToValue));
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

void Screen::CheckHover(bool& mouse1, double mouseX, double mouseY)
{
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		if (mouseX > elements[i]->pos.x - elements[i]->fWidth / 2.0f && mouseX < elements[i]->pos.x + elements[i]->fWidth / 2.0f &&
			mouseY > elements[i]->pos.y - elements[i]->fHeight / 2.0f && mouseY < elements[i]->pos.y + elements[i]->fHeight / 2.0f)
		{
			elements[i]->OnHover();

			if (mouse1)
			{
				elements[i]->OnClick();
				mouse1 = false;
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