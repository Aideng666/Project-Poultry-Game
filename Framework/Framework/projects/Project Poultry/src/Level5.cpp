#include "Level5.h"
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

Level5::Level5(std::string sceneName, GLFWwindow* wind)
	: Scene(sceneName, wind)
{
#pragma region Entities
	mainPlayer = Entity::Create();
	floorEnt = Entity::Create();
	leftEnt = Entity::Create();
	rightEnt = Entity::Create();
	backEnt = Entity::Create();

	wireEnt = Entity::Create();
	wireEnt2 = Entity::Create();
	wireEnt3 = Entity::Create();
	wireEnt4 = Entity::Create();
	wireEnt5 = Entity::Create();
	wireEnt6 = Entity::Create();
	wireEnt7 = Entity::Create();

	ventEnt = Entity::Create();
	ventEnt2 = Entity::Create();

	doorEnt = Entity::Create();

	andEnt = Entity::Create();
	orEnt = Entity::Create();
	orEnt2 = Entity::Create();

	buttonEnt = Entity::Create();
	buttonEnt2 = Entity::Create();
	buttonEnt3 = Entity::Create();
	buttonEnt4 = Entity::Create();

	coilEnt = Entity::Create();

	shelfPipeEnt = Entity::Create();
	shelfPipeEnt2 = Entity::Create();
	shelfPipeEnt3 = Entity::Create();
	shelfPipeEnt4 = Entity::Create();

	columnPipeEnt = Entity::Create();
	columnPipeEnt2 = Entity::Create();

	pipeEntC = Entity::Create();
	pipeEntC2 = Entity::Create();
	pipeEntS = Entity::Create();
	pipeEntS2 = Entity::Create();

	panelEnt = Entity::Create();

	pauseEnt = Entity::Create();
	optionEnt = Entity::Create();
	exitEnt = Entity::Create();
	retryEnt = Entity::Create();

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

void Level5::InitScene()
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
	playerTrans.SetPosition(glm::vec3(0.0f, 1.1f, 43.f));
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

	//Vent transforms
	auto& ventTrans = ventEnt.Add<Transform>();
	ventTrans.SetPosition(glm::vec3(20.f, 25.f, -50.5f));
	ventTrans.SetScale(glm::vec3(1.2f));
	ventTrans.SetRotationY(90.f);

	auto& ventTrans2 = ventEnt2.Add<Transform>();
	ventTrans2.SetPosition(glm::vec3(-20.f, 25.f, -50.5f));
	ventTrans2.SetScale(glm::vec3(1.2f));
	ventTrans2.SetRotationY(90.f);

	//Gate transforms
	//And Gate
	auto& gateTrans = andEnt.Add<Transform>();
	gateTrans.SetPosition(glm::vec3(-1.74f, 1.2f, -1.75f));
	gateTrans.SetRotationY(-90.0f);
	gateTrans.SetScale(glm::vec3(2.0f));

	//Or Gate
	auto& orTrans = orEnt.Add<Transform>();
	orTrans.SetPosition(glm::vec3(-21.f, 1.f, 14.9f));
	orTrans.SetRotationY(-90.f);
	orTrans.SetScale(glm::vec3(2.0f));

	auto& orTrans2 = orEnt2.Add<Transform>();
	orTrans2.SetPosition(glm::vec3(17.2f, 1.f, 14.7f));
	orTrans2.SetRotationY(-90.f);
	orTrans2.SetScale(glm::vec3(2.0f));

	//Button transforms
	auto& buttonTrans = buttonEnt.Add<Transform>();
	buttonTrans.SetPosition(glm::vec3(27.7f, -1.0f, 39.4f));

	auto& buttonTrans2 = buttonEnt2.Add<Transform>();
	buttonTrans2.SetPosition(glm::vec3(6.5f, -1.0f, 39.5f));

	auto& buttonTrans3 = buttonEnt3.Add<Transform>();
	buttonTrans3.SetPosition(glm::vec3(-10.4f, -1.0f, 39.5f));

	auto& buttonTrans4 = buttonEnt4.Add<Transform>();
	buttonTrans4.SetPosition(glm::vec3(-31.6f, -1.0f, 39.5f));

	//Coil Object
	auto& coilTrans = coilEnt.Add<Transform>();
	coilTrans.SetPosition(glm::vec3(-16.0f, 1.0f, -48.f));
	coilTrans.SetScale(glm::vec3(3.0f));
	coilTrans.SetRotationY(180.0f);

	//Shelf Pipe transforms
	auto& shelfPipeTrans = shelfPipeEnt.Add<Transform>();
	shelfPipeTrans.SetPosition(glm::vec3(46.5f, 9.5f, 20.f));
	shelfPipeTrans.SetRotationY(180.f);
	shelfPipeTrans.SetScale(glm::vec3(1.5f));

	auto& shelfPipeTrans2 = shelfPipeEnt2.Add<Transform>();
	shelfPipeTrans2.SetPosition(glm::vec3(-46.5f, 9.5f, -22.f));
	shelfPipeTrans2.SetScale(glm::vec3(1.5f));

	auto& shelfPipeTrans3 = shelfPipeEnt3.Add<Transform>();
	shelfPipeTrans3.SetPosition(glm::vec3(46.5f, 9.5f, -34.f));
	shelfPipeTrans3.SetRotationY(180.f);
	shelfPipeTrans3.SetScale(glm::vec3(1.5f));

	auto& shelfPipeTrans4 = shelfPipeEnt4.Add<Transform>();
	shelfPipeTrans4.SetPosition(glm::vec3(-46.5f, 9.5f, 34.f));
	shelfPipeTrans4.SetScale(glm::vec3(1.5f));

	//Column Pipe transforms
	auto& colPipeTrans = columnPipeEnt.Add<Transform>();
	colPipeTrans.SetPosition(glm::vec3(49.f, 1.f, 0.f));
	colPipeTrans.SetScale(glm::vec3(1.5f));

	auto& colPipeTrans2 = columnPipeEnt2.Add<Transform>();
	colPipeTrans2.SetPosition(glm::vec3(-49.f, 1.f, 0.f));
	colPipeTrans2.SetScale(glm::vec3(1.5f));

	//Panel transforms
	auto& panelTrans = panelEnt.Add<Transform>();
	panelTrans.SetScale(glm::vec3(4.0f));
	panelTrans.SetPosition(glm::vec3(-51.f, 2.0f, 25.f));

	//Pipe transforms
	auto& pipeTrans = pipeEntC.Add<Transform>();
	pipeTrans.SetPosition(glm::vec3(-51.5f, 47.f, -40.f));
	pipeTrans.SetRotationX(90.f);
	pipeTrans.SetRotationY(90.f);

	auto& pipeTrans2 = pipeEntC2.Add<Transform>();
	pipeTrans2.SetPosition(glm::vec3(51.5f, 47.f, -40.f));
	pipeTrans2.SetRotationX(90.f);
	pipeTrans2.SetRotationY(-90.f);

	auto& pipeTrans3 = pipeEntS.Add<Transform>();
	pipeTrans3.SetPosition(glm::vec3(40.f, 21.5f, -40.f));
	pipeTrans3.SetRotationX(90.f);

	auto& pipeTrans4 = pipeEntS2.Add<Transform>();
	pipeTrans4.SetPosition(glm::vec3(-40.f, 21.5f, -40.f));
	pipeTrans4.SetRotationX(90.f);

	//Pause UI
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
#pragma endregion

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
	auto& floorMesh = floorEnt.Add<MeshRenderer>(floorEnt, *floorLab, untexturedShader);
	auto& leftMesh = leftEnt.Add<MeshRenderer>(leftEnt, *leftWallLab, untexturedShader);
	auto& rightMesh = rightEnt.Add<MeshRenderer>(rightEnt, *rightWallLab, untexturedShader);
	auto& backMesh = backEnt.Add<MeshRenderer>(backEnt, *backWallLab, untexturedShader);

	auto& doorMesh = doorEnt.Add<MorphRenderer>(doorEnt, *doorM, animShader);

	auto& pauseMesh = pauseEnt.Add<MeshRenderer>(pauseEnt, *screen, pauseShader);
	auto& optionMesh = optionEnt.Add<MeshRenderer>(optionEnt, *options, pauseShader);
	auto& retryMesh = retryEnt.Add<MeshRenderer>(retryEnt, *retry, pauseShader);
	auto& exitMesh = exitEnt.Add<MeshRenderer>(exitEnt, *exit, pauseShader);

	auto& wireMesh = wireEnt.Add<MeshRenderer>(wireEnt, *wireM1L5, shader);
	auto& wireMesh2 = wireEnt2.Add<MeshRenderer>(wireEnt2, *wireM2L5, shader);
	auto& wireMesh3 = wireEnt3.Add<MeshRenderer>(wireEnt3, *wireM3L5, shader);
	auto& wireMesh4 = wireEnt4.Add<MeshRenderer>(wireEnt4, *wireM4L5, shader);
	auto& wireMesh5 = wireEnt5.Add<MeshRenderer>(wireEnt5, *wireM5L5, shader);
	auto& wireMesh6 = wireEnt6.Add<MeshRenderer>(wireEnt6, *wireM6L5, shader);
	auto& wireMesh7 = wireEnt7.Add<MeshRenderer>(wireEnt7, *wireM7L5, shader);

	auto& vent = ventEnt.Add<MeshRenderer>(ventEnt, *ventB, shader);
	auto& vent2 = ventEnt2.Add<MeshRenderer>(ventEnt2, *ventB, shader);

	auto& gateMesh = andEnt.Add<MeshRenderer>(andEnt, *and, shader);
	auto& orM = orEnt.Add<MeshRenderer>(orEnt, *orMesh, shader);
	auto& orM2 = orEnt2.Add<MeshRenderer>(orEnt2, *orMesh, shader);

	auto& buttonMesh = buttonEnt.Add<MeshRenderer>(buttonEnt, *buttonM, shader);
	auto& buttonMesh2 = buttonEnt2.Add<MeshRenderer>(buttonEnt2, *buttonM, shader);
	auto& buttonMesh3 = buttonEnt3.Add<MeshRenderer>(buttonEnt3, *buttonM, shader);
	auto& buttonMesh4 = buttonEnt4.Add<MeshRenderer>(buttonEnt4, *buttonM, shader);

	auto& coilMesh = coilEnt.Add<MeshRenderer>(coilEnt, *coil, shader);

	auto& shelfPipeMesh = shelfPipeEnt.Add<MeshRenderer>(shelfPipeEnt, *shelfPipe, shader);
	auto& shelfPipeMesh2 = shelfPipeEnt2.Add<MeshRenderer>(shelfPipeEnt2, *shelfPipe, shader);
	auto& shelfPipeMesh3 = shelfPipeEnt3.Add<MeshRenderer>(shelfPipeEnt3, *shelfPipe, shader);
	auto& shelfPipeMesh4 = shelfPipeEnt4.Add<MeshRenderer>(shelfPipeEnt4, *shelfPipe, shader);

	auto& colPipeMesh = columnPipeEnt.Add<MeshRenderer>(columnPipeEnt, *columnPipe, shader);
	auto& colPipeMesh2 = columnPipeEnt2.Add<MeshRenderer>(columnPipeEnt2, *columnPipe, shader);

	auto& pipeMesh = pipeEntC.Add<MeshRenderer>(pipeEntC, *pipeC, shader);
	auto& pipeMesh2 = pipeEntC2.Add<MeshRenderer>(pipeEntC2, *pipeC, shader);
	auto& pipeMesh3 = pipeEntS.Add<MeshRenderer>(pipeEntS, *pipeS, shader);
	auto& pipeMesh4 = pipeEntS2.Add<MeshRenderer>(pipeEntS2, *pipeS, shader);

	auto& panelMesh = panelEnt.Add<MeshRenderer>(panelEnt, *panel, shader);

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

void Level5::Update(float dt)
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
	auto& orthoCam = uiCamEnt.Get<Camera>();

	//Get reference to the model matrix
	glm::mat4 transform = mainPlayer.Get<Transform>().GetModelMatrix();
	glm::mat4 transformGround = floorEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformLeft = leftEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformRight = rightEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformBack = backEnt.Get<Transform>().GetModelMatrix();

	glm::mat4 transformDoor = doorEnt.Get<Transform>().GetModelMatrix();

	glm::mat4 transformWire = wireEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire2 = wireEnt2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire3 = wireEnt3.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire4 = wireEnt4.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire5 = wireEnt5.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire6 = wireEnt6.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire7 = wireEnt7.Get<Transform>().GetModelMatrix();

	glm::mat4 transformVent = ventEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformVent2 = ventEnt2.Get<Transform>().GetModelMatrix();

	glm::mat4 transformGate = andEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformOr = orEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformOr2 = orEnt2.Get<Transform>().GetModelMatrix();

	glm::mat4 transformButton = buttonTrans.GetModelMatrix();
	glm::mat4 transformButton2 = buttonTrans2.GetModelMatrix();
	glm::mat4 transformButton3 = buttonTrans3.GetModelMatrix();
	glm::mat4 transformButton4 = buttonTrans4.GetModelMatrix();

	glm::mat4 transformCoil = coilEnt.Get<Transform>().GetModelMatrix();

	glm::mat4 transformShelfPipe = shelfPipeEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformShelfPipe2 = shelfPipeEnt2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformShelfPipe3 = shelfPipeEnt3.Get<Transform>().GetModelMatrix();
	glm::mat4 transformShelfPipe4 = shelfPipeEnt4.Get<Transform>().GetModelMatrix();

	glm::mat4 transformColPipe = columnPipeEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformColPipe2 = columnPipeEnt2.Get<Transform>().GetModelMatrix();

	glm::mat4 transformPipe = pipeEntC.Get<Transform>().GetModelMatrix();
	glm::mat4 transformPipe2 = pipeEntC2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformPipe3 = pipeEntS.Get<Transform>().GetModelMatrix();
	glm::mat4 transformPipe4 = pipeEntS2.Get<Transform>().GetModelMatrix();

	glm::mat4 transformPanel = panelEnt.Get<Transform>().GetModelMatrix();

	glm::mat4 transformPause = pauseEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformOptions = optionEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformRetry = retryEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformExit = exitEnt.Get<Transform>().GetModelMatrix();

	pauseWatch.Poll(window);

#pragma region PlayerMovement
	if (!isPaused)
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

	if (!isPaused)
	{
		Input::MoveCamera(window, camEnt, dt);
	}
#pragma endregion

	lightNum = Input::ChangeLighting(window, lightNum);

	if (lightNum < 1 || lightNum > 5)
		lightNum = 1;

	animShader->SetUniform("u_LightNum", lightNum);
	untexturedShader->SetUniform("u_LightNum", lightNum);
	pauseShader->SetUniform("u_LightNum", lightNum);
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

		pauseShader->Bind();
		pauseShader->SetUniform("s_Diffuse", 0);
		pauseMat.Albedo->Bind(0);

		if (isPaused)
		{
			pauseEnt.Get<MeshRenderer>().Render(orthoCam, transformPause);
		}

		pauseShader->SetUniform("s_Diffuse", 1);
		optionMat.Albedo->Bind(1);

		if (isPaused)
		{
			optionEnt.Get<MeshRenderer>().Render(orthoCam, transformOptions);
		}

		pauseShader->SetUniform("s_Diffuse", 2);
		retryMat.Albedo->Bind(2);

		if (isPaused)
		{
			retryEnt.Get<MeshRenderer>().Render(orthoCam, transformRetry);
		}

		pauseShader->SetUniform("s_Diffuse", 2);
		exitMat.Albedo->Bind(2);

		if (isPaused)
		{
			exitEnt.Get<MeshRenderer>().Render(orthoCam, transformExit);
		}

		shader->Bind();
		//Wires
		shader->SetUniform("s_Diffuse", 0);
		wireMat.Albedo->Bind(0);
		wireEnt.Get<MeshRenderer>().Render(camera, transformWire);
		wireEnt2.Get<MeshRenderer>().Render(camera, transformWire2);
		wireEnt3.Get<MeshRenderer>().Render(camera, transformWire3);
		wireEnt4.Get<MeshRenderer>().Render(camera, transformWire4);
		wireEnt5.Get<MeshRenderer>().Render(camera, transformWire5);
		wireEnt6.Get<MeshRenderer>().Render(camera, transformWire6);
		wireEnt7.Get<MeshRenderer>().Render(camera, transformWire7);

		//Vents
		shader->SetUniform("s_Diffuse", 1);
		ventMat.Albedo->Bind(1);
		ventEnt.Get<MeshRenderer>().Render(camera, transformVent);
		ventEnt2.Get<MeshRenderer>().Render(camera, transformVent2);

		//Gates
		//And-Gate
		shader->SetUniform("s_Diffuse", 2);
		andMat.Albedo->Bind(2);
		andEnt.Get<MeshRenderer>().Render(camera, transformGate);

		//Or-Gate
		shader->SetUniform("s_Diffuse", 3);
		orMat.Albedo->Bind(3);
		orEnt.Get<MeshRenderer>().Render(camera, transformOr);
		orEnt2.Get<MeshRenderer>().Render(camera, transformOr2);

		//Buttons
		shader->SetUniform("s_Diffuse", 4);
		buttonMat.Albedo->Bind(4);
		buttonEnt.Get<MeshRenderer>().Render(camera, transformButton);
		buttonEnt2.Get<MeshRenderer>().Render(camera, transformButton2);
		buttonEnt3.Get<MeshRenderer>().Render(camera, transformButton3);
		buttonEnt4.Get<MeshRenderer>().Render(camera, transformButton4);

		//Tesla Coil (remember to add the other texture)
		shader->SetUniform("s_Diffuse", 5);
		coilMatOff.Albedo->Bind(5);
		coilEnt.Get<MeshRenderer>().Render(camera, transformCoil);

		//Shelf Pipes
		shader->SetUniform("s_Diffuse", 6);
		shelfPipeMat.Albedo->Bind(6);
		shelfPipeEnt.Get<MeshRenderer>().Render(camera, transformShelfPipe);
		shelfPipeEnt2.Get<MeshRenderer>().Render(camera, transformShelfPipe2);
		shelfPipeEnt3.Get<MeshRenderer>().Render(camera, transformShelfPipe3);
		shelfPipeEnt4.Get<MeshRenderer>().Render(camera, transformShelfPipe4);

		//Column Pipes
		shader->SetUniform("s_Diffuse", 7);
		columnPipeMat.Albedo->Bind(7);
		columnPipeEnt.Get<MeshRenderer>().Render(camera, transformColPipe);
		columnPipeEnt2.Get<MeshRenderer>().Render(camera, transformColPipe2);

		//Panels
		shader->SetUniform("s_Diffuse", 8);
		panelMat.Albedo->Bind(8);
		panelEnt.Get<MeshRenderer>().Render(camera, transformPanel);

		//Curved Pipe
		shader->SetUniform("s_Diffuse", 9);
		curvedPipeMat.Albedo->Bind(9);
		pipeEntC.Get<MeshRenderer>().Render(camera, transformPipe);
		pipeEntC2.Get<MeshRenderer>().Render(camera, transformPipe2);

		//Straight Pipe
		shader->SetUniform("s_Diffuse", 10);
		straightPipeMat.Albedo->Bind(10);
		pipeEntS.Get<MeshRenderer>().Render(camera, transformPipe3);
		pipeEntS2.Get<MeshRenderer>().Render(camera, transformPipe4);
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

		pauseShader->Bind();
		pauseShader->SetUniform("s_Diffuse", 0);
		clearMat.Albedo->Bind(0);

		if (isPaused)
		{
			pauseEnt.Get<MeshRenderer>().Render(orthoCam, transformPause);
		}

		shader->Bind();
		shader->SetUniform("s_Diffuse", 0);
		clearMat.Albedo->Bind(0);
		wireEnt.Get<MeshRenderer>().Render(camera, transformWire);
		wireEnt2.Get<MeshRenderer>().Render(camera, transformWire2);
		wireEnt3.Get<MeshRenderer>().Render(camera, transformWire3);
		wireEnt4.Get<MeshRenderer>().Render(camera, transformWire4);
		wireEnt5.Get<MeshRenderer>().Render(camera, transformWire5);
		wireEnt6.Get<MeshRenderer>().Render(camera, transformWire6);
		wireEnt7.Get<MeshRenderer>().Render(camera, transformWire7);
		ventEnt.Get<MeshRenderer>().Render(camera, transformVent);
		ventEnt2.Get<MeshRenderer>().Render(camera, transformVent2);
		andEnt.Get<MeshRenderer>().Render(camera, transformGate);
		orEnt.Get<MeshRenderer>().Render(camera, transformOr);
		orEnt2.Get<MeshRenderer>().Render(camera, transformOr2);
		buttonEnt.Get<MeshRenderer>().Render(camera, transformButton);
		buttonEnt2.Get<MeshRenderer>().Render(camera, transformButton2);
		buttonEnt3.Get<MeshRenderer>().Render(camera, transformButton3);
		buttonEnt4.Get<MeshRenderer>().Render(camera, transformButton4);
		coilEnt.Get<MeshRenderer>().Render(camera, transformCoil);
		shelfPipeEnt.Get<MeshRenderer>().Render(camera, transformShelfPipe);
		shelfPipeEnt2.Get<MeshRenderer>().Render(camera, transformShelfPipe2);
		shelfPipeEnt3.Get<MeshRenderer>().Render(camera, transformShelfPipe3);
		shelfPipeEnt4.Get<MeshRenderer>().Render(camera, transformShelfPipe4);
		columnPipeEnt.Get<MeshRenderer>().Render(camera, transformColPipe);
		columnPipeEnt2.Get<MeshRenderer>().Render(camera, transformColPipe2);
		panelEnt.Get<MeshRenderer>().Render(camera, transformPanel);
		pipeEntC.Get<MeshRenderer>().Render(camera, transformPipe);
		pipeEntC2.Get<MeshRenderer>().Render(camera, transformPipe2);
		pipeEntS.Get<MeshRenderer>().Render(camera, transformPipe3);
		pipeEntS2.Get<MeshRenderer>().Render(camera, transformPipe4);
	}
#pragma endregion

	basicEffect->UnbindBuffer();

	effects[activeEffect]->ApplyEffect(basicEffect);

	effects[activeEffect]->DrawToScreen();

}

void Level5::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}