#include "Level3.h"
#include <iostream>
#include <GLFW\glfw3.h>

#include "Application.h"
#include <imgui.h>
#include <AABB.h>
#include <MeshRenderer.h>
#include <MorphRenderer.h>
#include "Texture2DData.h"
#include "Texture2D.h"
#include <stb_image.h>
#include <MorphAnimation.h>

using namespace freebird;


Level3::Level3(std::string sceneName, GLFWwindow* wind)
	: Scene(sceneName, wind)
{
#pragma region Entities
	mainPlayer = Entity::Create();
	floorEnt = Entity::Create();
	leftEnt = Entity::Create();
	rightEnt = Entity::Create();
	backEnt = Entity::Create();
	optionEnt = Entity::Create();
	exitEnt = Entity::Create();
	retryEnt = Entity::Create();
	buttonEnt = Entity::Create();
	buttonEnt2 = Entity::Create();
	buttonEnt3 = Entity::Create();
	doorEnt = Entity::Create();
	andEnt = Entity::Create();
	andEnt2 = Entity::Create();
	andEnt3 = Entity::Create();
	notEnt = Entity::Create();
	wireEnt = Entity::Create();
	wireEnt2 = Entity::Create();
	wireEnt3 = Entity::Create();
	wireEnt4 = Entity::Create();
	wireEnt5 = Entity::Create();
	wireEnt6 = Entity::Create();
	wireEnt7 = Entity::Create();
	coilEnt = Entity::Create();
	completeEnt = Entity::Create();
	boxEnt = Entity::Create();
	boxEnt2 = Entity::Create();
	boxEnt3 = Entity::Create();
	boxEnt4 = Entity::Create();
	panelEnt = Entity::Create();
	panelEnt2 = Entity::Create();
	panelEnt3 = Entity::Create();
	ventEnt = Entity::Create();
	ventEnt2 = Entity::Create();
	pipeC = Entity::Create();
	pipeC2 = Entity::Create();
	pipeC3 = Entity::Create();
	pipeS = Entity::Create();
	tabletEnt = Entity::Create();
	tabletScreenEnt = Entity::Create();

	FBO = Entity::Create();
	greyscaleEnt = Entity::Create();
	sepiaEnt = Entity::Create();
	colorCorrectEnt = Entity::Create();
	bloomEnt = Entity::Create();
	pauseEnt = Entity::Create();
#pragma endregion

#pragma region Model Manager
	drumstick = ModelManager::FindMesh(drumFile);
	floor = ModelManager::FindMesh(floorFile);
	screen = ModelManager::FindMesh(screenFile);
	leftWall = ModelManager::FindMesh(leftWallFile);
	rightWall = ModelManager::FindMesh(rightWallFile);
	backWall = ModelManager::FindMesh(backWallFile);
	doorM = ModelManager::FindMesh(doorFile);
	buttonM = ModelManager::FindMesh(buttonFile);
	and = ModelManager::FindMesh(gateFile);
	not = ModelManager::FindMesh(notFile);
	wireM1 = ModelManager::FindMesh(wire1File);
	wireM2 = ModelManager::FindMesh(wire2File);
	wireM3 = ModelManager::FindMesh(wire3File);
	wireM4 = ModelManager::FindMesh(wire4File);
	wireM5 = ModelManager::FindMesh(wire5File);
	wireM6 = ModelManager::FindMesh(wire6File);
	wireM7 = ModelManager::FindMesh(wire7File);
	coil = ModelManager::FindMesh(coilFile);
	options = ModelManager::FindMesh(pauseButtonFile);
	exit = ModelManager::FindMesh(pauseButtonFile);
	retry = ModelManager::FindMesh(pauseButtonFile);
	boxMesh = ModelManager::FindMesh(boxFile);
	panelMesh = ModelManager::FindMesh(panelFile);
	ventMesh = ModelManager::FindMesh(ventFile);
	pipeCMesh = ModelManager::FindMesh(pipeCFile);
	pipeSMesh = ModelManager::FindMesh(pipeSFile);
	tablet = ModelManager::FindMesh(tabletFile);

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
#pragma endregion

}

