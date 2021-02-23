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
	mainPlayer = Entity::Create();
	floorEnt = Entity::Create();
	leftEnt = Entity::Create();
	rightEnt = Entity::Create();
	backEnt = Entity::Create();
	buttonEnt = Entity::Create();
	buttonEnt2 = Entity::Create();
	wireEnt = Entity::Create();
	wireEnt2 = Entity::Create();
	wireEnt3 = Entity::Create();
	andEnt = Entity::Create();
	doorEnt = Entity::Create();
	doorCloseEnt = Entity::Create();
	coilEnt = Entity::Create();
	coilPowered = Entity::Create();
	pipeEnt = Entity::Create();
	boxEnt = Entity::Create();
	particleEnt = Entity::Create();
	wirePowered = Entity::Create();
	wirePowered2 = Entity::Create();
	wirePowered3 = Entity::Create();
	completeEnt = Entity::Create();
	tutEnt = Entity::Create();
	FBO = Entity::Create();
	greyscaleEnt = Entity::Create();
	sepiaEnt = Entity::Create();
	colorCorrectEnt = Entity::Create();
	bloomEnt = Entity::Create();
	pauseEnt = Entity::Create();
	ventEnt	 = Entity::Create();
	panelEnt = Entity::Create();
	pipesEnt = Entity::Create();
	optionEnt = Entity::Create();
	exitEnt = Entity::Create();
	retryEnt = Entity::Create();

	drumstick = ModelManager::FindMesh(drumFile);
	floor = ModelManager::FindMesh(floorFile);
	wall = ModelManager::FindMesh(wallFile);
	doorM = ModelManager::FindMesh(doorFile);
	doorCloseM = ModelManager::FindMesh(doorFile10);
	buttonM = ModelManager::FindMesh(buttonFile);
	wireL = ModelManager::FindMesh(wire1File, glm::vec3(1.0f, 0.0f, 0.0f));
	wireR = ModelManager::FindMesh(wire2File, glm::vec3(1.0f, 0.0f, 0.0f));
	wireC = ModelManager::FindMesh(wire3File, glm::vec3(1.0f, 0.0f, 0.0f));
	wireLPower = ModelManager::FindMesh(wire1File, glm::vec3(0.0f, 1.0f, 0.0f));
	wireRPower = ModelManager::FindMesh(wire2File, glm::vec3(0.0f, 1.0f, 0.0f));
	wireCPower = ModelManager::FindMesh(wire3File, glm::vec3(0.0f, 1.0f, 0.0f));
	gate = ModelManager::FindMesh(gateFile);
	coil = ModelManager::FindMesh(coilFile, glm::vec3(1.0f, 0.0f, 0.0f));
	coilP = ModelManager::FindMesh(coilFile, glm::vec3(0.0f, 1.0f, 0.0f));
	pipe = ModelManager::FindMesh(pipeFile, glm::vec3(0.6f, 0.45f, 0.0f));
	tut = ModelManager::FindMesh(tutFile, glm::vec3(1.0f, 0.0f, 0.0f));
	vent = ModelManager::FindMesh(ventFile);
	pipes = ModelManager::FindMesh(pipesFile);
	panel = ModelManager::FindMesh(panelFile);
	options = ModelManager::FindMesh(pauseButtonFile);
	exit = ModelManager::FindMesh(pauseButtonFile);
	retry = ModelManager::FindMesh(pauseButtonFile);

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
	glm::vec3 lightCol = glm::vec3(1.f, 1.f, 1.f);
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

	particleShader = Shader::Create();
	particleShader->LoadShaderPartFromFile("Shaders/particle_vertex.glsl", GL_VERTEX_SHADER);
	particleShader->LoadShaderPartFromFile("Shaders/particle_geom.glsl", GL_GEOMETRY_SHADER);
	particleShader->LoadShaderPartFromFile("Shaders/particle_frag.glsl", GL_FRAGMENT_SHADER);
	particleShader->Link();

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
	Texture2D::sptr diffuseFloor = Texture2D::LoadFromFile("Textures/FloorTexture.jpg");
	Texture2D::sptr diffuseWall = Texture2D::LoadFromFile("Textures/WallTexture.jpg");
	Texture2D::sptr diffuseWire = Texture2D::LoadFromFile("Textures/WireTexture.png");
	Texture2D::sptr diffuseUI = Texture2D::LoadFromFile("Textures/Buttons/Default/Option.png");
	Texture2D::sptr diffuseComplete = Texture2D::LoadFromFile("Textures/LevelComplete.png");
	Texture2D::sptr diffuseAnd = Texture2D::LoadFromFile("Textures/AndGate.png");
	Texture2D::sptr diffusePause = Texture2D::LoadFromFile("Textures/PauseMenu.png");
	Texture2D::sptr diffuseBox = Texture2D::LoadFromFile("Textures/Box.png");
	Texture2D::sptr diffusePipeStraight = Texture2D::LoadFromFile("Textures/StraightPipe.png");
	Texture2D::sptr diffusePipeCurved = Texture2D::LoadFromFile("Textures/CurvedPipe.png");
	Texture2D::sptr diffuseOptions = Texture2D::LoadFromFile("Textures/Buttons/Default/Option.png");
	Texture2D::sptr diffuseExit = Texture2D::LoadFromFile("Textures/Buttons/Default/Exit.png");
	Texture2D::sptr diffuseRetry = Texture2D::LoadFromFile("Textures/Buttons/Default/Replay.png");

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
	completeMat.Albedo = diffuseComplete;
	gateMat.Albedo = diffuseAnd;
	clearMat.Albedo = texture2;
	pauseMat.Albedo = diffusePause;
	boxMat.Albedo = diffuseBox;
	straightPipeMat.Albedo = diffusePipeStraight;
	curvedPipeMat.Albedo = diffusePipeCurved;
	optionMat.Albedo = diffuseOptions;
	exitMat.Albedo = diffuseExit;
	retryMat.Albedo = diffuseRetry;

