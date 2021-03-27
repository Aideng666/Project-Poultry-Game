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
	//Player
	Entity mainPlayer;
	//Floor
	Entity floorEnt;
	//Walls
	Entity leftEnt, rightEnt, backEnt;
	//Door
	Entity doorEnt;
	//Pipes
	Entity pipeEntS, pipeEntS2, pipeEntC, pipeEntC2;
	//Level Complete
	Entity completeEnt;
	//Gates
	Entity andEnt, andEnt2;
	//Buttons
	Entity buttonEnt, buttonEnt2, buttonEnt3;
	//Wires
	Entity wireEnt, wireEnt2, wireEnt3, wireEnt4, wireEnt5;
	//Tesla Coil 
	Entity coilEnt;
	//Boxes
	Entity boxEnt, boxEnt2, boxEnt3, boxEnt4;
	//Panels
	Entity panelEnt, panelEnt2, panelEnt3;
	//Vents
	Entity ventEnt, ventEnt2;

	GLfloat time = 0.0f;

	float t = 0.0f;
	float totalTime;

	float speed = 4.0f;

	glm::vec3 point1 = glm::vec3(-3.0f, 15.0f, 3.0f);
	glm::vec3 point2 = glm::vec3(3.0f, 15.0f, 3.0f);

	glm::vec3 currentPos = glm::vec3(3.0f, 15.0f, 3.0f);

	bool forwards = true;

	bool camClose = false;
	bool camFar = false;

	int lightNum = 5;

	bool showLevelComplete = false;

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
	
	KeyPressWatcher button3Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		buttonEnt3.Get<Lever>().SetPowered(!buttonEnt3.Get<Lever>().GetPowered());
		button3AnimOn = true;
		isPecking = true;
		});

	KeyPressWatcher pauseWatch = KeyPressWatcher(GLFW_KEY_P, [&]() {
		isPaused = !isPaused;

		if (isPaused)
			lightOn = false;
		else
			lightOn = true;
		});

};