void Level3::InitScene()
{
	Application::SetClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	scene = new entt::registry();

	Entity::SetReg(scene);

	float distance = glm::distance(point2, point1);

	totalTime = distance / speed;

	glm::vec3 lightPos = glm::vec3(0.0f, 9.5f, -45.0f);
	glm::vec3 lightDir = glm::vec3(0.0f, -1.0f, 0.0f);
	glm::vec3 lightCol = glm::vec3(1.f, 1.f, 1.f);
	float     lightAmbientPow = 0.05f;
	float	  pauseAmbientPow = 0.25f;
	float     lightSpecularPow = 1.0f;
	float     lightSpecularPow2 = 0.2f;
	glm::vec3 ambientCol = glm::vec3(1.0f);
	float     ambientPow = 0.1f;
	float     shininess = 16.0f;

#pragma region Shader Stuff

	animShader = Shader::Create();
	animShader->LoadShaderPartFromFile("Shaders/morph_shader.glsl", GL_VERTEX_SHADER);
	animShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	animShader->Link();
	SetShaderValues(animShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, ambientCol, ambientPow, shininess);

	shader = Shader::Create();
	shader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	shader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	shader->Link();
	SetShaderValues(shader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, ambientCol, ambientPow, shininess);

	untexturedShader = Shader::Create();
	untexturedShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	untexturedShader->LoadShaderPartFromFile("Shaders/frag_untextured.glsl", GL_FRAGMENT_SHADER);
	untexturedShader->Link();
	SetShaderValues(untexturedShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, ambientCol, ambientPow, shininess);

	pauseShader = Shader::Create();
	pauseShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	pauseShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	pauseShader->Link();
	SetShaderValues(pauseShader, lightPos, lightDir, lightCol, pauseAmbientPow, lightSpecularPow, ambientCol, pauseAmbientPow, shininess);
#pragma endregion

#pragma region Texture Stuff
	Texture2D::sptr diffuseButton = Texture2D::LoadFromFile("Textures/ButtonTexture.png");
	Texture2D::sptr diffuseDrum = Texture2D::LoadFromFile("Textures/DrumstickTexture.png");
	Texture2D::sptr diffuseDoor = Texture2D::LoadFromFile("Textures/DoorTexture.png");
	Texture2D::sptr diffuseFloor = Texture2D::LoadFromFile("Textures/FloorTilesetFinal.png");
	Texture2D::sptr diffuseWall = Texture2D::LoadFromFile("Textures/WallTileset.png");
	Texture2D::sptr diffuseWire = Texture2D::LoadFromFile("Textures/Wire_Off_Texture.png");
	Texture2D::sptr diffuseWireOn = Texture2D::LoadFromFile("Textures/Wire_On_Texture.png");
	Texture2D::sptr diffuseComplete = Texture2D::LoadFromFile("Textures/LevelComplete.png");
	Texture2D::sptr diffuseAnd = Texture2D::LoadFromFile("Textures/AndGate.png");
	Texture2D::sptr diffuseNot = Texture2D::LoadFromFile("Textures/NotGate.png");
	Texture2D::sptr diffusePause = Texture2D::LoadFromFile("Textures/PauseMenu.png");
	Texture2D::sptr diffuseBox = Texture2D::LoadFromFile("Textures/Box_Texture.png");
	Texture2D::sptr diffusePipeStraight = Texture2D::LoadFromFile("Textures/Pipe_Straight_Texture.png");
	Texture2D::sptr diffusePipeCurved = Texture2D::LoadFromFile("Textures/Pipe_Curved_Texture.png");
	Texture2D::sptr diffuseOptions = Texture2D::LoadFromFile("Textures/Buttons/Default/Option.png");
	Texture2D::sptr diffuseRetry = Texture2D::LoadFromFile("Textures/Buttons/Default/Replay.png");
	Texture2D::sptr diffuseExit = Texture2D::LoadFromFile("Textures/Buttons/Default/Exit.png");
	Texture2D::sptr diffuseCoilOff = Texture2D::LoadFromFile("Textures/Tesla_Coil_Texture_Off.png");
	Texture2D::sptr diffuseCoilOn = Texture2D::LoadFromFile("Textures/Tesla_Coil_Texture_On.png");
	Texture2D::sptr diffusePanel = Texture2D::LoadFromFile("Textures/PanelTexture.png");
	Texture2D::sptr diffuseVent = Texture2D::LoadFromFile("Textures/VentTexture.png");
	Texture2D::sptr diffuseTablet = Texture2D::LoadFromFile("Textures/TabletTexture.png");
	Texture2D::sptr diffuseTabletScreen = Texture2D::LoadFromFile("Textures/NotGateTablet.png");

	Texture2DDescription desc = Texture2DDescription();
	desc.Width = 1;
	desc.Height = 1;
	desc.Format = InternalFormat::RGB8;
	Texture2D::sptr texture2 = Texture2D::Create(desc);
	texture2->Clear();

	buttonMat.Albedo = diffuseButton;
	drumstickMat.Albedo = diffuseDrum;
	doorMat.Albedo = diffuseDoor;
	floorMat.Albedo = diffuseFloor;
	wallMat.Albedo = diffuseWall;
	wireMat.Albedo = diffuseWire;
	wireMatOn.Albedo = diffuseWireOn;
	completeMat.Albedo = diffuseComplete;
	andMat.Albedo = diffuseAnd;
	notMat.Albedo = diffuseNot;
	pauseMat.Albedo = diffusePause;
	boxMat.Albedo = diffuseBox;
	straightPipeMat.Albedo = diffusePipeStraight;
	curvedPipeMat.Albedo = diffusePipeCurved;
	optionMat.Albedo = diffuseOptions;
	retryMat.Albedo = diffuseRetry;
	exitMat.Albedo = diffuseExit;
	coilMatOff.Albedo = diffuseCoilOff;
	coilMatOn.Albedo = diffuseCoilOn;
	panelMat.Albedo = diffusePanel;
	ventMat.Albedo = diffuseVent;
	tabletMat.Albedo = diffuseTablet;
	tabletScreenMat.Albedo = diffuseTabletScreen;
	clearMat.Albedo = texture2;

#pragma endregion

#pragma region Transforms
	//Player transforms
	auto& playerTrans = mainPlayer.Add<Transform>();
	playerTrans.SetPosition(glm::vec3(0.0f, 1.0f, 32.0f));
	playerTrans.SetRotationY(180.0f);

	//Floor transform
	auto& groundTrans = floorEnt.Add<Transform>();
	groundTrans.SetPositionY(1.0f);

	//Wall transforms
	auto& leftTrans = leftEnt.Add<Transform>();
	leftTrans.SetScale(glm::vec3(1.0f, 2.0f, 1.0f));
	auto& rightTrans = rightEnt.Add<Transform>();
	rightTrans.SetScale(glm::vec3(1.0f, 2.0f, 1.0f));
	auto& backTrans = backEnt.Add<Transform>();
	backTrans.SetScale(glm::vec3(1.0f, 2.0f, 1.0f));

	//Door transform
	auto& doorTrans = doorEnt.Add<Transform>();
	doorTrans.SetPosition(glm::vec3(0.0f, -1.0f, -36.0f));
	doorTrans.SetScale(glm::vec3(1.5f));

	//Wire transforms
	auto& wireTrans = wireEnt.Add<Transform>();
	wireTrans.SetPosition(glm::vec3(-1.f, 1.0f, 1.2f));
	
	auto& wireTrans2 = wireEnt2.Add<Transform>();
	wireTrans2.SetPosition(glm::vec3(-1.f, 1.0f, 2.3f));
	
	auto& wireTrans3 = wireEnt3.Add<Transform>();
	wireTrans3.SetPosition(glm::vec3(-1.1f, 1.0f, 1.3f));
	
	auto& wireTrans4 = wireEnt4.Add<Transform>();
	wireTrans4.SetPosition(glm::vec3(-1.f, 1.0f, 1.1f));
	
	auto& wireTrans5 = wireEnt5.Add<Transform>();
	wireTrans5.SetPosition(glm::vec3(-1.f, 1.0f, 1.0f));
	
	auto& wireTrans6 = wireEnt6.Add<Transform>();
	wireTrans6.SetPosition(glm::vec3(-1.f, 1.0f, 1.0f));
	
	auto& wireTrans7 = wireEnt7.Add<Transform>();
	wireTrans7.SetPosition(glm::vec3(-1.f, 1.0f, 0.0f));

	//Gate transforms
	//And Gate
	auto& gateTrans = andEnt.Add<Transform>();
	gateTrans.SetPosition(glm::vec3(-10.4f, 1.0f, 3.6f));
	gateTrans.SetRotationY(-90.0f);
	gateTrans.SetScale(glm::vec3(2.0f));
	
	auto& gateTrans2 = andEnt2.Add<Transform>();
	gateTrans2.SetPosition(glm::vec3(10.9f, 1.0f, 3.6f));
	gateTrans2.SetRotationY(-90.0f);
	gateTrans2.SetScale(glm::vec3(2.0f));
	
	auto& gateTrans3 = andEnt3.Add<Transform>();
	gateTrans3.SetPosition(glm::vec3(0.3f, 1.0f, -5.5f));
	gateTrans3.SetRotationY(-90.0f);
	gateTrans3.SetScale(glm::vec3(2.0f));
	
	//Not Gate
	auto& notTrans = notEnt.Add<Transform>();
	notTrans.SetPosition(glm::vec3(0.0f, 0.5f, 13.0f));
	notTrans.SetRotationY(-90.0f);
	notTrans.SetScale(glm::vec3(2.0f));

	//Button transforms
	auto& buttonTrans = buttonEnt.Add<Transform>();
	buttonTrans.SetPosition(glm::vec3(-12.5f, -1.0f, 27.f));

	auto& buttonTrans2 = buttonEnt2.Add<Transform>();
	buttonTrans2.SetPosition(glm::vec3(0.1f, -1.0f, 28.f));

	auto& buttonTrans3 = buttonEnt3.Add<Transform>();
	buttonTrans3.SetPosition(glm::vec3(12.7f, -1.0f, 27.f));

	//Coil transform
	auto& coilTrans = coilEnt.Add<Transform>();
	coilTrans.SetPosition(glm::vec3(-17.0f, 1.0f, -31.f));
	coilTrans.SetScale(glm::vec3(3.0f));
	coilTrans.SetRotationY(180.0f);

	//Box transforms
	auto& boxTrans = boxEnt.Add<Transform>();
	boxTrans.SetPosition(glm::vec3(22.f, 4.5f, -33.f));

	auto& boxTrans2 = boxEnt2.Add<Transform>();
	boxTrans2.SetPosition(glm::vec3(34.f, 4.5f, 0.f));

	auto& boxTrans3 = boxEnt3.Add<Transform>();
	boxTrans3.SetPosition(glm::vec3(-35.f, 4.5f, 10.f));
	boxTrans3.SetRotationY(90.f);

	auto& boxTrans4 = boxEnt4.Add<Transform>();
	boxTrans4.SetPosition(glm::vec3(-35.f, 4.5f, 20.f));
	boxTrans4.SetRotationY(90.f);

	//Vent transforms
	auto& ventTrans = ventEnt.Add<Transform>();
	ventTrans.SetPosition(glm::vec3(-38.f, 15.f, -22.f));
	ventTrans.SetScale(glm::vec3(0.8f));
	ventTrans.SetRotationY(180.f);

	auto& ventTrans2 = ventEnt2.Add<Transform>();
	ventTrans2.SetPosition(glm::vec3(-38.f, 15.f, 22.f));
	ventTrans2.SetScale(glm::vec3(0.8f));
	ventTrans2.SetRotationY(180.f);

	//Panel transforms
	auto& panelTrans = panelEnt.Add<Transform>();
	panelTrans.SetPosition(glm::vec3(-30.f, 7.0f, -39.f));
	panelTrans.SetScale(glm::vec3(2.0f));
	panelTrans.SetRotationY(-90.0f);

	auto& panelTrans2 = panelEnt2.Add<Transform>();
	panelTrans2.SetPosition(glm::vec3(39.f, 7.0f, 18.f));
	panelTrans2.SetScale(glm::vec3(2.0f));
	panelTrans2.SetRotationY(180.0f);

	auto& panelTrans3 = panelEnt3.Add<Transform>();
	panelTrans3.SetPosition(glm::vec3(39.f, 7.0f, 22.f));
	panelTrans3.SetScale(glm::vec3(2.0f));
	panelTrans3.SetRotationY(180.0f);

	//Pipe transforms
	auto& pipeTrans = pipeC.Add<Transform>();
	pipeTrans.SetPosition(glm::vec3(12.f, 1.f, -33.f));
	pipeTrans.SetRotationY(90.0f);

	auto& pipeTrans2 = pipeC2.Add<Transform>();
	pipeTrans2.SetPosition(glm::vec3(22.2f, 12.5f, -33.f));
	pipeTrans2.SetRotationZ(-90.0f);
	
	auto& pipeTrans3 = pipeC3.Add<Transform>();
	pipeTrans3.SetPosition(glm::vec3(34.f, 1.f, 23.f));
	pipeTrans3.SetRotationY(180.0f);

	auto& pipeTrans4 = pipeS.Add<Transform>();
	pipeTrans4.SetPosition(glm::vec3(34.f, 12.5f, -8.f));

	//Level complete transform
	auto& completeTrans = completeEnt.Add<Transform>();
	completeTrans.SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	completeTrans.SetScale(glm::vec3(0.22f));

	//Pause UI transforms
	auto& pauseTrans = pauseEnt.Add<Transform>();
	pauseTrans.SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	pauseTrans.SetScale(glm::vec3(0.20f, 1.0f, 0.12f));

	auto& optionsTrans = optionEnt.Add<Transform>();
	optionsTrans.SetPosition(glm::vec3(-5.0f, 2.0f, 0.0f));
	optionsTrans.SetScale(glm::vec3(1.5f));
	optionsTrans.SetRotationY(96.0f);

	auto& retryTrans = retryEnt.Add<Transform>();
	retryTrans.SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));
	retryTrans.SetScale(glm::vec3(1.5f));
	retryTrans.SetRotationY(96.0f);

	auto& exitTrans = exitEnt.Add<Transform>();
	exitTrans.SetPosition(glm::vec3(5.0f, 2.0f, 0.0f));
	exitTrans.SetScale(glm::vec3(1.5f));
	exitTrans.SetRotationY(96.0f);

	//Tablet Stuff
	auto& tabletTrans = tabletEnt.Add<Transform>();
	tabletTrans.SetPosition(glm::vec3(0.0f, 5.0f, 5.0f));
	tabletTrans.SetRotationY(180.0f);

	auto& tabletScreenTrans = tabletScreenEnt.Add<Transform>();
	tabletScreenTrans.SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	tabletScreenTrans.SetScale(glm::vec3(0.20f, 1.0f, 0.12f));

