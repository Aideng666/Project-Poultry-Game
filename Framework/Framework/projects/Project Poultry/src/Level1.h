//#pragma once
//
//#include "Scene.h"
//#include "Input.h"
//#include "Wire.h"
//#include "Lever.h"
//#include <vector>
//#include <iostream>
//
//using namespace freebird;
//
//class Level1 : public Scene
//{
//public:
//
//	Level1(std::string sceneName, GLFWwindow* wind);
//
//	void InitScene();
//
//	void Update(float dt);
//
//	void Unload();
//
//
//private:
//	Entity mainPlayer;
//	Entity ground, leftWall, rightWall, backWall;
//	Entity andEnt;
//	Entity wireEnt, wireEnt2;
//	Entity leverEnt, leverEnt2;
//	Entity doorEnt;
//	Entity boxEnt;
//
//	Shader::sptr playerShader, wallShader, gateShader, wireShader, doorShader, leverShader;
//
//	std::vector<std::unique_ptr<Mesh>> morphFrames;
//
//	GLfloat time = 0.0f;
//
//	Mat material;
//
//	std::unique_ptr<Mesh> morph0;
//	std::unique_ptr<Mesh> morph1;
//	
//	float t = 0.0f;
//	float totalTime;
//
//	float speed = 4.0f;
//
//	glm::vec3 point1 = glm::vec3(-3.0f, 5.0f, 3.0f);
//	glm::vec3 point2 = glm::vec3(3.0f, 5.0f, 3.0f);
//
//	glm::vec3 currentPos = glm::vec3(3.0f, 5.0f, 3.0f);
//
//	bool forwards = true;
//
//	bool camClose = false;
//	bool camFar = false;
//
//	bool imguiStarted = false;
//
//	KeyPressWatcher lever1Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
//		leverEnt.Get<Lever>().SetPowered(!leverEnt.Get<Lever>().GetPowered());
//		std::cout << "Lever 1 Power: " << leverEnt.Get<Lever>().GetPowered() << std::endl;
//		});
//
//	KeyPressWatcher lever2Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
//		leverEnt2.Get<Lever>().SetPowered(!leverEnt2.Get<Lever>().GetPowered());
//		std::cout << "Lever 2 Power: " << leverEnt2.Get<Lever>().GetPowered() << std::endl;
//		});
//};

#pragma once
#include "Scene.h"
#include "Input.h"
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

	Entity mainPlayer;
	Entity floorEnt;
	Entity leftEnt, rightEnt, backEnt;
	Entity andEnt;
	Entity wireEnt, wireEnt2, wireEnt3;
	Entity buttonEnt, buttonEnt2;
	Entity doorEnt;
	Entity coilEnt, coilPowered;
	Entity pipeEnt;
	Entity boxEnt;
	Entity particleEnt;
	Entity wirePowered, wirePowered2, wirePowered3;

	Shader::sptr playerShader, levelShader, floorShader, gateShader, wireShader, doorShader, buttonShader, particleShader, untexturedShader;

	GLfloat time = 0.0f;

	Mat buttonMat, drumstickMat, doorMat, floorMat, wallMat, wireMat, coilMat, gateMat;

	std::vector<std::unique_ptr<Mesh>> doorFrames;

	std::unique_ptr<Mesh> door0;
	std::unique_ptr<Mesh> door1;
	std::unique_ptr<Mesh> door2;
	std::unique_ptr<Mesh> door3;
	std::unique_ptr<Mesh> door4;
	std::unique_ptr<Mesh> door5;
	std::unique_ptr<Mesh> door6;
	std::unique_ptr<Mesh> door7;
	std::unique_ptr<Mesh> door8;
	std::unique_ptr<Mesh> door9;
	std::unique_ptr<Mesh> door10;

	ParticleParam particleData;

	float t = 0.0f;
	float totalTime;

	float speed = 4.0f;

	glm::vec3 point1 = glm::vec3(-3.0f, 15.0f, 3.0f);
	glm::vec3 point2 = glm::vec3(3.0f, 15.0f, 3.0f);

	glm::vec3 currentPos = glm::vec3(3.0f, 15.0f, 3.0f);

	bool forwards = true;

	bool camClose = false;
	bool camFar = false;

	KeyPressWatcher button1Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		buttonEnt.Get<Lever>().SetPowered(!buttonEnt.Get<Lever>().GetPowered());
		std::cout << "Button 1 Power: " << buttonEnt.Get<Lever>().GetPowered() << std::endl;
		});

	KeyPressWatcher button2Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		buttonEnt2.Get<Lever>().SetPowered(!buttonEnt2.Get<Lever>().GetPowered());
		std::cout << "Button 2 Power: " << buttonEnt2.Get<Lever>().GetPowered() << std::endl;
		});

};