#pragma endregion

	//Transforms
	auto& particleTrans = particleEnt.Add<Transform>();
	particleTrans.SetPosition(glm::vec3(0.0f, 4.0f, -2.0f));

	auto& playerTrans = mainPlayer.Add<Transform>();
	playerTrans.SetPosition(glm::vec3(0.0f, 1.0f, 30.0f));
	playerTrans.SetRotationY(0.0f);

	auto& tutTrans = tutEnt.Add<Transform>();
	tutTrans.SetPosition(glm::vec3(-8.0f, 1.0f, 15.0f));
	tutTrans.SetScale(glm::vec3(3.0f));

	auto& groundTrans = floorEnt.Add<Transform>();

	auto& leftTrans = leftEnt.Add<Transform>();

	auto& rightTrans = rightEnt.Add<Transform>();

	auto& backTrans = backEnt.Add<Transform>();

	auto& wireTrans = wireEnt.Add<Transform>();
	wireTrans.SetPosition(glm::vec3(-6.4f, 2.0f, 1.5f));

	auto& wireTrans2 = wireEnt2.Add<Transform>();
	wireTrans2.SetPosition(glm::vec3(22.0f, 2.0f, 5.0f));

	auto& wireTrans3 = wireEnt3.Add<Transform>();
	wireTrans3.SetPosition(glm::vec3(-16.2f, 2.0f, -10.5));

	auto& buttonTrans = buttonEnt.Add<Transform>();
	buttonTrans.SetPosition(glm::vec3(-22.0f, -2.0f, 21.0f));
	buttonTrans.SetRotationY(90.0f);

	auto& buttonTrans2 = buttonEnt2.Add<Transform>();
	buttonTrans2.SetPosition(glm::vec3(22.0f, -2.0f, 21.0f));
	buttonTrans2.SetRotationY(90.0f);

	auto& doorTrans = doorEnt.Add<Transform>();
	doorTrans.SetPosition(glm::vec3(0.0f, -1.0f, -36.0f));
	doorTrans.SetScale(glm::vec3(1.5f));

	auto& doorCloseTrans = doorCloseEnt.Add<Transform>();
	doorCloseTrans.SetPosition(glm::vec3(0.0f, -1.0f, -36.0f));
	doorCloseTrans.SetScale(glm::vec3(1.5f));

	auto& pipeTrans = pipeEnt.Add<Transform>();
	pipeTrans.SetPositionX(-35.5f);
	pipeTrans.SetPositionY(10.5f);

	auto& gateTrans = andEnt.Add<Transform>();
	gateTrans.SetPosition(glm::vec3(0.0f, 1.0f, -2.0f));
	gateTrans.SetRotationY(-90.0f);
	gateTrans.SetScale(glm::vec3(2.0f));

	auto& coilTrans = coilEnt.Add<Transform>();
	coilTrans.SetPosition(glm::vec3(-16.0f, 2.0f, -33.0f));
	coilTrans.SetScale(glm::vec3(3.0f));
	coilTrans.SetRotationY(180.0f);

	auto& completeTrans = completeEnt.Add<Transform>();
	completeTrans.SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	completeTrans.SetScale(glm::vec3(0.22f));

	auto& pauseTrans = pauseEnt.Add<Transform>();
	pauseTrans.SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	pauseTrans.SetScale(glm::vec3(0.20f, 1.0f, 0.12f));

	auto& optionsTrans = optionEnt.Add<Transform>();
	optionsTrans.SetPosition(glm::vec3(-5.0f, 0.0f, -6.0f));
	optionsTrans.SetScale(glm::vec3(1.5f));
	optionsTrans.SetRotationY(96.0f);

	auto& retryTrans = retryEnt.Add<Transform>();
	retryTrans.SetPosition(glm::vec3(0.0f, 0.0f, -6.0f));
	retryTrans.SetScale(glm::vec3(1.5f));
	retryTrans.SetRotationY(96.0f);

	auto& exitTrans = exitEnt.Add<Transform>();
	exitTrans.SetPosition(glm::vec3(5.0f, 0.0f, -6.0f));
	exitTrans.SetScale(glm::vec3(1.5f));
	exitTrans.SetRotationY(96.0f);

	auto& ventTrans = ventEnt.Add<Transform>();
	ventTrans.SetPosition(glm::vec3(5.0f, 2.0f, 0.0f));
	ventTrans.SetScale(glm::vec3(2.0f));

	auto& panelTrans = panelEnt.Add<Transform>();
	panelTrans.SetPosition(glm::vec3(15.0f, 2.0f, 0.0f));
	panelTrans.SetScale(glm::vec3(2.0f));

	auto& pipesTrans = pipesEnt.Add<Transform>();
	pipesTrans.SetPosition(glm::vec3(25.0f, 2.0f, 0.0f));
	pipesTrans.SetScale(glm::vec3(2.0f));


	//AABB
	auto& leftCol = leftEnt.Add<AABB>(leftEnt, mainPlayer);
	auto& rightCol = rightEnt.Add<AABB>(rightEnt, mainPlayer);
	auto& backCol = backEnt.Add<AABB>(backEnt, mainPlayer);
	auto& gateCol = andEnt.Add<AABB>(andEnt, mainPlayer);
	auto& coilCol = coilEnt.Add<AABB>(coilEnt, mainPlayer, 4.0f, 4.0f);
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
	auto& particleSystem = particleEnt.Add<ParticleSystem>(particleEnt, particleData);

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

	auto& playerMesh = mainPlayer.Add<MorphRenderer>(mainPlayer, *drumstick, animShader);
	auto& floorMesh = floorEnt.Add<MeshRenderer>(floorEnt, *floor, shader);
	auto& leftMesh = leftEnt.Add<MeshRenderer>(leftEnt, *wall, shader);
	auto& rightMesh = rightEnt.Add<MeshRenderer>(rightEnt, *wall, shader);
	auto& backMesh = backEnt.Add<MeshRenderer>(backEnt, *wall, shader);
	auto& gateMesh = andEnt.Add<MeshRenderer>(andEnt, *gate, shader);
	auto& buttonMesh = buttonEnt.Add<MeshRenderer>(buttonEnt, *buttonM, shader);
	auto& buttonMesh2 = buttonEnt2.Add<MeshRenderer>(buttonEnt2, *buttonM, shader);
	auto& wireMesh = wireEnt.Add<MeshRenderer>(wireEnt, *wireL, shader);
	auto& wireMesh2 = wireEnt2.Add<MeshRenderer>(wireEnt2, *wireR, shader);
	auto& wireMesh3 = wireEnt3.Add<MeshRenderer>(wireEnt3, *wireC, shader);
	auto& wireMeshP = wirePowered.Add<MeshRenderer>(wirePowered, *wireLPower, shader);
	auto& wireMeshP2 = wirePowered2.Add<MeshRenderer>(wirePowered2, *wireRPower, shader);
	auto& wireMeshP3 = wirePowered3.Add<MeshRenderer>(wirePowered3, *wireCPower, shader);
	auto& doorMesh = doorEnt.Add<MorphRenderer>(doorEnt, *doorM, animShader);
	auto& doorCloseMesh = doorCloseEnt.Add<MorphRenderer>(doorCloseEnt, *doorCloseM, animShader);
	auto& pipeMesh = pipeEnt.Add<MeshRenderer>(pipeEnt, *pipe, untexturedShader);
	auto& coilMesh = coilEnt.Add<MeshRenderer>(coilEnt, *coil, untexturedShader);
	auto& coilMeshP = coilPowered.Add<MeshRenderer>(coilPowered, *coilP, untexturedShader);
	auto& tutMesh = tutEnt.Add<MeshRenderer>(tutEnt, *tut, untexturedShader);
	auto& completeMesh = completeEnt.Add<MeshRenderer>(completeEnt, *floor, shader);
	auto& ventMesh = ventEnt.Add<MeshRenderer>(ventEnt, *vent, shader);
	auto& panelMesh = panelEnt.Add<MeshRenderer>(panelEnt, *panel, shader);
	auto& pipesMesh = pipesEnt.Add<MeshRenderer>(pipesEnt, *pipes, shader);
	auto& pauseMesh = pauseEnt.Add<MeshRenderer>(pauseEnt, *floor, pauseShader);
	auto& optionMesh = optionEnt.Add<MeshRenderer>(optionEnt, *options, pauseShader);
	auto& retryMesh = retryEnt.Add<MeshRenderer>(retryEnt, *retry, pauseShader);
	auto& exitMesh = exitEnt.Add<MeshRenderer>(exitEnt, *exit, pauseShader);

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

	auto& camera = camEnt.Add<Camera>();

	camera.SetPosition(glm::vec3(0, 15, mainPlayer.Get<Transform>().GetPositionZ() + 12)); // Set initial position
	camera.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
	camera.LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camera.SetFovDegrees(90.0f); // Set an initial FOV

	auto& orthoCam = uiCamEnt.Add<Camera>();
	orthoCam.SetPosition(glm::vec3(0, 10, 0)); // Set initial position
	orthoCam.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
	orthoCam.LookAt(glm::vec3(0.0f)); // Look at center of the screen
	orthoCam.SetFovDegrees(90.0f); // Set an initial FOV

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

	//if (doorEnt.Get<Door>().GetOpen())
	//	doorEnt.Get<MorphAnimation>().SetFrames(doorFrames);
	//else
	//	doorEnt.Get<MorphAnimation>().SetFrames(doorCloseFrames);

	//Transforms
	auto& playerTrans = mainPlayer.Get<Transform>();
	auto& groundTrans = floorEnt.Get<Transform>();
	auto& leftTrans = leftEnt.Get<Transform>();
	auto& rightTrans = rightEnt.Get<Transform>();
	auto& backTrans = backEnt.Get<Transform>();
	auto& doorTrans = doorEnt.Get<Transform>();
	auto& doorCloseTrans = doorCloseEnt.Get<Transform>();
	auto& pipeTrans = pipeEnt.Get<Transform>();
	auto& buttonTrans = buttonEnt.Get<Transform>();
	auto& buttonTrans2 = buttonEnt2.Get<Transform>();
	auto& wireTrans = wireEnt.Get<Transform>();
	auto& wireTrans2 = wireEnt2.Get<Transform>();
	auto& wireTrans3 = wireEnt3.Get<Transform>();
	auto& gateTrans = andEnt.Get<Transform>();
	auto& coilTrans = coilEnt.Get<Transform>();
	auto& tutTrans = tutEnt.Get<Transform>();
	auto& completeTrans = completeEnt.Get<Transform>();
	auto& ventTrans = ventEnt.Get<Transform>();
	auto& panelTrans = panelEnt.Get<Transform>();
	auto& pipesTrans = pipesEnt.Get<Transform>();
	auto& pauseTrans = pauseEnt.Get<Transform>();
	auto& optionsTrans = optionEnt.Get<Transform>();
	auto& exitTrans = exitEnt.Get<Transform>();
	auto& retryTrans = retryEnt.Get<Transform>();
	
	backTrans.SetPositionZ(-39.0f);
	backTrans.SetPositionY(9.0f);

	leftTrans.SetPositionX(-39.0f);
	leftTrans.SetRotationY(90.0f);
	leftTrans.SetPositionY(9.0f);

	rightTrans.SetPositionX(39.0f);
	rightTrans.SetRotationY(90.0f);
	rightTrans.SetPositionY(9.0f);

	auto& camera = camEnt.Get<Camera>();
	auto& orthoCam = uiCamEnt.Get<Camera>();

	camera.LookAt(glm::vec3(playerTrans.GetPositionX(), playerTrans.GetPositionY() + 5.0f, playerTrans.GetPositionZ()));

	auto& meshMain = mainPlayer.Get<MorphRenderer>();
	auto& groundMesh = floorEnt.Get<MeshRenderer>();
	auto& leftMesh = leftEnt.Get<MeshRenderer>();
	auto& rightMesh = rightEnt.Get<MeshRenderer>();
	auto& backMesh = backEnt.Get<MeshRenderer>();
	auto& doorMesh = doorEnt.Get<MorphRenderer>();
	auto& doorCloseMesh = doorCloseEnt.Get<MorphRenderer>();
	auto& pipeMesh = pipeEnt.Get<MeshRenderer>();
	auto& buttonMesh = buttonEnt.Get<MeshRenderer>();
	auto& buttonMesh2 = buttonEnt2.Get<MeshRenderer>();
	auto& wireMesh = wireEnt.Get<MeshRenderer>();
	auto& wireMesh2 = wireEnt2.Get<MeshRenderer>();
	auto& wireMesh3 = wireEnt3.Get<MeshRenderer>();
	auto& wireMeshP = wirePowered.Get<MeshRenderer>();
	auto& wireMeshP2 = wirePowered2.Get<MeshRenderer>();
	auto& wireMeshP3 = wirePowered3.Get<MeshRenderer>();
	auto& gateMesh = andEnt.Get<MeshRenderer>();
	auto& coilMesh = coilEnt.Get<MeshRenderer>();
	auto& coilMeshP = coilPowered.Get<MeshRenderer>();
	auto& completeMesh = completeEnt.Get<MeshRenderer>();
	auto& tutMesh = tutEnt.Get<MeshRenderer>();
	auto& ventMesh = ventEnt.Get<MeshRenderer>();
	auto& panelMesh = panelEnt.Get<MeshRenderer>();
	auto& pipesMesh = pipesEnt.Get<MeshRenderer>();
	auto& pauseMesh = pauseEnt.Get<MeshRenderer>();
	auto& optionMesh = optionEnt.Get<MeshRenderer>();
	auto& retryMesh = retryEnt.Get<MeshRenderer>();
	auto& exitMesh = exitEnt.Get<MeshRenderer>();


	glm::mat4 transform = playerTrans.GetModelMatrix();
	glm::mat4 transformGround = groundTrans.GetModelMatrix();
	glm::mat4 transformLeft = leftTrans.GetModelMatrix();
	glm::mat4 transformRight = rightTrans.GetModelMatrix();
	glm::mat4 transformBack = backTrans.GetModelMatrix();
	glm::mat4 transformDoor = doorTrans.GetModelMatrix();
	glm::mat4 transformDoorClose = doorCloseTrans.GetModelMatrix();
	glm::mat4 transformPipe = pipeTrans.GetModelMatrix();
	glm::mat4 transformButton = buttonTrans.GetModelMatrix();
	glm::mat4 transformButton2 = buttonTrans2.GetModelMatrix();
	glm::mat4 transformWire = wireTrans.GetModelMatrix();
	glm::mat4 transformWire2 = wireTrans2.GetModelMatrix();
	glm::mat4 transformWire3 = wireTrans3.GetModelMatrix();
	glm::mat4 transformGate = gateTrans.GetModelMatrix();
	glm::mat4 transformCoil = coilTrans.GetModelMatrix();
	glm::mat4 transformComplete = completeTrans.GetModelMatrix();
	glm::mat4 transformTut = tutTrans.GetModelMatrix();
	glm::mat4 transformPanel = panelTrans.GetModelMatrix();
	glm::mat4 transformPipes = pipesTrans.GetModelMatrix();
	glm::mat4 transformVent = ventTrans.GetModelMatrix();
	glm::mat4 transformPause = pauseTrans.GetModelMatrix();
	glm::mat4 transformOptions = optionsTrans.GetModelMatrix();
	glm::mat4 transformExit = exitTrans.GetModelMatrix();
	glm::mat4 transformRetry = retryTrans.GetModelMatrix();

	auto& particleSystem = particleEnt.Get<ParticleSystem>();

	if (playerTrans.GetPositionX() - buttonTrans.GetPositionX() < 2.0f && playerTrans.GetPositionX() - buttonTrans.GetPositionX() > -2.0f
		&& playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() > -3.0f)
		button1Watch.Poll(window);

	if (playerTrans.GetPositionX() - buttonTrans2.GetPositionX() < 2.0f && playerTrans.GetPositionX() - buttonTrans2.GetPositionX() > -2.0f
		&& playerTrans.GetPositionZ() - buttonTrans2.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans2.GetPositionZ() > -3.0f)
		button2Watch.Poll(window);

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
			//Bind and render the objects using the animation shader
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

			//Bind and render the objects using the basic shader
			shader->Bind();

			//Floor
			shader->SetUniform("s_Diffuse", 0);
			floorMat.Albedo->Bind(0);
			groundMesh.Render(camera, transformGround);

			//Buttons
			shader->SetUniform("s_Diffuse", 1);
			buttonMat.Albedo->Bind(1);
			buttonMesh.Render(camera, transformButton);
			buttonMesh2.Render(camera, transformButton2);

			//Wires
			shader->SetUniform("s_Diffuse", 2);
			wireMat.Albedo->Bind(2);

			if (wireEnt.Get<Wire>().GetIsPowered())
				wireMeshP.Render(camera, transformWire);
			else
				wireMesh.Render(camera, transformWire);

			if (wireEnt2.Get<Wire>().GetIsPowered())
				wireMeshP2.Render(camera, transformWire2);
			else
				wireMesh2.Render(camera, transformWire2);

			if (wireEnt3.Get<Wire>().GetIsPowered())
				wireMeshP3.Render(camera, transformWire3);
			else
				wireMesh3.Render(camera, transformWire3);


			//Walls
			shader->SetUniform("s_Diffuse", 3);
			wallMat.Albedo->Bind(3);
			leftMesh.Render(camera, transformLeft);
			rightMesh.Render(camera, transformRight);
			backMesh.Render(camera, transformBack); 

			//Gate
			shader->SetUniform("s_Diffuse", 4);
			gateMat.Albedo->Bind(4);
			gateMesh.Render(camera, transformGate);

			ventMesh.Render(camera, transformVent);
			panelMesh.Render(camera, transformPanel);
			pipesMesh.Render(camera, transformPipes);

			untexturedShader->Bind();
			pipeMesh.Render(camera, transformPipe);

			if (wireEnt3.Get<Wire>().GetIsPowered())
				coilMeshP.Render(camera, transformCoil);
			else
				coilMesh.Render(camera, transformCoil);

			tutMesh.Render(camera, transformTut);

			if (!isPaused)
			{
				particleSystem.Update(dt, camera);

				if (!andEnt.Get<AndGate>().GetOutput())
				{
					particleShader->Bind();
					glDisable(GL_DEPTH_TEST);
					particleSystem.Draw(camera, particleShader);
					glEnable(GL_DEPTH_TEST);
				}
			}
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
			pauseMat.Albedo->Bind(0);

			if (isPaused)
			{
				pauseMesh.Render(orthoCam, transformPause);
			}

			shader->Bind();
			shader->SetUniform("s_Diffuse", 0);
			clearMat.Albedo->Bind(0);
			groundMesh.Render(camera, transformGround);

			shader->SetUniform("s_Diffuse", 1);
			clearMat.Albedo->Bind(1);
			buttonMesh.Render(camera, transformButton);
			buttonMesh2.Render(camera, transformButton2);

			shader->SetUniform("s_Diffuse", 2);
			clearMat.Albedo->Bind(2);

			if (wireEnt.Get<Wire>().GetIsPowered())
				wireMeshP.Render(camera, transformWire);
			else
				wireMesh.Render(camera, transformWire);

			if (wireEnt2.Get<Wire>().GetIsPowered())
				wireMeshP2.Render(camera, transformWire2);
			else
				wireMesh2.Render(camera, transformWire2);

			if (wireEnt3.Get<Wire>().GetIsPowered())
				wireMeshP3.Render(camera, transformWire3);
			else
				wireMesh3.Render(camera, transformWire3);

			shader->SetUniform("s_Diffuse", 3);
			clearMat.Albedo->Bind(3);
			leftMesh.Render(camera, transformLeft);
			rightMesh.Render(camera, transformRight);
			backMesh.Render(camera, transformBack); 

			shader->SetUniform("s_Diffuse", 4);
			clearMat.Albedo->Bind(4);
			gateMesh.Render(camera, transformGate);

			ventMesh.Render(camera, transformVent);
			panelMesh.Render(camera, transformPanel);
			pipesMesh.Render(camera, transformPipes);

			untexturedShader->Bind();
			pipeMesh.Render(camera, transformPipe);

			if (wireEnt3.Get<Wire>().GetIsPowered())
				coilMeshP.Render(camera, transformCoil);
			else
				coilMesh.Render(camera, transformCoil);

			tutMesh.Render(camera, transformTut);
			if (!isPaused)
			{
				particleSystem.Update(dt, camera);

				if (!andEnt.Get<AndGate>().GetOutput())
				{
					particleShader->Bind();
					glDisable(GL_DEPTH_TEST);
					particleSystem.Draw(camera, particleShader);
					glEnable(GL_DEPTH_TEST);
				}
			}
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

	leftEnt.Get<AABB>().Update();
	rightEnt.Get<AABB>().Update();
	backEnt.Get<AABB>().Update();
	doorEnt.Get<AABB>().Update();
	andEnt.Get<AABB>().Update();
	coilEnt.Get<AABB>().Update();
	buttonEnt.Get<Lever>().Update();
	buttonEnt2.Get<Lever>().Update();
	wireEnt.Get<Wire>().Update();
	wireEnt2.Get<Wire>().Update();
	wireEnt3.Get<Wire>().Update();
	andEnt.Get<AndGate>().Update();

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

