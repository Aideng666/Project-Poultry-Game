#pragma once

#include "Entity.h"
#include "Input.h"
#include "Camera.h"
#include "Mesh.h"
#include "Transform.h"
#include "Shader.h"
#include "AndGate.h"
#include "OrGate.h"
#include "NotGate.h"
#include "Texture2DData.h"
#include "Texture2D.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <MeshRenderer.h>
#include <ModelManager.h>
#include "Greyscale.h"
#include "Sepia.h"
#include "ColorCorrect.h"
#include "FilmGrain.h"
#include "Pixelate.h"
#include "GBuffer.h"

#include "BloomEffect.h"

using namespace freebird;

class Scene
{

public:
	Scene()
	{
		scene = new entt::registry();
	}
	Scene(std::string sceneName, GLFWwindow* wind);
 

	virtual void InitScene();
	virtual void Update(float dt) {}

	virtual void Unload();

	void InitTextures();
	void InitShaders();
	void InitMeshes();

	bool GetComplete();
	void SetComplete(bool complete);

	Entity GetCamera();

	entt::registry* GetScene();
	Shader::sptr GetShader();

	bool GetLoad();

	void SetShaderValues(Shader::sptr& shader, glm::vec3 lightPos = glm::vec3(0.f, 0.f, 0.f), 
		glm::vec3 lightDir = glm::vec3(0.f, 0.f, 0.f), glm::vec3 lightCol = glm::vec3(1.0f, 1.0f, 1.0f),
		float lightAmbientPow = 0.f, float lightSpecularPow = 0.f, 
		glm::vec3 ambientCol = glm::vec3(0.f, 0.f, 0.f), float ambientPow = 0.f, float shininess = 0.f);

	struct Mat
	{
		Texture2D::sptr Albedo;
		float Shininess;
	};

	void LoadTexImage();

	//Entity GetFBO();
	//Entity GetGreyscaleEnt();

	std::vector<PostEffect*> GetEffects();

	bool GetTextured();
	void SetTextured(bool isTex);

	int GetActiveEffect();
	void SetActiveEffect(int activeEffect);

protected:

	entt::registry* scene = nullptr;
	std::string name = " ";

	Shader::sptr shader, animShader, pauseShader, untexturedShader, particleShader, gBufferShader;

	GLFWwindow* window;

	Entity camEnt, uiCamEnt;

	Entity FBO, greyscaleEnt, sepiaEnt, colorCorrectEnt;
	Entity filmGrainEnt, pixelateEnt;
	Entity bloomEnt;
	Entity gBufferEnt;

	Entity pauseEnt, optionEnt, exitEnt, retryEnt;

	Mat clearMat, pauseMat, boxMat, curvedPipeMat, straightPipeMat, optionMat, exitMat, retryMat;
	Mat buttonMat, drumstickMat, doorMat, floorMat, wallMat, completeMat, wireMat, panelMat, ventMat, tabletMat, andTabletScreenMat, notTabletScreenMat, orTabletScreenMat, coilMatOn, coilMatOff;
	Mat andMat, notMat, wireMatOn;

	//Meshes for multiple levels
	Mesh* options;
	Mesh* exit;
	Mesh* retry;
	Mesh* drumstick;
	Mesh* floor;
	Mesh* screen;
	Mesh* leftWall;
	Mesh* rightWall;
	Mesh* backWall;
	Mesh* doorM;
	Mesh* doorCloseM;
	Mesh* buttonM;
	Mesh* coil;
	Mesh* boxM;
	Mesh* panel;
	Mesh* ventB;
	Mesh* ventS;
	Mesh* pipeS;
	Mesh* pipeC;
	Mesh* tablet;
	Mesh* tut;
	Mesh* and;

	//Main Menu Level Meshes
	Mesh* startWord;
	Mesh* optionsWord;
	Mesh* exitWord;

	//Level 1 Meshes
	Mesh* wireM1L1;
	Mesh* wireM2L1;
	Mesh* wireM3L1;
	Mesh* floorL1;

	//Level 2 Meshes
	Mesh* wireM1L2;
	Mesh* wireM2L2;
	Mesh* wireM3L2;
	Mesh* wireM4L2;
	Mesh* wireM5L2;
	Mesh* floorL2;

	//Level 3 Meshes
	Mesh* not;
	Mesh* wireM1L3;
	Mesh* wireM2L3;
	Mesh* wireM3L3;
	Mesh* wireM4L3;
	Mesh* wireM5L3;
	Mesh* wireM6L3;
	Mesh* wireM7L3;
	Mesh* floorL3;

	//Level 4 Meshes
	Mesh* floorL4;
	Mesh* backWallL4;
	Mesh* leftWallL4;
	Mesh* rightWallL4;

	//Files for multiple levels
	std::string drumFile = "Models/ChickenFrames/Walk1.obj";
	std::string floorFile = "Models/Floor.obj";
	std::string floorL1File = "Models/Level1Floor.obj";
	std::string floorL2File = "Models/Level2Floor.obj";
	std::string floorL3File = "Models/Level3Floor.obj";
	std::string floorL4File = "Models/Level4Floor.obj";
	std::string screenFile = "Models/Floor.obj";
	std::string leftWallFile = "Models/LeftWall.obj";
	std::string rightWallFile = "Models/RightWall.obj";
	std::string backWallFile = "Models/BackWall.obj";
	std::string doorFile = "Models/DoorFrames/Door0.obj";
	std::string andFile = "Models/AndGate.obj";
	std::string buttonFile = "Models/Button.obj";
	std::string coilFile = "Models/TeslaCoil.obj";
	std::string boxFile = "Models/Box.obj";
	std::string panelFile = "Models/Panel.obj";
	std::string ventFileB = "Models/New2_VentLarge.obj";
	std::string ventFileS = "Models/New_VentSmall.obj";
	std::string tabletFile = "Models/Tablet.obj";
	std::string tutFile = "Models/Interact.obj";
	std::string pauseButtonFile = "Models/UI_Button.obj";
	std::string pipeFileS = "Models/New2_StraightPipe.obj";
	std::string pipeFileC = "Models/New2_CurvedPipe.obj";

