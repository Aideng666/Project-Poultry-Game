#pragma once
#include "Scene.h"
#include "Wire.h"
#include "Lever.h"
#include <vector>
#include <iostream>

using namespace freebird;

class Level9 : public Scene
{
public:
	Level9(std::string sceneName, GLFWwindow* wind);

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
	Entity wireEnt, wireEnt2, wireEnt3, wireEnt4, wireEnt5, wireEnt6, wireEnt7, wireEnt8, wireEnt9, wireEnt10, wireEnt11, wireEnt12, wireEnt13, wireEnt14, wireEnt15, wireEnt16, wireEnt17, wireEnt18, wireEnt19, wireEnt20, wireEnt21, wireEnt22;
	//Door
	Entity doorEnt;
	//Tesla Coil
	Entity coilEnt;
	//Buttons
	Entity buttonEnt, buttonEnt2, buttonEnt3, buttonEnt4, buttonEnt5, buttonEnt6, buttonEnt7, buttonEnt8;
	//And-Gate
	Entity andEnt, andEnt2, andEnt3, andEnt4, andEnt5;
	//Or-Gate
	Entity orEnt, orEnt2, orEnt3;
	//Xor-Gates
	Entity xorEnt, xorEnt2, xorEnt4;
	//Nor-Gates
	Entity norEnt;
	//XNor-Gate
	Entity xnorEnt, xnorEnt2;
	//Level Complete Ent
	Entity completeEnt;

	//Vent Entities
	Entity ventEnt, ventEnt2, ventEnt3, ventEnt4;

	//Panel
	Entity panelEnt, panelEnt2;

	//Tables
	Entity tableEnt, tableEnt2;

	//Shelf Pipe
	Entity shelfPipeEnt, shelfPipeEnt2, shelfPipeEnt3, shelfPipeEnt4,
		shelfPipeEnt5, shelfPipeEnt6, shelfPipeEnt7, shelfPipeEnt8;

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

	KeyPressWatcher button6Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		buttonEnt6.Get<Lever>().SetPowered(!buttonEnt6.Get<Lever>().GetPowered());

		button6AnimOn = true;
		isPecking = true;
		});

	KeyPressWatcher button7Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		buttonEnt7.Get<Lever>().SetPowered(!buttonEnt7.Get<Lever>().GetPowered());

		button7AnimOn = true;
		isPecking = true;
		});

	KeyPressWatcher button8Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		buttonEnt8.Get<Lever>().SetPowered(!buttonEnt8.Get<Lever>().GetPowered());

		button8AnimOn = true;
		isPecking = true;
		});

	KeyPressWatcher tabletWatch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		tabletOpen = !tabletOpen;

		if (tabletOpen)
			pauseLighting = true;
		else
			pauseLighting = false;
		});
};