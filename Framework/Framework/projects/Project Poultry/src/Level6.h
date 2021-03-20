#pragma once
#pragma once
#include "Scene.h"
#include "Wire.h"
#include "Lever.h"
#include <vector>
#include <iostream>

using namespace freebird;

class Level6 : public Scene
{
public:
	Level6(std::string sceneName, GLFWwindow* wind);

	void InitScene();

	void Update(float dt);

	void Unload();

private:
	//Main Player
	Entity mainPlayer;
	//Floor
	Entity floorEnt;
	//Walls
	Entity leftEnt, rightEnt, backEnt;
	//Wires
	Entity wireEnt, wireEnt2, wireEnt3, wireEnt4, wireEnt5, wireEnt6, wireEnt7,
		wireEnt8, wireEnt9;
	//Door
	Entity doorEnt;
	//Tesla Coil
	Entity coilEnt;
	//Panels
	Entity panelEnt, panelEnt2;
	//Buttons
	Entity buttonEnt, buttonEnt2, buttonEnt3;

	KeyPressWatcher pauseWatch = KeyPressWatcher(GLFW_KEY_P, [&]() {
		isPaused = !isPaused;

		if (isPaused)
			lightNum = 2;
		else
			lightNum = 5;
	});
};