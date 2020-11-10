#pragma once

#include "Scene.h"
#include <vector>

using namespace freebird;

class Level2 : public Scene
{
public:

	Level2(std::string sceneName, GLFWwindow* wind);

	void InitScene();

	void Update(float dt);

	void Unload();


private:
	Entity mainPlayer;
	Entity camEnt;
	Entity ground, leftWall, rightWall, backWall;
	Entity andEnt;
	Entity wireEnt, wireEnt2;
	Entity leverEnt, leverEnt2;

	bool camClose = false;
	bool camFar = false;
};
