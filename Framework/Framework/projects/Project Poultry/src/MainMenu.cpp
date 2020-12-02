#include "MainMenu.h"
#include <iostream>
#include <GLFW\glfw3.h>

#include "Application.h"
#include <imgui.h>
#include <AABB.h>
#include <MeshRenderer.h>
#include <MorphRenderer.h>
#include "Texture2DData.h"
#include "Texture2D.h"
#include <stb_image.h>
#include <MorphAnimation.h>

using namespace freebird;


MainMenu::MainMenu(std::string sceneName, GLFWwindow* wind)
	: Scene(sceneName, wind)
{
	
}

void MainMenu::InitScene()
{

}

void MainMenu::Update(float dt)
{

}

void MainMenu::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}
