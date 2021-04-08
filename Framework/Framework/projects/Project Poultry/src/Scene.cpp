#include "Scene.h"
#include <iostream>
#include <stb_image.h>

using namespace freebird;

Scene::Scene(std::string sceneName, GLFWwindow* wind)
{
	name = sceneName;
	window = wind;

	hWnd = glfwGetWin32Window(window);
}

void Scene::InitScene()
{
	scene = new entt::registry();

	Entity::SetReg(scene);


	//Set Up Camera
	Entity camEnt = Entity::Create();
	auto& camera = camEnt.Add<Camera>();

	camera.SetPosition(glm::vec3(0, 3, 3)); // Set initial position
	camera.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
	camera.LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camera.SetFovDegrees(90.0f); // Set an initial FOV
}

void Scene::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}

void Scene::InitTextures()
{
	Texture2D::sptr diffuseButton = Texture2D::LoadFromFile("Textures/ButtonTexture.png");
	Texture2D::sptr diffuseDrum = Texture2D::LoadFromFile("Textures/DrumstickTexture.png");
	Texture2D::sptr diffuseDoor = Texture2D::LoadFromFile("Textures/DoorTex.png");
	Texture2D::sptr diffuseDoorOn = Texture2D::LoadFromFile("Textures/DoorTexOn.png");
	Texture2D::sptr diffuseFloor = Texture2D::LoadFromFile("Textures/FloorTilesetFinal.png");
	Texture2D::sptr diffuseLabFloor = Texture2D::LoadFromFile("Textures/LabFloorTileset.png");
	Texture2D::sptr diffuseWall = Texture2D::LoadFromFile("Textures/WallTileset.png");
	Texture2D::sptr diffuseLabWall = Texture2D::LoadFromFile("Textures/Lab-WallTileset.png");
	Texture2D::sptr diffuseComplete = Texture2D::LoadFromFile("Textures/LevelComplete.png");
	Texture2D::sptr diffuseAnd = Texture2D::LoadFromFile("Textures/AndGate.png");
	Texture2D::sptr diffuseNot = Texture2D::LoadFromFile("Textures/NotGate.png");
	Texture2D::sptr diffuseOr = Texture2D::LoadFromFile("Textures/OrGate.png");
	Texture2D::sptr diffuseXor = Texture2D::LoadFromFile("Textures/XorGateTex.png");
	Texture2D::sptr diffuseNor = Texture2D::LoadFromFile("Textures/NorGateTex.png");
	Texture2D::sptr diffuseXNor = Texture2D::LoadFromFile("Textures/XNorGateTex.png");
	Texture2D::sptr diffuseWire = Texture2D::LoadFromFile("Textures/Wire_Off_Texture.png");
	Texture2D::sptr diffuseWireOn = Texture2D::LoadFromFile("Textures/Wire_On_Texture.png");
	Texture2D::sptr diffuseBox = Texture2D::LoadFromFile("Textures/Box_Texture.png");
	Texture2D::sptr diffusePanel = Texture2D::LoadFromFile("Textures/PanelTexture.png");
	Texture2D::sptr diffuseVent = Texture2D::LoadFromFile("Textures/VentTexture.png");
	Texture2D::sptr diffusePipeStraight = Texture2D::LoadFromFile("Textures/Pipe_Straight_Texture.png");
	Texture2D::sptr diffusePipeCurved = Texture2D::LoadFromFile("Textures/Pipe_Curved_Texture.png");
	Texture2D::sptr diffusePipeShelf = Texture2D::LoadFromFile("Textures/ShelfPipeTexture.png");
	Texture2D::sptr diffusePipeColumn = Texture2D::LoadFromFile("Textures/ColumnPipeTexture.png");
	Texture2D::sptr diffusePause = Texture2D::LoadFromFile("Textures/PauseMenu.png");
	Texture2D::sptr diffuseOptions = Texture2D::LoadFromFile("Textures/Buttons/Default/Options.png");
	Texture2D::sptr diffuseRetry = Texture2D::LoadFromFile("Textures/Buttons/Default/Retry.png");
	Texture2D::sptr diffuseExit = Texture2D::LoadFromFile("Textures/Buttons/Default/Exit.png");
	Texture2D::sptr diffuseOptionsMenu = Texture2D::LoadFromFile("Textures/OptionsMenu.png");
	Texture2D::sptr diffusePressOptions = Texture2D::LoadFromFile("Textures/Buttons/Pressed/Options.png");
	Texture2D::sptr diffusePressRetry = Texture2D::LoadFromFile("Textures/Buttons/Pressed/Retry.png");
	Texture2D::sptr diffusePressExit = Texture2D::LoadFromFile("Textures/Buttons/Pressed/Exit.png");
	Texture2D::sptr diffuseTablet = Texture2D::LoadFromFile("Textures/TabletTexture.png");
	Texture2D::sptr diffuseAndTabletScreen = Texture2D::LoadFromFile("Textures/AndGateTablet.png");
	Texture2D::sptr diffuseNotTabletScreen = Texture2D::LoadFromFile("Textures/NotGateTablet.png");
	Texture2D::sptr diffuseOrTabletScreen = Texture2D::LoadFromFile("Textures/OrGateTablet.png");
	Texture2D::sptr diffuseNorTabletScreen = Texture2D::LoadFromFile("Textures/NorGateTablet.png");
	Texture2D::sptr diffuseXorTabletScreen = Texture2D::LoadFromFile("Textures/XorGateTablet.png");
	Texture2D::sptr diffuseXnorTabletScreen = Texture2D::LoadFromFile("Textures/XNorGateTablet.png");
	Texture2D::sptr diffuseFinalTablet = Texture2D::LoadFromFile("Textures/FinalTablet.png");
	Texture2D::sptr diffuseCoilOff = Texture2D::LoadFromFile("Textures/Tesla_Coil_Texture_Off.png");
	Texture2D::sptr diffuseCoilOn = Texture2D::LoadFromFile("Textures/Tesla_Coil_Texture_On.png");
	Texture2D::sptr diffuseTable = Texture2D::LoadFromFile("Textures/TableTexture.png");
	Texture2D::sptr diffuseOnToggle = Texture2D::LoadFromFile("Textures/OnToggle.png");
	Texture2D::sptr diffuseOffToggle = Texture2D::LoadFromFile("Textures/OffToggle.png");
	Texture2D::sptr diffuseVolume1 = Texture2D::LoadFromFile("Textures/Volume/1.png");
	Texture2D::sptr diffuseVolume2 = Texture2D::LoadFromFile("Textures/Volume/2.png");
	Texture2D::sptr diffuseVolume3 = Texture2D::LoadFromFile("Textures/Volume/3.png");
	Texture2D::sptr diffuseVolume4 = Texture2D::LoadFromFile("Textures/Volume/4.png");
	Texture2D::sptr diffuseVolume5 = Texture2D::LoadFromFile("Textures/Volume/5.png");
	Texture2D::sptr diffuseVolume6 = Texture2D::LoadFromFile("Textures/Volume/6.png");
	Texture2D::sptr diffuseVolume7 = Texture2D::LoadFromFile("Textures/Volume/7.png");
	Texture2D::sptr diffuseVolume8 = Texture2D::LoadFromFile("Textures/Volume/8.png");
	Texture2D::sptr diffuseVolume9 = Texture2D::LoadFromFile("Textures/Volume/9.png");
	Texture2D::sptr diffuseVolume10 = Texture2D::LoadFromFile("Textures/Volume/10.png");

	Texture2DDescription desc = Texture2DDescription();
	desc.Width = 1;
	desc.Height = 1;
	desc.Format = InternalFormat::RGB8;
	Texture2D::sptr texture2 = Texture2D::Create(desc);
	texture2->Clear();

	buttonMat.Albedo = diffuseButton;
	drumstickMat.Albedo = diffuseDrum;
	doorMat.Albedo = diffuseDoor;
	doorOnMat.Albedo = diffuseDoorOn;
	floorMat.Albedo = diffuseFloor;
	labFloorMat.Albedo = diffuseLabFloor;
	wallMat.Albedo = diffuseWall;
	labWallMat.Albedo = diffuseLabWall;
	completeMat.Albedo = diffuseComplete;
	andMat.Albedo = diffuseAnd;
	notMat.Albedo = diffuseNot;
	orMat.Albedo = diffuseOr;
	xorMat.Albedo = diffuseXor;
	norMat.Albedo = diffuseNor;
	xnorMat.Albedo = diffuseXNor;
	wireMat.Albedo = diffuseWire;
	wireMatOn.Albedo = diffuseWireOn;
	boxMat.Albedo = diffuseBox;
	panelMat.Albedo = diffusePanel;
	ventMat.Albedo = diffuseVent;
	straightPipeMat.Albedo = diffusePipeStraight;
	curvedPipeMat.Albedo = diffusePipeCurved;
	shelfPipeMat.Albedo = diffusePipeShelf;
	columnPipeMat.Albedo = diffusePipeColumn;
	optionMenuMat.Albedo = diffuseOptionsMenu;
	pauseMat.Albedo = diffusePause;
	optionMat.Albedo = diffuseOptions;
	retryMat.Albedo = diffuseRetry;
	exitMat.Albedo = diffuseExit;
	optionPressMat.Albedo = diffusePressOptions;
	exitPressMat.Albedo = diffusePressExit;
	retryPressMat.Albedo = diffusePressRetry;
	tabletMat.Albedo = diffuseTablet;
	andTabletScreenMat.Albedo = diffuseAndTabletScreen;
	notTabletScreenMat.Albedo = diffuseNotTabletScreen;
	orTabletScreenMat.Albedo = diffuseOrTabletScreen;
	norTabletScreenMat.Albedo = diffuseNorTabletScreen;
	xorTabletScreenMat.Albedo = diffuseXorTabletScreen;
	xnorTabletScreenMat.Albedo = diffuseXnorTabletScreen;
	finalTabletMat.Albedo = diffuseFinalTablet;
	coilMatOff.Albedo = diffuseCoilOff;
	coilMatOn.Albedo = diffuseCoilOn;
	tableMat.Albedo = diffuseTable;
	toggleOnMat.Albedo = diffuseOnToggle;
	toggleOffMat.Albedo = diffuseOffToggle;
	volumeMat1.Albedo = diffuseVolume1;
	volumeMat2.Albedo = diffuseVolume2;
	volumeMat3.Albedo = diffuseVolume3;
	volumeMat4.Albedo = diffuseVolume4;
	volumeMat5.Albedo = diffuseVolume5;
	volumeMat6.Albedo = diffuseVolume6;
	volumeMat7.Albedo = diffuseVolume7;
	volumeMat8.Albedo = diffuseVolume8;
	volumeMat9.Albedo = diffuseVolume9;
	volumeMat10.Albedo = diffuseVolume10;
	clearMat.Albedo = texture2;
}

