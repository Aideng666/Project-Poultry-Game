#include "Level1.h"
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

Level1::Level1(std::string sceneName, GLFWwindow* wind)
	: Scene(sceneName, wind)
{

#pragma region Entities
	mainPlayer = Entity::Create();
	floorEnt = Entity::Create();
	leftEnt = Entity::Create();
	rightEnt = Entity::Create();
	backEnt = Entity::Create();
	doorEnt = Entity::Create();
	doorCloseEnt = Entity::Create();
	completeEnt = Entity::Create();
	pauseEnt = Entity::Create();
	optionEnt = Entity::Create();
	exitEnt = Entity::Create();
	retryEnt = Entity::Create();
	andEnt = Entity::Create();
	buttonEnt = Entity::Create();
	buttonEnt2 = Entity::Create();
	wireEnt = Entity::Create();
	wireEnt2 = Entity::Create();
	wireEnt3 = Entity::Create();
	coilEnt = Entity::Create();
	boxEnt = Entity::Create();
	boxEnt2 = Entity::Create();
	boxEnt3 = Entity::Create();
	boxEnt4 = Entity::Create();
	boxEnt5 = Entity::Create();
	panelEnt = Entity::Create();
	panelEnt2 = Entity::Create();
	bigVentEnt = Entity::Create();
	smallVentEnt = Entity::Create();
	smallVentEnt2 = Entity::Create();
	pipeEntS = Entity::Create();
	pipeEntC = Entity::Create();
	tabletEnt = Entity::Create();
	tabletScreenEnt = Entity::Create();
	tutEnt = Entity::Create();
	//particleEnt = Entity::Create();

	FBO = Entity::Create();
	greyscaleEnt = Entity::Create();
	sepiaEnt = Entity::Create();
	colorCorrectEnt = Entity::Create();
	bloomEnt = Entity::Create();
#pragma endregion

#pragma region Model Manager
	drumstick = ModelManager::FindMesh(drumFile);
	floor = ModelManager::FindMesh(floorFile);
	wall = ModelManager::FindMesh(wallFile);
	doorM = ModelManager::FindMesh(doorFile);
	doorCloseM = ModelManager::FindMesh(doorFile10);
	options = ModelManager::FindMesh(pauseButtonFile);
	exit = ModelManager::FindMesh(pauseButtonFile);
	retry = ModelManager::FindMesh(pauseButtonFile);
	gate = ModelManager::FindMesh(gateFile);
	buttonM = ModelManager::FindMesh(buttonFile);
	wireL = ModelManager::FindMesh(wire1File);
	wireR = ModelManager::FindMesh(wire2File);
	wireC = ModelManager::FindMesh(wire3File);
	coil = ModelManager::FindMesh(coilFile, glm::vec3(1.0f, 0.0f, 0.0f));
	boxM = ModelManager::FindMesh(boxFile);
	panel = ModelManager::FindMesh(panelFile);
	ventB = ModelManager::FindMesh(ventFileB);
	ventS = ModelManager::FindMesh(ventFileS);
	pipeS = ModelManager::FindMesh(pipesFileS);
	pipeC = ModelManager::FindMesh(pipesFileC);
	tablet = ModelManager::FindMesh(tabletFile);
	tut = ModelManager::FindMesh(tutFile, glm::vec3(1.0f, 0.0f, 0.0f));

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

void Level1::InitScene()
{
	Application::SetClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	scene = new entt::registry();

	Entity::SetReg(scene);

	float distance = glm::distance(point2, point1);

	totalTime = distance / speed;

#pragma region Shader Stuff
	glm::vec3 lightPos = glm::vec3(0.0f, 9.5f, -35.0f);
	glm::vec3 lightDir = glm::vec3(0.0f, -1.0f, 0.0f);
	glm::vec3 lightCol = glm::vec3(1.f);
	float     lightAmbientPow = 0.05f;
	float	  pauseAmbientPow = 0.25f;
	float     lightSpecularPow = 1.0f;
	glm::vec3 ambientCol = glm::vec3(1.0f);
	float     ambientPow = 0.1f;
	float     shininess = 16.0f;

	//Basic shader
	shader = Shader::Create();
	shader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	shader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	shader->Link();
	SetShaderValues(shader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, ambientCol, ambientPow, shininess);

	//For any objects with animations
	animShader = Shader::Create();
	animShader->LoadShaderPartFromFile("Shaders/morph_shader.glsl", GL_VERTEX_SHADER);
	animShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	animShader->Link();
	SetShaderValues(animShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, ambientCol, ambientPow, shininess);

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
	SetShaderValues(untexturedShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, ambientCol, ambientPow, shininess);

	//Pause UI Shader
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
	Texture2D::sptr diffuseFloor = Texture2D::LoadFromFile("Textures/FloorTexture.jpg");
	Texture2D::sptr diffuseWall = Texture2D::LoadFromFile("Textures/WallTexture.jpg");
	Texture2D::sptr diffuseComplete = Texture2D::LoadFromFile("Textures/LevelComplete.png");
	Texture2D::sptr diffuseAnd = Texture2D::LoadFromFile("Textures/AndGate.png");
	Texture2D::sptr diffuseWire = Texture2D::LoadFromFile("Textures/Wire_Off_Texture.png");
	Texture2D::sptr diffuseWireOn = Texture2D::LoadFromFile("Textures/Wire_On_Texture.png");
	Texture2D::sptr diffuseBox = Texture2D::LoadFromFile("Textures/Box_Texture.png");
	Texture2D::sptr diffusePanel = Texture2D::LoadFromFile("Textures/PanelTexture.png");
	Texture2D::sptr diffuseVent = Texture2D::LoadFromFile("Textures/VentTexture.png");
	Texture2D::sptr diffusePipeStraight = Texture2D::LoadFromFile("Textures/Pipe_Straight_Texture.png");
	Texture2D::sptr diffusePipeCurved = Texture2D::LoadFromFile("Textures/Pipe_Curved_Texture.png");
	Texture2D::sptr diffusePause = Texture2D::LoadFromFile("Textures/PauseMenu.png");
	Texture2D::sptr diffuseOptions = Texture2D::LoadFromFile("Textures/Buttons/Default/Option.png");
	Texture2D::sptr diffuseRetry = Texture2D::LoadFromFile("Textures/Buttons/Default/Replay.png");
	Texture2D::sptr diffuseExit = Texture2D::LoadFromFile("Textures/Buttons/Default/Exit.png");
	Texture2D::sptr diffuseTablet = Texture2D::LoadFromFile("Textures/TabletTexture.png");
	Texture2D::sptr diffuseTabletScreen = Texture2D::LoadFromFile("Textures/AndGateTablet.png");

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
	completeMat.Albedo = diffuseComplete;
	gateMat.Albedo = diffuseAnd;
	wireMat.Albedo = diffuseWire;
	wirePowerMat.Albedo = diffuseWireOn;
	boxMat.Albedo = diffuseBox;
	panelMat.Albedo = diffusePanel;
	ventMat.Albedo = diffuseVent;
	straightPipeMat.Albedo = diffusePipeStraight;
	curvedPipeMat.Albedo = diffusePipeCurved;
	pauseMat.Albedo = diffusePause;
	optionMat.Albedo = diffuseOptions;
	retryMat.Albedo = diffuseRetry;
	exitMat.Albedo = diffuseExit;
	tabletMat.Albedo = diffuseTablet;
	tabletScreenMat.Albedo = diffuseTabletScreen;
	clearMat.Albedo = texture2;
#pragma endregion

#pragma region Transforms
	//Particle transform
	//auto& particleTrans = particleEnt.Add<Transform>();
	//particleTrans.SetPosition(glm::vec3(0.0f, 4.0f, -2.0f));

	//Player transform
	auto& playerTrans = mainPlayer.Add<Transform>();
	playerTrans.SetPosition(glm::vec3(0.0f, 1.0f, 30.0f));
	playerTrans.SetRotationY(180.0f);

	//Floor transform
	auto& groundTrans = floorEnt.Add<Transform>();

	//Wall transforms
	auto& leftTrans = leftEnt.Add<Transform>();
	auto& rightTrans = rightEnt.Add<Transform>();
	auto& backTrans = backEnt.Add<Transform>();

	//Door transforms
	auto& doorTrans = doorEnt.Add<Transform>();
	doorTrans.SetPosition(glm::vec3(0.0f, -1.0f, -36.0f));
	doorTrans.SetScale(glm::vec3(1.5f));

	auto& doorCloseTrans = doorCloseEnt.Add<Transform>();
	doorCloseTrans.SetPosition(glm::vec3(0.0f, -1.0f, -36.0f));
	doorCloseTrans.SetScale(glm::vec3(1.5f));

	//Button transforms
	auto& buttonTrans = buttonEnt.Add<Transform>();
	buttonTrans.SetPosition(glm::vec3(-11.0f, -1.0f, 23.0f));
	buttonTrans.SetRotationY(90.0f);

	auto& buttonTrans2 = buttonEnt2.Add<Transform>();
	buttonTrans2.SetPosition(glm::vec3(10.5f, -1.0f, 23.0f));
	buttonTrans2.SetRotationY(90.0f);

	//Wire transforms
	auto& wireTrans = wireEnt.Add<Transform>();
	wireTrans.SetPosition(glm::vec3(-0.2f, 1.0f, -2.2f));

	auto& wireTrans2 = wireEnt2.Add<Transform>();
	wireTrans2.SetPosition(glm::vec3(-0.2f, 1.0f, -2.2f));

	auto& wireTrans3 = wireEnt3.Add<Transform>();
	wireTrans3.SetPosition(glm::vec3(0.f, 1.0f, -2.2f));

	//Gate transform
	auto& gateTrans = andEnt.Add<Transform>();
	gateTrans.SetPosition(glm::vec3(0.0f, 1.0f, -2.0f));
	gateTrans.SetRotationY(-90.0f);
	gateTrans.SetScale(glm::vec3(2.0f));

	//Coil transform
	auto& coilTrans = coilEnt.Add<Transform>();
	coilTrans.SetPosition(glm::vec3(-18.2f, 1.0f, -32.7f));
	coilTrans.SetScale(glm::vec3(3.0f));
	coilTrans.SetRotationY(180.0f);

	//Box transform
	auto& boxTrans = boxEnt.Add<Transform>();
	boxTrans.SetPosition(glm::vec3(-34.f, 4.5f, -33.f));

	auto& boxTrans2 = boxEnt2.Add<Transform>();
	boxTrans2.SetPosition(glm::vec3(19.f, 4.5f, -33.f));

	auto& boxTrans3 = boxEnt3.Add<Transform>();
	boxTrans3.SetPosition(glm::vec3(34.f, 4.5f, -9.f));

	auto& boxTrans4 = boxEnt4.Add<Transform>();
	boxTrans4.SetPosition(glm::vec3(34.f, 4.5f, -3.f));

	auto& boxTrans5 = boxEnt5.Add<Transform>();
	boxTrans5.SetPosition(glm::vec3(34.f, 10.5f, -4.f));
	boxTrans5.SetScale(glm::vec3(0.684f));

	//Panel transform
	auto& panelTrans = panelEnt.Add<Transform>();
	panelTrans.SetPosition(glm::vec3(38.f, 7.0f, 6.f));
	panelTrans.SetScale(glm::vec3(2.0f));
	panelTrans.SetRotationY(180.0f);

	auto& panelTrans2 = panelEnt2.Add<Transform>();
	panelTrans2.SetPosition(glm::vec3(38.f, 7.0f, 10.f));
	panelTrans2.SetScale(glm::vec3(2.0f));
	panelTrans2.SetRotationY(180.0f);

	//Vent transform
	auto& ventTrans = bigVentEnt.Add<Transform>();
	ventTrans.SetPosition(glm::vec3(37.f, 12.0f, 22.0f));
	ventTrans.SetScale(glm::vec3(0.8f));

	auto& ventTrans2 = smallVentEnt.Add<Transform>();
	ventTrans2.SetPosition(glm::vec3(-37.f, 16.0f, -17.f));

	auto& ventTrans3 = smallVentEnt2.Add<Transform>();
	ventTrans3.SetPosition(glm::vec3(-37.f, 16.0f, 6.f));

	//Pipe transforms
	auto& pipeTrans = pipeEntS.Add<Transform>();
	pipeTrans.SetPosition(glm::vec3(-33.5f, 12.5f, -23.f));

	auto& pipeTrans2 = pipeEntC.Add<Transform>();
	pipeTrans2.SetPosition(glm::vec3(-33.5f, 1.f, 8.5f));
	pipeTrans2.SetRotationY(180.0f);

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

	auto& tabletTrans = tabletEnt.Add<Transform>();
	tabletTrans.SetPosition(glm::vec3(0.0f, 5.0f, 10.0f));
	//tabletTrans.SetRotationX(90.0f);
	tabletTrans.SetRotationY(180.0f);

	auto& tabletScreenTrans = tabletScreenEnt.Add<Transform>();
	tabletScreenTrans.SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	tabletScreenTrans.SetScale(glm::vec3(0.20f, 1.0f, 0.12f));

	//Interact text transform
	auto& tutTrans = tutEnt.Add<Transform>();
	tutTrans.SetPosition(glm::vec3(1.0f, 2.0f, 5.0f));
	tutTrans.SetScale(glm::vec3(1.0f));

#pragma endregion

	//AABB
	auto& leftCol = leftEnt.Add<AABB>(leftEnt, mainPlayer);
	auto& rightCol = rightEnt.Add<AABB>(rightEnt, mainPlayer);
	auto& backCol = backEnt.Add<AABB>(backEnt, mainPlayer);
	auto& gateCol = andEnt.Add<AABB>(andEnt, mainPlayer, 5.0f, 3.0f);
	gateCol.SetIsAmbient(true);
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
	auto& boxCol5 = boxEnt5.Add<AABB>(boxEnt5, mainPlayer, 5.0f, 5.0f);
	boxCol5.SetIsAmbient(true);

	auto& doorCol = doorEnt.Add<AABB>(doorEnt, mainPlayer);
	doorCol.SetComplete(false);

	//Buttons
	auto& button = buttonEnt.Add<Lever>(wireEnt);
	button.SetPowered(false);
	auto& button2 = buttonEnt2.Add<Lever>(wireEnt2);
	button2.SetPowered(false);

	//Wires
	auto& wire = wireEnt.Add<Wire>(buttonEnt);
	auto& wire2 = wireEnt2.Add<Wire>(buttonEnt2);
	auto& wire3 = wireEnt3.Add<Wire>(andEnt);

	//Gates
	auto& andGate = andEnt.Add<AndGate>(wireEnt, wireEnt2, doorEnt);

	//Door
	auto& door = doorEnt.Add<Door>();
	door.SetOpen(false);

	//Particle
	//auto& particleSystem = particleEnt.Add<ParticleSystem>(particleEnt, particleData);

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
#pragma endregion

#pragma region Mesh Loading 
	auto& playerMesh = mainPlayer.Add<MorphRenderer>(mainPlayer, *drumstick, animShader);
	auto& floorMesh = floorEnt.Add<MeshRenderer>(floorEnt, *floor, shader);
	auto& leftMesh = leftEnt.Add<MeshRenderer>(leftEnt, *wall, shader);
	auto& rightMesh = rightEnt.Add<MeshRenderer>(rightEnt, *wall, shader);
	auto& backMesh = backEnt.Add<MeshRenderer>(backEnt, *wall, shader);
	auto& doorMesh = doorEnt.Add<MorphRenderer>(doorEnt, *doorM, animShader);
	auto& doorCloseMesh = doorCloseEnt.Add<MorphRenderer>(doorCloseEnt, *doorCloseM, animShader);
	auto& completeMesh = completeEnt.Add<MeshRenderer>(completeEnt, *floor, shader);
	auto& gateMesh = andEnt.Add<MeshRenderer>(andEnt, *gate, shader);
	auto& buttonMesh = buttonEnt.Add<MeshRenderer>(buttonEnt, *buttonM, shader);
	auto& buttonMesh2 = buttonEnt2.Add<MeshRenderer>(buttonEnt2, *buttonM, shader);
	auto& wireMesh = wireEnt.Add<MeshRenderer>(wireEnt, *wireL, shader);
	auto& wireMesh2 = wireEnt2.Add<MeshRenderer>(wireEnt2, *wireR, shader);
	auto& wireMesh3 = wireEnt3.Add<MeshRenderer>(wireEnt3, *wireC, shader);
	auto& coilMesh = coilEnt.Add<MeshRenderer>(coilEnt, *coil, untexturedShader);
	auto& boxMesh = boxEnt.Add<MeshRenderer>(boxEnt, *boxM, shader);
	auto& boxMesh2 = boxEnt2.Add<MeshRenderer>(boxEnt2, *boxM, shader);
	auto& boxMesh3 = boxEnt3.Add<MeshRenderer>(boxEnt3, *boxM, shader);
	auto& boxMesh4 = boxEnt4.Add<MeshRenderer>(boxEnt4, *boxM, shader);
	auto& boxMesh5 = boxEnt5.Add<MeshRenderer>(boxEnt5, *boxM, shader);
	auto& panelMesh = panelEnt.Add<MeshRenderer>(panelEnt, *panel, shader);
	auto& panelMesh2 = panelEnt2.Add<MeshRenderer>(panelEnt2, *panel, shader);
	auto& ventMesh = bigVentEnt.Add<MeshRenderer>(bigVentEnt, *ventB, shader);
	auto& ventMesh2 = smallVentEnt.Add<MeshRenderer>(smallVentEnt, *ventS, shader);
	auto& ventMesh3 = smallVentEnt2.Add<MeshRenderer>(smallVentEnt2, *ventS, shader);
	auto& pipeMesh = pipeEntS.Add<MeshRenderer>(pipeEntS, *pipeS, shader);
	auto& pipeMesh2 = pipeEntC.Add<MeshRenderer>(pipeEntC, *pipeC, shader);
	auto& tutMesh = tutEnt.Add<MeshRenderer>(tutEnt, *tut, untexturedShader);
	auto& pauseMesh = pauseEnt.Add<MeshRenderer>(pauseEnt, *floor, pauseShader);
	auto& tabletScreenMesh = tabletScreenEnt.Add<MeshRenderer>(tabletScreenEnt, *floor, pauseShader);
	auto& optionMesh = optionEnt.Add<MeshRenderer>(optionEnt, *options, pauseShader);
	auto& retryMesh = retryEnt.Add<MeshRenderer>(retryEnt, *retry, pauseShader);
	auto& exitMesh = exitEnt.Add<MeshRenderer>(exitEnt, *exit, pauseShader);
	auto& tabletMesh = tabletEnt.Add<MeshRenderer>(tabletEnt, *tablet, shader);

	auto& doorAnimator = doorEnt.Add<MorphAnimation>(doorEnt);
	doorAnimator.SetTime(0.2f);
	doorAnimator.SetFrames(doorFrames);
	doorAnimator.SetLoop(false);

	auto& doorCloseAnimator = doorCloseEnt.Add<MorphAnimation>(doorCloseEnt);
	doorCloseAnimator.SetTime(0.2f);
	doorCloseAnimator.SetFrames(doorCloseFrames);
	doorCloseAnimator.SetLoop(false);

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
}

void Level1::Update(float dt)
{
	time += dt;
	untexturedShader->SetUniform("u_Time", time);
	shader->SetUniform("u_Time", time);
	pauseShader->SetUniform("u_Time", time);
	animShader->SetUniform("u_Time", time);

	if (forwards)
		t += dt / totalTime;
	else
		t -= dt / totalTime;

	if (t < 0.0f)
		t = 0.0f;

	if (t > 1.0f)
		t = 1.0f;

	if (t >= 1.0f || t <= 0.0f)
		forwards = !forwards;

	currentPos = glm::mix(point1, point2, t);

	untexturedShader->SetUniform("u_Position", currentPos);
	shader->SetUniform("u_Position", currentPos);
	pauseShader->SetUniform("u_Position", currentPos);
	animShader->SetUniform("u_Position", currentPos);

#pragma region Transforms
	auto& playerTrans = mainPlayer.Get<Transform>();
	auto& groundTrans = floorEnt.Get<Transform>();
	auto& leftTrans = leftEnt.Get<Transform>();
	auto& rightTrans = rightEnt.Get<Transform>();
	auto& backTrans = backEnt.Get<Transform>();
	auto& doorTrans = doorEnt.Get<Transform>();
	auto& doorCloseTrans = doorCloseEnt.Get<Transform>();
	auto& completeTrans = completeEnt.Get<Transform>();
	auto& gateTrans = andEnt.Get<Transform>();
	auto& buttonTrans = buttonEnt.Get<Transform>();
	auto& buttonTrans2 = buttonEnt2.Get<Transform>();
	auto& wireTrans = wireEnt.Get<Transform>();
	auto& wireTrans2 = wireEnt2.Get<Transform>();
	auto& wireTrans3 = wireEnt3.Get<Transform>();
	auto& coilTrans = coilEnt.Get<Transform>();
	auto& boxTrans = boxEnt.Get<Transform>();
	auto& boxTrans2 = boxEnt2.Get<Transform>();
	auto& boxTrans3 = boxEnt3.Get<Transform>();
	auto& boxTrans4 = boxEnt4.Get<Transform>();
	auto& boxTrans5 = boxEnt5.Get<Transform>();
	auto& panelTrans = panelEnt.Get<Transform>();
	auto& panelTrans2 = panelEnt2.Get<Transform>();
	auto& ventTrans = bigVentEnt.Get<Transform>();
	auto& ventTrans2 = smallVentEnt.Get<Transform>();
	auto& ventTrans3 = smallVentEnt2.Get<Transform>();
	auto& pipeTrans = pipeEntS.Get<Transform>();
	auto& pipeTrans2 = pipeEntC.Get<Transform>();
	auto& tutTrans = tutEnt.Get<Transform>();
	auto& pauseTrans = pauseEnt.Get<Transform>();
	auto& optionsTrans = optionEnt.Get<Transform>();
	auto& retryTrans = retryEnt.Get<Transform>();
	auto& exitTrans = exitEnt.Get<Transform>();
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
	camera.LookAt(glm::vec3(playerTrans.GetPositionX(), playerTrans.GetPositionY() + 5.0f, playerTrans.GetPositionZ()));

	//Get references to the meshes
	auto& meshMain = mainPlayer.Get<MorphRenderer>();
	auto& groundMesh = floorEnt.Get<MeshRenderer>();
	auto& leftMesh = leftEnt.Get<MeshRenderer>();
	auto& rightMesh = rightEnt.Get<MeshRenderer>();
	auto& backMesh = backEnt.Get<MeshRenderer>();
	auto& doorMesh = doorEnt.Get<MorphRenderer>();
	auto& doorCloseMesh = doorCloseEnt.Get<MorphRenderer>();
	auto& completeMesh = completeEnt.Get<MeshRenderer>();
	auto& gateMesh = andEnt.Get<MeshRenderer>();
	auto& buttonMesh = buttonEnt.Get<MeshRenderer>();
	auto& buttonMesh2 = buttonEnt2.Get<MeshRenderer>();
	auto& wireMesh = wireEnt.Get<MeshRenderer>();
	auto& wireMesh2 = wireEnt2.Get<MeshRenderer>();
	auto& wireMesh3 = wireEnt3.Get<MeshRenderer>();
	auto& coilMesh = coilEnt.Get<MeshRenderer>();
	auto& boxMesh = boxEnt.Get<MeshRenderer>();
	auto& boxMesh2 = boxEnt2.Get<MeshRenderer>();
	auto& boxMesh3 = boxEnt3.Get<MeshRenderer>();
	auto& boxMesh4 = boxEnt4.Get<MeshRenderer>();
	auto& boxMesh5 = boxEnt5.Get<MeshRenderer>();
	auto& panelMesh = panelEnt.Get<MeshRenderer>();
	auto& panelMesh2 = panelEnt2.Get<MeshRenderer>();
	auto& ventMesh = bigVentEnt.Get<MeshRenderer>();
	auto& ventMesh2 = smallVentEnt.Get<MeshRenderer>();
	auto& ventMesh3 = smallVentEnt2.Get<MeshRenderer>();
	auto& pipeMesh = pipeEntS.Get<MeshRenderer>();
	auto& pipeMesh2 = pipeEntC.Get<MeshRenderer>();
	auto& tutMesh = tutEnt.Get<MeshRenderer>();
	auto& pauseMesh = pauseEnt.Get<MeshRenderer>();
	auto& optionMesh = optionEnt.Get<MeshRenderer>();
	auto& retryMesh = retryEnt.Get<MeshRenderer>();
	auto& exitMesh = exitEnt.Get<MeshRenderer>();
	auto& tabletMesh = tabletEnt.Get<MeshRenderer>();
	auto& tabletScreenMesh = tabletScreenEnt.Get<MeshRenderer>();

	//Get reference to the model matrix
	glm::mat4 transform = playerTrans.GetModelMatrix();
	glm::mat4 transformGround = groundTrans.GetModelMatrix();
	glm::mat4 transformLeft = leftTrans.GetModelMatrix();
	glm::mat4 transformRight = rightTrans.GetModelMatrix();
	glm::mat4 transformBack = backTrans.GetModelMatrix();
	glm::mat4 transformDoor = doorTrans.GetModelMatrix();
	glm::mat4 transformDoorClose = doorCloseTrans.GetModelMatrix();
	glm::mat4 transformComplete = completeTrans.GetModelMatrix();
	glm::mat4 transformGate = gateTrans.GetModelMatrix();
	glm::mat4 transformButton = buttonTrans.GetModelMatrix();
	glm::mat4 transformButton2 = buttonTrans2.GetModelMatrix();
	glm::mat4 transformWire = wireTrans.GetModelMatrix();
	glm::mat4 transformWire2 = wireTrans2.GetModelMatrix();
	glm::mat4 transformWire3 = wireTrans3.GetModelMatrix();
	glm::mat4 transformCoil = coilTrans.GetModelMatrix();
	glm::mat4 transformBox = boxTrans.GetModelMatrix();
	glm::mat4 transformBox2 = boxTrans2.GetModelMatrix();
	glm::mat4 transformBox3 = boxTrans3.GetModelMatrix();
	glm::mat4 transformBox4 = boxTrans4.GetModelMatrix();
	glm::mat4 transformBox5 = boxTrans5.GetModelMatrix();
	glm::mat4 transformPanel = panelTrans.GetModelMatrix();
	glm::mat4 transformPanel2 = panelTrans2.GetModelMatrix();
	glm::mat4 transformVent = ventTrans.GetModelMatrix();
	glm::mat4 transformVent2 = ventTrans2.GetModelMatrix();
	glm::mat4 transformVent3 = ventTrans3.GetModelMatrix();
	glm::mat4 transformPipe = pipeTrans.GetModelMatrix();
	glm::mat4 transformPipe2 = pipeTrans2.GetModelMatrix();
	glm::mat4 transformTut = tutTrans.GetModelMatrix();
	glm::mat4 transformPause = pauseTrans.GetModelMatrix();
	glm::mat4 transformOptions = optionsTrans.GetModelMatrix();
	glm::mat4 transformRetry = retryTrans.GetModelMatrix();
	glm::mat4 transformExit = exitTrans.GetModelMatrix();
	glm::mat4 transformTablet = tabletTrans.GetModelMatrix();
	glm::mat4 transformTabletScreen = tabletScreenTrans.GetModelMatrix();

	//Particle Stuff
	//auto& particleSystem = particleEnt.Get<ParticleSystem>();
	
	if (playerTrans.GetPositionX() - buttonTrans.GetPositionX() < 2.0f && playerTrans.GetPositionX() - buttonTrans.GetPositionX() > -2.0f
		&& playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() > -3.0f)
		button1Watch.Poll(window);
	
	if (playerTrans.GetPositionX() - buttonTrans2.GetPositionX() < 2.0f && playerTrans.GetPositionX() - buttonTrans2.GetPositionX() > -2.0f
		&& playerTrans.GetPositionZ() - buttonTrans2.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans2.GetPositionZ() > -3.0f)
		button2Watch.Poll(window);

	if ((playerTrans.GetPositionX() > -3.0f && playerTrans.GetPositionX() < 3.0f
		&& playerTrans.GetPositionZ() > 7.0f && playerTrans.GetPositionZ() < 13.0f
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
		Input::MovePlayer(window, mainPlayer, camEnt, dt, camFar, camClose);
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

	if (!showLevelComplete && !isPaused)
	{
		Input::MoveCamera(window, camEnt, dt);
	}
#pragma endregion

	lightNum = Input::ChangeLighting(window, lightNum);

	if (lightNum < 1 || lightNum > 5)
		lightNum = 1;

	untexturedShader->SetUniform("u_LightNum", lightNum);
	shader->SetUniform("u_LightNum", lightNum);
	pauseShader->SetUniform("u_LightNum", lightNum);
	animShader->SetUniform("u_LightNum", lightNum);

	//Post-Effect Stuff
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
		if (!showLevelComplete)
		{
			//Bind and render the player and door using the animation shader
			animShader->Bind();
			animShader->SetUniform("s_Diffuse", 0);
			drumstickMat.Albedo->Bind(0);
			meshMain.Render(camera, transform);

			animShader->SetUniform("s_Diffuse", 1);
			doorMat.Albedo->Bind(1);

			if (doorEnt.Get<Door>().GetOpen())
			{
				doorMesh.Render(camera, transformDoor);
			}
			else
			{
				doorCloseMesh.Render(camera, transformDoor);
			}
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

			//Bind and render the other objects using the basic shader
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

			//Gate
			shader->SetUniform("s_Diffuse", 2);
			gateMat.Albedo->Bind(2);
			gateMesh.Render(camera, transformGate);

			//Buttons
			shader->SetUniform("s_Diffuse", 3);
			buttonMat.Albedo->Bind(3);
			buttonMesh.Render(camera, transformButton);
			buttonMesh2.Render(camera, transformButton2);

			//Wires
			shader->SetUniform("s_Diffuse", 4);

			if (wireEnt.Get<Wire>().GetIsPowered())
			{
				wirePowerMat.Albedo->Bind(4);
				wireMesh.Render(camera, transformWire);
			}
			else
			{
				wireMat.Albedo->Bind(4);
				wireMesh.Render(camera, transformWire);
			}

			if (wireEnt2.Get<Wire>().GetIsPowered())
			{
				wirePowerMat.Albedo->Bind(4);
				wireMesh2.Render(camera, transformWire2);
			}
			else
			{
				wireMat.Albedo->Bind(4);
				wireMesh2.Render(camera, transformWire2);
			}

			if (wireEnt3.Get<Wire>().GetIsPowered())
			{
				wirePowerMat.Albedo->Bind(4);
				wireMesh3.Render(camera, transformWire3);
			}
			else
			{
				wireMat.Albedo->Bind(4);
				wireMesh3.Render(camera, transformWire3);
			}

			//Boxes
			shader->SetUniform("s_Diffuse", 5);
			boxMat.Albedo->Bind(5);
			boxMesh.Render(camera, transformBox);
			boxMesh2.Render(camera, transformBox2);
			boxMesh3.Render(camera, transformBox3);
			boxMesh4.Render(camera, transformBox4);
			boxMesh5.Render(camera, transformBox5);

			//Panels
			shader->SetUniform("s_Diffuse", 6);
			panelMat.Albedo->Bind(6);
			panelMesh.Render(camera, transformPanel);
			panelMesh2.Render(camera, transformPanel2);

			//Vents
			shader->SetUniform("s_Diffuse", 7);
			ventMat.Albedo->Bind(7);
			ventMesh.Render(camera, transformVent);
			ventMesh2.Render(camera, transformVent2);
			ventMesh3.Render(camera, transformVent3);

			//Pipes
			//Straight Pipe
			shader->SetUniform("s_Diffuse", 8);
			straightPipeMat.Albedo->Bind(8);
			pipeMesh.Render(camera, transformPipe);

			//Curved Pipe
			shader->SetUniform("s_Diffuse", 9);
			curvedPipeMat.Albedo->Bind(9);
			pipeMesh2.Render(camera, transformPipe2);

			shader->SetUniform("s_Diffuse", 10);
			tabletMat.Albedo->Bind(10);
			tabletMesh.Render(camera, transformTablet);

			//Bind and render the objects with no textures
			untexturedShader->Bind();
			coilMesh.Render(camera, transformCoil);

			if (playerTrans.GetPositionX() > -3.0f && playerTrans.GetPositionX() < 3.0f
				&& playerTrans.GetPositionZ() > 7.0f && playerTrans.GetPositionZ() < 13.0f)
			{
				tutMesh.Render(orthoCam, transformTut);
			}

			/*if (!isPaused)
			{
				particleSystem.Update(dt, camera);
				
				if (!andEnt.Get<AndGate>().GetOutput())
				{
					particleShader->Bind();
					glDisable(GL_DEPTH_TEST);
					particleSystem.Draw(camera, particleShader);
					glEnable(GL_DEPTH_TEST);
				}
			}*/
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

			if (doorEnt.Get<Door>().GetOpen())
			{
				doorMesh.Render(camera, transformDoor);
			}
			else
			{
				doorCloseMesh.Render(camera, transformDoor);
			}
			doorMat.Albedo->Unbind(1);

			pauseShader->Bind();
			pauseShader->SetUniform("s_Diffuse", 0);
			clearMat.Albedo->Bind(0);

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
			gateMesh.Render(camera, transformGate);
			buttonMesh.Render(camera, transformButton);
			buttonMesh2.Render(camera, transformButton2);
			wireMesh.Render(camera, transformWire);
			wireMesh2.Render(camera, transformWire2);
			wireMesh3.Render(camera, transformWire3);
			boxMesh.Render(camera, transformBox);
			boxMesh2.Render(camera, transformBox2);
			boxMesh3.Render(camera, transformBox3);
			boxMesh4.Render(camera, transformBox4);
			boxMesh5.Render(camera, transformBox5);
			panelMesh.Render(camera, transformPanel);
			panelMesh2.Render(camera, transformPanel2);
			ventMesh.Render(camera, transformVent);
			ventMesh2.Render(camera, transformVent2);
			ventMesh3.Render(camera, transformVent3);
			pipeMesh.Render(camera, transformPipe);
			pipeMesh2.Render(camera, transformPipe2);
			tabletMesh.Render(camera, transformTablet);

			untexturedShader->Bind();
			coilMesh.Render(camera, transformCoil);

			/*if (!isPaused)
			{
				particleSystem.Update(dt, camera);
				
				if (!andEnt.Get<AndGate>().GetOutput())
				{
					particleShader->Bind();
					glDisable(GL_DEPTH_TEST);
					particleSystem.Draw(camera, particleShader);
					glEnable(GL_DEPTH_TEST);
				}
			}*/
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
	boxEnt.Get<AABB>().Update();
	boxEnt2.Get<AABB>().Update();
	boxEnt3.Get<AABB>().Update();
	boxEnt4.Get<AABB>().Update();
	boxEnt5.Get<AABB>().Update();
	andEnt.Get<AndGate>().Update();
	coilEnt.Get<AABB>().Update();
	buttonEnt.Get<Lever>().Update();
	buttonEnt2.Get<Lever>().Update();
	wireEnt.Get<Wire>().Update();
	wireEnt2.Get<Wire>().Update();
	wireEnt3.Get<Wire>().Update();

	//Door Logic
	if (doorEnt.Get<Door>().GetOpen())
	{
		doorEnt.Get<MorphAnimation>().SetLoop(true);
		doorEnt.Get<MorphAnimation>().SetLoop(false);
		doorEnt.Get<MorphAnimation>().Update(dt);
	}

	if (!doorEnt.Get<Door>().GetOpen())
	{
		doorCloseEnt.Get<MorphAnimation>().SetLoop(true);
		doorCloseEnt.Get<MorphAnimation>().SetLoop(false);
		doorCloseEnt.Get<MorphAnimation>().Update(dt);
	}

	if (doorEnt.Get<AABB>().GetComplete())
		showLevelComplete = true;
}

void Level1::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}