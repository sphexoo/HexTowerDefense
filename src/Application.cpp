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
#include "Cursor.h"
#include "Model.h"
//#include "Gui.h"

#include "Hexagon.h"

#ifdef RELEASE
	float fWidth = 1920.0f;
	float fHeight = 1080.0f;
#else
	float fWidth = 1280.0f;
	float fHeight = 720.0f;
#endif


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

	//Gui gui(fWidth, fHeight);
	//gui.CreateScreen("HUD");

	void(*fcnPtr)(int state) = nullptr; 

	//gui.AddImageBox(100.0f, 100.0f, 1.0f, "res/textures/texture.png");

	Renderer renderer(70.0f, fWidth, fHeight, 0.01f, 1000.0f);
	Camera camera(glm::vec3(0.0f, -25.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), fWidth, fHeight);

	/* Create Shader specified in Shader.h */
	Shader shader_tex("res/shaders/texture_vertex.shader", "res/shaders/texture_fragment.shader");
	Shader shader("res/shaders/basic_vertex.shader", "res/shaders/basic_fragment.shader");
	shader.Bind();

	Playfield playfield;
	Cursor cursor(glm::vec3(0.0f, 0.0f, 0.0f));

	Model model;
	model.Load("res/models/monkey.obj");

	const double maxFps = 200;
	const double maxPeriod = 1 / maxFps;
	double deltaTime, time;
	double lastTime = 0;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		time = glfwGetTime();
		deltaTime = time - lastTime;
		if (deltaTime > maxPeriod)
		{
			lastTime = time;
			/* Update game state */
			cursor.Update();
			camera.Update(cursor);
			playfield.Update(cursor.pos);
			
		}
		if (input.IsPressed(Input::KEY_SPACE))
		{
			playfield.Change();
		}

		renderer.Clear();

		/* Render new frame */
		playfield.Draw(renderer, shader, camera.viewMatrix);
		model.Draw(renderer, shader, camera.viewMatrix);
		cursor.Draw(renderer, shader_tex, camera.viewMatrix);
		
		//gui.Draw(renderer, shader);
		debugWindow.Draw(cursor.pos);
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