void Scene::InitShaders()
{
	glm::vec3 lightPos = glm::vec3(0.0f, 5.0f, -5.0f);
	glm::vec3 lightDir = glm::vec3(0.0f, -1.0f, 1.0f);
	glm::vec3 lightCol = glm::vec3(1.f);
	float     lightAmbientPow = 0.25f;
	float	  pauseAmbientPow = 0.25f;
	float     lightSpecularPow = 1.0f;
	glm::vec3 ambientCol = glm::vec3(1.0f);
	float     ambientPow = 0.1f;
	float     shininess = 16.0f;
	float     lightLinearFalloff = 0.09f;
	float     lightQuadraticFalloff = 0.032f;



	//Basic shader
	shader = Shader::Create();
	shader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	shader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	shader->Link();
	SetShaderValues(shader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, ambientCol, ambientPow, shininess, lightLinearFalloff, lightQuadraticFalloff);

	rimLightShader = Shader::Create();
	rimLightShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	rimLightShader->LoadShaderPartFromFile("Shaders/rim_lighting_shader.glsl", GL_FRAGMENT_SHADER);
	rimLightShader->Link();
	SetShaderValues(rimLightShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, ambientCol, ambientPow, shininess, lightLinearFalloff, lightQuadraticFalloff);

	//For any objects with animations
	animShader = Shader::Create();
	animShader->LoadShaderPartFromFile("Shaders/morph_shader.glsl", GL_VERTEX_SHADER);
	animShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	animShader->Link();
	SetShaderValues(animShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, ambientCol, ambientPow, shininess, lightLinearFalloff, lightQuadraticFalloff);

	//Particle shader
	particleShader = Shader::Create();
	particleShader->LoadShaderPartFromFile("Shaders/particle_vertex.glsl", GL_VERTEX_SHADER);
	particleShader->LoadShaderPartFromFile("Shaders/particle_geom.glsl", GL_GEOMETRY_SHADER);
	particleShader->LoadShaderPartFromFile("Shaders/particle_frag.glsl", GL_FRAGMENT_SHADER);
	particleShader->Link();

	//Shader for unextured objects
	untexturedShader = Shader::Create();
	untexturedShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	untexturedShader->LoadShaderPartFromFile("Shaders/frag_untextured.glsl", GL_FRAGMENT_SHADER);
	untexturedShader->Link();
	SetShaderValues(untexturedShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, ambientCol, ambientPow, shininess, lightLinearFalloff, lightQuadraticFalloff);

	//Pause UI Shader
	pauseShader = Shader::Create();
	pauseShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	pauseShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	pauseShader->Link();
	SetShaderValues(pauseShader, lightPos, lightDir, lightCol, pauseAmbientPow, lightSpecularPow, ambientCol, pauseAmbientPow, shininess, lightLinearFalloff, lightQuadraticFalloff);

	simpleDepthShader = Shader::Create();
	simpleDepthShader->LoadShaderPartFromFile("Shaders/simple_depth_vert.glsl", GL_VERTEX_SHADER);
	simpleDepthShader->LoadShaderPartFromFile("Shaders/simple_depth_frag.glsl", GL_FRAGMENT_SHADER);
	simpleDepthShader->Link();
	SetShaderValues(simpleDepthShader, lightPos, lightDir, lightCol, pauseAmbientPow, lightSpecularPow, ambientCol, pauseAmbientPow, shininess, lightLinearFalloff, lightQuadraticFalloff);

	/*Shader::sptr gBufferShader = Shader::Create();
	gBufferShader->LoadShaderPartFromFile("shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	gBufferShader->LoadShaderPartFromFile("shaders/gBuffer_pass_frag.glsl", GL_FRAGMENT_SHADER);
	gBufferShader->Link();*/
}

