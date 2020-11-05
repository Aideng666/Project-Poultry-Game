#include "Scene.h"
#include <iostream>

using namespace freebird;

Scene::Scene(std::string sceneName, GLFWwindow* wind)
{
	name = sceneName;
	window = wind;
}

void Scene::InitScene()
{
	scene = new entt::registry();

	Entity::SetReg(scene);


	//Set Up Camera
	Entity camEnt = Entity::Create();
	auto& camera = camEnt.Add<Camera>();

	camera.SetPosition(glm::vec3(0, 3, 3)); // Set initial position
	camera.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
	camera.LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camera.SetFovDegrees(90.0f); // Set an initial FOV
}

void Scene::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}

entt::registry* Scene::GetScene()
{
	return scene;
}