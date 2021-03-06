#pragma once
#include "Scene.h"
#include "Wire.h"
#include "Lever.h"
#include <vector>
#include <iostream>

using namespace freebird;

class Level6 : public Scene
{
public:
	Level6(std::string sceneName, GLFWwindow* wind);

	void InitScene();

	void Update(float dt);

	void Unload();

private:
	//Main Player
	Entity mainPlayer;
	//Floor
	Entity floorEnt;
	//Walls
	Entity leftEnt, rightEnt, backEnt;
	//Wires
	Entity wireEnt, wireEnt2, wireEnt3, wireEnt4, wireEnt5, wireEnt6, wireEnt7, wireEnt8, wireEnt9, wireEnt10, wireEnt11, wireEnt12, wireEnt13, wireEnt14, wireEnt15, wireEnt16, wireEnt17;
	//Door
	Entity doorEnt;
	//Tesla Coil
	Entity coilEnt;
	//Panels
	Entity panelEnt, panelEnt2;
	//Buttons
	Entity buttonEnt, buttonEnt2, buttonEnt3, buttonEnt4, buttonEnt5;
	//Column Pipes
	Entity columnPipeEnt, columnPipeEnt2;
	//Shelf Pipes
	Entity shelfPipeEnt, shelfPipeEnt2;
	//Vents
	Entity ventEnt, ventEnt2, ventEnt3;
	//Gates
	//And-Gate
	Entity andEnt, andEnt2, andEnt3, andEnt4, andEnt5, andEnt6, andEnt7;
	//Not-Gate
	Entity notEnt, notEnt2, notEnt3;
	//Or-Gate
	Entity orEnt, orEnt2;
	//Boxes
	Entity boxEnt, boxEnt2, boxEnt3, boxEnt4;
	//Level Complete Ent
	Entity completeEnt;

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

	KeyPressWatcher button3Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		buttonEnt3.Get<Lever>().SetPowered(!buttonEnt3.Get<Lever>().GetPowered());

		button3AnimOn = true;
		isPecking = true;
		});

	KeyPressWatcher button4Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		buttonEnt4.Get<Lever>().SetPowered(!buttonEnt4.Get<Lever>().GetPowered());

		button4AnimOn = true;
		isPecking = true;
		});

	KeyPressWatcher button5Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		buttonEnt5.Get<Lever>().SetPowered(!buttonEnt5.Get<Lever>().GetPowered());

		button5AnimOn = true;
		isPecking = true;
		});
};