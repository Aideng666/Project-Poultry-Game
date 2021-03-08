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
	Entity doorEnt, doorCloseEnt;
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
	//Tablet
	Entity tabletEnt;
	Entity tabletScreenEnt;
	//Particle
	//Entity particleEnt;
	//Interact
	Entity tutEnt;

	Entity screenEnt;

	Shader::sptr shader, animShader, particleShader, untexturedShader;

	GLfloat time = 0.0f;

	Mat buttonMat, drumstickMat, doorMat, floorMat, wallMat, completeMat, gateMat, wireMat, wirePowerMat, boxMat, panelMat, ventMat, tabletMat, tabletScreenMat, coilMatOn, coilMatOff;

	Mesh* drumstick;
	Mesh* floor;
	Mesh* screen;
	Mesh* leftWall;
	Mesh* rightWall;
	Mesh* backWall;
	Mesh* doorM;
	Mesh* doorCloseM;
	Mesh* gate;
	Mesh* buttonM;
	Mesh* wireL;
	Mesh* wireR;
	Mesh* wireC;
	Mesh* coil;
	Mesh* boxM;
	Mesh* panel;
	Mesh* ventB;
	Mesh* ventS;
	Mesh* pipeS;
	Mesh* pipeC;
	Mesh* tablet;
	Mesh* tut;

	std::string drumFile = "Models/ChickenFrames/Walk1.obj";
	std::string floorFile = "Models/Floor.obj";
	std::string screenFile = "Models/Floor.obj";
	std::string leftWallFile = "Models/LeftWall.obj";
	std::string rightWallFile = "Models/RightWall.obj";
	std::string backWallFile = "Models/BackWall.obj";
	std::string doorFile = "Models/DoorFrames/Door0.obj";
	std::string gateFile = "Models/AndGate.obj";
	std::string buttonFile = "Models/Button.obj";
	std::string wire1File = "Models/New_Level1Wire1.obj";
	std::string wire2File = "Models/New_Level1Wire2.obj";
	std::string wire3File = "Models/New2_Level1Wire3.obj";
	std::string coilFile = "Models/TeslaCoil.obj";
	std::string boxFile = "Models/Box.obj";
	std::string panelFile = "Models/Panel.obj";
	std::string ventFileB = "Models/New2_VentLarge.obj";
	std::string ventFileS = "Models/New_VentSmall.obj";
	std::string pipesFileS = "Models/New2_StraightPipe.obj";
	std::string pipesFileC = "Models/New2_CurvedPipe.obj";
	std::string tabletFile = "Models/Tablet.obj";
	std::string tutFile = "Models/Interact.obj";

	ParticleParam particleData;

	float t = 0.0f;
	float totalTime;

	float speed = 4.0f;

	glm::vec3 point1 = glm::vec3(-3.0f, 15.0f, 3.0f);
	glm::vec3 point2 = glm::vec3(3.0f, 15.0f, 3.0f);

	glm::vec3 currentPos = glm::vec3(3.0f, 15.0f, 3.0f);

	bool forwards = true;

	bool showLevelComplete = false;

	KeyPressWatcher button1Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		buttonEnt.Get<Lever>().SetPowered(!buttonEnt.Get<Lever>().GetPowered());
		std::cout << "Button 1 Power: " << buttonEnt.Get<Lever>().GetPowered() << std::endl;
		});

	KeyPressWatcher button2Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		buttonEnt2.Get<Lever>().SetPowered(!buttonEnt2.Get<Lever>().GetPowered());
		std::cout << "Button 2 Power: " << buttonEnt2.Get<Lever>().GetPowered() << std::endl;
		});

	KeyPressWatcher tabletWatch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		tabletOpen = !tabletOpen;

		if (tabletOpen)
			lightNum = 2;
		else
			lightNum = 5;
		});


};