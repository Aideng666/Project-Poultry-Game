#include "Level4.h"
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

Level4::Level4(std::string sceneName, GLFWwindow* wind)
	: Scene(sceneName, wind)
{
#pragma region Entities
	mainPlayer = Entity::Create();
	floorEnt = Entity::Create();
	leftEnt = Entity::Create();
	rightEnt = Entity::Create();
	backEnt = Entity::Create();
	doorEnt = Entity::Create();
	buttonEnt = Entity::Create();
	buttonEnt2 = Entity::Create();
	buttonEnt3 = Entity::Create();
	buttonEnt4 = Entity::Create();
	colPipeEnt = Entity::Create();
	colPipeEnt2 = Entity::Create();
	shelfPipeEnt = Entity::Create();
	shelfPipeEnt2 = Entity::Create();
	shelfPipeEnt3 = Entity::Create();
	panelEnt = Entity::Create();
	panelEnt2 = Entity::Create();
	ventEntL = Entity::Create();
	ventEntS = Entity::Create();
	andEnt = Entity::Create();
	andEnt2 = Entity::Create();
	andEnt3 = Entity::Create();
	notEnt = Entity::Create();
	notEnt2 = Entity::Create();
	notEnt3 = Entity::Create();
	coilEnt = Entity::Create();

	wireEnt = Entity::Create();
	wireEnt2 = Entity::Create();
	wireEnt3 = Entity::Create();
	wireEnt4 = Entity::Create();
	wireEnt5 = Entity::Create();
	wireEnt6 = Entity::Create();
	wireEnt7 = Entity::Create();
	wireEnt8 = Entity::Create();
	wireEnt9 = Entity::Create();
	wireEnt10 = Entity::Create();

	FBO = Entity::Create();
	greyscaleEnt = Entity::Create();
	sepiaEnt = Entity::Create();
	colorCorrectEnt = Entity::Create();

	filmGrainEnt = Entity::Create();
	pixelateEnt = Entity::Create();
	bloomEnt = Entity::Create();
#pragma endregion

	InitMeshes();
}

