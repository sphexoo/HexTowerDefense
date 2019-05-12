#pragma once

class StateHandler
{
	/* state handler class which manages current states and state transitions */
private:
	static GLFWwindow* window;
	static Gui* gui;
	static int state;

public:
	enum State
	{
		Startup = 0,
		Pause = 1,
		MainMenue = 2,
		Running = 3,
		Quit = 4,
		LevelEditor = 5,
		PauseLevelEditor = 6,
		SaveLevel = 7
	};

public:
	StateHandler(GLFWwindow* window, Gui* gui, State state);
	~StateHandler();
	static void SetState(int state);
	static bool IsState(State state);

	static int GetState() { return state; }
};