#pragma endregion

	//AABB
	auto& leftCol = leftEnt.Add<AABB>(leftEnt, mainPlayer);
	auto& rightCol = rightEnt.Add<AABB>(rightEnt, mainPlayer);
	auto& backCol = backEnt.Add<AABB>(backEnt, mainPlayer);
	auto& gateCol = andEnt.Add<AABB>(andEnt, mainPlayer, 5.0f, 3.0f);
	gateCol.SetIsAmbient(true);
	auto& gateCol2 = andEnt2.Add<AABB>(andEnt2, mainPlayer, 5.0f, 3.0f);
	gateCol2.SetIsAmbient(true);
	auto& gateCol3 = andEnt3.Add<AABB>(andEnt3, mainPlayer, 5.0f, 3.0f);
	gateCol3.SetIsAmbient(true);
	auto& gateCol4 = notEnt.Add<AABB>(notEnt, mainPlayer, 3.0f, 3.0f);
	gateCol4.SetIsAmbient(true);
	auto& coilCol = coilEnt.Add<AABB>(coilEnt, mainPlayer, 4.0f, 4.0f);
	coilCol.SetIsAmbient(true);
	auto& boxCol = boxEnt.Add<AABB>(boxEnt, mainPlayer, 5.0f, 5.0f);
	boxCol.SetIsAmbient(true);
	auto& boxCol2 = boxEnt2.Add<AABB>(boxEnt2, mainPlayer, 5.0f, 5.0f);
	boxCol2.SetIsAmbient(true);
	auto& boxCol3 = boxEnt3.Add<AABB>(boxEnt3, mainPlayer, 5.0f, 5.0f);
	boxCol3.SetIsAmbient(true);
	auto& boxCol4 = boxEnt4.Add<AABB>(boxEnt4, mainPlayer, 5.0f, 5.0f);
	boxCol4.SetIsAmbient(true);
	auto& pipeCol = pipeC.Add<AABB>(pipeC, mainPlayer, 2.5f, 2.5f);
	pipeCol.SetIsAmbient(true);
	auto& pipeCol2 = pipeC2.Add<AABB>(pipeC2, mainPlayer, 2.5f, 2.5f);
	pipeCol2.SetIsAmbient(true);
	auto& pipeCol3 = pipeC3.Add<AABB>(pipeC3, mainPlayer, 2.5f, 2.5f);
	pipeCol3.SetIsAmbient(true);

	auto& doorCol = doorEnt.Add<AABB>(doorEnt, mainPlayer);
	doorCol.SetComplete(false);

	//Buttons
	auto& button = buttonEnt.Add<Lever>(wireEnt);
	button.SetPowered(false);
	auto& button2 = buttonEnt2.Add<Lever>(wireEnt2);
	button2.SetPowered(false);
	auto& button3 = buttonEnt3.Add<Lever>(wireEnt3);
	button3.SetPowered(false);

	//Wires
	auto& wire = wireEnt.Add<Wire>(buttonEnt);
	auto& wire2 = wireEnt2.Add<Wire>(buttonEnt2);
	auto& wire3 = wireEnt3.Add<Wire>(buttonEnt3);
	auto& wire4 = wireEnt4.Add<Wire>(notEnt);
	auto& wire5 = wireEnt5.Add<Wire>(andEnt);
	auto& wire6 = wireEnt6.Add<Wire>(andEnt2);
	auto& wire7 = wireEnt7.Add<Wire>(andEnt3);

	//Gates
	auto& andGate = andEnt.Add<AndGate>(wireEnt, wireEnt4, wireEnt5);
	auto& andGate2 = andEnt2.Add<AndGate>(wireEnt4, wireEnt3, wireEnt6);
	auto& andGate3 = andEnt3.Add<AndGate>(wireEnt5, wireEnt6, doorEnt);
	auto& notGate = notEnt.Add<NotGate>(wireEnt2, wireEnt4);

	//Door
	auto& door = doorEnt.Add<Door>();
	door.SetOpen(false);

