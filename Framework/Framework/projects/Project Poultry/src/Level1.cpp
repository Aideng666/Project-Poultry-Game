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
	coilEnt = Entity::Create();
	coilPowered = Entity::Create();
	pipeEnt = Entity::Create();
	boxEnt = Entity::Create();
	particleEnt = Entity::Create();
	wirePowered = Entity::Create();
	wirePowered2 = Entity::Create();
	wirePowered3 = Entity::Create();
	UIEnt = Entity::Create();
	tutEnt = Entity::Create();
}

void Level1::InitScene()
{
	Application::SetClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	scene = new entt::registry();

	Entity::SetReg(scene);

	float distance = glm::distance(point2, point1);

	totalTime = distance / speed;

	glm::vec3 lightPos = glm::vec3(0.0f, 9.5f, -35.0f);
	glm::vec3 lightDir = glm::vec3(0.0f, -1.0f, 0.0f);
	glm::vec3 lightCol = glm::vec3(1.f, 1.f, 1.f);
	float     lightAmbientPow = 0.05f;
	float     lightSpecularPow = 1.0f;
	float     lightSpecularPow2 = 0.2f;
	glm::vec3 ambientCol = glm::vec3(1.0f);
	float     ambientPow = 0.1f;
	float     shininess = 16.0f;

#pragma region Shader Stuff

	playerShader = Shader::Create();
	playerShader->LoadShaderPartFromFile("Shaders/morph_shader.glsl", GL_VERTEX_SHADER);
	playerShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	playerShader->Link();

	SetShaderValues(playerShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

	levelShader = Shader::Create();
	levelShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	levelShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	levelShader->Link();

	SetShaderValues(levelShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

	floorShader = Shader::Create();
	floorShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	floorShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	floorShader->Link();

	SetShaderValues(floorShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

	wireShader = Shader::Create();
	wireShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	wireShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	wireShader->Link();

	SetShaderValues(wireShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

	gateShader = Shader::Create();
	gateShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	gateShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	gateShader->Link();

	SetShaderValues(gateShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

	buttonShader = Shader::Create();
	buttonShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	buttonShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	buttonShader->Link();

	SetShaderValues(buttonShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

	doorShader = Shader::Create();
	doorShader->LoadShaderPartFromFile("Shaders/morph_shader.glsl", GL_VERTEX_SHADER);
	doorShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	doorShader->Link();

	SetShaderValues(doorShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

	particleShader = Shader::Create();
	particleShader->LoadShaderPartFromFile("Shaders/particle_vertex.glsl", GL_VERTEX_SHADER);
	particleShader->LoadShaderPartFromFile("Shaders/particle_geom.glsl", GL_GEOMETRY_SHADER);
	particleShader->LoadShaderPartFromFile("Shaders/particle_frag.glsl", GL_FRAGMENT_SHADER);
	particleShader->Link();

	untexturedShader = Shader::Create();
	untexturedShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	untexturedShader->LoadShaderPartFromFile("Shaders/frag_untextured.glsl", GL_FRAGMENT_SHADER);
	untexturedShader->Link();

	SetShaderValues(untexturedShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

	uiShader = Shader::Create();
	uiShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	uiShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	uiShader->Link();

	SetShaderValues(uiShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

#pragma endregion

#pragma region Texture Stuff
	Texture2DData::sptr buttonMap = Texture2DData::LoadFromFile("Textures/ButtonTexture.png");
	Texture2DData::sptr drumstickMap = Texture2DData::LoadFromFile("Textures/DrumstickTexture.png");
	Texture2DData::sptr doorMap = Texture2DData::LoadFromFile("Textures/DoorTexture.png");
	Texture2DData::sptr floorMap = Texture2DData::LoadFromFile("Textures/FloorTexture.jpg");
	Texture2DData::sptr wallMap = Texture2DData::LoadFromFile("Textures/WallTexture.jpg");
	Texture2DData::sptr wireMap = Texture2DData::LoadFromFile("Textures/WireTexture.png");
	Texture2DData::sptr uiMap = Texture2DData::LoadFromFile("Textures/Buttons/Default/Option.png");

	Texture2D::sptr diffuseButton = Texture2D::Create();
	diffuseButton->LoadData(buttonMap);

	Texture2D::sptr diffuseDrum = Texture2D::Create();
	diffuseDrum->LoadData(drumstickMap);

	Texture2D::sptr diffuseDoor = Texture2D::Create();
	diffuseDoor->LoadData(doorMap);

	Texture2D::sptr diffuseFloor = Texture2D::Create();
	diffuseFloor->LoadData(floorMap);

	Texture2D::sptr diffuseWall = Texture2D::Create();
	diffuseWall->LoadData(wallMap);

	Texture2D::sptr diffuseWire = Texture2D::Create();
	diffuseWire->LoadData(wireMap);

	Texture2D::sptr diffuseUI = Texture2D::Create();
	diffuseUI->LoadData(uiMap);

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
	uiMat.Albedo = diffuseUI;

#pragma endregion


	//Transforms
	auto& particleTrans = particleEnt.Add<Transform>();
	particleTrans.SetPosition(glm::vec3(0.0f, 4.0f, -2.0f));

	auto& playerTrans = mainPlayer.Add<Transform>();
	playerTrans.SetPosition(glm::vec3(0.0f, 1.0f, 30.0f));
	playerTrans.SetRotationY(0.0f);

	auto& uiTrans = UIEnt.Add<Transform>();
	uiTrans.SetPosition(glm::vec3(8.0f, 8.0f, 0.0f));
	uiTrans.SetRotationY(50.0f);

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
	doorTrans.SetPosition(glm::vec3(-5.0f, 1.0f, -36.0f));
	doorTrans.SetScale(glm::vec3(1.5f));

	auto& pipeTrans = pipeEnt.Add<Transform>();
	pipeTrans.SetPositionX(-35.5f);
	pipeTrans.SetPositionY(10.5f);

	auto& gateTrans = andEnt.Add<Transform>();
	gateTrans.SetPosition(glm::vec3(0.0f, 1.0f, -2.0f));
	gateTrans.SetRotationY(-90.0f);

	auto& coilTrans = coilEnt.Add<Transform>();
	coilTrans.SetPosition(glm::vec3(-15.0f, 2.0f, -36.0f));
	coilTrans.SetRotationY(180.0f);


	//AABB
	auto& leftCol = leftEnt.Add<AABB>(leftEnt, mainPlayer);
	auto& rightCol = rightEnt.Add<AABB>(rightEnt, mainPlayer);
	auto& backCol = backEnt.Add<AABB>(backEnt, mainPlayer);
	auto& gateCol = andEnt.Add<AABB>(andEnt, mainPlayer);
	auto& coilCol = coilEnt.Add<AABB>(coilEnt, mainPlayer);
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

	Mesh drumstick("Models/ChickenFrames/Walk1.obj");
	Mesh floor("Models/Floor.obj");
	Mesh wall("Models/Wall.obj");
	Mesh doorM("Models/DoorFrames/Door0.obj");
	Mesh pipe("Models/Level1Pipe.obj", glm::vec3(0.6f, 0.45f, 0.0f));
	Mesh buttonM("Models/Button.obj");
	Mesh wireL("Models/LeftWire.obj", glm::vec3(1.0f, 0.0f, 0.0f));
	Mesh wireR("Models/RightWire.obj", glm::vec3(1.0f, 0.0f, 0.0f));
	Mesh wireC("Models/CoilWire.obj", glm::vec3(1.0f, 0.0f, 0.0f));
	Mesh wireLPower("Models/LeftWire.obj", glm::vec3(0.0f, 1.0f, 0.0f));
	Mesh wireRPower("Models/RightWire.obj", glm::vec3(0.0f, 1.0f, 0.0f));
	Mesh wireCPower("Models/CoilWire.obj", glm::vec3(0.0f, 1.0f, 0.0f));
	Mesh gate("Models/AndGate.obj", glm::vec3(0.0f, 0.0f, 1.0f));
	Mesh coil("Models/Coil.obj", glm::vec3(1.0f, 0.0f, 0.0f));
	Mesh coilP("Models/Coil.obj", glm::vec3(0.0f, 1.0f, 0.0f));
	Mesh ui("Models/UI_Button.obj");
	Mesh tut("Models/Interact.obj", glm::vec3(1.0f, 0.0f, 0.0f));

	door0 = std::make_unique<Mesh>("Models/DoorFrames/Door0.obj");
	door1 = std::make_unique<Mesh>("Models/DoorFrames/Door1.obj");
	door2 = std::make_unique<Mesh>("Models/DoorFrames/Door2.obj");
	door3 = std::make_unique<Mesh>("Models/DoorFrames/Door3.obj");
	door4 = std::make_unique<Mesh>("Models/DoorFrames/Door4.obj");
	door5 = std::make_unique<Mesh>("Models/DoorFrames/Door5.obj");
	door6 = std::make_unique<Mesh>("Models/DoorFrames/Door6.obj");
	door7 = std::make_unique<Mesh>("Models/DoorFrames/Door7.obj");
	door8 = std::make_unique<Mesh>("Models/DoorFrames/Door8.obj");
	door9 = std::make_unique<Mesh>("Models/DoorFrames/Door9.obj");
	door10 = std::make_unique<Mesh>("Models/DoorFrames/Door10.obj");
	
	doorFrames.push_back(std::move(door0));
	doorFrames.push_back(std::move(door1));
	doorFrames.push_back(std::move(door2));
	doorFrames.push_back(std::move(door3));
	doorFrames.push_back(std::move(door4));
	doorFrames.push_back(std::move(door5));
	doorFrames.push_back(std::move(door6));
	doorFrames.push_back(std::move(door7));
	doorFrames.push_back(std::move(door8));
	doorFrames.push_back(std::move(door9));
	doorFrames.push_back(std::move(door10));

	walk1 = std::make_unique<Mesh>("Models/ChickenFrames/Walk1.obj");
	walk2 = std::make_unique<Mesh>("Models/ChickenFrames/Walk2.obj");
	walk3 = std::make_unique<Mesh>("Models/ChickenFrames/Walk3.obj");
	walk4 = std::make_unique<Mesh>("Models/ChickenFrames/Walk4.obj");
	walk5 = std::make_unique<Mesh>("Models/ChickenFrames/Walk5.obj");
	walk6 = std::make_unique<Mesh>("Models/ChickenFrames/Walk6.obj");
	walk7 = std::make_unique<Mesh>("Models/ChickenFrames/Walk7.obj");
	walk8 = std::make_unique<Mesh>("Models/ChickenFrames/Walk8.obj");
	walk9 = std::make_unique<Mesh>("Models/ChickenFrames/Walk9.obj");
	walk10 = std::make_unique<Mesh>("Models/ChickenFrames/Walk10.obj");
	walk11 = std::make_unique<Mesh>("Models/ChickenFrames/Walk11.obj");
	walk12 = std::make_unique<Mesh>("Models/ChickenFrames/Walk12.obj");
	walk13 = std::make_unique<Mesh>("Models/ChickenFrames/Walk13.obj");
	walk14 = std::make_unique<Mesh>("Models/ChickenFrames/Walk14.obj");

	walkFrames.push_back(std::move(walk1));
	walkFrames.push_back(std::move(walk2));
	walkFrames.push_back(std::move(walk3));
	walkFrames.push_back(std::move(walk4));
	walkFrames.push_back(std::move(walk5));
	walkFrames.push_back(std::move(walk6));
	walkFrames.push_back(std::move(walk7));
	walkFrames.push_back(std::move(walk8));
	walkFrames.push_back(std::move(walk9));
	walkFrames.push_back(std::move(walk10));
	walkFrames.push_back(std::move(walk11));
	walkFrames.push_back(std::move(walk12));
	walkFrames.push_back(std::move(walk13));
	walkFrames.push_back(std::move(walk14));

	auto& playerMesh = mainPlayer.Add<MorphRenderer>(mainPlayer, drumstick, playerShader);
	auto& floorMesh = floorEnt.Add<MeshRenderer>(floorEnt, floor, floorShader);
	auto& leftMesh = leftEnt.Add<MeshRenderer>(leftEnt, wall, levelShader);
	auto& rightMesh = rightEnt.Add<MeshRenderer>(rightEnt, wall, levelShader);
	auto& backMesh = backEnt.Add<MeshRenderer>(backEnt, wall, levelShader);
	auto& gateMesh = andEnt.Add<MeshRenderer>(andEnt, gate, untexturedShader);
	auto& buttonMesh = buttonEnt.Add<MeshRenderer>(buttonEnt, buttonM, buttonShader);
	auto& buttonMesh2 = buttonEnt2.Add<MeshRenderer>(buttonEnt2, buttonM, buttonShader);
	auto& wireMesh = wireEnt.Add<MeshRenderer>(wireEnt, wireL, wireShader);
	auto& wireMesh2 = wireEnt2.Add<MeshRenderer>(wireEnt2, wireR, wireShader);
	auto& wireMesh3 = wireEnt3.Add<MeshRenderer>(wireEnt3, wireC, wireShader);
	auto& wireMeshP = wirePowered.Add<MeshRenderer>(wirePowered, wireLPower, wireShader);
	auto& wireMeshP2 = wirePowered2.Add<MeshRenderer>(wirePowered2, wireRPower, wireShader);
	auto& wireMeshP3 = wirePowered3.Add<MeshRenderer>(wirePowered3, wireCPower, wireShader);
	auto& doorMesh = doorEnt.Add<MorphRenderer>(doorEnt, doorM, doorShader);
	auto& pipeMesh = pipeEnt.Add<MeshRenderer>(pipeEnt, pipe, untexturedShader);
	auto& coilMesh = coilEnt.Add<MeshRenderer>(coilEnt, coil, untexturedShader);
	auto& coilMeshP = coilPowered.Add<MeshRenderer>(coilPowered, coilP, untexturedShader);
	auto& uiMesh = UIEnt.Add<MeshRenderer>(UIEnt, ui, uiShader);
	auto& tutMesh = tutEnt.Add<MeshRenderer>(tutEnt, tut, untexturedShader);

	auto& doorAnimator = doorEnt.Add<MorphAnimation>(doorEnt);
	doorAnimator.SetTime(0.2f);
	doorAnimator.SetFrames(doorFrames);
	doorAnimator.SetLoop(false);

	auto& walkAnimator = mainPlayer.Add<MorphAnimation>(mainPlayer);
	walkAnimator.SetTime(0.05f);
	walkAnimator.SetFrames(walkFrames);

	auto& camera = camEnt.Add<Camera>();

	camera.SetPosition(glm::vec3(0, 15, mainPlayer.Get<Transform>().GetPositionZ() + 12)); // Set initial position
	camera.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
	camera.LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camera.SetFovDegrees(90.0f); // Set an initial FOV

	auto& uiCam = uiCamEnt.Add<Camera>();
	uiCam.SetIsOrtho(true);
	uiCam.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	uiCam.SetForward(glm::vec3(0.0f, 0.0f, -1.0f));
	uiCam.SetUp(glm::vec3(0.0f, 1.0f, 0.0f));

}

void Level1::Update(float dt)
{

	time += dt;
	playerShader->SetUniform("u_Time", time);
	levelShader->SetUniform("u_Time", time);
	floorShader->SetUniform("u_Time", time);
	gateShader->SetUniform("u_Time", time);
	wireShader->SetUniform("u_Time", time);
	buttonShader->SetUniform("u_Time", time);
	doorShader->SetUniform("u_Time", time);
	untexturedShader->SetUniform("u_Time", time);
	uiShader->SetUniform("u_Time", time);

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

	playerShader->SetUniform("u_Position", currentPos);
	levelShader->SetUniform("u_Position", currentPos);
	floorShader->SetUniform("u_Position", currentPos);
	gateShader->SetUniform("u_Position", currentPos);
	wireShader->SetUniform("u_Position", currentPos);
	doorShader->SetUniform("u_Position", currentPos);
	buttonShader->SetUniform("u_Position", currentPos);
	untexturedShader->SetUniform("u_Position", currentPos);
	uiShader->SetUniform("u_Position", currentPos);

	//Transforms
	auto& playerTrans = mainPlayer.Get<Transform>();
	auto& groundTrans = floorEnt.Get<Transform>();
	auto& leftTrans = leftEnt.Get<Transform>();
	auto& rightTrans = rightEnt.Get<Transform>();
	auto& backTrans = backEnt.Get<Transform>();
	auto& doorTrans = doorEnt.Get<Transform>();
	auto& pipeTrans = pipeEnt.Get<Transform>();
	auto& buttonTrans = buttonEnt.Get<Transform>();
	auto& buttonTrans2 = buttonEnt2.Get<Transform>();
	auto& wireTrans = wireEnt.Get<Transform>();
	auto& wireTrans2 = wireEnt2.Get<Transform>();
	auto& wireTrans3 = wireEnt3.Get<Transform>();
	auto& gateTrans = andEnt.Get<Transform>();
	auto& coilTrans = coilEnt.Get<Transform>();
	auto& uiTrans = UIEnt.Get<Transform>();
	auto& tutTrans =tutEnt.Get<Transform>();
	
	backTrans.SetPositionZ(-39.0f);
	backTrans.SetPositionY(9.0f);

	leftTrans.SetPositionX(-39.0f);
	leftTrans.SetRotationY(90.0f);
	leftTrans.SetPositionY(9.0f);

	rightTrans.SetPositionX(39.0f);
	rightTrans.SetRotationY(90.0f);
	rightTrans.SetPositionY(9.0f);

	uiTrans.SetRotationY(uiTrans.GetRotation().y + 10.0f * dt);

	auto& camera = camEnt.Get<Camera>();
	auto& uiCamera = uiCamEnt.Get<Camera>();


	auto& meshMain = mainPlayer.Get<MorphRenderer>();
	auto& groundMesh = floorEnt.Get<MeshRenderer>();
	auto& leftMesh = leftEnt.Get<MeshRenderer>();
	auto& rightMesh = rightEnt.Get<MeshRenderer>();
	auto& backMesh = backEnt.Get<MeshRenderer>();
	auto& doorMesh = doorEnt.Get<MorphRenderer>();
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
	auto& uiMesh = UIEnt.Get<MeshRenderer>();
	auto& tutMesh = tutEnt.Get<MeshRenderer>();

	camera.LookAt(glm::vec3(playerTrans.GetPosition()));

	glm::mat4 transform = playerTrans.GetModelMatrix();
	glm::mat4 transformGround = groundTrans.GetModelMatrix();
	glm::mat4 transformLeft = leftTrans.GetModelMatrix();
	glm::mat4 transformRight = rightTrans.GetModelMatrix();
	glm::mat4 transformBack = backTrans.GetModelMatrix();
	glm::mat4 transformDoor = doorTrans.GetModelMatrix();
	glm::mat4 transformPipe = pipeTrans.GetModelMatrix();
	glm::mat4 transformButton = buttonTrans.GetModelMatrix();
	glm::mat4 transformButton2 = buttonTrans2.GetModelMatrix();
	glm::mat4 transformWire = wireTrans.GetModelMatrix();
	glm::mat4 transformWire2 = wireTrans2.GetModelMatrix();
	glm::mat4 transformWire3 = wireTrans3.GetModelMatrix();
	glm::mat4 transformGate = gateTrans.GetModelMatrix();
	glm::mat4 transformCoil = coilTrans.GetModelMatrix();
	glm::mat4 transformUI = uiTrans.GetModelMatrix();
	glm::mat4 transformTut = tutTrans.GetModelMatrix();

	auto& particleSystem = particleEnt.Get<ParticleSystem>();

	if (playerTrans.GetPositionX() - buttonTrans.GetPositionX() < 2.0f && playerTrans.GetPositionX() - buttonTrans.GetPositionX() > -2.0f
		&& playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() > -3.0f)
		button1Watch.Poll(window);

	if (playerTrans.GetPositionX() - buttonTrans2.GetPositionX() < 2.0f && playerTrans.GetPositionX() - buttonTrans2.GetPositionX() > -2.0f
		&& playerTrans.GetPositionZ() - buttonTrans2.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans2.GetPositionZ() > -3.0f)
		button2Watch.Poll(window);



#pragma region PlayerMovement
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{

		playerTrans.SetRotationY(225.0f);

		playerTrans.SetPositionX(playerTrans.GetPositionX() - 10 * dt);
		playerTrans.SetPositionZ(playerTrans.GetPositionZ() - 10 * dt);

		camera.SetPosition(glm::vec3(playerTrans.GetPositionX(), camera.GetPosition().y, camera.GetPosition().z));

		if (camFar)
			camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z - 10 * dt));

		mainPlayer.Get<MorphAnimation>().Update(dt);
	} 

	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{

		playerTrans.SetRotationY(315.0f);

		playerTrans.SetPositionX(playerTrans.GetPositionX() - 10 * dt);
		playerTrans.SetPositionZ(playerTrans.GetPositionZ() + 10 * dt);

		camera.SetPosition(glm::vec3(playerTrans.GetPositionX(), camera.GetPosition().y, camera.GetPosition().z));

		if (camClose)
			camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z + 10 * dt));

		mainPlayer.Get<MorphAnimation>().Update(dt);
	}

	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{

		playerTrans.SetRotationY(45.0f);

		playerTrans.SetPositionX(playerTrans.GetPositionX() + 10 * dt);
		playerTrans.SetPositionZ(playerTrans.GetPositionZ() + 10 * dt);

		camera.SetPosition(glm::vec3(playerTrans.GetPositionX(), camera.GetPosition().y, camera.GetPosition().z));

		if (camClose)
			camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z + 10 * dt));

		mainPlayer.Get<MorphAnimation>().Update(dt);
	}

	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{

		playerTrans.SetRotationY(135.0f);

		playerTrans.SetPositionX(playerTrans.GetPositionX() + 10 * dt);
		playerTrans.SetPositionZ(playerTrans.GetPositionZ() - 10 * dt);

		camera.SetPosition(glm::vec3(playerTrans.GetPositionX(), camera.GetPosition().y, camera.GetPosition().z));

		if (camFar)
			camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z - 10 * dt));

		mainPlayer.Get<MorphAnimation>().Update(dt);
	}

	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{

		if (playerTrans.GetCanMoveLeft())
		{
			playerTrans.SetPositionX(playerTrans.GetPositionX() - 10 * dt);
			playerTrans.SetRotationY(270.0f);
			camera.SetPosition(glm::vec3(playerTrans.GetPositionX(), camera.GetPosition().y, camera.GetPosition().z));

			mainPlayer.Get<MorphAnimation>().Update(dt);
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{

		if (playerTrans.GetCanMoveRight())
		{
			playerTrans.SetPositionX(playerTrans.GetPositionX() + 10 * dt);
			playerTrans.SetRotationY(90.0f);
			camera.SetPosition(glm::vec3(playerTrans.GetPositionX(), camera.GetPosition().y, camera.GetPosition().z));

			mainPlayer.Get<MorphAnimation>().Update(dt);
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{

		if (playerTrans.GetCanMoveUp())
		{
			playerTrans.SetPositionZ(playerTrans.GetPositionZ() - 10 * dt);
			playerTrans.SetRotationY(180.0f);

			if (camFar)
				camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z - 10 * dt));

			mainPlayer.Get<MorphAnimation>().Update(dt);
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{

		if (playerTrans.GetCanMoveDown())
		{
			playerTrans.SetPositionZ(playerTrans.GetPositionZ() + 10 * dt);
			playerTrans.SetRotationY(0.0f);

			if (camClose)
				camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z + 10 * dt));

			mainPlayer.Get<MorphAnimation>().Update(dt);
		}
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

	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	{
		camera.SetPosition(glm::vec3(camera.GetPosition().x - 10 * dt, camera.GetPosition().y, camera.GetPosition().z));
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		camera.SetPosition(glm::vec3(camera.GetPosition().x + 10 * dt, camera.GetPosition().y, camera.GetPosition().z));
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z - 10 * dt));
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z + 10 * dt));
	}
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
	{
		camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y + 10 * dt, camera.GetPosition().z));
	}
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
	{
		camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y - 10 * dt, camera.GetPosition().z));
	}
