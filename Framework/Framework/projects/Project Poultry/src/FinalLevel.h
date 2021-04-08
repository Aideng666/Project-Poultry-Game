#pragma once
#include "Scene.h"
#include "Wire.h"
#include "Lever.h"
#include <vector>
#include <iostream>

using namespace freebird;

class FinalLevel : public Scene
{
public:
	FinalLevel(std::string sceneName, GLFWwindow* wind);

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
	Entity wireEnt;
	//Door
	Entity doorEnt;
	//Tesla Coil
	Entity coilEnt;
	//Buttons
	Entity buttonEnt;
	//Level Complete Ent
	Entity completeEnt;
	//To Activate Door
	Entity orEnt;

	GLfloat time = 0.0f;

	KeyPressWatcher button1Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		buttonEnt.Get<Lever>().SetPowered(!buttonEnt.Get<Lever>().GetPowered());

		buttonAnimOn = true;
		isPecking = true;
		});

	KeyPressWatcher tabletWatch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		tabletOpen = !tabletOpen;

		if (tabletOpen)
			pauseLighting = true;
		else
			pauseLighting = false;
		});
};