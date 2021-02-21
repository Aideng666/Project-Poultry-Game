#pragma once
#include "Scene.h"
#include "Input.h"
#include <vector>
#include <iostream>

class TestScene : public Scene
{
public:
	TestScene(std::string sceneName, GLFWwindow* window);

	void InitScene();

	void Update(float dt);

private:
	Entity mainPlayer;

	Shader::sptr shader;

	Mat playerMat, clearMat;

	Mesh* monkey;

	std::string monkeyFile = "Models/Monkey.obj";
};