#pragma once
#include "Scene.h"
#include "Input.h"
#include "Wire.h"
#include "Lever.h"
#include <vector>
#include <iostream>

using namespace freebird;

class Level3 : public Scene
{
public:

	Level3(std::string sceneName, GLFWwindow* wind);

	void InitScene();

	void Update(float dt);

	void Unload();

	void StartSegment(int startInd);

	glm::vec3 Catmull(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float t);

	struct Sample
	{
		glm::vec3 pt;
		float t;
		float accumulated;
	};
	
	class Segment
	{
	public:
	
		std::vector<Sample> samples;
	};

private:
	//Player
	Entity mainPlayer;
	//Floor
	Entity floorEnt;
	//Walls
	Entity leftEnt, rightEnt, backEnt;
	//Gates
	Entity andEnt, andEnt2, andEnt3;
	Entity notEnt;
	//Wires
	Entity wireEnt, wireEnt2, wireEnt3, wireEnt4, wireEnt5, wireEnt6, wireEnt7;
	//Buttons
	Entity buttonEnt, buttonEnt2, buttonEnt3;
	//Door
	Entity doorEnt;
	//Tesla Coil
	Entity coilEnt;
	//Level Complete
	Entity completeEnt;
	//Boxes
	Entity boxEnt, boxEnt2, boxEnt3, boxEnt4;
	//Panels
	Entity panelEnt, panelEnt2, panelEnt3;
	//Vents
	Entity ventEnt, ventEnt2;
	//Pipes
	Entity pipeSEnt, pipeCEnt, pipeC2Ent, pipeC3Ent;

	//Tablet
	Entity tabletEnt;
	Entity tabletScreenEnt;

	//Interact
	Entity tutEnt;

	GLfloat time = 0.0f;

	float t = 0.0f;
	float totalTime;

	std::vector<glm::vec3> points;
	
	float segmentTime;
	
	int currentIndex = 0;

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
		std::cout << "Button 1 Power: " << buttonEnt.Get<Lever>().GetPowered() << std::endl;
		});
	
	KeyPressWatcher button2Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		buttonEnt2.Get<Lever>().SetPowered(!buttonEnt2.Get<Lever>().GetPowered());
		std::cout << "Button 2 Power: " << buttonEnt2.Get<Lever>().GetPowered() << std::endl;
		});
	
	KeyPressWatcher button3Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		buttonEnt3.Get<Lever>().SetPowered(!buttonEnt3.Get<Lever>().GetPowered());
		std::cout << "Button 3 Power: " << buttonEnt3.Get<Lever>().GetPowered() << std::endl;
		});

	KeyPressWatcher pauseWatch = KeyPressWatcher(GLFW_KEY_P, [&]() {
		isPaused = !isPaused;

		if (isPaused)
			lightNum = 2;
		else
			lightNum = 5;
		});

	KeyPressWatcher tabletWatch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		tabletOpen = !tabletOpen;

		if (tabletOpen)
			lightNum = 2;
		else
			lightNum = 5;
		});
};