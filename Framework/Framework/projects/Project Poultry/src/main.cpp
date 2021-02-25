#include <Logging.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>

#include <filesystem>
#include <fstream>

#include "TestScene.h"

#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "MainMenu.h"
#include "MainMenuLevel.h"
#include "Application.h"
#include <ModelManager.h>
#include "Greyscale.h"

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

int main()
{
	//Inits the window
	if (!(window = Application::Init("Project Poultry", 1200, 1000)))
	{
		return 1;
	}

	//Sets the clear colour of the window
	Application::SetClearColor(glm::vec4(0.08f, 0.17f, 0.31f, 1.0f));

	scenes.push_back(new MainMenu("Main Menu", window));
	scenes.push_back(new Level1("Level 1", window));
	scenes.push_back(new Level2("Level 2", window));

	SetActiveScene(1);
	
	//Calculates our timer
	Application::Tick();

	int activeEffect = 0;
	bool isTextured = true;

	//ImGui Stuff
	Application::imGuiCallbacks.push_back([&]() {

		//Put tabs, headers, buttons and all that jazz in here

		if (ImGui::Checkbox("Texture Toggle", &isTextured))
		{
			currentScene->SetTextured(isTextured);
		}
		if (ImGui::CollapsingHeader("Effect Controls"))
		{
			ImGui::SliderInt("Chosen Effect", &activeEffect, 0, currentScene->GetEffects().size() - 1);

			if (activeEffect == 0)
			{
				currentScene->SetActiveEffect(0);

				ImGui::Text("Active Effect: Nothing");
			}
			if (activeEffect == 1)
			{
				currentScene->SetActiveEffect(1);

				ImGui::Text("Active Effect: Greyscale");

				Greyscale* temp = (Greyscale*)currentScene->GetEffects()[activeEffect];
				float intensity = temp->GetIntensity();

				if (ImGui::SliderFloat("Intensity", &intensity, 0.0f, 1.0f))
				{
					temp->SetIntensity(intensity);
				}
			}
			if (activeEffect == 2)
			{
				currentScene->SetActiveEffect(2);

				ImGui::Text("Active Effect: Sepia");

				Sepia* temp = (Sepia*)currentScene->GetEffects()[activeEffect];
				float intensity = temp->GetIntensity();

				if (ImGui::SliderFloat("Intensity", &intensity, 0.0f, 1.0f))
				{
					temp->SetIntensity(intensity);
				}
			}
			if (activeEffect == 3)
			{
				currentScene->SetActiveEffect(3);

				ImGui::Text("Active Effect: Bloom");

				Bloom* temp = (Bloom*)currentScene->GetEffects()[activeEffect];
				float threshold = temp->GetThreshold();

				if (ImGui::SliderFloat("Threshold", &threshold, 0.0f, 1.0f))
				{
					temp->SetThreshold(threshold);
				}

				float downscale = temp->GetDownscale();

				if (ImGui::SliderFloat("Blur", &downscale, 1.0f, 5.0f))
				{
					temp->SetDownscale(downscale);
				}
			}
			if (activeEffect == 4)
			{
				currentScene->SetActiveEffect(4);

				ImGui::Text("Active Effect: Color Correct Effect");

				ColorCorrect* temp = (ColorCorrect*)currentScene->GetEffects()[activeEffect];
			}

		}
	});

	Application::InitImGui();

	//Main Loop//
	while (!Application::IsClosing()) {

		//Close the window
		Application::ProcessInput(window);

		//Updates the window
		Application::Update();

		//Grabs the time
		float dt = Application::GetDT();

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

		Application::RenderImGui();

		Application::SwapBuffers();
	}

	Application::ShutdownImGui();

	//Cleans up the window and glfw
	Application::Cleanup();

	Logger::Uninitialize();
	return 0;
}