void Scene::InitMeshes()
{
	//For Door Anim
	door1 = ModelManager::FindMesh(doorFile1);
	door2 = ModelManager::FindMesh(doorFile2);
	door3 = ModelManager::FindMesh(doorFile3);
	door4 = ModelManager::FindMesh(doorFile4);
	door5 = ModelManager::FindMesh(doorFile5);
	door6 = ModelManager::FindMesh(doorFile6);
	door7 = ModelManager::FindMesh(doorFile7);
	door8 = ModelManager::FindMesh(doorFile8);
	door9 = ModelManager::FindMesh(doorFile9);
	door10 = ModelManager::FindMesh(doorFile10);

	//For Walking Anim
	walk1 = ModelManager::FindMesh(walkFile1);
	walk2 = ModelManager::FindMesh(walkFile2);
	walk3 = ModelManager::FindMesh(walkFile3);
	walk4 = ModelManager::FindMesh(walkFile4);
	walk5 = ModelManager::FindMesh(walkFile5);
	walk6 = ModelManager::FindMesh(walkFile6);
	walk7 = ModelManager::FindMesh(walkFile7);
	walk8 = ModelManager::FindMesh(walkFile8);
	walk9 = ModelManager::FindMesh(walkFile9);
	walk10 = ModelManager::FindMesh(walkFile10);
	walk11 = ModelManager::FindMesh(walkFile11);
	walk12 = ModelManager::FindMesh(walkFile12);
	walk13 = ModelManager::FindMesh(walkFile13);
	walk14 = ModelManager::FindMesh(walkFile14);

	//For Idle Anim
	idle1 = ModelManager::FindMesh(idleFile1);
	idle2 = ModelManager::FindMesh(idleFile2);
	idle3 = ModelManager::FindMesh(idleFile3);
	idle4 = ModelManager::FindMesh(idleFile4);
	idle5 = ModelManager::FindMesh(idleFile5);
	idle6 = ModelManager::FindMesh(idleFile6);
	idle7 = ModelManager::FindMesh(idleFile7);
	idle8 = ModelManager::FindMesh(idleFile8);
	idle9 = ModelManager::FindMesh(idleFile9);
	idle10 = ModelManager::FindMesh(idleFile10);
	idle11 = ModelManager::FindMesh(idleFile11);
	idle12 = ModelManager::FindMesh(idleFile12);
	idle13 = ModelManager::FindMesh(idleFile13);
	idle14 = ModelManager::FindMesh(idleFile14);
	idle15 = ModelManager::FindMesh(idleFile15);
	idle16 = ModelManager::FindMesh(idleFile16);
	idle17 = ModelManager::FindMesh(idleFile17);
	idle18 = ModelManager::FindMesh(idleFile18);

	//For Button Anim
	button1 = ModelManager::FindMesh(buttonFile1);
	button2 = ModelManager::FindMesh(buttonFile2);
	button3 = ModelManager::FindMesh(buttonFile3);

	//For Pecking Anim
	peck1 = ModelManager::FindMesh(peckFile1);
	peck2 = ModelManager::FindMesh(peckFile2);
	peck3 = ModelManager::FindMesh(peckFile3);
	peck4 = ModelManager::FindMesh(peckFile4);
	peck5 = ModelManager::FindMesh(peckFile5);
	peck6 = ModelManager::FindMesh(peckFile6);
	peck7 = ModelManager::FindMesh(peckFile7);
	peck8 = ModelManager::FindMesh(peckFile8);
	peck9 = ModelManager::FindMesh(peckFile9);

	//Multiple Levels
	//drumstick = ModelManager::FindMesh(drumFile);
	floor = ModelManager::FindMesh(floorFile);
	screen = ModelManager::FindMesh(screenFile);
	leftWall = ModelManager::FindMesh(leftWallFile);
	rightWall = ModelManager::FindMesh(rightWallFile);
	backWall = ModelManager::FindMesh(backWallFile);
	options = ModelManager::FindMesh(pauseButtonFile);
	exit = ModelManager::FindMesh(pauseButtonFile);
	retry = ModelManager::FindMesh(pauseButtonFile);
	and = ModelManager::FindMesh(andFile);
	not = ModelManager::FindMesh(notFile);
	xor = ModelManager::FindMesh(xorFile);
	nor = ModelManager::FindMesh(norFile);
	xnor = ModelManager::FindMesh(xnorFile);
	orMesh = ModelManager::FindMesh(orFile);
	buttonM = ModelManager::FindMesh(buttonFile);
	coil = ModelManager::FindMesh(coilFile);
	boxM = ModelManager::FindMesh(boxFile);
	panel = ModelManager::FindMesh(panelFile);
	ventB = ModelManager::FindMesh(ventFileB);
	ventS = ModelManager::FindMesh(ventFileS);
	pipeS = ModelManager::FindMesh(pipeFileS);
	pipeC = ModelManager::FindMesh(pipeFileC);
	shelfPipe = ModelManager::FindMesh(shelfPipeFile);
	columnPipe = ModelManager::FindMesh(columnPipeFile);
	tablet = ModelManager::FindMesh(tabletFile);
	tut = ModelManager::FindMesh(tutFile, glm::vec3(1.0f, 0.0f, 0.0f));
	optionsButton = ModelManager::FindMesh(optionsButtonFile);
	table = ModelManager::FindMesh(tableFile);

	//Lab Levels(tentative)
	floorLab = ModelManager::FindMesh(floorL4File);
	leftWallLab = ModelManager::FindMesh(labLeftWallFile);
	rightWallLab = ModelManager::FindMesh(labRightWallFile);
	backWallLab = ModelManager::FindMesh(labBackWallFile);

	//Main Menu Level
	startWord = ModelManager::FindMesh(startFile, glm::vec3(1.0f, 0.0f, 0.0f));
	exitWord = ModelManager::FindMesh(exitFile, glm::vec3(1.0f, 0.0f, 0.0f));
	optionsWord = ModelManager::FindMesh(optFile, glm::vec3(1.0f, 0.0f, 0.0f));
	mainMenuFloor = ModelManager::FindMesh(mainMenuFloorFile);
	mainMenuBackWall = ModelManager::FindMesh(mainMenuBackWallFile);
	mainMenuLeftWall = ModelManager::FindMesh(mainMenuLeftWallFile);
	mainMenuRightWall = ModelManager::FindMesh(mainMenuRightWallFile);
	mainMenuWire1 = ModelManager::FindMesh(mainMenuWire1File);
	mainMenuWire2 = ModelManager::FindMesh(mainMenuWire2File);
	WASD = ModelManager::FindMesh(WASDFile, glm::vec3(1.0f, 0.0f, 0.0f));

	//Level 1
	wireM1L1 = ModelManager::FindMesh(wire1L1File);
	wireM2L1 = ModelManager::FindMesh(wire2L1File);
	wireM3L1 = ModelManager::FindMesh(wire3L1File);
	floorL1 = ModelManager::FindMesh(floorL1File);

	//Level 2
	wireM1L2 = ModelManager::FindMesh(wire1L2File);
	wireM2L2 = ModelManager::FindMesh(wire2L2File);
	wireM3L2 = ModelManager::FindMesh(wire3L2File);
	wireM4L2 = ModelManager::FindMesh(wire4L2File);
	wireM5L2 = ModelManager::FindMesh(wire5L2File);
	floorL2 = ModelManager::FindMesh(floorL2File);

	//Level 3
	wireM1L3 = ModelManager::FindMesh(wire1L3File);
	wireM2L3 = ModelManager::FindMesh(wire2L3File);
	wireM3L3 = ModelManager::FindMesh(wire3L3File);
	wireM4L3 = ModelManager::FindMesh(wire4L3File);
	wireM5L3 = ModelManager::FindMesh(wire5L3File);
	wireM6L3 = ModelManager::FindMesh(wire6L3File);
	wireM7L3 = ModelManager::FindMesh(wire7L3File);
	floorL3 = ModelManager::FindMesh(floorL3File);

	//Level4
	wireM1L4 = ModelManager::FindMesh(wire1L4File);
	wireM2L4 = ModelManager::FindMesh(wire2L4File);
	wireM3L4 = ModelManager::FindMesh(wire3L4File);
	wireM4L4 = ModelManager::FindMesh(wire4L4File);
	wireM5L4 = ModelManager::FindMesh(wire5L4File);
	wireM6L4 = ModelManager::FindMesh(wire6L4File);
	wireM7L4 = ModelManager::FindMesh(wire7L4File);
	wireM8L4 = ModelManager::FindMesh(wire8L4File);
	wireM9L4 = ModelManager::FindMesh(wire9L4File);
	wireM10L4 = ModelManager::FindMesh(wire10L4File);

	//Level5
	wireM1L5 = ModelManager::FindMesh(wire1L5File);
	wireM2L5 = ModelManager::FindMesh(wire2L5File);
	wireM3L5 = ModelManager::FindMesh(wire3L5File);
	wireM4L5 = ModelManager::FindMesh(wire4L5File);
	wireM5L5 = ModelManager::FindMesh(wire5L5File);
	wireM6L5 = ModelManager::FindMesh(wire6L5File);
	wireM7L5 = ModelManager::FindMesh(wire7L5File);

	//Level6
	wireM1L6 = ModelManager::FindMesh(wire1L6File);
	wireM2L6 = ModelManager::FindMesh(wire2L6File);
	wireM3L6 = ModelManager::FindMesh(wire3L6File);
	wireM4L6 = ModelManager::FindMesh(wire4L6File);
	wireM5L6 = ModelManager::FindMesh(wire5L6File);
	wireM6L6 = ModelManager::FindMesh(wire6L6File);
	wireM7L6 = ModelManager::FindMesh(wire7L6File);
	wireM8L6 = ModelManager::FindMesh(wire8L6File);
	wireM9L6 = ModelManager::FindMesh(wire9L6File);
	wireM10L6 = ModelManager::FindMesh(wire10L6File);
	wireM11L6 = ModelManager::FindMesh(wire11L6File);
	wireM12L6 = ModelManager::FindMesh(wire12L6File);
	wireM13L6 = ModelManager::FindMesh(wire13L6File);
	wireM14L6 = ModelManager::FindMesh(wire14L6File);
	wireM15L6 = ModelManager::FindMesh(wire15L6File);
	wireM16L6 = ModelManager::FindMesh(wire16L6File);
	wireM17L6 = ModelManager::FindMesh(wire17L6File);

	//Level 7
	wireM1L7 = ModelManager::FindMesh(wire1L7File);
	wireM2L7 = ModelManager::FindMesh(wire2L7File);
	wireM3L7 = ModelManager::FindMesh(wire3L7File);
	wireM4L7 = ModelManager::FindMesh(wire4L7File);
	wireM5L7 = ModelManager::FindMesh(wire5L7File);
	wireM6L7 = ModelManager::FindMesh(wire6L7File);
	wireM7L7 = ModelManager::FindMesh(wire7L7File);
	wireM8L7 = ModelManager::FindMesh(wire8L7File);
	wireM9L7 = ModelManager::FindMesh(wire9L7File);
	wireM10L7 = ModelManager::FindMesh(wire10L7File);
	wireM11L7 = ModelManager::FindMesh(wire11L7File);
	wireM12L7 = ModelManager::FindMesh(wire12L7File);
	wireM13L7 = ModelManager::FindMesh(wire13L7File);
	wireM14L7 = ModelManager::FindMesh(wire14L7File);
	wireM15L7 = ModelManager::FindMesh(wire15L7File);
	wireM16L7 = ModelManager::FindMesh(wire16L7File);
	wireM17L7 = ModelManager::FindMesh(wire17L7File);
	wireM18L7 = ModelManager::FindMesh(wire18L7File);
	wireM19L7 = ModelManager::FindMesh(wire19L7File);

	//Level 8
	wireM1L8 = ModelManager::FindMesh(wire1L8File);
	wireM2L8 = ModelManager::FindMesh(wire2L8File);
	wireM3L8 = ModelManager::FindMesh(wire3L8File);
	wireM4L8 = ModelManager::FindMesh(wire4L8File);
	wireM5L8 = ModelManager::FindMesh(wire5L8File);
	wireM6L8 = ModelManager::FindMesh(wire6L8File);
	wireM7L8 = ModelManager::FindMesh(wire7L8File);
	wireM8L8 = ModelManager::FindMesh(wire8L8File);
	wireM9L8 = ModelManager::FindMesh(wire9L8File);
	wireM10L8 = ModelManager::FindMesh(wire10L8File);
	wireM11L8 = ModelManager::FindMesh(wire11L8File);
	wireM12L8 = ModelManager::FindMesh(wire12L8File);
	wireM13L8 = ModelManager::FindMesh(wire13L8File);
	wireM14L8 = ModelManager::FindMesh(wire14L8File);
	wireM15L8 = ModelManager::FindMesh(wire15L8File);
	wireM16L8 = ModelManager::FindMesh(wire16L8File);
	wireM17L8 = ModelManager::FindMesh(wire17L8File);
	wireM18L8 = ModelManager::FindMesh(wire18L8File);

	//Level 9
	wireM1L9   = ModelManager::FindMesh(wire1L9File);
	wireM2L9 = ModelManager::FindMesh(wire2L9File);
	wireM3L9 = ModelManager::FindMesh(wire3L9File);
	wireM4L9 = ModelManager::FindMesh(wire4L9File);
	wireM5L9 = ModelManager::FindMesh(wire5L9File);
	wireM6L9 = ModelManager::FindMesh(wire6L9File);
	wireM7L9 = ModelManager::FindMesh(wire7L9File);
	wireM8L9 = ModelManager::FindMesh(wire8L9File);
	wireM9L9 = ModelManager::FindMesh(wire9L9File);
	wireM10L9 = ModelManager::FindMesh(wire10L9File);
	wireM11L9 = ModelManager::FindMesh(wire11L9File);
	wireM12L9 = ModelManager::FindMesh(wire12L9File);
	wireM13L9 = ModelManager::FindMesh(wire13L9File);
	wireM14L9 = ModelManager::FindMesh(wire14L9File);
	wireM15L9 = ModelManager::FindMesh(wire15L9File);
	wireM16L9 = ModelManager::FindMesh(wire16L9File);
	wireM17L9 = ModelManager::FindMesh(wire17L9File);
	wireM18L9 = ModelManager::FindMesh(wire18L9File);
	wireM19L9 = ModelManager::FindMesh(wire19L9File);
	wireM20L9 = ModelManager::FindMesh(wire20L9File);
	wireM21L9 = ModelManager::FindMesh(wire21L9File);
	wireM22L9 = ModelManager::FindMesh(wire22L9File);

	//Final Level
	finalWire = ModelManager::FindMesh(finalWireFile);

	entList.clear();
}

