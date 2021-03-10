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

	Entity screenEnt;

	//Shader::sptr shader, animShader, untexturedShader;

	GLfloat time = 0.0f;

	//Mat buttonMat, drumstickMat, doorMat, floorMat, wallMat, gateMat, wireMat, wirePowerMat, completeMat, boxMat, panelMat, ventMat, coilMatOn, coilMatOff;

	/*Mesh* drumstick;
	Mesh* floor;
	Mesh* screen;
	Mesh* leftWall;
	Mesh* rightWall;
	Mesh* backWall;
	Mesh* doorM;
	Mesh* pipeS;
	Mesh* pipeC;
	Mesh* gate;
	Mesh* buttonM;
	Mesh* wireM1;
	Mesh* wireM2;
	Mesh* wireM3;
	Mesh* wireM4;
	Mesh* wireM5;
	Mesh* coil;
	Mesh* boxM;
	Mesh* panel;
	Mesh* vent;

	std::string drumFile = "Models/ChickenFrames/Walk1.obj";
	std::string floorFile = "Models/Level2Floor.obj";
	std::string screenFile = "Models/Floor.obj";
	std::string leftWallFile = "Models/LeftWall.obj";
	std::string rightWallFile = "Models/RightWall.obj";
	std::string backWallFile = "Models/BackWall.obj";
	std::string doorFile = "Models/DoorFrames/Door0.obj";
	std::string pipeFileS = "Models/New2_StraightPipe.obj";
	std::string pipeFileC = "Models/New2_CurvedPipe.obj";
	std::string gateFile = "Models/AndGate.obj";
	std::string buttonFile = "Models/Button.obj";
	std::string wire1File = "Models/Level2Wire1.obj";
	std::string wire2File = "Models/Level2Wire2.obj";
	std::string wire3File = "Models/Level2Wire3.obj";
	std::string wire4File = "Models/Level2Wire4.obj";
	std::string wire5File = "Models/New_Level2Wire5.obj";
	std::string coilFile = "Models/TeslaCoil.obj";
	std::string boxFile = "Models/Box.obj";
	std::string panelFile = "Models/Panel.obj";
	std::string ventFile = "Models/New_VentSmall.obj";*/

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

};