#pragma region Animation Frames
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
#pragma endregion


#pragma region Mesh Loading
	auto& playerMesh = mainPlayer.Add<MorphRenderer>(mainPlayer, *drumstick, animShader);
	auto& floorMesh = floorEnt.Add<MeshRenderer>(floorEnt, *floor, shader);
	auto& leftMesh = leftEnt.Add<MeshRenderer>(leftEnt, *leftWall, shader);
	auto& rightMesh = rightEnt.Add<MeshRenderer>(rightEnt, *rightWall, shader);
	auto& backMesh = backEnt.Add<MeshRenderer>(backEnt, *backWall, shader);
	auto& doorMesh = doorEnt.Add<MorphRenderer>(doorEnt, *doorM, animShader);
	auto& buttonMesh = buttonEnt.Add<MeshRenderer>(buttonEnt, *buttonM, shader);
	auto& buttonMesh2 = buttonEnt2.Add<MeshRenderer>(buttonEnt2, *buttonM, shader);
	auto& buttonMesh3 = buttonEnt3.Add<MeshRenderer>(buttonEnt3, *buttonM, shader);
	auto& gateMesh = andEnt.Add<MeshRenderer>(andEnt, *and, shader);
	auto& gateMesh2 = andEnt2.Add<MeshRenderer>(andEnt2, *and, shader);
	auto& gateMesh3 = andEnt3.Add<MeshRenderer>(andEnt3, *and, shader);
	auto& notMesh = notEnt.Add<MeshRenderer>(notEnt, *not, shader);
	auto& wireMesh = wireEnt.Add<MeshRenderer>(wireEnt, *wireM1, shader);
	auto& wireMesh2 = wireEnt2.Add<MeshRenderer>(wireEnt2, *wireM2, shader);
	auto& wireMesh3 = wireEnt3.Add<MeshRenderer>(wireEnt3, *wireM3, shader);
	auto& wireMesh4 = wireEnt4.Add<MeshRenderer>(wireEnt4, *wireM4, shader);
	auto& wireMesh5 = wireEnt5.Add<MeshRenderer>(wireEnt5, *wireM5, shader);
	auto& wireMesh6 = wireEnt6.Add<MeshRenderer>(wireEnt6, *wireM6, shader);
	auto& wireMesh7 = wireEnt7.Add<MeshRenderer>(wireEnt7, *wireM7, shader);
	auto& coilMesh = coilEnt.Add<MeshRenderer>(coilEnt, *coil, shader);
	auto& completeMesh = completeEnt.Add<MeshRenderer>(completeEnt, *screen, shader);
	auto& pauseMesh = pauseEnt.Add<MeshRenderer>(pauseEnt, *screen, pauseShader);
	auto& optionMesh = optionEnt.Add<MeshRenderer>(optionEnt, *options, pauseShader);
	auto& retryMesh = retryEnt.Add<MeshRenderer>(retryEnt, *retry, pauseShader);
	auto& exitMesh = exitEnt.Add<MeshRenderer>(exitEnt, *exit, pauseShader);
	auto& boxM = boxEnt.Add<MeshRenderer>(boxEnt, *boxMesh, shader);
	auto& boxM2 = boxEnt2.Add<MeshRenderer>(boxEnt2, *boxMesh, shader);
	auto& boxM3 = boxEnt3.Add<MeshRenderer>(boxEnt3, *boxMesh, shader);
	auto& boxM4 = boxEnt4.Add<MeshRenderer>(boxEnt4, *boxMesh, shader);
	auto& panel = panelEnt.Add<MeshRenderer>(panelEnt, *panelMesh, shader);
	auto& panel2 = panelEnt2.Add<MeshRenderer>(panelEnt2, *panelMesh, shader);
	auto& panel3 = panelEnt3.Add<MeshRenderer>(panelEnt3, *panelMesh, shader);
	auto& vent = ventEnt.Add<MeshRenderer>(ventEnt, *ventMesh, shader);
	auto& vent2 = ventEnt2.Add<MeshRenderer>(ventEnt2, *ventMesh, shader);
	auto& pipeCM = pipeC.Add<MeshRenderer>(pipeC, *pipeCMesh, shader);
	auto& pipeCM2 = pipeC2.Add<MeshRenderer>(pipeC2, *pipeCMesh, shader);
	auto& pipeCM3 = pipeC3.Add<MeshRenderer>(pipeC3, *pipeCMesh, shader);
	auto& pipeSM = pipeS.Add<MeshRenderer>(pipeS, *pipeSMesh, shader);
	auto& tabletScreenMesh = tabletScreenEnt.Add<MeshRenderer>(tabletScreenEnt, *screen, pauseShader);
	auto& tabletMesh = tabletEnt.Add<MeshRenderer>(tabletEnt, *tablet, shader);

	auto& doorAnimator = doorEnt.Add<MorphAnimation>(doorEnt);
	doorAnimator.SetTime(0.2f);
	doorAnimator.SetFrames(doorFrames);
	doorAnimator.SetLoop(false);

	auto& walkAnimator = mainPlayer.Add<MorphAnimation>(mainPlayer);
	walkAnimator.SetTime(0.05f);
	walkAnimator.SetFrames(walkFrames);