void Scene::InitAnims()
{
	doorFrames.clear();
	doorCloseFrames.clear();
	walkFrames.clear();
	idleFrames.clear();
	buttonFrames.clear();
	peckFrames.clear();

	//Door Animations
	doorFrames.push_back(std::unique_ptr<Mesh>(door1));
	doorFrames.push_back(std::unique_ptr<Mesh>(door2));
	doorFrames.push_back(std::unique_ptr<Mesh>(door3));
	doorFrames.push_back(std::unique_ptr<Mesh>(door4));
	doorFrames.push_back(std::unique_ptr<Mesh>(door5));
	doorFrames.push_back(std::unique_ptr<Mesh>(door6));
	doorFrames.push_back(std::unique_ptr<Mesh>(door7));
	doorFrames.push_back(std::unique_ptr<Mesh>(door8));
	doorFrames.push_back(std::unique_ptr<Mesh>(door9));
	doorFrames.push_back(std::unique_ptr<Mesh>(door10));
	

	doorCloseFrames.push_back(std::unique_ptr<Mesh>(door10));
	doorCloseFrames.push_back(std::unique_ptr<Mesh>(door9));
	doorCloseFrames.push_back(std::unique_ptr<Mesh>(door8));
	doorCloseFrames.push_back(std::unique_ptr<Mesh>(door7));
	doorCloseFrames.push_back(std::unique_ptr<Mesh>(door6));
	doorCloseFrames.push_back(std::unique_ptr<Mesh>(door5));
	doorCloseFrames.push_back(std::unique_ptr<Mesh>(door4));
	doorCloseFrames.push_back(std::unique_ptr<Mesh>(door3));
	doorCloseFrames.push_back(std::unique_ptr<Mesh>(door2));
	doorCloseFrames.push_back(std::unique_ptr<Mesh>(door1));

	//Walking Animations
	walkFrames.push_back(std::unique_ptr<Mesh>(walk1));
	walkFrames.push_back(std::unique_ptr<Mesh>(walk2));
	walkFrames.push_back(std::unique_ptr<Mesh>(walk3));
	walkFrames.push_back(std::unique_ptr<Mesh>(walk4));
	walkFrames.push_back(std::unique_ptr<Mesh>(walk5));
	walkFrames.push_back(std::unique_ptr<Mesh>(walk6));
	walkFrames.push_back(std::unique_ptr<Mesh>(walk7));
	walkFrames.push_back(std::unique_ptr<Mesh>(walk8));
	walkFrames.push_back(std::unique_ptr<Mesh>(walk9));
	walkFrames.push_back(std::unique_ptr<Mesh>(walk10));
	walkFrames.push_back(std::unique_ptr<Mesh>(walk11));
	walkFrames.push_back(std::unique_ptr<Mesh>(walk12));
	walkFrames.push_back(std::unique_ptr<Mesh>(walk13));
	walkFrames.push_back(std::unique_ptr<Mesh>(walk14));

	//Idle Animations
	idleFrames.push_back(std::unique_ptr<Mesh>(idle1));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle2));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle3));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle4));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle5));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle6));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle7));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle8));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle9));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle10));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle11));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle12));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle13));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle14));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle15));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle16));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle17));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle18));

	//Button Animations
	buttonFrames.push_back(std::unique_ptr<Mesh>(button1));
	buttonFrames.push_back(std::unique_ptr<Mesh>(button2));
	buttonFrames.push_back(std::unique_ptr<Mesh>(button3));

	//Pecking Animation
	peckFrames.push_back(std::unique_ptr<Mesh>(peck1));
	peckFrames.push_back(std::unique_ptr<Mesh>(peck2));
	peckFrames.push_back(std::unique_ptr<Mesh>(peck3));
	peckFrames.push_back(std::unique_ptr<Mesh>(peck4));
	peckFrames.push_back(std::unique_ptr<Mesh>(peck5));
	peckFrames.push_back(std::unique_ptr<Mesh>(peck6));
	peckFrames.push_back(std::unique_ptr<Mesh>(peck7));
	peckFrames.push_back(std::unique_ptr<Mesh>(peck8));
	peckFrames.push_back(std::unique_ptr<Mesh>(peck9));
}