#pragma endregion

#pragma region Renders

	playerShader->Bind();
	playerShader->SetUniform("s_Diffuse", 0);
	drumstickMat.Albedo->Bind(0);
	meshMain.Render(camera, transform);

	levelShader->Bind();
	levelShader->SetUniform("s_Diffuse", 0);
	wallMat.Albedo->Bind(0);
	leftMesh.Render(camera, transformLeft);
	rightMesh.Render(camera, transformRight);
	backMesh.Render(camera, transformBack);

	floorShader->Bind();
	floorShader->SetUniform("s_Diffuse", 0);
	floorMat.Albedo->Bind(0);
	groundMesh.Render(camera, transformGround);

	doorShader->Bind();
	doorShader->SetUniform("s_Diffuse", 0);
	doorMat.Albedo->Bind(0);
	doorMesh.Render(camera, transformDoor);
	doorMat.Albedo->UnBind(0);

	untexturedShader->Bind();
	pipeMesh.Render(camera, transformPipe);

	if (wireEnt3.Get<Wire>().GetIsPowered())
		coilMeshP.Render(camera, transformCoil);
	else
		coilMesh.Render(camera, transformCoil);

	gateMesh.Render(camera, transformGate);
	tutMesh.Render(camera, transformTut);

	wireShader->Bind();
	wireShader->SetUniform("s_Diffuse", 0);
	wireMat.Albedo->Bind(0);

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

	buttonShader->Bind();
	buttonShader->SetUniform("s_Diffuse", 0);
	buttonMat.Albedo->Bind(0);
	buttonMesh.Render(camera, transformButton);
	buttonMesh2.Render(camera, transformButton2);

	uiShader->Bind();
	uiShader->SetUniform("s_Diffuse", 0);
	uiMat.Albedo->Bind(0);
	uiMesh.Render(uiCamera, transformUI);

	particleSystem.Update(dt, camera);

	if (!andEnt.Get<AndGate>().GetOutput())
	{
		particleShader->Bind();
		glDisable(GL_DEPTH_TEST);
		particleSystem.Draw(camera, particleShader);
		glEnable(GL_DEPTH_TEST);
	}
#pragma endregion

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
		doorEnt.Get<MorphAnimation>().Update(dt);

	if (doorEnt.Get<AABB>().GetComplete())
		levelComplete = true;
}

void Level1::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}

