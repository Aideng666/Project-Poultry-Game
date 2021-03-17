#pragma once
#include "Scene.h"
#include "Wire.h"
#include "Lever.h"
#include <vector>
#include <iostream>

using namespace freebird;

class Level4 : public Scene
{
public:

	Level4(std::string sceneName, GLFWwindow* wind);

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
	//Door
	Entity doorEnt;
	//Buttons
	Entity buttonEnt, buttonEnt2, buttonEnt3, buttonEnt4;
	//And-Gates
	Entity andEnt, andEnt2, andEnt3;
	//Not-Gates
	Entity notEnt, notEnt2, notEnt3;
	//Wires
	Entity wireEnt, wireEnt2, wireEnt3, wireEnt4, wireEnt5, wireEnt6,
		wireEnt7, wireEnt8, wireEnt9, wireEnt10;
	//Panels
	Entity panelEnt, panelEnt2;
	//Vents 
	Entity ventEntS, ventEntL;
	//Boxes
	Entity boxEnt, boxEnt2, boxEnt3, boxEnt4, boxEnt5, boxEnt6;
	//Column Pipes
	Entity colPipeEnt, colPipeEnt2;
	//Shelf Pipes
	Entity shelfPipeEnt, shelfPipeEnt2, shelfPipeEnt3;
	//Tesla Coil
	Entity coilEnt;
};