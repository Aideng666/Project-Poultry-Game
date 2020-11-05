#include "Level1.h"
#include <iostream>

Level1::Level1(std::string sceneName, GLFWwindow* wind)
	: Scene(sceneName, wind)
{
}

void Level1::InitScene()
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

void Level1::Update(float dt)
{
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