#pragma endregion

	//Camera Objects
	auto& camera = camEnt.Add<Camera>();
	camera.SetPosition(glm::vec3(0, 12, mainPlayer.Get<Transform>().GetPositionZ() + 12)); // Set initial position
	camera.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
	camera.LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camera.SetFovDegrees(90.0f); // Set an initial FOV

	auto& orthoCam = uiCamEnt.Add<Camera>();
	orthoCam.SetPosition(glm::vec3(0, 10, 0)); // Set initial position
	orthoCam.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
	orthoCam.LookAt(glm::vec3(0.0f)); // Look at center of the screen
	orthoCam.SetFovDegrees(90.0f); // Set an initial FOV

#pragma region Post-Effects
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	auto basicEffect = &FBO.Add<PostEffect>();
	basicEffect->Init(width, height);

	effects.push_back(basicEffect);

	auto greyscaleEffect = &greyscaleEnt.Add<Greyscale>();
	greyscaleEffect->Init(width, height);

	effects.push_back(greyscaleEffect);

	auto sepiaEffect = &sepiaEnt.Add<Sepia>();
	sepiaEffect->Init(width, height);

	effects.push_back(sepiaEffect);

	auto bloomEffect = &bloomEnt.Add<Bloom>();
	bloomEffect->Init(width, height);

	effects.push_back(bloomEffect);

	auto colorCorrectEffect = &colorCorrectEnt.Add<ColorCorrect>();
	colorCorrectEffect->Init(width, height);

	effects.push_back(colorCorrectEffect);
#pragma endregion

	//Interpolation Stuff
	points.push_back(glm::vec3(3.0f, 15.0f, 6.0f));
	points.push_back(glm::vec3(-3.0f, 15.0f, 6.0f));
	points.push_back(glm::vec3(-3.0f, 15.0f, 0.0f));
	points.push_back(glm::vec3(3.0f, 15.0f, 0.0f));
	
	segmentTime = 1.0f;
	
	if (points.size() > 0)
		currentPos = points[0];
	
	StartSegment(0);
}

