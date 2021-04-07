#pragma once
#include "Scene.h"
#include "Wire.h"
#include "Lever.h"
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
	Entity startEnt, exitEnt;
	Entity wasdEnt;

	GLfloat time = 0.0f;

	KeyPressWatcher button1Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		buttonEnt.Get<Lever>().SetPowered(!buttonEnt.Get<Lever>().GetPowered());

		buttonAnimOn = true;
		isPecking = true;
		});

	KeyPressWatcher button2Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		buttonEnt2.Get<Lever>().SetPowered(!buttonEnt2.Get<Lever>().GetPowered());

		button2AnimOn = true;
		isPecking = true;
		});
};