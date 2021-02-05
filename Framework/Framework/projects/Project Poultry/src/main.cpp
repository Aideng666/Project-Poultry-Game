#include <Logging.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>

#include <filesystem>
#include <fstream>

#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "MainMenu.h"
#include "MainMenuLevel.h"
#include "Application.h"
#include <ModelManager.h>

//ImGui
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

using namespace freebird; //referencing the module's includes/src's

using namespace std;

GLFWwindow* window;

//The main register for our ECS
entt::registry* ECS = nullptr;

//Scenes
Scene* currentScene = nullptr;
std::vector<Scene*> scenes;

int level = 0;

//Need to figure out how to load objects better for faster scene swtiching and loading
void SetActiveScene(int sceneNum)
{
	if (currentScene != nullptr)
	{
		currentScene->Unload();
	}

	scenes[sceneNum]->InitScene();
	ECS = scenes[sceneNum]->GetScene();
	currentScene = scenes[sceneNum];
	level = sceneNum + 1;

	if (level > 4)
		level = 1;
}

void InitImGui() {
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.ConfigFlags |= ImGuiConfigFlags_TransparentBackbuffers;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 410");

	ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 0.8f;
	}
}

void ShutdownImGui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

std::vector<std::function<void()>> imGuiCallbacks;

void RenderImGui() {
	// Implementation new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	// ImGui context new frame
	ImGui::NewFrame();

	if (ImGui::Begin("Debug")) {
		// Render our GUI stuff
		for (auto& func : imGuiCallbacks) {
			func();
		}
		ImGui::End();
	}

	// Make sure ImGui knows how big our window is
	ImGuiIO& io = ImGui::GetIO();
	int width{ 0 }, height{ 0 };
	glfwGetWindowSize(window, &width, &height);
	io.DisplaySize = ImVec2((float)width, (float)height);

	// Render all of our ImGui elements
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// If we have multiple viewports enabled (can drag into a new window)
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		// Update the windows that ImGui is using
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		// Restore our gl context
		glfwMakeContextCurrent(window);
	}
}

int main()
{
	//Inits the window
	if (!(window = Application::Init("Project Poultry", 1200, 1000)))
	{
		return 1;
	}

	//Sets the clear colour of the window
	Application::SetClearColor(glm::vec4(0.08f, 0.17f, 0.31f, 1.0f));

	//Application::InitImGui();

	scenes.push_back(new MainMenu("Main Menu", window));
	scenes.push_back(new MainMenuLevel("Main Menu Level", window));
	/*scenes.push_back(new Level1("Level 1", window));
	scenes.push_back(new Level2("Level 2", window));
	scenes.push_back(new Level3("Level 3", window));*/

	SetActiveScene(1);
	
	//Calculates our timer
	Application::Tick();

	//ImGui Stuff
	imGuiCallbacks.push_back([&]() {

		//Put tabs, headers, buttons and all that jazz in here

	});

	InitImGui();

	//Main Loop//
	while (!Application::IsClosing()) {

		//Close the window
		Application::ProcessInput(window);

		//Updates the window
		Application::Update();

		//Grabs the time
		float dt = Application::GetDT();

		//For ImGui Stuff
		//Application::StartImGui();

		//static bool panelOpen = true;
		//ImGui::Begin("TEST IMGUI PANEL", &panelOpen, ImVec2(300, 100));

		//ImGui::End();
		//Application::EndImGui();

		if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)
		{
			SetActiveScene(4);
		}
		if (glfwGetKey(window, GLFW_KEY_KP_3) == GLFW_PRESS)
		{
			SetActiveScene(3);
		}
		if (glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS)
		{
			SetActiveScene(2);
		}
		if (glfwGetKey(window, GLFW_KEY_KP_1) == GLFW_PRESS)
		{
			SetActiveScene(1);
		}
		if (glfwGetKey(window, GLFW_KEY_KP_0) == GLFW_PRESS)
		{
			SetActiveScene(0);
		}

		if (currentScene->GetComplete())
		{
			currentScene->SetComplete(false);
			SetActiveScene(level);
		}

		if (currentScene->GetLoad())
		{
			scenes.push_back(new MainMenuLevel("Main Menu Level", window));
			scenes.push_back(new Level1("Level 1", window));
			scenes.push_back(new Level2("Level 2", window));
			scenes.push_back(new Level3("Level 3", window));

			SetActiveScene(1);
		}

		currentScene->Update(dt);

		RenderImGui();

		Application::SwapBuffers();
	}

	ShutdownImGui();

	//Cleans up the window and glfw
	Application::Cleanup();

	Logger::Uninitialize();
	return 0;
}