void Level4::InitScene()
{
	Application::SetClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	scene = new entt::registry();

	Entity::SetReg(scene);

	//Initialize the shaders for the level
	InitShaders();
	//Initialize the Textures for the level
	InitTextures();

#pragma region Transforms
	//Player transform
	auto& playerTrans = mainPlayer.Add<Transform>();
	playerTrans.SetPosition(glm::vec3(0.0f, 1.0f, 42.0f));
	playerTrans.SetRotationY(180.0f);

	//Floor transform
	auto& groundTrans = floorEnt.Add<Transform>();
	groundTrans.SetPositionY(1.0f);

	//Wall transforms
	auto& leftTrans = leftEnt.Add<Transform>();
	auto& rightTrans = rightEnt.Add<Transform>();
	auto& backTrans = backEnt.Add<Transform>();

	//Door transforms
	auto& doorTrans = doorEnt.Add<Transform>();
	doorTrans.SetPosition(glm::vec3(0.0f, -1.0f, -50.0f));
	doorTrans.SetScale(glm::vec3(1.5f));

	//Button transforms
	auto& buttonTrans = buttonEnt.Add<Transform>();
	buttonTrans.SetPosition(glm::vec3(24.8f, -1.0f, 35.f));

	auto& buttonTrans2 = buttonEnt2.Add<Transform>();
	buttonTrans2.SetPosition(glm::vec3(3.5f, -1.0f, 35.f));

	auto& buttonTrans3 = buttonEnt3.Add<Transform>();
	buttonTrans3.SetPosition(glm::vec3(-5.f, -1.0f, 35.f));

	auto& buttonTrans4 = buttonEnt4.Add<Transform>();
	buttonTrans4.SetPosition(glm::vec3(-20.2f, -1.0f, 35.5f));

	//Column Pipe transforms
	auto& colPipeTrans = colPipeEnt.Add<Transform>();
	colPipeTrans.SetPosition(glm::vec3(32.f, 1.f, -48.f));
	colPipeTrans.SetRotationY(90.f);
	colPipeTrans.SetScale(glm::vec3(1.5f));

	auto& colPipeTrans2 = colPipeEnt2.Add<Transform>();
	colPipeTrans2.SetPosition(glm::vec3(-32.f, 1.f, -48.f));
	colPipeTrans2.SetRotationY(90.f);
	colPipeTrans2.SetScale(glm::vec3(1.5f));

	//Shelf Pipe transforms
	auto& shelfPipeTrans = shelfPipeEnt.Add<Transform>();
	shelfPipeTrans.SetPosition(glm::vec3(46.5f, 17.f, 0.f));
	shelfPipeTrans.SetRotationY(180.f);
	shelfPipeTrans.SetScale(glm::vec3(1.5f));

	auto& shelfPipeTrans2 = shelfPipeEnt2.Add<Transform>();
	shelfPipeTrans2.SetPosition(glm::vec3(-46.5f, 17.f, -20.f));
	shelfPipeTrans2.SetScale(glm::vec3(1.5f));

	auto& shelfPipeTrans3 = shelfPipeEnt3.Add<Transform>();
	shelfPipeTrans3.SetPosition(glm::vec3(-46.5f, 17.f, 20.f));
	shelfPipeTrans3.SetScale(glm::vec3(1.5f));

	//Panel transforms
	auto& panelTrans = panelEnt.Add<Transform>();
	panelTrans.SetScale(glm::vec3(4.0f));
	panelTrans.SetPosition(glm::vec3(-51.f, 7.0f, 4.f));

	auto& panelTrans2 = panelEnt2.Add<Transform>();
	panelTrans2.SetScale(glm::vec3(4.0f));
	panelTrans2.SetPosition(glm::vec3(-51.f, 7.0f, 12.f));

	//Vent transforms
	auto& ventTrans = ventEntL.Add<Transform>();
	ventTrans.SetPosition(glm::vec3(50.5f, 25.f, -17.f));
	ventTrans.SetScale(glm::vec3(1.2f));

	auto& ventTrans2 = ventEntS.Add<Transform>();
	ventTrans2.SetPosition(glm::vec3(50.8f, 25.f, 20.f));
	ventTrans2.SetScale(glm::vec3(1.2f));
	ventTrans2.SetRotationZ(180.f);

	//Gate transforms
	//And Gate
	auto& gateTrans = andEnt.Add<Transform>();
	gateTrans.SetPosition(glm::vec3(0.f, 1.2f, 0.f));
	gateTrans.SetRotationY(-90.0f);
	gateTrans.SetScale(glm::vec3(2.0f));

	auto& gateTrans2 = andEnt2.Add<Transform>();
	gateTrans2.SetPosition(glm::vec3(10.f, 1.2f, 0.f));
	gateTrans2.SetRotationY(-90.0f);
	gateTrans2.SetScale(glm::vec3(2.0f));

	auto& gateTrans3 = andEnt3.Add<Transform>();
	gateTrans3.SetPosition(glm::vec3(-10.f, 1.2f, 0.f));
	gateTrans3.SetRotationY(-90.0f);
	gateTrans3.SetScale(glm::vec3(2.0f));

	//Not Gate
	auto& notTrans = notEnt.Add<Transform>();
	notTrans.SetPosition(glm::vec3(0.0f, 1.f, -10.f));
	notTrans.SetRotationY(-90.0f);
	notTrans.SetScale(glm::vec3(2.0f));

	auto& notTrans2 = notEnt2.Add<Transform>();
	notTrans2.SetPosition(glm::vec3(10.0f, 1.f, -10.f));
	notTrans2.SetRotationY(-90.0f);
	notTrans2.SetScale(glm::vec3(2.0f));

	auto& notTrans3 = notEnt3.Add<Transform>();
	notTrans3.SetPosition(glm::vec3(-10.0f, 1.f, -10.f));
	notTrans3.SetRotationY(-90.0f);
	notTrans3.SetScale(glm::vec3(2.0f));

	//Coil Object
	auto& coilTrans = coilEnt.Add<Transform>();
	coilTrans.SetPosition(glm::vec3(-13.0f, 1.0f, -48.f));
	coilTrans.SetScale(glm::vec3(3.0f));
	coilTrans.SetRotationY(180.0f);

	//Wire Objects
	auto& wireTrans = wireEnt.Add<Transform>();
	wireTrans.SetPosition(glm::vec3(0.f, 1.f, 0.f));

	auto& wireTrans2 = wireEnt2.Add<Transform>();
	wireTrans2.SetPosition(glm::vec3(0.f, 1.f, 0.f));

	auto& wireTrans3 = wireEnt3.Add<Transform>();
	wireTrans3.SetPosition(glm::vec3(0.f, 1.f, 0.f));

	auto& wireTrans4 = wireEnt4.Add<Transform>();
	wireTrans4.SetPosition(glm::vec3(0.f, 1.f, 0.f));

	auto& wireTrans5 = wireEnt5.Add<Transform>();
	wireTrans5.SetPosition(glm::vec3(0.f, 1.f, 0.f));

	auto& wireTrans6 = wireEnt6.Add<Transform>();
	wireTrans6.SetPosition(glm::vec3(0.f, 1.f, 0.f));

	auto& wireTrans7 = wireEnt7.Add<Transform>();
	wireTrans7.SetPosition(glm::vec3(0.f, 1.f, 0.f));

	auto& wireTrans8 = wireEnt8.Add<Transform>();
	wireTrans8.SetPosition(glm::vec3(0.f, 1.f, 0.f));

	auto& wireTrans9 = wireEnt9.Add<Transform>();
	wireTrans9.SetPosition(glm::vec3(0.f, 1.f, 0.f));

	auto& wireTrans10 = wireEnt10.Add<Transform>();
	wireTrans10.SetPosition(glm::vec3(0.f, 1.f, 0.f));

#pragma endregion
	
	//AABB
	//auto& leftCol = leftEnt.Add<AABB>(leftEnt, mainPlayer);
	//auto& rightCol = rightEnt.Add<AABB>(rightEnt, mainPlayer);
	//auto& backCol = backEnt.Add<AABB>(backEnt, mainPlayer);

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
	auto& floorMesh = floorEnt.Add<MeshRenderer>(floorEnt, *floorL4, untexturedShader);
	auto& leftMesh = leftEnt.Add<MeshRenderer>(leftEnt, *leftWallL4, untexturedShader);
	auto& rightMesh = rightEnt.Add<MeshRenderer>(rightEnt, *rightWallL4, untexturedShader);
	auto& backMesh = backEnt.Add<MeshRenderer>(backEnt, *backWallL4, untexturedShader);
	auto& doorMesh = doorEnt.Add<MorphRenderer>(doorEnt, *doorM, animShader);
	auto& buttonMesh = buttonEnt.Add<MeshRenderer>(buttonEnt, *buttonM, shader);
	auto& buttonMesh2 = buttonEnt2.Add<MeshRenderer>(buttonEnt2, *buttonM, shader);
	auto& buttonMesh3 = buttonEnt3.Add<MeshRenderer>(buttonEnt3, *buttonM, shader);
	auto& buttonMesh4 = buttonEnt4.Add<MeshRenderer>(buttonEnt4, *buttonM, shader);
	auto& colPipeMesh = colPipeEnt.Add<MeshRenderer>(colPipeEnt, *columnPipe, shader);
	auto& colPipeMesh2 = colPipeEnt2.Add<MeshRenderer>(colPipeEnt2, *columnPipe, shader);
	auto& shelfPipeMesh = shelfPipeEnt.Add<MeshRenderer>(shelfPipeEnt, *shelfPipe, shader);
	auto& shelfPipeMesh2 = shelfPipeEnt2.Add<MeshRenderer>(shelfPipeEnt2, *shelfPipe, shader);
	auto& shelfPipeMesh3 = shelfPipeEnt3.Add<MeshRenderer>(shelfPipeEnt3, *shelfPipe, shader);
	auto& panelMesh = panelEnt.Add<MeshRenderer>(panelEnt, *panel, shader);
	auto& panelMesh2 = panelEnt2.Add<MeshRenderer>(panelEnt2, *panel, shader);
	auto& vent = ventEntL.Add<MeshRenderer>(ventEntL, *ventB, shader);
	auto& vent2 = ventEntS.Add<MeshRenderer>(ventEntS, *ventS, shader);

	auto& gateMesh = andEnt.Add<MeshRenderer>(andEnt, *and, shader);
	auto& gateMesh2 = andEnt2.Add<MeshRenderer>(andEnt2, *and, shader);
	auto& gateMesh3 = andEnt3.Add<MeshRenderer>(andEnt3, *and, shader);

	auto& notMesh = notEnt.Add<MeshRenderer>(notEnt, *not, shader);
	auto& notMesh2 = notEnt2.Add<MeshRenderer>(notEnt2, *not, shader);
	auto& notMesh3 = notEnt3.Add<MeshRenderer>(notEnt3, *not, shader);

	auto& coilMesh = coilEnt.Add<MeshRenderer>(coilEnt, *coil, shader);

	auto& wireMesh = wireEnt.Add<MeshRenderer>(wireEnt, *wireM1L4, shader);
	auto& wireMesh2 = wireEnt2.Add<MeshRenderer>(wireEnt2, *wireM2L4, shader);
	auto& wireMesh3 = wireEnt3.Add<MeshRenderer>(wireEnt3, *wireM3L4, shader);
	auto& wireMesh4 = wireEnt4.Add<MeshRenderer>(wireEnt4, *wireM4L4, shader);
	auto& wireMesh5 = wireEnt5.Add<MeshRenderer>(wireEnt5, *wireM5L4, shader);
	auto& wireMesh6 = wireEnt6.Add<MeshRenderer>(wireEnt6, *wireM6L4, shader);
	auto& wireMesh7 = wireEnt7.Add<MeshRenderer>(wireEnt7, *wireM7L4, shader);
	auto& wireMesh8 = wireEnt8.Add<MeshRenderer>(wireEnt8, *wireM8L4, shader);
	auto& wireMesh9 = wireEnt9.Add<MeshRenderer>(wireEnt9, *wireM9L4, shader);
	auto& wireMesh10 = wireEnt10.Add<MeshRenderer>(wireEnt10, *wireM10L4, shader);

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

	auto colorCorrectEffect = &colorCorrectEnt.Add<ColorCorrect>();
	colorCorrectEffect->Init(width, height);

	effects.push_back(colorCorrectEffect);

	auto filmGrainEffect = &filmGrainEnt.Add<FilmGrain>();
	filmGrainEffect->Init(width, height);

	effects.push_back(filmGrainEffect);

	auto pixelateEffect = &pixelateEnt.Add<Pixelate>();
	pixelateEffect->Init(width, height);

	effects.push_back(pixelateEffect);

	auto bloomEffect = &bloomEnt.Add<BloomEffect>();
	bloomEffect->Init(width, height);

	effects.push_back(bloomEffect);
#pragma endregion


}

