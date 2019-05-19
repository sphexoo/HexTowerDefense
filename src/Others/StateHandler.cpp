#include <GLFW/glfw3.h>
#include <iostream>

#include "Playfield.h"
#include "Gui.h"
#include "StateHandler.h"
#include "Cursor.h"
#include "Input.h"

extern Input input;

GLFWwindow* StateHandler::window;
Gui* StateHandler::gui;
Playfield* StateHandler::playfield;
Cursor* StateHandler::cursor;
int StateHandler::state;

StateHandler::StateHandler(GLFWwindow* window, Gui* gui, Playfield* playfield, Cursor* cursor, State state)
{
	/* creates an instance of the state handler. */
	StateHandler::window = window;
	StateHandler::gui = gui;
	StateHandler::playfield = playfield;
	StateHandler::cursor = cursor;
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
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			input.ResetMouse();
		}
		else if (IsState(MainMenue))
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			gui->SwitchScreen("MainMenue");
		}
		else if (IsState(Startup))
		{
			SetState(MainMenue);
		}
		else if (IsState(Pause))
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			gui->SwitchScreen("Pause");
		}
		else if (IsState(LevelEditor))
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			input.ResetMouse();
			playfield->path.clear();
		}
		else if (IsState(PauseLevelEditor))
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}
}

bool StateHandler::IsState(State state)
{
	/* returns true if specified state matches current state */
	return (StateHandler::state == state);
}