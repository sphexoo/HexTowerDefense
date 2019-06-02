#include <GLFW/glfw3.h>
#include <iostream>

#include "Gui.h"
#include "Playfield.h"
#include "StateHandler.h"

#include "Input.h"

extern Input input;

GLFWwindow* StateHandler::window;
Gui* StateHandler::gui;
Playfield* StateHandler::playfield;
int StateHandler::state;

StateHandler::StateHandler(GLFWwindow* window, Gui* gui, Playfield* playfield, State state)
{
	/* creates an instance of the state handler. */
	StateHandler::window = window;
	StateHandler::gui = gui;
	StateHandler::playfield = playfield;
	StateHandler::state = state;
}

StateHandler::~StateHandler()
{

}

void StateHandler::SetState(int state)
{
	/* updates current state to specified state.
	sets additional state specific parameters (e.g. mouse lock) */

	if (StateHandler::state != state)
	{
		StateHandler::state = state;

		if (IsState(Running))
		{

		}
		else if (IsState(MainMenue))
		{
			gui->SwitchScreen("MainMenue");
		}
		else if (IsState(Startup))
		{
			SetState(MainMenue);
		}
		else if (IsState(Pause))
		{
			gui->SwitchScreen("Pause");
		}
		else if (IsState(Restart))
		{
			playfield->ClearEnemies();
			playfield->SpawnEnemy();

			SetState(Running);
		}
		else if (IsState(LevelEditor))
		{
			playfield->ClearEnvObjects();
			playfield->GenerateEnvironment(5, 0, 12);
			
			playfield->path.clear();
		}
		else if (IsState(PauseLevelEditor))
		{

			playfield->ClearEntities();
			gui->SwitchScreen("PauseLevelEditor");
		}
		else if (IsState(SaveLevel))
		{
			// saving created level (to be implemented)


			bool validPath = playfield->GeneratePath();
			
			if (validPath)
			{
				SetState(MainMenue);
			}
			else
			{
				SetState(LevelEditor);
			}
			
		}
		else
		{

		}
	}
}

bool StateHandler::IsState(State state)
{
	/* returns true if specified state matches current state */
	return (StateHandler::state == state);
}