void Scene::InitLuts()
{
	lut.loadFromFile("GameColorCorrection.cube");
	brightLut.loadFromFile("BrightMode.cube");
	colorCorrectLut.loadFromFile("ColorBlindMode.cube");
}

void Scene::PauseInput()
{
	GetCursorPos(&mousePos);

	ScreenToClient(hWnd, &mousePos);

	if (GetAsyncKeyState(0x01) && isPaused && mousePos.y > 403 && mousePos.y < 597 && mousePos.x > 865 && mousePos.x < 1097)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (GetAsyncKeyState(0x01) && isPaused && mousePos.y > 403 && mousePos.y < 595 && mousePos.x > 487 && mousePos.x < 714)
	{
		levelRetry = true;
	}

	if (GetAsyncKeyState(0x01) && isPaused && mousePos.y > 403 && mousePos.y < 594 && mousePos.x > 104 && mousePos.x < 336)
	{
		isPaused = false;
		optionsOpen = true;
	}

	if (optionsOpen && (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS))
	{
		optionsOpen = false;
		lightOn = true;
		pauseLighting = false;
	}

	if (optionsOpen && GetAsyncKeyState(0x01))
	{
		std::cout << mousePos.x << " " << mousePos.y << std::endl;
	}

	//To Mute
	if (GetAsyncKeyState(0x01) && optionsOpen && mousePos.y > 291 && mousePos.y < 379 && mousePos.x > 848 && mousePos.x < 959)
	{
		Sleep(100);
		isMute = !isMute;
	}

	//Bright Mode
	if (GetAsyncKeyState(0x01) && optionsOpen && mousePos.y > 745 && mousePos.y < 836 && mousePos.x > 848 && mousePos.x < 959)
	{
		Sleep(100);
		isBright = !isBright;
	}

	//Color Blind Mode
	if (GetAsyncKeyState(0x01) && optionsOpen && mousePos.y > 653 && mousePos.y < 740 && mousePos.x > 848 && mousePos.x < 959)
	{
		Sleep(100);
		isCorrected = !isCorrected;
	}

	//Control Change
	if (GetAsyncKeyState(0x01) && optionsOpen && mousePos.y > 839 && mousePos.y < 932 && mousePos.x > 848 && mousePos.x < 959)
	{
		Sleep(100);
		isArrow = !isArrow;
	}

	////Increase Sound Effect Volume
	if (GetAsyncKeyState(0x01) && optionsOpen && mousePos.y > 391 && mousePos.y < 407 && mousePos.x > 927 && mousePos.x < 947)
	{
		Sleep(100);
		if (soundVol < 10)
			soundVol++;
	}

	////Decrease Sound Effect Volume
	if (GetAsyncKeyState(0x01) && optionsOpen && mousePos.y > 451 && mousePos.y < 468 && mousePos.x > 927 && mousePos.x < 947)
	{
		Sleep(200);

		if (soundVol > 1)
			soundVol--;
	}

	//////Increase Music Volume
	if (GetAsyncKeyState(0x01) && optionsOpen && mousePos.y > 485 && mousePos.y < 503 && mousePos.x > 927 && mousePos.x < 947)
	{
		Sleep(200);
		if (musicVol < 10)
			musicVol++;
	}

	//Decrease Music Volume
	if (GetAsyncKeyState(0x01) && optionsOpen && mousePos.y > 545 && mousePos.y < 565 && mousePos.x > 927 && mousePos.x < 947)
	{
		Sleep(200);

		if (musicVol > 1)
			musicVol--;
	}

	if (isMute)
	{
		AudioEngine::Instance().GetBus("SoundBus").SetVolume(0.0f);
		AudioEngine::Instance().GetBus("MusicBus").SetVolume(0.0f);
	}

	if (!isMute)
	{
		switch (soundVol)
		{
		case 1:
			AudioEngine::Instance().GetBus("SoundBus").SetVolume(0.1f);
			break;

		case 2:
			AudioEngine::Instance().GetBus("SoundBus").SetVolume(0.2f);
			break;

		case 3:
			AudioEngine::Instance().GetBus("SoundBus").SetVolume(0.3f);
			break;

		case 4:
			AudioEngine::Instance().GetBus("SoundBus").SetVolume(0.4f);
			break;

		case 5:
			AudioEngine::Instance().GetBus("SoundBus").SetVolume(0.5f);
			break;

		case 6:
			AudioEngine::Instance().GetBus("SoundBus").SetVolume(0.6f);
			break;

		case 7:
			AudioEngine::Instance().GetBus("SoundBus").SetVolume(0.7f);
			break;

		case 8:
			AudioEngine::Instance().GetBus("SoundBus").SetVolume(0.8f);
			break;

		case 9:
			AudioEngine::Instance().GetBus("SoundBus").SetVolume(0.9f);
			break;

		case 10:
			AudioEngine::Instance().GetBus("SoundBus").SetVolume(1.0f);
			break;
		}

		switch (musicVol)
		{
		case 1:
			AudioEngine::Instance().GetBus("MusicBus").SetVolume(0.1f);
			break;

		case 2:
			AudioEngine::Instance().GetBus("MusicBus").SetVolume(0.2f);
			break;

		case 3:
			AudioEngine::Instance().GetBus("MusicBus").SetVolume(0.3f);
			break;

		case 4:
			AudioEngine::Instance().GetBus("MusicBus").SetVolume(0.4f);
			break;

		case 5:
			AudioEngine::Instance().GetBus("MusicBus").SetVolume(0.5f);
			break;

		case 6:
			AudioEngine::Instance().GetBus("MusicBus").SetVolume(0.6f);
			break;

		case 7:
			AudioEngine::Instance().GetBus("MusicBus").SetVolume(0.7f);
			break;

		case 8:
			AudioEngine::Instance().GetBus("MusicBus").SetVolume(0.8f);
			break;

		case 9:
			AudioEngine::Instance().GetBus("MusicBus").SetVolume(0.9f);
			break;

		case 10:
			AudioEngine::Instance().GetBus("MusicBus").SetVolume(1.0f);
			break;
		}
	}
}