void Level3::Update(float dt)
{
	time += dt;
	animShader->SetUniform("u_Time", time);
	shader->SetUniform("u_Time", time);
	pauseShader->SetUniform("u_Time", time);
	untexturedShader->SetUniform("u_Time", time);

	if (points.size() >= 4)
	{
		t = glm::min(t + dt / segmentTime, 1.0f);
	
		int p1 = currentIndex;
	
		int p0 = currentIndex - 1;
	
		if (p0 < 0)
		{
			p0 = points.size() - 1;
		}
	
		int p2 = currentIndex + 1;
	
		if (p2 >= points.size())
			p2 = 0;
	
		int p3 = p2 + 1;
	
		if (p3 >= points.size())
			p3 = 0;
	
		currentPos = Catmull(points[p0], points[p1], points[p2], points[p3], t);
	
		if (t >= 1.0f)
			StartSegment(currentIndex + 1);
	}

	animShader->SetUniform("u_Position", currentPos);
	shader->SetUniform("u_Position", currentPos);
	pauseShader->SetUniform("u_Position", currentPos);
	untexturedShader->SetUniform("u_Position", currentPos);

#pragma region Transforms
	auto& playerTrans = mainPlayer.Get<Transform>();
	auto& groundTrans = floorEnt.Get<Transform>();
	auto& leftTrans = leftEnt.Get<Transform>();
	auto& rightTrans = rightEnt.Get<Transform>();
	auto& backTrans = backEnt.Get<Transform>();
	auto& doorTrans = doorEnt.Get<Transform>();
	auto& buttonTrans = buttonEnt.Get<Transform>();
	auto& buttonTrans2 = buttonEnt2.Get<Transform>();
	auto& buttonTrans3 = buttonEnt3.Get<Transform>();
	auto& gateTrans = andEnt.Get<Transform>();
	auto& gateTrans2 = andEnt2.Get<Transform>();
	auto& gateTrans3 = andEnt3.Get<Transform>();
	auto& notTrans = notEnt.Get<Transform>();
	auto& wireTrans = wireEnt.Get<Transform>();
	auto& wireTrans2 = wireEnt2.Get<Transform>();
	auto& wireTrans3 = wireEnt3.Get<Transform>();
	auto& wireTrans4 = wireEnt4.Get<Transform>();
	auto& wireTrans5 = wireEnt5.Get<Transform>();
	auto& wireTrans6 = wireEnt6.Get<Transform>();
	auto& wireTrans7 = wireEnt7.Get<Transform>();
	auto& coilTrans = coilEnt.Get<Transform>();
	auto& completeTrans = completeEnt.Get<Transform>();
	auto& pauseTrans = pauseEnt.Get<Transform>();
	auto& optionsTrans = optionEnt.Get<Transform>();
	auto& retryTrans = retryEnt.Get<Transform>();
	auto& exitTrans = exitEnt.Get<Transform>();
	auto& boxTrans = boxEnt.Get<Transform>();
	auto& boxTrans2 = boxEnt2.Get<Transform>();
	auto& boxTrans3 = boxEnt3.Get<Transform>();
	auto& boxTrans4 = boxEnt4.Get<Transform>();
	auto& panelTrans = panelEnt.Get<Transform>();
	auto& panelTrans2 = panelEnt2.Get<Transform>();
	auto& panelTrans3 = panelEnt3.Get<Transform>();
	auto& ventTrans = ventEnt.Get<Transform>();
	auto& ventTrans2 = ventEnt2.Get<Transform>();
	auto& pipeCTrans = pipeC.Get<Transform>();
	auto& pipeCTrans2 = pipeC2.Get<Transform>();
	auto& pipeCTrans3 = pipeC3.Get<Transform>();
	auto& pipeSTrans = pipeS.Get<Transform>();
	auto& tabletTrans = tabletEnt.Get<Transform>();
	auto& tabletScreenTrans = tabletScreenEnt.Get<Transform>();

	backTrans.SetPositionZ(-39.0f);
	backTrans.SetPositionY(9.0f);

	leftTrans.SetPositionX(-39.0f);
	leftTrans.SetRotationY(90.0f);
	leftTrans.SetPositionY(9.0f);

	rightTrans.SetPositionX(39.0f);
	rightTrans.SetRotationY(90.0f);
	rightTrans.SetPositionY(9.0f);

	tabletTrans.SetRotationY(tabletTrans.GetRotation().y + 100 * dt);
#pragma endregion

	auto& camera = camEnt.Get<Camera>();
	auto& orthoCam = uiCamEnt.Get<Camera>();
	//camera.LookAt(glm::vec3(playerTrans.GetPositionX(), playerTrans.GetPositionY() + 5.0f, playerTrans.GetPositionZ()));

	//Get references to the meshes
	auto& meshMain = mainPlayer.Get<MorphRenderer>();
	auto& groundMesh = floorEnt.Get<MeshRenderer>();
	auto& leftMesh = leftEnt.Get<MeshRenderer>();
	auto& rightMesh = rightEnt.Get<MeshRenderer>();
	auto& backMesh = backEnt.Get<MeshRenderer>();
	auto& doorMesh = doorEnt.Get<MorphRenderer>();
	auto& buttonMesh = buttonEnt.Get<MeshRenderer>();
	auto& buttonMesh2 = buttonEnt2.Get<MeshRenderer>();
	auto& buttonMesh3 = buttonEnt3.Get<MeshRenderer>();
	auto& gateMesh = andEnt.Get<MeshRenderer>();
	auto& gateMesh2 = andEnt2.Get<MeshRenderer>();
	auto& gateMesh3 = andEnt3.Get<MeshRenderer>();
	auto& notMesh = notEnt.Get<MeshRenderer>();
	auto& wireMesh = wireEnt.Get<MeshRenderer>();
	auto& wireMesh2 = wireEnt2.Get<MeshRenderer>();
	auto& wireMesh3 = wireEnt3.Get<MeshRenderer>();
	auto& wireMesh4 = wireEnt4.Get<MeshRenderer>();
	auto& wireMesh5 = wireEnt5.Get<MeshRenderer>();
	auto& wireMesh6 = wireEnt6.Get<MeshRenderer>();
	auto& wireMesh7 = wireEnt7.Get<MeshRenderer>();
	auto& coilMesh = coilEnt.Get<MeshRenderer>();
	auto& completeMesh = completeEnt.Get<MeshRenderer>();
	auto& pauseMesh = pauseEnt.Get<MeshRenderer>();
	auto& optionMesh = optionEnt.Get<MeshRenderer>();
	auto& retryMesh = retryEnt.Get<MeshRenderer>();
	auto& exitMesh = exitEnt.Get<MeshRenderer>();
	auto& boxM = boxEnt.Get<MeshRenderer>();
	auto& boxM2 = boxEnt2.Get<MeshRenderer>();
	auto& boxM3 = boxEnt3.Get<MeshRenderer>();
	auto& boxM4 = boxEnt4.Get<MeshRenderer>();
	auto& panel = panelEnt.Get<MeshRenderer>();
	auto& panel2 = panelEnt2.Get<MeshRenderer>();
	auto& panel3 = panelEnt3.Get<MeshRenderer>();
	auto& vent = ventEnt.Get<MeshRenderer>();
	auto& vent2 = ventEnt2.Get<MeshRenderer>();
	auto& pipeCM = pipeC.Get<MeshRenderer>();
	auto& pipeCM2 = pipeC2.Get<MeshRenderer>();
	auto& pipeCM3 = pipeC3.Get<MeshRenderer>();
	auto& pipeSM = pipeS.Get<MeshRenderer>();
	auto& tabletMesh = tabletEnt.Get<MeshRenderer>();
	auto& tabletScreenMesh = tabletScreenEnt.Get<MeshRenderer>();

	//Get reference to the model matrix
	glm::mat4 transform = playerTrans.GetModelMatrix();
	glm::mat4 transformGround = groundTrans.GetModelMatrix();
	glm::mat4 transformLeft = leftTrans.GetModelMatrix();
	glm::mat4 transformRight = rightTrans.GetModelMatrix();
	glm::mat4 transformBack = backTrans.GetModelMatrix();
	glm::mat4 transformDoor = doorTrans.GetModelMatrix();
	glm::mat4 transformButton = buttonTrans.GetModelMatrix();
	glm::mat4 transformButton2 = buttonTrans2.GetModelMatrix();
	glm::mat4 transformButton3 = buttonTrans3.GetModelMatrix();
	glm::mat4 transformGate = gateTrans.GetModelMatrix();
	glm::mat4 transformGate2 = gateTrans2.GetModelMatrix();
	glm::mat4 transformGate3 = gateTrans3.GetModelMatrix();
	glm::mat4 transformNot = notTrans.GetModelMatrix();
	glm::mat4 transformWire = wireTrans.GetModelMatrix();
	glm::mat4 transformWire2 = wireTrans2.GetModelMatrix();
	glm::mat4 transformWire3 = wireTrans3.GetModelMatrix();
	glm::mat4 transformWire4 = wireTrans4.GetModelMatrix();
	glm::mat4 transformWire5 = wireTrans5.GetModelMatrix();
	glm::mat4 transformWire6 = wireTrans6.GetModelMatrix();
	glm::mat4 transformWire7 = wireTrans7.GetModelMatrix();
	glm::mat4 transformCoil = coilTrans.GetModelMatrix();
	glm::mat4 transformComplete = completeTrans.GetModelMatrix();
	glm::mat4 transformOptions = optionsTrans.GetModelMatrix();
	glm::mat4 transformRetry = retryTrans.GetModelMatrix();
	glm::mat4 transformExit = exitTrans.GetModelMatrix();
	glm::mat4 transformPause = pauseTrans.GetModelMatrix();
	glm::mat4 transformBox = boxTrans.GetModelMatrix();
	glm::mat4 transformBox2 = boxTrans2.GetModelMatrix();
	glm::mat4 transformBox3 = boxTrans3.GetModelMatrix();
	glm::mat4 transformBox4 = boxTrans4.GetModelMatrix();
	glm::mat4 transformPanel = panelTrans.GetModelMatrix();
	glm::mat4 transformPanel2 = panelTrans2.GetModelMatrix();
	glm::mat4 transformPanel3 = panelTrans3.GetModelMatrix();
	glm::mat4 transformVent = ventTrans.GetModelMatrix();
	glm::mat4 transformVent2 = ventTrans2.GetModelMatrix();
	glm::mat4 transformPipeC = pipeCTrans.GetModelMatrix();
	glm::mat4 transformPipeC2 = pipeCTrans2.GetModelMatrix();
	glm::mat4 transformPipeC3 = pipeCTrans3.GetModelMatrix();
	glm::mat4 transformPipeS = pipeSTrans.GetModelMatrix();
	glm::mat4 transformTablet = tabletTrans.GetModelMatrix();
	glm::mat4 transformTabletScreen = tabletScreenTrans.GetModelMatrix();

	if (playerTrans.GetPositionX() - buttonTrans.GetPositionX() < 2.0f && playerTrans.GetPositionX() - buttonTrans.GetPositionX() > -2.0f
		&& playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() > -3.0f)
		button1Watch.Poll(window);
	
	if (playerTrans.GetPositionX() - buttonTrans2.GetPositionX() < 2.0f && playerTrans.GetPositionX() - buttonTrans2.GetPositionX() > -2.0f
		&& playerTrans.GetPositionZ() - buttonTrans2.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans2.GetPositionZ() > -3.0f)
		button2Watch.Poll(window);
	
	if (playerTrans.GetPositionX() - buttonTrans3.GetPositionX() < 2.0f && playerTrans.GetPositionX() - buttonTrans3.GetPositionX() > -2.0f
		&& playerTrans.GetPositionZ() - buttonTrans3.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans3.GetPositionZ() > -3.0f)
		button3Watch.Poll(window);

	if ((playerTrans.GetPositionX() > -3.0f && playerTrans.GetPositionX() < 3.0f
		&& playerTrans.GetPositionZ() > 2.0f && playerTrans.GetPositionZ() < 8.0f
		&& !tabletOpen) || tabletOpen)
		tabletWatch.Poll(window);

	pauseWatch.Poll(window);

	if (showLevelComplete)
	{
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			levelComplete = true;
			lightNum = 5;
		}
	}

