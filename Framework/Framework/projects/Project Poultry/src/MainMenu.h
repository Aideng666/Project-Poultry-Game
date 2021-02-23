#pragma once
#include "Scene.h"
#include <iostream>

using namespace freebird;

class MainMenu : public Scene
{
public:
	
	MainMenu(std::string sceneName, GLFWwindow* wind);

	void InitScene();

	void Update(float dt);

	void Unload();

private:

	//Create the entities
	//Background ent
	Entity backEnt;
	//Loading screen ent
	Entity loadEnt;

	Shader::sptr shader;

	Mat backMat, loadMat, clearMat;

	Mesh* back;

	std::string backFile = "Models/Floor.obj";

	GLfloat time = 0.0f;

	bool isLoading = false;
};