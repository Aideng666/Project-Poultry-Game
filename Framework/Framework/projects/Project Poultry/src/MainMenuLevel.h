#pragma once
#include "Scene.h"
#include "Input.h"
#include <vector>
#include <iostream>

class MainMenuLevel : public Scene
{
public:

	MainMenuLevel(std::string sceneName, GLFWwindow* wind);

	void InitScene();

	void Update(float dt);

	void Unload();

private:

	Entity startDoor, optionDoor, exitDoor;
	Entity floorEnt, backWall, leftAngledWall, rightAngledWall, leftWall, rightWall;
	Entity mainPlayer;
	Entity startEnt, optEnt, exitEnt;

	Shader::sptr shader, animShader;

	Mat drumstickMat, doorMat, floorMat, wallMat;

	std::vector<std::unique_ptr<Mesh>> doorFrames, walkFrames;

	Mesh* drumstick;
	Mesh* floor;
	Mesh* wall;
	Mesh* doorM;
	Mesh* start;
	Mesh* options;
	Mesh* exit;


	std::string drumFile = "Models/ChickenFrames/Walk1.obj";
	std::string doorFile = "Models/DoorFrames/Door0.obj";
	std::string floorFile = "Models/Floor.obj";
	std::string wallFile = "Models/Wall.obj";
	std::string startFile = "Models/Start.obj";
	std::string exitFile = "Models/Exit.obj";
	std::string optFile = "Models/Options.obj";


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
};
