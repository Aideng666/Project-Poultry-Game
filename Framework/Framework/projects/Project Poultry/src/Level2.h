#pragma once

#include "Scene.h"
#include "Input.h"
#include "Wire.h"
#include "Lever.h"
#include <vector>
#include <iostream>

using namespace freebird;

class Level2 : public Scene
{
public:

	Level2(std::string sceneName, GLFWwindow* wind);

	void InitScene();

	void Update(float dt);

	void Unload();


private:
	Entity mainPlayer;
	Entity ground, leftWall, rightWall, backWall;
	Entity andEnt, andEnt2;
	Entity wires[6];
	Entity levers[3];
	Entity doorEnt;

	GLfloat time = 0.0f;
	
	float t = 0.0f;
	float totalTime;

	float speed = 4.0f;

	glm::vec3 point1 = glm::vec3(-3.0f, 5.0f, 3.0f);
	glm::vec3 point2 = glm::vec3(3.0f, 5.0f, 3.0f);

	glm::vec3 currentPos = glm::vec3(3.0f, 5.0f, 3.0f);

	bool forwards = true;

	bool camClose = false;
	bool camFar = false;

	bool imguiStarted = false;

	KeyPressWatcher lever1Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		levers[0].Get<Lever>().SetPowered(!levers[0].Get<Lever>().GetPowered());
		std::cout << "Lever 1 Power: " << levers[0].Get<Lever>().GetPowered() << std::endl;
		});

	KeyPressWatcher lever2Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		levers[1].Get<Lever>().SetPowered(!levers[1].Get<Lever>().GetPowered());
		std::cout << "Lever 2 Power: " << levers[1].Get<Lever>().GetPowered() << std::endl;
		});

	KeyPressWatcher lever3Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		levers[2].Get<Lever>().SetPowered(!levers[2].Get<Lever>().GetPowered());
		std::cout << "Lever 3 Power: " << levers[2].Get<Lever>().GetPowered() << std::endl;
		});
};