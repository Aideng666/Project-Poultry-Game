#include <Logging.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>

#include <wtypes.h>

#include <filesystem>
#include <fstream>
#include <Shader.h>

using namespace std;

GLFWwindow* window;

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

void GlfwWindowResizedCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

bool initGLFW() {

	//Initialize GLFW
	if (glfwInit() == GLFW_FALSE) {
		std::cout << "Failed to Initialize GLFW" << std::endl;
		return false;
	}

	int horiz, vert;
	GetDesktopResolution(horiz, vert);
	//Create a new GLFW window
	window = glfwCreateWindow(horiz, vert, "Project Poultry Game", nullptr, nullptr);
	
	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window, GlfwWindowResizedCallback);

	return true;
}

bool initGLAD() {
	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) {
		std::cout << "Failed to initialize Glad" << std::endl;
		return false;
	}
}

GLuint shader_program;

int main()
{
	//Initialize GLFW
	if (!initGLFW())
		return 1;

	//Initialize GLAD
	if (!initGLAD())
		return 1;

	// Camera matrix 
	glm::mat4 View = glm::lookAt(
		glm::vec3(0, 0, 3), // Camera is at (0,0,3), in World Space 
		glm::vec3(0, 0, 0), // and looks at the origin 
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down) 
	);

	//Main Loop//
	while (!glfwWindowShouldClose(window)) {

		//Close the window
		processInput(window);

		glfwPollEvents();

		glClearColor(0.5f, 0.5f, 0.5f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
	}
}