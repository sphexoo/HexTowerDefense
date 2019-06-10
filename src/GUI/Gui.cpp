#include "Gui.h"
#include "StateHandler.h"

/* Access the logger object globally created in Application.cpp */
extern Logger logger;

Gui::Gui(float fWidth, float fHeight, fcnPtr handlerFcn)
	: fWidth(fWidth), fHeight(fHeight)
{
	/*Contructs new Gui object*/
	CreateScreen("MainMenue");
	AddButtonBox(fWidth * 0.5f, fHeight - 3.0f * 50.0f - 0.0f * 10.0f, "res/textures/b_Start.png", handlerFcn, StateHandler::Running);
	AddButtonBox(fWidth * 0.5f, fHeight - 4.0f * 50.0f - 1.0f * 10.0f, "res/textures/b_Level_Editor.png", handlerFcn, StateHandler::LevelEditor);
	AddButtonBox(fWidth * 0.5f, fHeight - 5.0f * 50.0f - 2.0f * 10.0f, "res/textures/b_Quit.png", handlerFcn, StateHandler::Quit);

	CreateScreen("Pause");
	AddButtonBox(fWidth * 0.5f, fHeight - 3.0f * 50.0f - 0.0f * 10.0f, "res/textures/b_Resume.png", handlerFcn, StateHandler::Running);
	AddButtonBox(fWidth * 0.5f, fHeight - 4.0f * 50.0f - 1.0f * 10.0f, "res/textures/b_Restart.png", handlerFcn, StateHandler::Restart);
	AddButtonBox(fWidth * 0.5f, fHeight - 5.0f * 50.0f - 2.0f * 10.0f, "res/textures/b_Back.png", handlerFcn, StateHandler::MainMenue);

	CreateScreen("PauseLevelEditor");
	AddButtonBox(fWidth * 0.5f, fHeight - 3.0f * 50.0f - 0.0f * 10.0f, "res/textures/b_Resume.png", handlerFcn, StateHandler::LevelEditor);
	AddButtonBox(fWidth * 0.5f, fHeight - 4.0f * 50.0f - 1.0f * 10.0f, "res/textures/b_Save_Map.png", handlerFcn, StateHandler::SaveLevel);
	AddButtonBox(fWidth * 0.5f, fHeight - 5.0f * 50.0f - 2.0f * 10.0f, "res/textures/b_Back.png", handlerFcn, StateHandler::MainMenue);

	//CreateScreen("HUD");

}

Gui::~Gui()
{
	/*Destructs existing Gui object*/
}

void Gui::Draw(Renderer& renderer)
{
	/*Calls draw function of currently selected screen*/
	currentScreen->Draw(renderer);
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
			return;
		}
	}
	logger.log("Screen not found.", Logger::Warning);
}

void Gui::HandleMouseInput()
{
	/*Passes mouse click event to currently selected screen*/
	currentScreen->CheckHover();
}