bool Scene::GetComplete()
{
	return levelComplete;
}

void Scene::SetComplete(bool complete)
{
	levelComplete = complete;
}

bool Scene::GetRetry()
{
	return levelRetry;
}

void Scene::SetRetry(bool retry)
{
	levelRetry = retry;
}

Entity Scene::GetCamera()
{
	return camEnt;
}

entt::registry* Scene::GetScene()
{
	return scene;
}

Shader::sptr Scene::GetShader()
{
	return shader;
}

bool Scene::GetLoad()
{
	return loadModels;
}

void Scene::SetShaderValues(Shader::sptr& shader, glm::vec3 lightPos, glm::vec3 lightDir, glm::vec3 lightCol, float lightAmbientPow, float lightSpecularPow, glm::vec3 ambientCol, float ambientPow, float shininess, float lightLinearFalloff, float lightQuadraticFalloff)
{
	shader->SetUniform("u_LightPos", lightPos);
	shader->SetUniform("u_LightDir", lightDir);
	shader->SetUniform("u_LightCol", lightCol);
	shader->SetUniform("u_AmbientLightStrength", lightAmbientPow);
	shader->SetUniform("u_SpecularLightStrength", lightSpecularPow);
	shader->SetUniform("u_AmbientCol", ambientCol);
	shader->SetUniform("u_AmbientStrength", ambientPow);
	shader->SetUniform("u_Shininess", shininess);
	shader->SetUniform("u_AmbientLightStrength2", 0.01f);
	shader->SetUniform("u_LightAttenuationConstant", 1.0f);
	shader->SetUniform("u_LightAttenuationLinear", lightLinearFalloff);
	shader->SetUniform("u_LightAttenuationQuadratic", lightQuadraticFalloff);
}

