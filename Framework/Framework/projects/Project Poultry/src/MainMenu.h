#pragma once
#include "Scene.h"

using namespace freebird;

class MainMenu : public Scene
{
public:
	
	MainMenu(std::string sceneName, GLFWwindow* wind);

	void InitScene();

	void Update(float dt);

	void Unload();

private:


};