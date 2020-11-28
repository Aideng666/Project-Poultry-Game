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

	glm::vec3 Catmull(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float t);

	float InverseLerp(float p, float p0, float p1);

	void Reparameterize();

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
	Entity mainPlayer;
	Entity ground, leftWall, rightWall, backWall;
	Entity notEnt;
	Entity andEnts[3];
	Entity wires[5];
	Entity levers[3];
	Entity doorEnt;

	std::vector<glm::vec3> points;

	float speed = 10.0f;

	int samples = 8;

	float sampleInterval;

	int currentSegment = 0;
	int currentSample = 0;

	float distanceTravelled = 0.0f;

	std::vector<Segment> curveTable;

	std::vector<Sample> sampleVec;

	float totalCurveLength = 0.0f;

	glm::vec3 currentPos;

	bool camClose = false;
	bool camFar = false;

	bool imguiStarted = false;

	float timer = 0;

	KeyPressWatcher lever1Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		levers[0].Get<Lever>().SetPowered(!levers[0].Get<Lever>().GetPowered());
		std::cout << "Lever 1 Power: " << levers[0].Get<Lever>().GetPowered() << std::endl;
		});

	KeyPressWatcher lever2Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		levers[1].Get<Lever>().SetPowered(!levers[1].Get<Lever>().GetPowered());
		std::cout << "Lever 2 Power: " << levers[1].Get<Lever>().GetPowered() << std::endl;
		});

	KeyPressWatcher lever3Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		levers[2].Get<Lever>().SetPowered(!levers[2].Get<Lever>().GetPowered());
		std::cout << "Lever 3 Power: " << levers[2].Get<Lever>().GetPowered() << std::endl;
		});
};