void Scene::LoadTexImage()
{
		int channels;
		stbi_set_flip_vertically_on_load(true);

		image = stbi_load(fileName, &width, &height, &channels, 0);

		if (image)
			std::cout << "Image loaded: " << width << " x " << height << std::endl;
		else std::cout << "Failed to load image" << std::endl;
}

std::vector<PostEffect*> Scene::GetEffects()
{
	return effects;
}

bool Scene::GetTextured()
{
	return isTextured;
}

void Scene::SetTextured(bool isTex)
{
	isTextured = isTex;
}

int Scene::GetActiveEffect()
{
	return activeEffect;
}

void Scene::SetActiveEffect(int activeEffect)
{
	this->activeEffect = activeEffect;
}

bool Scene::GetLightOn()
{
	return lightOn;
}

void Scene::SetLightOn(bool isOn)
{
	lightOn = isOn;
}

bool Scene::GetTopView()
{
	return topView;
}

void Scene::SetTopView(bool isTop)
{
	topView = isTop;
}

bool Scene::GetIsBright()
{
	return isBright;
}

bool Scene::GetIsCorrected()
{
	return isCorrected;
}

void Scene::SetIsBright(bool bright)
{
	isBright = bright;
}

void Scene::SetIsCorrected(bool correct)
{
	isCorrected = correct;
}
