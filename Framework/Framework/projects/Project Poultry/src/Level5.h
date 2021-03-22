#pragma once
#include "Scene.h"
#include "Wire.h"
#include "Lever.h"
#include <vector>
#include <iostream>

using namespace freebird;

class Level5 : public Scene
{
public:
	Level5(std::string sceneName, GLFWwindow* wind);

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
	Entity wireEnt, wireEnt2, wireEnt3, wireEnt4, wireEnt5, wireEnt6, wireEnt7;
	//Vents
	Entity ventEnt, ventEnt2;
	//Door
	Entity doorEnt;
	//And-Gate
	Entity andEnt;
	//Or-Gate
	Entity orEnt, orEnt2;
	//Buttons
	Entity buttonEnt, buttonEnt2, buttonEnt3, buttonEnt4;
	//Coil
	Entity coilEnt;
	//Shelf Pipe
	Entity shelfPipeEnt, shelfPipeEnt2, shelfPipeEnt3, shelfPipeEnt4;
	//Column Pipe
	Entity columnPipeEnt, columnPipeEnt2;
	//Pipes
	Entity pipeEntC, pipeEntC2, pipeEntS, pipeEntS2;
	//Panel
	Entity panelEnt;

	KeyPressWatcher pauseWatch = KeyPressWatcher(GLFW_KEY_P, [&]() {
		isPaused = !isPaused;
	});

	KeyPressWatcher button1Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		buttonEnt.Get<Lever>().SetPowered(!buttonEnt.Get<Lever>().GetPowered());
		std::cout << "Button 1 Power: " << buttonEnt.Get<Lever>().GetPowered() << std::endl;
		});

	KeyPressWatcher button2Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		buttonEnt2.Get<Lever>().SetPowered(!buttonEnt2.Get<Lever>().GetPowered());
		std::cout << "Button 2 Power: " << buttonEnt2.Get<Lever>().GetPowered() << std::endl;
		});

	KeyPressWatcher button3Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		buttonEnt3.Get<Lever>().SetPowered(!buttonEnt3.Get<Lever>().GetPowered());
		std::cout << "Button 3 Power: " << buttonEnt3.Get<Lever>().GetPowered() << std::endl;
		});

	KeyPressWatcher button4Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		buttonEnt4.Get<Lever>().SetPowered(!buttonEnt4.Get<Lever>().GetPowered());
		std::cout << "Button 4 Power: " << buttonEnt4.Get<Lever>().GetPowered() << std::endl;
		});
};