#pragma region PlayerMovement
	if (!showLevelComplete && !isPaused)
	{
		Input::MovePlayer(window, mainPlayer, camEnt, dt, camFar, camClose, camLeft, camRight);
	}
#pragma endregion

#pragma region CameraMovement

	if (camera.GetPosition().z - playerTrans.GetPositionZ() < 10.0f)
		camClose = true;
	else
		camClose = false;

	if (camera.GetPosition().z - playerTrans.GetPositionZ() > 12.5f)
		camFar = true;
	else
		camFar = false;

	if (camera.GetPosition().x - playerTrans.GetPositionX() < -1.0f)
		camLeft = true;
	else
		camLeft = false;

	if (camera.GetPosition().x - playerTrans.GetPositionX() > 1.0f)
		camRight = true;
	else
		camRight = false;

	if (!showLevelComplete && !isPaused)
	{
		Input::MoveCamera(window, camEnt, dt);
	}
#pragma endregion

	lightNum = Input::ChangeLighting(window, lightNum);

	if (lightNum < 1 || lightNum > 5)
		lightNum = 1;

	animShader->SetUniform("u_LightNum", lightNum);
	untexturedShader->SetUniform("u_LightNum", lightNum);
	shader->SetUniform("u_LightNum", lightNum);
	pauseShader->SetUniform("u_LightNum", lightNum);

	//Post-Effect stuff
	auto basicEffect = &FBO.Get<PostEffect>();

	basicEffect->Clear();

	for (int i = 0; i < effects.size(); i++)
	{
		effects[i]->Clear();
	}

	basicEffect->BindBuffer(0);