	//Main Menu Level Files
	std::string startFile = "Models/Start.obj";
	std::string exitFile = "Models/Exit.obj";
	std::string optFile = "Models/Options.obj";
	
	//Level 1 Files
	std::string wire1L1File = "Models/New_Level1Wire1.obj";
	std::string wire2L1File = "Models/New_Level1Wire2.obj";
	std::string wire3L1File = "Models/New2_Level1Wire3.obj";

	//Level 2 files
	std::string wire1L2File = "Models/Level2Wire1.obj";
	std::string wire2L2File = "Models/Level2Wire2.obj";
	std::string wire3L2File = "Models/Level2Wire3.obj";
	std::string wire4L2File = "Models/Level2Wire4.obj";
	std::string wire5L2File = "Models/New_Level2Wire5.obj";

	//Level 3 files
	std::string notFile = "Models/NotGate.obj";
	std::string wire1L3File = "Models/New_Level3Wire1.obj";
	std::string wire2L3File = "Models/New_Level3Wire2.obj";
	std::string wire3L3File = "Models/New_Level3Wire3.obj";
	std::string wire4L3File = "Models/New_Level3Wire4.obj";
	std::string wire5L3File = "Models/New_Level3Wire5.obj";
	std::string wire6L3File = "Models/New_Level3Wire6.obj";
	std::string wire7L3File = "Models/New_Level3Wire7.obj";

	//Level 4 files
	std::string level4BackWallFile = "Models/Level4BackWall.obj";
	std::string level4LeftWallFile = "Models/Level4LeftWall.obj";
	std::string level4RightWallFile = "Models/Level4RightWall.obj";

	std::vector<std::function<void()>> imGuiCallbacks;

	std::vector<Entity> ents;

	bool levelComplete = false;

	unsigned char* image;
	const char* fileName;
	int width, height;

	bool loadModels = false;
	bool isTextured = true;

	bool isPaused = false;
	bool tabletOpen = false;

	bool camClose = false;
	bool camFar = false;

	bool camLeft = false;
	bool camRight = false;

	int lightNum = 5;

	std::vector<PostEffect*> effects;
	int activeEffect = 0;

	KeyPressWatcher pauseWatch = KeyPressWatcher(GLFW_KEY_P, [&]() {
		isPaused = !isPaused;

		if (isPaused)
			lightNum = 2;
		else
			lightNum = 5;
		});

	//FOR ANIMATIONS//
	std::vector<std::unique_ptr<Mesh>> doorFrames, walkFrames, doorCloseFrames;

	Mesh* door1;
	Mesh* door2;
	Mesh* door3;
	Mesh* door4;
	Mesh* door5;
	Mesh* door6;
	Mesh* door7;
	Mesh* door8;
	Mesh* door9;
	Mesh* door10;

	Mesh* walk1;
	Mesh* walk2;
	Mesh* walk3;
	Mesh* walk4;
	Mesh* walk5;
	Mesh* walk6;
	Mesh* walk7;
	Mesh* walk8;
	Mesh* walk9;
	Mesh* walk10;
	Mesh* walk11;
	Mesh* walk12;
	Mesh* walk13;
	Mesh* walk14;

	std::string doorFile1 = "Models/DoorFrames/Door0.obj";
	std::string doorFile2 = "Models/DoorFrames/Door1.obj";
	std::string doorFile3 = "Models/DoorFrames/Door2.obj";
	std::string doorFile4 = "Models/DoorFrames/Door3.obj";
	std::string doorFile5 = "Models/DoorFrames/Door4.obj";
	std::string doorFile6 = "Models/DoorFrames/Door5.obj";
	std::string doorFile7 = "Models/DoorFrames/Door6.obj";
	std::string doorFile8 = "Models/DoorFrames/Door7.obj";
	std::string doorFile9 = "Models/DoorFrames/Door8.obj";
	std::string doorFile10 = "Models/DoorFrames/Door9.obj";

	std::string walkFile1 = "Models/ChickenFrames/Walk1.obj";
	std::string walkFile2 = "Models/ChickenFrames/Walk2.obj";
	std::string walkFile3 = "Models/ChickenFrames/Walk3.obj";
	std::string walkFile4 = "Models/ChickenFrames/Walk4.obj";
	std::string walkFile5 = "Models/ChickenFrames/Walk5.obj";
	std::string walkFile6 = "Models/ChickenFrames/Walk6.obj";
	std::string walkFile7 = "Models/ChickenFrames/Walk7.obj";
	std::string walkFile8 = "Models/ChickenFrames/Walk8.obj";
	std::string walkFile9 = "Models/ChickenFrames/Walk9.obj";
	std::string walkFile10 = "Models/ChickenFrames/Walk10.obj";
	std::string walkFile11 = "Models/ChickenFrames/Walk11.obj";
	std::string walkFile12 = "Models/ChickenFrames/Walk12.obj";
	std::string walkFile13 = "Models/ChickenFrames/Walk13.obj";
	std::string walkFile14 = "Models/ChickenFrames/Walk14.obj";
	///////////////

	std::vector<Entity> entList;
	std::vector<Mesh*> meshList;
};
