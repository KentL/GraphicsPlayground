// AS2-20170208.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <stdlib.h>
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include <string>
#include "InterpolationExample.h"

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(int argc, char *argv[])
{
	int width, height, x;
	int exampleIndex = argc > 1 ? std::stoi(argv[1]) : 0;

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		exit(EXIT_FAILURE);
	}

	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	// Open a window and create its OpenGL context
	GLFWwindow* window = glfwCreateWindow(640, 480, "3D City", NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetKeyCallback(window, key_callback);

	glewExperimental = GL_TRUE;
	glewInit();

	// Leave this here! On windows machines in Lab, glewInit is generating some mysterious, but apparently
	// harmless, error - and we need it gone.
	glGetError();

	// Enable vertical sync (on cards that support it)
	glfwSwapInterval(1);

	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	switch (exampleIndex)
	{
	case 0: InterpolationExample::Initialize(); break;
	default:
		break;
	}
	do
	{

		// Get window size (may be different than the requested size)
		glfwGetWindowSize(window, &width, &height);

		// Special case: avoid division by zero below
		height = height > 0 ? height : 1;

		glViewport(0, 0, width, height);

		// Clear color buffer to black
		glClearColor(0.4f, 0.4f, 0.4f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//render
		switch (exampleIndex)
		{
		case 0: InterpolationExample::Render(); break;
		default:
			break;
		}

		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (!glfwWindowShouldClose(window));

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	exit(EXIT_SUCCESS);
}