#pragma region Renders

	if (isTextured)
	{
		//Bind and render the player and door using the animation shader
		if (!showLevelComplete)
		{
			animShader->Bind();
			animShader->SetUniform("s_Diffuse", 0);
			drumstickMat.Albedo->Bind(0);
			meshMain.Render(camera, transform);

			animShader->SetUniform("s_Diffuse", 1);
			doorMat.Albedo->Bind(1);
			doorMesh.Render(camera, transformDoor);
			doorMat.Albedo->Unbind(1);

			//Bind and render the pause UI using the pause shader
			pauseShader->Bind();
			pauseShader->SetUniform("s_Diffuse", 0);
			pauseMat.Albedo->Bind(0);

			if (isPaused)
			{
				pauseMesh.Render(orthoCam, transformPause);
			}

			pauseShader->SetUniform("s_Diffuse", 1);
			optionMat.Albedo->Bind(1);

			if (isPaused)
			{
				optionMesh.Render(orthoCam, transformOptions);
			}

			pauseShader->SetUniform("s_Diffuse", 2);
			retryMat.Albedo->Bind(2);

			if (isPaused)
			{
				retryMesh.Render(orthoCam, transformRetry);
			}

			pauseShader->SetUniform("s_Diffuse", 2);
			exitMat.Albedo->Bind(2);

			if (isPaused)
			{
				exitMesh.Render(orthoCam, transformExit);
			}

			pauseShader->SetUniform("s_Diffuse", 3);
			tabletScreenMat.Albedo->Bind(3);

			if (tabletOpen)
			{
				tabletScreenMesh.Render(orthoCam, transformTabletScreen);
			}

			//Bind and render the objects using the basic shader
			shader->Bind();

			//Floor
			shader->SetUniform("s_Diffuse", 0);
			floorMat.Albedo->Bind(0);
			groundMesh.Render(camera, transformGround);

			//Walls
			shader->SetUniform("s_Diffuse", 1);
			wallMat.Albedo->Bind(1);
			leftMesh.Render(camera, transformLeft);
			rightMesh.Render(camera, transformRight);
			backMesh.Render(camera, transformBack);

			//Buttons
			shader->SetUniform("s_Diffuse", 2);
			buttonMat.Albedo->Bind(2);
			buttonMesh.Render(camera, transformButton);
			buttonMesh2.Render(camera, transformButton2);
			buttonMesh3.Render(camera, transformButton3);

			//Gates
			//And-Gate
			shader->SetUniform("s_Diffuse", 3);
			andMat.Albedo->Bind(3);
			gateMesh.Render(camera, transformGate);
			gateMesh2.Render(camera, transformGate2);
			gateMesh3.Render(camera, transformGate3);
			
			//Not-Gate
			shader->SetUniform("s_Diffuse", 4);
			notMat.Albedo->Bind(4);
			notMesh.Render(camera, transformNot);

			//Wires
			shader->SetUniform("s_Diffuse", 5);

			if (wireEnt.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(5);
				wireMesh.Render(camera, transformWire);
			}
			else
			{
				wireMat.Albedo->Bind(5);
				wireMesh.Render(camera, transformWire);
			}

			if (wireEnt2.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(5);
				wireMesh2.Render(camera, transformWire2);
			}
			else
			{
				wireMat.Albedo->Bind(5);
				wireMesh2.Render(camera, transformWire2);
			}

			if (wireEnt3.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(5);
				wireMesh3.Render(camera, transformWire3);
			}
			else
			{
				wireMat.Albedo->Bind(5);
				wireMesh3.Render(camera, transformWire3);
			}

			if (wireEnt4.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(5);
				wireMesh4.Render(camera, transformWire4);
			}
			else
			{
				wireMat.Albedo->Bind(5);
				wireMesh4.Render(camera, transformWire4);
			}

			if (wireEnt4.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(5);
				wireMesh4.Render(camera, transformWire4);
			}
			else
			{
				wireMat.Albedo->Bind(5);
				wireMesh4.Render(camera, transformWire4);
			}

			if (wireEnt5.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(5);
				wireMesh5.Render(camera, transformWire5);
			}
			else
			{
				wireMat.Albedo->Bind(5);
				wireMesh5.Render(camera, transformWire5);
			}

			if (wireEnt6.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(5);
				wireMesh6.Render(camera, transformWire6);
			}
			else
			{
				wireMat.Albedo->Bind(5);
				wireMesh6.Render(camera, transformWire6);
			}

			if (wireEnt7.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(5);
				wireMesh7.Render(camera, transformWire7);
			}
			else
			{
				wireMat.Albedo->Bind(5);
				wireMesh7.Render(camera, transformWire7);
			}

			//Tesla Coil
			shader->SetUniform("s_Diffuse", 6);

			if (!doorEnt.Get<Door>().GetOpen())
			{
				coilMatOff.Albedo->Bind(6);
				coilMesh.Render(camera, transformCoil);
			}
			else
			{
				coilMatOn.Albedo->Bind(6);
				coilMesh.Render(camera, transformCoil);
			}

			//Boxes
			shader->SetUniform("s_Diffuse", 7);
			boxMat.Albedo->Bind(7);
			boxM.Render(camera, transformBox);
			boxM2.Render(camera, transformBox2);
			boxM3.Render(camera, transformBox3);
			boxM4.Render(camera, transformBox4);
			
			//Vents
			shader->SetUniform("s_Diffuse", 8);
			ventMat.Albedo->Bind(8);
			vent.Render(camera, transformVent);
			vent2.Render(camera, transformVent2);

			//Panels
			shader->SetUniform("s_Diffuse", 9);
			panelMat.Albedo->Bind(9);
			panel.Render(camera, transformPanel);
			panel2.Render(camera, transformPanel2);
			panel3.Render(camera, transformPanel3);

			//Pipes
			//Curved Pipe
			shader->SetUniform("s_Diffuse", 10);
			curvedPipeMat.Albedo->Bind(10);
			pipeCM.Render(camera, transformPipeC);
			pipeCM2.Render(camera, transformPipeC2);
			pipeCM3.Render(camera, transformPipeC3);

			//Straight Pipe
			shader->SetUniform("s_Diffuse", 11);
			straightPipeMat.Albedo->Bind(11);
			pipeSM.Render(camera, transformPipeS);

			shader->SetUniform("s_Diffuse", 12);
			tabletMat.Albedo->Bind(12);
			tabletMesh.Render(camera, transformTablet);

			//Bind and render the objects with no textures
			//untexturedShader->Bind();
		}
	}
	else
	{
		if (!showLevelComplete)
		{
			animShader->Bind();
			animShader->SetUniform("s_Diffuse", 0);
			clearMat.Albedo->Bind(0);
			meshMain.Render(camera, transform);

			animShader->SetUniform("s_Diffuse", 1);
			clearMat.Albedo->Bind(1);
			doorMesh.Render(camera, transformDoor);
			clearMat.Albedo->Unbind(1);

			pauseShader->Bind();
			pauseShader->SetUniform("s_Diffuse", 0);
			pauseMat.Albedo->Bind(0);

			if (isPaused)
			{
				pauseMesh.Render(orthoCam, transformPause);
			}

			shader->Bind();
			shader->SetUniform("s_Diffuse", 0);
			clearMat.Albedo->Bind(0);
			groundMesh.Render(camera, transformGround);		
			leftMesh.Render(camera, transformLeft);
			rightMesh.Render(camera, transformRight);
			backMesh.Render(camera, transformBack);
			buttonMesh.Render(camera, transformButton);
			buttonMesh2.Render(camera, transformButton2);
			buttonMesh3.Render(camera, transformButton3);
			gateMesh.Render(camera, transformGate);
			gateMesh2.Render(camera, transformGate2);
			gateMesh3.Render(camera, transformGate3);
			notMesh.Render(camera, transformNot);
			wireMesh.Render(camera, transformWire);
			wireMesh2.Render(camera, transformWire2);
			wireMesh3.Render(camera, transformWire3);
			wireMesh4.Render(camera, transformWire4);
			wireMesh5.Render(camera, transformWire5);
			wireMesh6.Render(camera, transformWire6);
			wireMesh7.Render(camera, transformWire7);
			coilMesh.Render(camera, transformCoil);
			boxM.Render(camera, transformBox);
			boxM2.Render(camera, transformBox2);
			boxM3.Render(camera, transformBox3);
			boxM4.Render(camera, transformBox4);
			vent.Render(camera, transformVent);
			vent2.Render(camera, transformVent2);
			panel.Render(camera, transformPanel);
			panel2.Render(camera, transformPanel2);
			panel3.Render(camera, transformPanel3);
			pipeCM.Render(camera, transformPipeC);
			pipeCM2.Render(camera, transformPipeC2);
			pipeCM3.Render(camera, transformPipeC3);
			pipeSM.Render(camera, transformPipeS);
			tabletMesh.Render(camera, transformTablet);

			//untexturedShader->Bind();	
		}
	}

	if (showLevelComplete)
	{
		lightNum = 1;
		shader->Bind();
		shader->SetUniform("s_Diffuse", 0);
		completeMat.Albedo->Bind(0);
		completeMesh.Render(orthoCam, transformComplete);
	}
#pragma endregion

	basicEffect->UnbindBuffer();

	effects[activeEffect]->ApplyEffect(basicEffect);

	effects[activeEffect]->DrawToScreen();

	//Update the collisions
	leftEnt.Get<AABB>().Update();
	rightEnt.Get<AABB>().Update();
	backEnt.Get<AABB>().Update();
	doorEnt.Get<AABB>().Update();
	andEnt.Get<AABB>().Update();
	andEnt2.Get<AABB>().Update();
	andEnt3.Get<AABB>().Update();
	notEnt.Get<AABB>().Update();
	boxEnt.Get<AABB>().Update();
	boxEnt2.Get<AABB>().Update();
	boxEnt3.Get<AABB>().Update();
	boxEnt4.Get<AABB>().Update();
	pipeC.Get<AABB>().Update();
	pipeC2.Get<AABB>().Update();
	pipeC3.Get<AABB>().Update();
	andEnt.Get<AndGate>().Update();
	andEnt2.Get<AndGate>().Update();
	andEnt3.Get<AndGate>().Update();
	notEnt.Get<NotGate>().Update();
	buttonEnt.Get<Lever>().Update();
	buttonEnt2.Get<Lever>().Update();
	buttonEnt3.Get<Lever>().Update();
	wireEnt.Get<Wire>().Update();
	wireEnt2.Get<Wire>().Update();
	wireEnt3.Get<Wire>().Update();
	wireEnt4.Get<Wire>().Update();
	wireEnt5.Get<Wire>().Update();
	wireEnt6.Get<Wire>().Update();
	wireEnt7.Get<Wire>().Update();
	coilEnt.Get<AABB>().Update();
	
	//Door Logic
	if (doorEnt.Get<Door>().GetOpen())
		doorEnt.Get<MorphAnimation>().Update(dt);

	if (doorEnt.Get<AABB>().GetComplete())
		showLevelComplete = true;
}

void Level3::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}

glm::vec3 Level3::Catmull(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float t)
{
	return 0.5f * (2.0f * p1 + t * (-p0 + p2)
		+ t * t * (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3)
		+ t * t * t * (-p0 + 3.0f * p1 - 3.0f * p2 + p3));
}

void Level3::StartSegment(int startInd)
{
	currentIndex = startInd;

	if (currentIndex >= points.size())
		currentIndex = 0;

	t = 0.0f;
}