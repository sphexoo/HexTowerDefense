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
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "MyImGui.h"
#include "Input.h"
//#include "Gui.h"

#ifdef RELEASE
	float fWidth = 1920.0f;
	float fHeight = 1080.0f;
#else
	float fWidth = 1280.0f;
	float fHeight = 720.0f;
#endif


/* Creating instance of Logger class and setting its log level */
Logger logger(Logger::Info);

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
	Input input(window);

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

	/* Create Shader specified in Shader.h */
	Shader shader("res/shaders/texture_vertex.shader", "res/shaders/texture_fragment.shader");
	shader.Bind();

	const double maxFps = 144;
	const double maxPeriod = 1 / maxFps;
	double deltaTime, time;
	double lastTime = 0;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		//time = glfwGetTime();
		//deltaTime = time - lastTime;
		//if (deltaTime > maxPeriod)
		//{
		//	lastTime = time;
		//	/* Update game state */
		//
		//}

		renderer.Clear();

		/* Render new frame */
		//gui.Draw(renderer, shader);
		debugWindow.Draw();
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
