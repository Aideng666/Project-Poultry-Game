#include <Logging.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>

//#include <wtypes.h>

#include <filesystem>
#include <fstream>

#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Entity.h"
#include "Transform.h"
#include "Level1.h"
#include "Level2.h"
#include "Application.h"

using namespace freebird; //referencing the module's includes/src's

using namespace std;

GLFWwindow* window;

//The main register for our ECS
entt::registry* ECS = nullptr;

//Scenes
Scene* currentScene = nullptr;
std::vector<Scene*> scenes;


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
	//GetDesktopResolution(horiz, vert);
	//Create a new GLFW window
	window = glfwCreateWindow(800, 800, "Project Poultry Game", nullptr, nullptr);
	
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

void SetActiveScene(int sceneNum)
{
	if (currentScene != nullptr)
	{
		currentScene->Unload();
	}

	scenes[sceneNum]->InitScene();
	ECS = scenes[sceneNum]->GetScene();
	currentScene = scenes[sceneNum];
}

//GLuint shader_program;

int main()
{
	if (!(window = Application::Init("Project Poultry", 800, 800)))
	{
		return 1;
	}

	Application::SetClearColor(glm::vec4(0.08f, 0.17f, 0.31f, 1.0f));

	auto mainPlayer = Entity::Create();
	Mesh monkey = mainPlayer.Add<Mesh>("Models/Monkey.obj");
	Transform playerTrans = mainPlayer.Add<Transform>();

	playerTrans.SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));

	scenes.push_back(new Level1("Level 1", window));
	scenes.push_back(new Level2("Level 2", window));

	SetActiveScene(0);
	
	glEnable(GL_DEPTH_TEST);

	double lastFrame = glfwGetTime();

	//Main Loop//
	while (!glfwWindowShouldClose(window)) {

		//Close the window
		processInput(window);

		Application::Update();

		// Calculate the time since our last frame (dt)
		double thisFrame = glfwGetTime();
		float dt = static_cast<float>(thisFrame - lastFrame);

			if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
			{
				SetActiveScene(1);
			}
			if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
			{
				SetActiveScene(0);
			}

		currentScene->Update(dt);


		glfwSwapBuffers(window);
		lastFrame = thisFrame;
	}

	Logger::Uninitialize();
	return 0;
}