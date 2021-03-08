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
	Entity pipeS, pipeC, pipeC2, pipeC3;

	Entity screenEnt;

	Shader::sptr shader, animShader, untexturedShader;

	GLfloat time = 0.0f;

	Mat buttonMat, drumstickMat, doorMat, floorMat, wallMat, andMat, notMat, wireMat, wireMatOn, coilMatOn, coilMatOff, completeMat, boxMat, panelMat, ventMat, pipeSMat, pipeCMat;

	Mesh* drumstick;
	Mesh* floor;
	Mesh* screen;
	Mesh* leftWall;
	Mesh* rightWall;
	Mesh* backWall;
	Mesh* doorM;
	Mesh* and;
	Mesh* not;
	Mesh* buttonM;
	Mesh* wireM1;
	Mesh* wireM2;
	Mesh* wireM3;
	Mesh* wireM4;
	Mesh* wireM5;
	Mesh* wireM6;
	Mesh* wireM7;
	Mesh* coil;
	Mesh* boxMesh;
	Mesh* panelMesh;
	Mesh* ventMesh;
	Mesh* pipeSMesh;
	Mesh* pipeCMesh;

	std::string drumFile = "Models/ChickenFrames/Walk1.obj";
	std::string floorFile = "Models/Level3Floor.obj";
	std::string screenFile = "Models/Floor.obj";
	std::string leftWallFile = "Models/LeftWall.obj";
	std::string rightWallFile = "Models/RightWall.obj";
	std::string backWallFile = "Models/BackWall.obj";
	std::string doorFile = "Models/DoorFrames/Door0.obj";
	std::string gateFile = "Models/AndGate.obj";
	std::string notFile = "Models/NotGate.obj";
	std::string wire1File = "Models/New_Level3Wire1.obj";
	std::string wire2File = "Models/New_Level3Wire2.obj";
	std::string wire3File = "Models/New_Level3Wire3.obj";
	std::string wire4File = "Models/New_Level3Wire4.obj";
	std::string wire5File = "Models/New_Level3Wire5.obj";
	std::string wire6File = "Models/New_Level3Wire6.obj";
	std::string wire7File = "Models/New_Level3Wire7.obj";
	std::string buttonFile = "Models/Button.obj";
	std::string coilFile = "Models/TeslaCoil.obj";
	std::string boxFile = "Models/Box.obj";
	std::string panelFile = "Models/Panel.obj";
	std::string ventFile = "Models/New2_VentLarge.obj";
	std::string pipeSFile = "Models/New2_StraightPipe.obj";
	std::string pipeCFile = "Models/New2_CurvedPipe.obj";

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
};