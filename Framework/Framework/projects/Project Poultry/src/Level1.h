#pragma once
#include "Scene.h"
#include "Wire.h"
#include "Lever.h"
#include <vector>
#include <iostream>
#include <ParticleSystem.h>

using namespace freebird;

class Level1 : public Scene
{
public:

	Level1(std::string sceneName, GLFWwindow* wind);

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
	//Door
	Entity doorEnt;
	//Level complete
	Entity completeEnt;
	//AND-Gate
	Entity andEnt;
	//Buttons
	Entity buttonEnt, buttonEnt2;
	//Wires
	Entity wireEnt, wireEnt2, wireEnt3;
	//Tesla Coil
	Entity coilEnt;
	//Box
	Entity boxEnt, boxEnt2, boxEnt3, boxEnt4, boxEnt5;
	//Panel
	Entity panelEnt, panelEnt2;
	//Vent
	Entity bigVentEnt;
	Entity smallVentEnt, smallVentEnt2;
	//Pipe
	Entity pipeEntS, pipeEntC;
	//Controls
	Entity pauseControlEnt, shiftControlEnt;

	GLfloat time = 0.0f;

	ParticleParam particleData;

	float t = 0.0f;
	float totalTime;

	float speed = 4.0f;

	glm::vec3 point1 = glm::vec3(-3.0f, 15.0f, 3.0f);
	glm::vec3 point2 = glm::vec3(3.0f, 15.0f, 3.0f);

	glm::vec3 currentPos = glm::vec3(3.0f, 15.0f, 3.0f);

	bool forwards = true;

	KeyPressWatcher button1Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		buttonEnt.Get<Lever>().SetPowered(!buttonEnt.Get<Lever>().GetPowered());

		buttonAnimOn = true;
		isPecking = true;
		});

	KeyPressWatcher button2Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		buttonEnt2.Get<Lever>().SetPowered(!buttonEnt2.Get<Lever>().GetPowered());

		button2AnimOn = true;
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