#pragma once
#include <vector>

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
#include "DirectionalLight.h"
#include "UniformBuffer.h"
#include "BloomEffect.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

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
	void InitAnims();

	bool GetComplete();
	void SetComplete(bool complete);

	bool GetRetry();
	void SetRetry(bool retry);

	Entity GetCamera();

	entt::registry* GetScene();
	Shader::sptr GetShader();

	bool GetLoad();

	void SetShaderValues(Shader::sptr& shader, glm::vec3 lightPos = glm::vec3(0.f, 0.f, 0.f), 
		glm::vec3 lightDir = glm::vec3(0.f, 0.f, 0.f), glm::vec3 lightCol = glm::vec3(1.0f, 1.0f, 1.0f),
		float lightAmbientPow = 0.f, float lightSpecularPow = 0.f, 
		glm::vec3 ambientCol = glm::vec3(0.f, 0.f, 0.f), float ambientPow = 0.f, float shininess = 0.f, float lightLinearFalloff = 0.0f, float lightQuadraticFalloff = 0.0f);

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

	bool GetLightOn();
	void SetLightOn(bool isOn);

	bool GetTopView();
	void SetTopView(bool isTop);

protected:

	entt::registry* scene = nullptr;
	std::string name = " ";

	Shader::sptr shader, animShader, pauseShader, untexturedShader, particleShader, simpleDepthShader;

	GLFWwindow* window;
	HWND hWnd;
	POINT mousePos;

	Entity camEnt, uiCamEnt, topViewCamEnt;

	Camera::sptr toggleCam;

	Entity FBO, greyscaleEnt, sepiaEnt, colorCorrectEnt;
	Entity filmGrainEnt, pixelateEnt;
	Entity bloomEnt;
	Entity gBufferEnt, shadowBufferEnt;

	Entity pauseEnt, optionEnt, exitEnt, retryEnt, tutEnt, completeEnt;

	Mat clearMat, pauseMat, boxMat, curvedPipeMat, straightPipeMat, optionMat, exitMat, retryMat, optionPressMat, exitPressMat, retryPressMat;
	Mat buttonMat, drumstickMat, doorMat, doorOnMat, floorMat, wallMat, completeMat, wireMat, panelMat, ventMat, tabletMat, andTabletScreenMat, notTabletScreenMat, orTabletScreenMat, coilMatOn, coilMatOff;
	Mat andMat, notMat, orMat, wireMatOn, shelfPipeMat, columnPipeMat, labWallMat;

	//Meshes for multiple levels
	Mesh* options;
	Mesh* exit;
	Mesh* retry;
	Mesh* floor;
	Mesh* screen;
	Mesh* leftWall;
	Mesh* rightWall;
	Mesh* backWall;
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
	Mesh*and;
	Mesh* shelfPipe;
	Mesh* columnPipe;

	//For bigger "lab" levels
	Mesh* floorLab;
	Mesh* backWallLab;
	Mesh* leftWallLab;
	Mesh* rightWallLab;

	//Main Menu Level Meshes
	Mesh* startWord;
	Mesh* optionsWord;
	Mesh* exitWord;
	Mesh* mainMenuFloor;

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
	Mesh * not;
	Mesh* wireM1L3;
	Mesh* wireM2L3;
	Mesh* wireM3L3;
	Mesh* wireM4L3;
	Mesh* wireM5L3;
	Mesh* wireM6L3;
	Mesh* wireM7L3;
	Mesh* floorL3;

	//Level 4 Meshes
	Mesh* wireM1L4;
	Mesh* wireM2L4;
	Mesh* wireM3L4;
	Mesh* wireM4L4;
	Mesh* wireM5L4;
	Mesh* wireM6L4;
	Mesh* wireM7L4;
	Mesh* wireM8L4;
	Mesh* wireM9L4;
	Mesh* wireM10L4;

	//Level 5 Meshes
	Mesh* orMesh;
	Mesh* wireM1L5;
	Mesh* wireM2L5;
	Mesh* wireM3L5;
	Mesh* wireM4L5;
	Mesh* wireM5L5;
	Mesh* wireM6L5;
	Mesh* wireM7L5;

	//Level 6 Meshes
	Mesh* wireM1L6;
	Mesh* wireM2L6;
	Mesh* wireM3L6;
	Mesh* wireM4L6;
	Mesh* wireM5L6;
	Mesh* wireM6L6;
	Mesh* wireM7L6;
	Mesh* wireM8L6;
	Mesh* wireM9L6;

	//Files for multiple levels
	std::string drumFile = "Models/ChickenFrames/Walk/Walk1.obj";
	std::string floorFile = "Models/Floor.obj";
	std::string floorL1File = "Models/L1-Floor.obj";
	std::string floorL2File = "Models/L2-Floor.obj";
	std::string floorL3File = "Models/L3-Floor.obj";
	std::string floorL4File = "Models/Level4Floor.obj";
	std::string screenFile = "Models/Floor.obj";
	std::string leftWallFile = "Models/F-LW.obj";
	std::string rightWallFile = "Models/F-RW.obj";
	std::string backWallFile = "Models/F-FW.obj";
	std::string doorFile = "Models/DoorFrames/DoorFrame1.obj";
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
	std::string shelfPipeFile = "Models/ShelfPipe.obj";
	std::string columnPipeFile = "Models/New_Column_Pipe.obj";

	std::string labBackWallFile = "Models/BackWall_New.obj";
	std::string labLeftWallFile = "Models/LeftWall_New.obj";
	std::string labRightWallFile = "Models/RightWall_New.obj";

	//Main Menu Level Files
	std::string startFile = "Models/Start.obj";
	std::string exitFile = "Models/Exit.obj";
	std::string optFile = "Models/Options.obj";
	std::string mainMenuFloorFile = "Models/MainMenu-Floor.obj";

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
	std::string wire1L4File = "Models/Level4Wire1.obj";
	std::string wire2L4File = "Models/Level4Wire2.obj";
	std::string wire3L4File = "Models/Level4Wire3.obj";
	std::string wire4L4File = "Models/Level4Wire4.obj";
	std::string wire5L4File = "Models/Level4Wire5.obj";
	std::string wire6L4File = "Models/Level4Wire6.obj";
	std::string wire7L4File = "Models/Level4Wire7.obj";
	std::string wire8L4File = "Models/Level4Wire8.obj";
	std::string wire9L4File = "Models/Level4Wire9.obj";
	std::string wire10L4File = "Models/Level4Wire10.obj";

	//Level 5 files
	std::string orFile = "Models/OrGate.obj";
	std::string wire1L5File = "Models/Level5Wire1.obj";
	std::string wire2L5File = "Models/Level5Wire2.obj";
	std::string wire3L5File = "Models/Level5Wire3.obj";
	std::string wire4L5File = "Models/Level5Wire4.obj";
	std::string wire5L5File = "Models/Level5Wire5.obj";
	std::string wire6L5File = "Models/Level5Wire6.obj";
	std::string wire7L5File = "Models/Level5Wire7.obj";

	//Level 6 files
	std::string wire1L6File = "Models/Level6Wire1.obj";
	std::string wire2L6File = "Models/Level6Wire2.obj";
	std::string wire3L6File = "Models/Level6Wire3.obj";
	std::string wire4L6File = "Models/Level6Wire4.obj";
	std::string wire5L6File = "Models/Level6Wire5.obj";
	std::string wire6L6File = "Models/Level6Wire6.obj";
	std::string wire7L6File = "Models/Level6Wire7.obj";
	std::string wire8L6File = "Models/Level6Wire8.obj";
	std::string wire9L6File = "Models/Level6Wire9.obj";

	std::vector<std::function<void()>> imGuiCallbacks;

	std::vector<Entity> ents;

	bool levelComplete = false;
	bool levelRetry = false;

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
	int activeEffect = 3;

	KeyPressWatcher pauseWatch = KeyPressWatcher(GLFW_KEY_P, [&]() {
		isPaused = !isPaused;

		if (isPaused)
			lightOn = false;
		else
			lightOn = true;
		});

	KeyPressWatcher topViewToggle = KeyPressWatcher(GLFW_KEY_LEFT_SHIFT, [&]() {
		topView = !topView;
		});

	//FOR ANIMATIONS//
	std::vector<std::unique_ptr<Mesh>> doorFrames, walkFrames, doorCloseFrames, idleFrames, peckFrames, buttonFrames;

	Mesh* door1;
	Mesh* door2;
	Mesh* door3;
	Mesh* door4;

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

	Mesh* idle1;
	Mesh* idle2;
	Mesh* idle3;
	Mesh* idle4;
	Mesh* idle5;
	Mesh* idle6;
	Mesh* idle7;
	Mesh* idle8;
	Mesh* idle9;
	Mesh* idle10;
	Mesh* idle11;
	Mesh* idle12;
	Mesh* idle13;
	Mesh* idle14;
	Mesh* idle15;
	Mesh* idle16;
	Mesh* idle17;
	Mesh* idle18;

	Mesh* button1;
	Mesh* button2;
	Mesh* button3;

	Mesh* peck1;
	Mesh* peck2;
	Mesh* peck3;
	Mesh* peck4;
	Mesh* peck5;
	Mesh* peck6;
	Mesh* peck7;
	Mesh* peck8;
	Mesh* peck9;

	std::string doorFile1 = "Models/DoorFrames/DoorFrame1.obj";
	std::string doorFile2 = "Models/DoorFrames/DoorFrame2.obj";
	std::string doorFile3 = "Models/DoorFrames/DoorFrame3.obj";
	std::string doorFile4 = "Models/DoorFrames/DoorFrame4.obj";

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

	std::string idleFile1 = "Models/ChickenFrames/Idle/Idle1.obj";
	std::string idleFile2 = "Models/ChickenFrames/Idle/Idle2.obj";
	std::string idleFile3 = "Models/ChickenFrames/Idle/Idle3.obj";
	std::string idleFile4 = "Models/ChickenFrames/Idle/Idle4.obj";
	std::string idleFile5 = "Models/ChickenFrames/Idle/Idle5.obj";
	std::string idleFile6 = "Models/ChickenFrames/Idle/Idle6.obj";
	std::string idleFile7 = "Models/ChickenFrames/Idle/Idle7.obj";
	std::string idleFile8 = "Models/ChickenFrames/Idle/Idle8.obj";
	std::string idleFile9 = "Models/ChickenFrames/Idle/Idle9.obj";
	std::string idleFile10 = "Models/ChickenFrames/Idle/Idle10.obj";
	std::string idleFile11 = "Models/ChickenFrames/Idle/Idle11.obj";
	std::string idleFile12 = "Models/ChickenFrames/Idle/Idle12.obj";
	std::string idleFile13 = "Models/ChickenFrames/Idle/Idle13.obj";
	std::string idleFile14 = "Models/ChickenFrames/Idle/Idle14.obj";
	std::string idleFile15 = "Models/ChickenFrames/Idle/Idle15.obj";
	std::string idleFile16 = "Models/ChickenFrames/Idle/Idle16.obj";
	std::string idleFile17 = "Models/ChickenFrames/Idle/Idle17.obj";
	std::string idleFile18 = "Models/ChickenFrames/Idle/Idle18.obj";

	std::string buttonFile1 = "Models/ButtonFrames/Button_Press_Frame1.obj";
	std::string buttonFile2 = "Models/ButtonFrames/Button_Press_Frame2.obj";
	std::string buttonFile3 = "Models/ButtonFrames/Button_Press_Frame1.obj";

	std::string peckFile1 = "Models/ChickenFrames/Peck/Drumstick_Peck_Frame1.obj";
	std::string peckFile2 = "Models/ChickenFrames/Peck/Drumstick_Peck_Frame2.obj";
	std::string peckFile3 = "Models/ChickenFrames/Peck/Drumstick_Peck_Frame3.obj";
	std::string peckFile4 = "Models/ChickenFrames/Peck/Drumstick_Peck_Frame4.obj";
	std::string peckFile5 = "Models/ChickenFrames/Peck/Drumstick_Peck_Frame5.obj";
	std::string peckFile6 = "Models/ChickenFrames/Peck/Drumstick_Peck_Frame6.obj";
	std::string peckFile7 = "Models/ChickenFrames/Peck/Drumstick_Peck_Frame7.obj";
	std::string peckFile8 = "Models/ChickenFrames/Peck/Drumstick_Peck_Frame8.obj";
	std::string peckFile9 = "Models/ChickenFrames/Peck/Drumstick_Peck_Frame9.obj";
	///////////////

	DirectionalLight theSun;
	UniformBuffer directionalLightBuffer;

	int shadowWidth = 2048;
	int shadowHeight = 2048;

	std::vector<Entity*> entList;

	bool lightOn = true;
	int lightInt;

	bool isWalking;
	bool walkFramesApplied = false;
	bool idleFramesApplied = true;
	bool peckingFramesApplied = false;
	bool isPecking = false;

	bool showLevelComplete = false;

	bool topView = false;
	bool topChanged = false;
	bool camChanged = false;

	bool buttonAnimOn = false;
	bool button2AnimOn = false;
	bool button3AnimOn = false;
	bool button4AnimOn = false;
};