void Level4::Update(float dt)
{
#pragma region Transforms
	auto& playerTrans = mainPlayer.Get<Transform>();
	auto& buttonTrans = buttonEnt.Get<Transform>();
	auto& buttonTrans2 = buttonEnt2.Get<Transform>();
	auto& buttonTrans3 = buttonEnt3.Get<Transform>();
	auto& buttonTrans4 = buttonEnt4.Get<Transform>();

	backEnt.Get<Transform>().SetPositionZ(0.0f);
	backEnt.Get<Transform>().SetPositionY(1.0f);

	leftEnt.Get<Transform>().SetPositionX(0.0f);
	leftEnt.Get<Transform>().SetPositionY(1.0f);

	rightEnt.Get<Transform>().SetPositionX(0.0f);
	rightEnt.Get<Transform>().SetPositionY(1.0f);
#pragma endregion

	auto& camera = camEnt.Get<Camera>();

	//Get reference to the model matrix
	glm::mat4 transform = mainPlayer.Get<Transform>().GetModelMatrix();
	glm::mat4 transformGround = floorEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformLeft = leftEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformRight = rightEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformBack = backEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformDoor = doorEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformButton = buttonTrans.GetModelMatrix();
	glm::mat4 transformButton2 = buttonTrans2.GetModelMatrix();
	glm::mat4 transformButton3 = buttonTrans3.GetModelMatrix();
	glm::mat4 transformButton4 = buttonTrans4.GetModelMatrix();
	glm::mat4 transformColPipe = colPipeEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformColPipe2 = colPipeEnt2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformShelfPipe = shelfPipeEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformShelfPipe2 = shelfPipeEnt2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformShelfPipe3 = shelfPipeEnt3.Get<Transform>().GetModelMatrix();

	glm::mat4 transformPanel = panelEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformPanel2 = panelEnt2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformVent = ventEntL.Get<Transform>().GetModelMatrix();
	glm::mat4 transformVent2 = ventEntS.Get<Transform>().GetModelMatrix();

	glm::mat4 transformGate = andEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformGate2 = andEnt2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformGate3 = andEnt3.Get<Transform>().GetModelMatrix();

	glm::mat4 transformNot = notEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformNot2 = notEnt2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformNot3 = notEnt3.Get<Transform>().GetModelMatrix();

	glm::mat4 transformCoil = coilEnt.Get<Transform>().GetModelMatrix();

	glm::mat4 transformWire = wireEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire2 = wireEnt2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire3 = wireEnt3.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire4 = wireEnt4.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire5 = wireEnt5.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire6 = wireEnt6.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire7 = wireEnt7.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire8 = wireEnt8.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire9 = wireEnt9.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire10 = wireEnt10.Get<Transform>().GetModelMatrix();

#pragma region PlayerMovement
	Input::MovePlayer(window, mainPlayer, camEnt, dt, camFar, camClose, camLeft, camRight);
#pragma endregion

#pragma region Camera Movement
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

	Input::MoveCamera(window, camEnt, dt);
#pragma endregion

	lightNum = Input::ChangeLighting(window, lightNum);

	if (lightNum < 1 || lightNum > 5)
		lightNum = 1;

	animShader->SetUniform("u_LightNum", lightNum);
	untexturedShader->SetUniform("u_LightNum", lightNum);
	shader->SetUniform("u_LightNum", lightNum);

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
		//Bind and render the player and door using the animation shader
		animShader->Bind();
		animShader->SetUniform("s_Diffuse", 0);
		drumstickMat.Albedo->Bind(0);
		mainPlayer.Get<MorphRenderer>().Render(camera, transform);

		animShader->SetUniform("s_Diffuse", 1);
		doorMat.Albedo->Bind(1);	
		doorEnt.Get<MorphRenderer>().Render(camera, transformDoor);	
		doorMat.Albedo->Unbind(1);

		untexturedShader->Bind();
		//Floor (no texture for now)
		floorEnt.Get<MeshRenderer>().Render(camera, transformGround);

		//Walls (no textures for now)
		leftEnt.Get<MeshRenderer>().Render(camera, transformLeft);
		rightEnt.Get<MeshRenderer>().Render(camera, transformRight);
		backEnt.Get<MeshRenderer>().Render(camera, transformBack);

		shader->Bind();

		//Column Pipes
		shader->SetUniform("s_Diffuse", 0);
		columnPipeMat.Albedo->Bind(0);
		colPipeEnt.Get<MeshRenderer>().Render(camera, transformColPipe);
		colPipeEnt2.Get<MeshRenderer>().Render(camera, transformColPipe2);

		//Panels
		shader->SetUniform("s_Diffuse", 1);
		panelMat.Albedo->Bind(1);
		panelEnt.Get<MeshRenderer>().Render(camera, transformPanel);
		panelEnt2.Get<MeshRenderer>().Render(camera, transformPanel2);

		//Vents
		shader->SetUniform("s_Diffuse", 2);
		ventMat.Albedo->Bind(2);
		ventEntL.Get<MeshRenderer>().Render(camera, transformVent);
		ventEntS.Get<MeshRenderer>().Render(camera, transformVent2);

		//Shelf Pipes
		shader->SetUniform("s_Diffuse", 3);
		shelfPipeMat.Albedo->Bind(3);
		shelfPipeEnt.Get<MeshRenderer>().Render(camera, transformShelfPipe);
		shelfPipeEnt2.Get<MeshRenderer>().Render(camera, transformShelfPipe2);
		shelfPipeEnt3.Get<MeshRenderer>().Render(camera, transformShelfPipe3);

		//Gates
		//And-Gate
		shader->SetUniform("s_Diffuse", 4);
		andMat.Albedo->Bind(4);
		andEnt.Get<MeshRenderer>().Render(camera, transformGate);
		andEnt2.Get<MeshRenderer>().Render(camera, transformGate2);
		andEnt3.Get<MeshRenderer>().Render(camera, transformGate3);

		//Not-Gate
		shader->SetUniform("s_Diffuse", 5);
		notMat.Albedo->Bind(5);
		notEnt.Get<MeshRenderer>().Render(camera, transformNot);
		notEnt2.Get<MeshRenderer>().Render(camera, transformNot2);
		notEnt3.Get<MeshRenderer>().Render(camera, transformNot3);

		//Buttons
		shader->SetUniform("s_Diffuse", 6);
		buttonMat.Albedo->Bind(6);
		buttonEnt.Get<MeshRenderer>().Render(camera, transformButton);
		buttonEnt2.Get<MeshRenderer>().Render(camera, transformButton2);
		buttonEnt3.Get<MeshRenderer>().Render(camera, transformButton3);
		buttonEnt4.Get<MeshRenderer>().Render(camera, transformButton4);

		//Tesla Coil (remember to add the other texture)
		shader->SetUniform("s_Diffuse", 7);
		coilMatOff.Albedo->Bind(7);
		coilEnt.Get<MeshRenderer>().Render(camera, transformCoil);

		//Wires
		shader->SetUniform("s_Diffuse", 8);
		wireMat.Albedo->Bind(8);
		wireEnt.Get<MeshRenderer>().Render(camera, transformWire);
		wireEnt2.Get<MeshRenderer>().Render(camera, transformWire2);
		wireEnt3.Get<MeshRenderer>().Render(camera, transformWire3);
		wireEnt4.Get<MeshRenderer>().Render(camera, transformWire4);
		wireEnt5.Get<MeshRenderer>().Render(camera, transformWire5);
		wireEnt6.Get<MeshRenderer>().Render(camera, transformWire6);
		wireEnt7.Get<MeshRenderer>().Render(camera, transformWire7);
		wireEnt8.Get<MeshRenderer>().Render(camera, transformWire8);
		wireEnt9.Get<MeshRenderer>().Render(camera, transformWire9);
		wireEnt10.Get<MeshRenderer>().Render(camera, transformWire10);
	}
	else
	{
		animShader->Bind();
		animShader->SetUniform("s_Diffuse", 0);
		clearMat.Albedo->Bind(0);
		mainPlayer.Get<MorphRenderer>().Render(camera, transform);

		animShader->SetUniform("s_Diffuse", 1);
		clearMat.Albedo->Bind(1);
		doorEnt.Get<MorphRenderer>().Render(camera, transformDoor);
		clearMat.Albedo->Unbind(1);

		untexturedShader->Bind();
		floorEnt.Get<MeshRenderer>().Render(camera, transformGround);
		leftEnt.Get<MeshRenderer>().Render(camera, transformLeft);
		rightEnt.Get<MeshRenderer>().Render(camera, transformRight);
		backEnt.Get<MeshRenderer>().Render(camera, transformBack);

		shader->Bind();
		shader->SetUniform("s_Diffuse", 0);
		clearMat.Albedo->Bind(0);
		colPipeEnt.Get<MeshRenderer>().Render(camera, transformColPipe);
		colPipeEnt2.Get<MeshRenderer>().Render(camera, transformColPipe2);
		panelEnt.Get<MeshRenderer>().Render(camera, transformPanel);
		panelEnt2.Get<MeshRenderer>().Render(camera, transformPanel2);
		ventEntL.Get<MeshRenderer>().Render(camera, transformVent);
		ventEntS.Get<MeshRenderer>().Render(camera, transformVent2);
		shelfPipeEnt.Get<MeshRenderer>().Render(camera, transformShelfPipe);
		shelfPipeEnt2.Get<MeshRenderer>().Render(camera, transformShelfPipe2);
		shelfPipeEnt3.Get<MeshRenderer>().Render(camera, transformShelfPipe3);
		andEnt.Get<MeshRenderer>().Render(camera, transformGate);
		andEnt2.Get<MeshRenderer>().Render(camera, transformGate2);
		andEnt3.Get<MeshRenderer>().Render(camera, transformGate3);
		notEnt.Get<MeshRenderer>().Render(camera, transformNot);
		notEnt2.Get<MeshRenderer>().Render(camera, transformNot2);
		notEnt3.Get<MeshRenderer>().Render(camera, transformNot3);
		buttonEnt.Get<MeshRenderer>().Render(camera, transformButton);
		buttonEnt2.Get<MeshRenderer>().Render(camera, transformButton2);
		buttonEnt3.Get<MeshRenderer>().Render(camera, transformButton3);
		buttonEnt4.Get<MeshRenderer>().Render(camera, transformButton4);
		coilEnt.Get<MeshRenderer>().Render(camera, transformCoil);
		wireEnt.Get<MeshRenderer>().Render(camera, transformWire);
		wireEnt2.Get<MeshRenderer>().Render(camera, transformWire2);
		wireEnt3.Get<MeshRenderer>().Render(camera, transformWire3);
		wireEnt4.Get<MeshRenderer>().Render(camera, transformWire4);
		wireEnt5.Get<MeshRenderer>().Render(camera, transformWire5);
		wireEnt6.Get<MeshRenderer>().Render(camera, transformWire6);
		wireEnt7.Get<MeshRenderer>().Render(camera, transformWire7);
		wireEnt8.Get<MeshRenderer>().Render(camera, transformWire8);
		wireEnt9.Get<MeshRenderer>().Render(camera, transformWire9);
		wireEnt10.Get<MeshRenderer>().Render(camera, transformWire10);
	}
#pragma endregion

	basicEffect->UnbindBuffer();

	effects[activeEffect]->ApplyEffect(basicEffect);

	effects[activeEffect]->DrawToScreen();

	//Update the collisions
	//leftEnt.Get<AABB>().Update();
	//rightEnt.Get<AABB>().Update();
	//backEnt.Get<AABB>().Update();
	
}

void Level4::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}