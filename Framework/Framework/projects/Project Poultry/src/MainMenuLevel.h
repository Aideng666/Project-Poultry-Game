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

	Entity floorEnt, backWallEnt, leftWallEnt, rightWallEnt;
	Entity startDoor, exitDoor;
	Entity mainPlayer;
	Entity coilEnt, coilEnt2;
	Entity wireEnt, wireEnt2;
	Entity buttonEnt, buttonEnt2;
	//Entity startEnt, optEnt, exitEnt;

	std::vector<std::unique_ptr<Mesh>> /*doorFrames,*/ walkFrames;

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