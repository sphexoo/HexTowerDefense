#include "Gui.h"

Gui::Gui(float fWidth, float fHeight)
	: fWidth(fWidth), fHeight(fHeight)
{
	/*Contructs new Gui object*/
}

Gui::~Gui()
{
	/*Destructs existing Gui object*/
}

void Gui::Draw(Renderer& renderer, Shader& shader)
{
	/*Calls draw function of currently selected screen*/
	currentScreen->Draw(renderer, shader);
}

void Gui::CreateScreen(std::string name)
{
	/*Creates new screen and makes it the current screen*/
	screens.push_back(new Screen(name, fWidth, fHeight));
	SwitchScreen(name);
}

ScreenElement* Gui::AddImageBox(float fPosX, float fPosY, float fScale, std::string path)
{
	/*Calls AddImageBox function of currently selected screen*/
	return currentScreen->AddImageBox(fPosX, fPosY, fScale, path);
}

void Gui::AddButtonBox(float fPosX, float fPosY, std::string path, fcnPtr handlerFcn, int handleToValue /*= 0*/)
{
	/*Calls AddImageBox function of currently selected screen*/
	currentScreen->AddButtonBox(fPosX, fPosY, path, handlerFcn, handleToValue);
}

void Gui::AddTextBox(float fPosX, float fPosY, float charSize, std::string text, int* handle /*= nullptr*/)
{
	/*Calls AddTextBox function of currently selected screen*/
	currentScreen->AddTextBox(fPosX, fPosY, charSize, text, handle);
}

void Gui::SwitchScreen(std::string name)
{
	/*Switches to screen specified in input argument name*/
	for (unsigned int i = 0; i < screens.size(); i++)
	{
		if (screens[i]->name == name)
		{
			currentScreen = screens[i];
			break;
		}
	}
}

void Gui::HandleMouseInput(bool& mouse1, double mouseX, double mouseY)
{
	/*Passes mouse click event to currently selected screen*/
	currentScreen->CheckHover(mouse1, mouseX, mouseY);
}