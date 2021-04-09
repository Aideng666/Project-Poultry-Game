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
#include "XorGate.h"
#include "NorGate.h"
#include "XNorGate.h"
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
#include "AudioEngine.h"
#include "Tree.h"

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
	void InitLuts();

	void PauseInput();

	bool GetComplete();
	void SetComplete(bool complete);

	bool GetRetry();
	void SetRetry(bool retry);

	Entity GetCamera();

	entt::registry* GetScene();
	Shader::sptr GetShader();

	bool GetLoad();
	void SetLoad(bool load);

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

	bool GetIsBright();
	bool GetIsCorrected();

	void SetIsBright(bool bright);
	void SetIsCorrected(bool correct);

protected:

	entt::registry* scene = nullptr;
	std::string name = " ";

	Shader::sptr shader, animShader, pauseShader, untexturedShader, particleShader, simpleDepthShader, rimLightShader;

	GLFWwindow* window;
	HWND hWnd;
	POINT mousePos;

	Entity camEnt, uiCamEnt, topViewCamEnt;

	Camera::sptr toggleCam;

	Entity FBO, greyscaleEnt, sepiaEnt, colorCorrectEnt;
	Entity filmGrainEnt, pixelateEnt;
	Entity bloomEnt;
	Entity gBufferEnt, shadowBufferEnt;
	//Tablet
	Entity tabletEnt;
	Entity tabletScreenEnt;

	Entity pauseEnt, optionEnt, exitEnt, retryEnt, tutEnt, completeEnt, optionsMenuEnt;
	Entity muteEnt, colorBlindEnt, brightEnt, musicEnt, soundEnt, controlsEnt;

	Mat clearMat, pauseMat, optionMenuMat, boxMat, curvedPipeMat, straightPipeMat, optionMat, exitMat, retryMat, optionPressMat, exitPressMat, retryPressMat;
	Mat buttonMat, drumstickMat, doorMat, doorOnMat, floorMat, wallMat, completeMat, wireMat, panelMat, ventMat, tabletMat, andTabletScreenMat, notTabletScreenMat, orTabletScreenMat, norTabletScreenMat, xorTabletScreenMat, xnorTabletScreenMat, finalTabletMat, coilMatOn, coilMatOff;
	Mat andMat, notMat, orMat, xorMat, norMat, xnorMat, wireMatOn, shelfPipeMat, columnPipeMat, labWallMat, labFloorMat, tableMat, toggleOnMat, toggleOffMat, volumeMat;
	Mat volumeMat1, volumeMat2, volumeMat3, volumeMat4, volumeMat5, volumeMat6, volumeMat7, volumeMat8, volumeMat9, volumeMat10;
	Mat goodEndMat, badEndMat;

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
	Mesh* optionsButton;
	Mesh* table;
	Mesh* pauseControls;
	Mesh* topViewControls;

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
	Mesh* mainMenuBackWall;
	Mesh* mainMenuLeftWall;
	Mesh* mainMenuRightWall;
	Mesh* mainMenuWire1;
	Mesh* mainMenuWire2;
	Mesh* WASD;

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
	Mesh* wireM10L6;
	Mesh* wireM11L6;
	Mesh* wireM12L6;
	Mesh* wireM13L6;
	Mesh* wireM14L6;
	Mesh* wireM15L6;
	Mesh* wireM16L6;
	Mesh* wireM17L6;

	//Level 7 Meshes
	Mesh* wireM1L7;
	Mesh* wireM2L7;
	Mesh* wireM3L7;
	Mesh* wireM4L7;
	Mesh* wireM5L7;
	Mesh* wireM6L7;
	Mesh* wireM7L7;
	Mesh* wireM8L7;
	Mesh* wireM9L7;
	Mesh* wireM10L7;
	Mesh* wireM11L7;
	Mesh* wireM12L7;
	Mesh* wireM13L7;
	Mesh* wireM14L7;
	Mesh* wireM15L7;
	Mesh* wireM16L7;
	Mesh* wireM17L7;
	Mesh* wireM18L7;
	Mesh* wireM19L7;
	Mesh* xor;

	//Level 8
	Mesh* nor;
	Mesh* wireM1L8;
	Mesh* wireM2L8;
	Mesh* wireM3L8;
	Mesh* wireM4L8;
	Mesh* wireM5L8;
	Mesh* wireM6L8;
	Mesh* wireM7L8;
	Mesh* wireM8L8;
	Mesh* wireM9L8;
	Mesh* wireM10L8;
	Mesh* wireM11L8;
	Mesh* wireM12L8;
	Mesh* wireM13L8;
	Mesh* wireM14L8;
	Mesh* wireM15L8;
	Mesh* wireM16L8;
	Mesh* wireM17L8;
	Mesh* wireM18L8;

	//Level 9
	Mesh* xnor;
	Mesh* wireM1L9;
	Mesh* wireM2L9;
	Mesh* wireM3L9;
	Mesh* wireM4L9;
	Mesh* wireM5L9;
	Mesh* wireM6L9;
	Mesh* wireM7L9;
	Mesh* wireM8L9;
	Mesh* wireM9L9;
	Mesh* wireM10L9;
	Mesh* wireM11L9;
	Mesh* wireM12L9;
	Mesh* wireM13L9;
	Mesh* wireM14L9;
	Mesh* wireM15L9;
	Mesh* wireM16L9;
	Mesh* wireM17L9;
	Mesh* wireM18L9;
	Mesh* wireM19L9;
	Mesh* wireM20L9;
	Mesh* wireM21L9;
	Mesh* wireM22L9;

	//Final Level
	Mesh* finalWire;


	//Files for multiple levels
	std::string drumFile = "Models/ChickenFrames/Walk/Walk1.obj";
	std::string floorFile = "Models/Floor.obj";
	std::string floorL1File = "Models/L1-Floor.obj";
	std::string floorL2File = "Models/L2-Floor.obj";
	std::string floorL3File = "Models/L3-Floor.obj";
	std::string floorL4File = "Models/Floor-Level4.obj";
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
	std::string pauseButtonFile = "Models/UI_Buttons.obj";
	std::string optionsButtonFile = "Models/OptionsButtons.obj";
	std::string pipeFileS = "Models/New2_StraightPipe.obj";
	std::string pipeFileC = "Models/New2_CurvedPipe.obj";
	std::string shelfPipeFile = "Models/ShelfPipe.obj";
	std::string columnPipeFile = "Models/New_Column_Pipe.obj";
	std::string tableFile = "Models/Table.obj";
	std::string pauseControlFile = "Models/Pause_Controls.obj";
	std::string topViewControlFile = "Models/Shift_Controls.obj";

	std::string labBackWallFile = "Models/BackWall_New.obj";
	std::string labLeftWallFile = "Models/LeftWall_New.obj";
	std::string labRightWallFile = "Models/RightWall_New.obj";

	//Main Menu Level Files
	std::string startFile = "Models/Start.obj";
	std::string exitFile = "Models/Exit.obj";
	std::string optFile = "Models/Options.obj";
	std::string mainMenuFloorFile = "Models/MainMenu_Floor_Updated.obj";
	std::string mainMenuBackWallFile = "Models/MainMenu_BW_Updated.obj";
	std::string mainMenuLeftWallFile = "Models/MainMenu_LW_Updated.obj";
	std::string mainMenuRightWallFile = "Models/MainMenu_RW_Updated.obj";
	std::string mainMenuWire1File = "Models/MainMenu_Wire1.obj";
	std::string mainMenuWire2File = "Models/MainMenu_Wire2.obj";
	std::string WASDFile = "Models/MainMenu_WASD_Controls.obj";

	//Level 1 Files
	std::string wire1L1File = "Models/Wires/New_Level1Wire1.obj";
	std::string wire2L1File = "Models/Wires/New_Level1Wire2.obj";
	std::string wire3L1File = "Models/Wires/New2_Level1Wire3.obj";

	//Level 2 files
	std::string wire1L2File = "Models/Wires/Level2Wire1.obj";
	std::string wire2L2File = "Models/Wires/Level2Wire2.obj";
	std::string wire3L2File = "Models/Wires/Level2Wire3.obj";
	std::string wire4L2File = "Models/Wires/Level2Wire4.obj";
	std::string wire5L2File = "Models/Wires/New_Level2Wire5.obj";

	//Level 3 files
	std::string notFile = "Models/NotGate.obj";
	std::string wire1L3File = "Models/Wires/New_Level3Wire1.obj";
	std::string wire2L3File = "Models/Wires/New_Level3Wire2.obj";
	std::string wire3L3File = "Models/Wires/New_Level3Wire3.obj";
	std::string wire4L3File = "Models/Wires/New_Level3Wire4.obj";
	std::string wire5L3File = "Models/Wires/New_Level3Wire5.obj";
	std::string wire6L3File = "Models/Wires/New_Level3Wire6.obj";
	std::string wire7L3File = "Models/Wires/New_Level3Wire7.obj";

	//Level 4 files
	std::string wire1L4File = "Models/Wires/Level4Wire1.obj";
	std::string wire2L4File = "Models/Wires/Level4Wire2.obj";
	std::string wire3L4File = "Models/Wires/Level4Wire3.obj";
	std::string wire4L4File = "Models/Wires/Level4Wire4.obj";
	std::string wire5L4File = "Models/Wires/Level4Wire5.obj";
	std::string wire6L4File = "Models/Wires/Level4Wire6.obj";
	std::string wire7L4File = "Models/Wires/Level4Wire7.obj";
	std::string wire8L4File = "Models/Wires/Level4Wire8.obj";
	std::string wire9L4File = "Models/Wires/Level4Wire9.obj";
	std::string wire10L4File = "Models/Wires/Level4Wire10.obj";

	//Level 5 files
	std::string orFile = "Models/OrGate.obj";
	std::string wire1L5File = "Models/Wires/Level5Wire1.obj";
	std::string wire2L5File = "Models/Wires/Level5Wire2.obj";
	std::string wire3L5File = "Models/Wires/Level5Wire3.obj";
	std::string wire4L5File = "Models/Wires/Level5Wire4.obj";
	std::string wire5L5File = "Models/Wires/Level5Wire5.obj";
	std::string wire6L5File = "Models/Wires/Level5Wire6.obj";
	std::string wire7L5File = "Models/Wires/Level5Wire7.obj";

	//Level 6 files
	std::string xorFile = "Models/XorGate.obj";
	std::string wire1L6File = "Models/Wires/New_Level6_Wire1.obj";
	std::string wire2L6File = "Models/Wires/New_Level6_Wire2.obj";
	std::string wire3L6File = "Models/Wires/New_Level6_Wire3.obj";
	std::string wire4L6File = "Models/Wires/New_Level6_Wire4.obj";
	std::string wire5L6File = "Models/Wires/New_Level6_Wire5.obj";
	std::string wire6L6File = "Models/Wires/New_Level6_Wire6.obj";
	std::string wire7L6File = "Models/Wires/New_Level6_Wire7.obj";
	std::string wire8L6File = "Models/Wires/New_Level6_Wire8.obj";
	std::string wire9L6File = "Models/Wires/New_Level6_Wire9.obj";
	std::string wire10L6File = "Models/Wires/New_Level6_Wire10.obj";
	std::string wire11L6File = "Models/Wires/New_Level6_Wire11.obj";
	std::string wire12L6File = "Models/Wires/New_Level6_Wire12.obj";
	std::string wire13L6File = "Models/Wires/New_Level6_Wire13.obj";
	std::string wire14L6File = "Models/Wires/New_Level6_Wire14.obj";
	std::string wire15L6File = "Models/Wires/New_Level6_Wire15.obj";
	std::string wire16L6File = "Models/Wires/New_Level6_Wire16.obj";
	std::string wire17L6File = "Models/Wires/New_Level6_Wire17.obj";

	//Level 7 files
	std::string wire1L7File = "Models/Wires/Level7_Wire1.obj";
	std::string wire2L7File = "Models/Wires/Level7_Wire2.obj";
	std::string wire3L7File = "Models/Wires/Level7_Wire3.obj";
	std::string wire4L7File = "Models/Wires/Level7_Wire4.obj";
	std::string wire5L7File = "Models/Wires/Level7_Wire5.obj";
	std::string wire6L7File = "Models/Wires/Level7_Wire6.obj";
	std::string wire7L7File = "Models/Wires/Level7_Wire7.obj";
	std::string wire8L7File = "Models/Wires/Level7_Wire8.obj";
	std::string wire9L7File = "Models/Wires/Level7_Wire9.obj";
	std::string wire10L7File = "Models/Wires/Level7_Wire10.obj";
	std::string wire11L7File = "Models/Wires/Level7_Wire11.obj";
	std::string wire12L7File = "Models/Wires/Level7_Wire12.obj";
	std::string wire13L7File = "Models/Wires/Level7_Wire13.obj";
	std::string wire14L7File = "Models/Wires/Level7_Wire14.obj";
	std::string wire15L7File = "Models/Wires/Level7_Wire15.obj";
	std::string wire16L7File = "Models/Wires/Level7_Wire16.obj";
	std::string wire17L7File = "Models/Wires/Level7_Wire17.obj";
	std::string wire18L7File = "Models/Wires/Level7_Wire18.obj";
	std::string wire19L7File = "Models/Wires/Level7_Wire19.obj";

	//Level 8 files
	std::string norFile = "Models/NorGate.obj";
	std::string wire1L8File = "Models/Wires/Level8_Wire1.obj";
	std::string wire2L8File = "Models/Wires/Level8_Wire2.obj";
	std::string wire3L8File = "Models/Wires/Level8_Wire3.obj";
	std::string wire4L8File = "Models/Wires/Level8_Wire4.obj";
	std::string wire5L8File = "Models/Wires/Level8_Wire5.obj";
	std::string wire6L8File = "Models/Wires/Level8_Wire6.obj";
	std::string wire7L8File = "Models/Wires/Level8_Wire7.obj";
	std::string wire8L8File = "Models/Wires/Level8_Wire8.obj";
	std::string wire9L8File = "Models/Wires/Level8_Wire9.obj";
	std::string wire10L8File = "Models/Wires/Level8_Wire10.obj";
	std::string wire11L8File = "Models/Wires/Level8_Wire11.obj";
	std::string wire12L8File = "Models/Wires/Level8_Wire12.obj";
	std::string wire13L8File = "Models/Wires/Level8_Wire13.obj";
	std::string wire14L8File = "Models/Wires/Level8_Wire14.obj";
	std::string wire15L8File = "Models/Wires/Level8_Wire15.obj";
	std::string wire16L8File = "Models/Wires/Level8_Wire16.obj";
	std::string wire17L8File = "Models/Wires/Level8_Wire17.obj";
	std::string wire18L8File = "Models/Wires/Level8_Wire18.obj";
	std::string wire19L8File = "Models/Wires/Level8_Wire19.obj";

	//Level 9 files
	std::string xnorFile = "Models/XNorGate.obj";
	std::string wire1L9File = "Models/Wires/New_Level9_Wire1.obj"; 
	std::string wire2L9File = "Models/Wires/New_Level9_Wire2.obj"; 
	std::string wire3L9File = "Models/Wires/New_Level9_Wire3.obj"; 
	std::string wire4L9File = "Models/Wires/New_Level9_Wire4.obj"; 
	std::string wire5L9File = "Models/Wires/New_Level9_Wire5.obj"; 
	std::string wire6L9File = "Models/Wires/New_Level9_Wire6.obj"; 
	std::string wire7L9File = "Models/Wires/New_Level9_Wire7.obj"; 
	std::string wire8L9File = "Models/Wires/New_Level9_Wire8.obj"; 
	std::string wire9L9File = "Models/Wires/New_Level9_Wire9.obj"; 
	std::string wire10L9File = "Models/Wires/New_Level9_Wire10.obj"; 
	std::string wire11L9File = "Models/Wires/New_Level9_Wire11.obj"; 
	std::string wire12L9File = "Models/Wires/New_Level9_Wire12.obj"; 
	std::string wire13L9File = "Models/Wires/New_Level9_Wire13.obj"; 
	std::string wire14L9File = "Models/Wires/New_Level9_Wire14.obj"; 
	std::string wire15L9File = "Models/Wires/New_Level9_Wire15.obj"; 
	std::string wire16L9File = "Models/Wires/New_Level9_Wire16.obj"; 
	std::string wire17L9File = "Models/Wires/New_Level9_Wire17.obj"; 
	std::string wire18L9File = "Models/Wires/New_Level9_Wire18.obj"; 
	std::string wire19L9File = "Models/Wires/New_Level9_Wire19.obj"; 
	std::string wire20L9File = "Models/Wires/New_Level9_Wire20.obj"; 
	std::string wire21L9File = "Models/Wires/New_Level9_Wire21.obj"; 
	std::string wire22L9File = "Models/Wires/New_Level9_Wire22.obj"; 

	//Final Level
	std::string finalWireFile = "Models/Wires/FinalLevel_Wire1.obj";

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
	bool optionsOpen = false;

	bool isMute = false;
	int musicVol = 5;
	int soundVol = 5;
	bool isBright = false;
	bool isCorrected = false;
	bool isArrow = false;

	bool camClose = false;
	bool camFar = false;

	bool camLeft = false;
	bool camRight = false;

	std::vector<PostEffect*> effects;
	int activeEffect = 3;

	KeyPressWatcher pauseWatch = KeyPressWatcher(GLFW_KEY_P, [&]() {
		isPaused = !isPaused;

		if (isPaused)
			pauseLighting = true;
		else
			pauseLighting = false;
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
	Mesh* door5;
	Mesh* door6;
	Mesh* door7;
	Mesh* door8;
	Mesh* door9;
	Mesh* door10;
	Mesh* door11;

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
	std::string doorFile5 = "Models/DoorFrames/DoorFrame5.obj";
	std::string doorFile6 = "Models/DoorFrames/DoorFrame6.obj";
	std::string doorFile7 = "Models/DoorFrames/DoorFrame7.obj";
	std::string doorFile8 = "Models/DoorFrames/DoorFrame8.obj";
	std::string doorFile9 = "Models/DoorFrames/DoorFrame9.obj";
	std::string doorFile10 = "Models/DoorFrames/DoorFrame10.obj";
	std::string doorFile11 = "Models/DoorFrames/DoorFrame11.obj";

	std::string walkFile1 = "Models/ChickenFrames/Walk/Walk1.obj";
	std::string walkFile2 = "Models/ChickenFrames/Walk/Walk2.obj";
	std::string walkFile3 = "Models/ChickenFrames/Walk/Walk3.obj";
	std::string walkFile4 = "Models/ChickenFrames/Walk/Walk4.obj";
	std::string walkFile5 = "Models/ChickenFrames/Walk/Walk5.obj";
	std::string walkFile6 = "Models/ChickenFrames/Walk/Walk6.obj";
	std::string walkFile7 = "Models/ChickenFrames/Walk/Walk7.obj";
	std::string walkFile8 = "Models/ChickenFrames/Walk/Walk8.obj";
	std::string walkFile9 = "Models/ChickenFrames/Walk/Walk9.obj";
	std::string walkFile10 = "Models/ChickenFrames/Walk/Walk10.obj";
	std::string walkFile11 = "Models/ChickenFrames/Walk/Walk11.obj";
	std::string walkFile12 = "Models/ChickenFrames/Walk/Walk12.obj";
	std::string walkFile13 = "Models/ChickenFrames/Walk/Walk13.obj";
	std::string walkFile14 = "Models/ChickenFrames/Walk/Walk14.obj";

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
	bool pauseLighting = false;
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
	bool button5AnimOn = false;
	bool button6AnimOn = false;
	bool button7AnimOn = false;
	bool button8AnimOn = false;

	bool doorOpenApplied = true;
	bool doorOpenApplied2 = true;
	bool doorClosingApplied = false;
	bool doorClosingApplied2 = false;

	bool isTalking = false;
	bool completeSoundPlaying = false;

	LUT3D lut;
	LUT3D brightLut;
	LUT3D colorCorrectLut;
};
