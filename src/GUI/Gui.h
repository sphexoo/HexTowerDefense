#pragma once

#include "Renderer.h"
#include "Screen.h"

typedef void(*fcnPtr)(int state);

class Gui
{
	/*Class for displaying 2D images onto 3D scene.
	Can handle and switch between multiple screens */
private:
	float fWidth, fHeight; // screen width and height

	Screen* currentScreen = nullptr; // pointer to current screen; can be changed with SwitchScreen method.

	std::vector<Screen*> screens; // stores all created screens

public:
	Gui(float fWidth, float fHeight, fcnPtr handlerFcn);
	~Gui();
	void Draw(Renderer& renderer);
	void CreateScreen(std::string name);
	ScreenElement* AddImageBox(float fPosX, float fPosY, float fScale, std::string path);
	void AddButtonBox(float fPosX, float fPosY, std::string path, fcnPtr handlerFcn, int handleToValue = 0);
	void AddTextBox(float fPosX, float fPosY, float charSize, std::string text, int* handle = nullptr);
	void SwitchScreen(std::string name);
	void HandleMouseInput();
};