#pragma once
#include "Scene.h"
#include "Wire.h"
#include "Lever.h"
#include <vector>
#include <iostream>

using namespace freebird;

class Level5 : public Scene
{
public:
	Level5(std::string sceneName, GLFWwindow* wind);

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
	Entity wireEnt, wireEnt2, wireEnt3, wireEnt4, wireEnt5, wireEnt6, wireEnt7;
	//Vents
	Entity ventEnt, ventEnt2;
	//Door
	Entity doorEnt;
	//And-Gate
	Entity andEnt;
	//Or-Gate
	Entity orEnt, orEnt2;
	//Buttons
	Entity buttonEnt, buttonEnt2, buttonEnt3, buttonEnt4;
	//Coil
	Entity coilEnt;
	//Shelf Pipe
	Entity shelfPipeEnt, shelfPipeEnt2, shelfPipeEnt3, shelfPipeEnt4;
	//Column Pipe
	Entity columnPipeEnt, columnPipeEnt2;

	KeyPressWatcher pauseWatch = KeyPressWatcher(GLFW_KEY_P, [&]() {
		isPaused = !isPaused;

		if (isPaused)
			lightNum = 2;
		else
			lightNum = 5;
		});
};