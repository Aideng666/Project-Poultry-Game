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
	Entity camEnt;
	Entity ground, leftWall, rightWall, backWall;
	Entity andEnt;
	Entity wireEnt, wireEnt2;
	Entity leverEnt, leverEnt2;

	bool camClose = false;
	bool camFar = false;

	bool imguiStarted = false;

	KeyPressWatcher lever1Watch = KeyPressWatcher(GLFW_KEY_Q, [&]() {
		leverEnt.Get<Lever>().SetPowered(!leverEnt.Get<Lever>().GetPowered());
		std::cout << "Lever 1 Power: " << leverEnt.Get<Lever>().GetPowered() << std::endl;
		});

	KeyPressWatcher lever2Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		leverEnt2.Get<Lever>().SetPowered(!leverEnt2.Get<Lever>().GetPowered());
		std::cout << "Lever 2 Power: " << leverEnt2.Get<Lever>().GetPowered() << std::endl;
		});

	KeyPressWatcher gateWatch = KeyPressWatcher(GLFW_KEY_R, [&]() {
		std::cout << "Gate Power: " << andEnt.Get<AndGate>().GetOutput() << std::endl;
		});
};