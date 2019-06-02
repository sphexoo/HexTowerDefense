#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Logger.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexAttributes.h"
#include "Renderer.h"
#include "Texture.h"
#include "MyImGui.h"
#include "Input.h"
#include "Camera.h"
#include "Playfield.h"
#include "Model.h"
#include "Gui.h"
#include "StateHandler.h"
#include "Enemy.h"

#include "Tower.h"

#ifdef RELEASE
	float fWidth = 1920.0f;
	float fHeight = 1080.0f;
#else
	float fWidth = 1280.0f;
	float fHeight = 720.0f;
#endif

typedef void(*fcnPtr)(int state);

/* Creating instance of Logger class and setting its log level */
Logger logger(Logger::Info);
Input input;

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	if (type != 0x8251)
	{
		fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
			type, severity, message);
	}
}

int main()
{
	/* Creating instance if class GLFWwindow */
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
	{
		logger.log("Initialisation of GLFW failed", logger.Error);
		return -1;
	}

	/* Create a windowed mode window and its OpenGL context */
	#ifdef RELEASE
		window = glfwCreateWindow((int)fWidth, (int)fHeight, "Application", glfwGetPrimaryMonitor(), NULL);
	#else
		window = glfwCreateWindow((int)fWidth, (int)fHeight, "Application", NULL, NULL);
	#endif
	
	if (!window)
	{
		logger.log("Window creation failed", logger.Error);
		glfwTerminate();
		return -1;
	}

	MyImGui debugWindow(window);
	input.SetWindowCallback(window);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // vsync off --> 0

	/* Log current OpenGL version */
	logger.log((const char*)glGetString(GL_VERSION), logger.Info);

	/* Test if glew has been initialized succesfully */
	if (glewInit() != GLEW_OK)
	{
		logger.log("GLEW has not been initialized successfully", logger.Warning);
	}

	/* Enable OpenGL Debugging */
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
	
	Gui gui(fWidth, fHeight, StateHandler::SetState);
	Playfield playfield;

	StateHandler statehandler(window, &gui, &playfield, StateHandler::Startup);

	Renderer renderer(70.0f, fWidth, fHeight, 0.01f, 1000.0f);
	Camera camera(glm::vec3(8.0f, -5.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), fWidth, fHeight);

	/* Create Shader specified in Shader.h */

	//shader_bsc.Bind();

	statehandler.SetState(StateHandler::MainMenue);

	const double maxFps = 200;
	const double maxPeriod = 1 / maxFps;
	double deltaTime, time;
	double lastTime = 0;

	/* main loop */
	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear();

		// STATE RUNNING
		if (statehandler.IsState(StateHandler::Running))
		{
			playfield.Draw(renderer, *(renderer.shader_bsc), camera.viewMatrix);

			time = glfwGetTime();
			deltaTime = time - lastTime;
			if (deltaTime > maxPeriod)
			{
				lastTime = time;

				/* Update game state */
				camera.Update();
				playfield.UpdateEntities();
				playfield.Update2(camera.viewMatrix, renderer.projMatrix3D, fWidth, fHeight);
			}

			playfield.DrawEntities(renderer, *(renderer.shader_lgt), camera.viewMatrix);

			if (input.IsPressed(Input::KEY_ESC))
			{
				statehandler.SetState(StateHandler::Pause);
			}
		}
		// STATE LEVELEDITOR
		if (statehandler.IsState(StateHandler::LevelEditor))
		{
			playfield.Draw(renderer, *(renderer.shader_bsc), camera.viewMatrix);

			time = glfwGetTime();
			deltaTime = time - lastTime;
			if (deltaTime > maxPeriod)
			{
				lastTime = time;

				/* Update game state */
				camera.Update();
				playfield.Update(camera.viewMatrix, renderer.projMatrix3D, fWidth, fHeight);
			}

			playfield.DrawEntities(renderer, *(renderer.shader_lgt), camera.viewMatrix);

			if (input.IsPressed(Input::KEY_ESC))
			{
				statehandler.SetState(StateHandler::PauseLevelEditor);
			}
		}
		// STATE PAUSE
		else if (statehandler.IsState(StateHandler::Pause))
		{
			playfield.Draw(renderer, *(renderer.shader_bsc), camera.viewMatrix);
			playfield.DrawEntities(renderer, *(renderer.shader_lgt), camera.viewMatrix);

			gui.HandleMouseInput();
			gui.Draw(renderer, *(renderer.shader_tex));
		}
		// STATE PAUSE LEVELEDITOR
		else if (statehandler.IsState(StateHandler::PauseLevelEditor))
		{
			playfield.Draw(renderer, *(renderer.shader_bsc), camera.viewMatrix);

			gui.HandleMouseInput();
			gui.Draw(renderer, *(renderer.shader_tex));
		}
		// STATE MAINMENUE
		else if (statehandler.IsState(StateHandler::MainMenue))
		{
			gui.HandleMouseInput();
			gui.Draw(renderer, *(renderer.shader_tex));
		}
		// STATE QUIT
		else if (statehandler.IsState(StateHandler::Quit))
		{
			break;
		}

		/* Draw debug window */
		debugWindow.Draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
