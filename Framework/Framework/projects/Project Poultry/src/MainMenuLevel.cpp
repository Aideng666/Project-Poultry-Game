#include "MainMenuLevel.h"
#include <iostream>
#include <GLFW\glfw3.h>

#include "Application.h"
#include <AABB.h>
#include <MeshRenderer.h>
#include <MorphRenderer.h>
#include "Texture2DData.h"
#include "Texture2D.h"
#include <stb_image.h>
#include <MorphAnimation.h>

MainMenuLevel::MainMenuLevel(std::string sceneName, GLFWwindow* wind)
	: Scene(sceneName, wind)
{
#pragma region Entities
	mainPlayer = Entity::Create();
	startDoor = Entity::Create();
	exitDoor = Entity::Create();
	floorEnt = Entity::Create();
	backWallEnt = Entity::Create();
	leftWallEnt = Entity::Create();
	rightWallEnt = Entity::Create();
	
	coilEnt = Entity::Create();
	coilEnt2 = Entity::Create();

	wireEnt = Entity::Create();
	wireEnt2 = Entity::Create();

	buttonEnt = Entity::Create();
	buttonEnt2 = Entity::Create();

	//startEnt = Entity::Create();
	//optEnt = Entity::Create();
	//exitEnt = Entity::Create();

	tutEnt = Entity::Create();

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

void MainMenuLevel::InitScene()
{
	Application::SetClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	scene = new entt::registry();

	Entity::SetReg(scene);

	activeEffect = 4;

	effects.clear();

	InitShaders();

	InitTextures();

#pragma region Transforms

	//Floor Transform
	auto& floorTrans = floorEnt.Add<Transform>();

	//Wall Transforms
	auto& leftTrans = leftWallEnt.Add<Transform>();
	leftTrans.SetRotationY(45.0f);
	leftTrans.SetPositionX(-38.0f);
	leftTrans.SetPositionZ(-11.0f);
	leftTrans.SetPositionY(1.3f);
	
	auto& rightTrans = rightWallEnt.Add<Transform>();
	rightTrans.SetRotationY(-45.0f);
	rightTrans.SetPositionX(38.0f);
	rightTrans.SetPositionZ(-11.0f);
	rightTrans.SetPositionY(1.3f);
	
	auto& backTrans = backWallEnt.Add<Transform>();
	backTrans.SetPositionZ(-39.0f);
	backTrans.SetPositionY(0.0f);

	//Player Transform
	auto& playerTrans = mainPlayer.Add<Transform>();
	playerTrans.SetPosition(glm::vec3(0.0f, 1.5f, 10.f));
	playerTrans.SetRotationY(180.0f);

	//Door Transforms
	auto& startTrans = startDoor.Add<Transform>();
	startTrans.SetPosition(glm::vec3(-27.0f, 1.5f, -19.5f));
	startTrans.SetRotationY(45.0f);
	
	auto& exitTrans = exitDoor.Add<Transform>();
	exitTrans.SetPosition(glm::vec3(28.0f, 1.5f, -18.5f));
	exitTrans.SetRotationY(-45.0f);

	//Coil Transforms
	auto& coilTrans = coilEnt.Add<Transform>();
	coilTrans.SetPosition(glm::vec3(-13.5f, 1.1f, -24.f));
	coilTrans.SetScale(glm::vec3(3.0f));
	coilTrans.SetRotationY(180.0f);

	auto& coilTrans2 = coilEnt2.Add<Transform>();
	coilTrans2.SetPosition(glm::vec3(14.5f, 1.1f, -24.f));
	coilTrans2.SetScale(glm::vec3(3.0f));
	coilTrans2.SetRotationY(180.0f);

	//Wire Transforms
	auto& wireTrans = wireEnt.Add<Transform>();
	wireTrans.SetPosition(glm::vec3(0.f, 0.0f, 0.f));

	auto& wireTrans2 = wireEnt2.Add<Transform>();
	wireTrans2.SetPosition(glm::vec3(0.f, 0.0f, 0.f));

	//Button Transforms
	auto& buttonTrans = buttonEnt.Add<Transform>();
	buttonTrans.SetPosition(glm::vec3(-8.7f, -1.f, 4.8f));
	buttonTrans.SetRotationY(90.0f);

	auto& buttonTrans2 = buttonEnt2.Add<Transform>();
	buttonTrans2.SetPosition(glm::vec3(10.2f, -1.f, 4.8f));
	buttonTrans2.SetRotationY(90.0f);

	//Interact text transform
	auto& tutTrans = tutEnt.Add<Transform>();
	tutTrans.SetPosition(glm::vec3(1.0f, 2.0f, 5.0f));
	tutTrans.SetScale(glm::vec3(1.0f));

	//Text Transforms
	//auto& sTrans = startEnt.Add<Transform>();
	//sTrans.SetPosition(glm::vec3(-4.0f, 1.f, -25.0f));
	//sTrans.SetScale(glm::vec3(4.0f));

	//auto& eTrans = exitEnt.Add<Transform>();
	//eTrans.SetRotationY(-45.0f);
	//eTrans.SetPosition(glm::vec3(19.0f, 1.f, -21.0f));
	//eTrans.SetScale(glm::vec3(4.0f));

	//auto& oTrans = optEnt.Add<Transform>();
	//oTrans.SetRotationY(45.0f);
	//oTrans.SetPosition(glm::vec3(-26.0f, 1.f, -13.0f));
	//oTrans.SetScale(glm::vec3(4.0f));
#pragma endregion

	//AABB
	//auto& leftCol = leftWallEnt.Add<AABB>(leftWallEnt, mainPlayer);
	//auto& rightCol = rightWallEnt.Add<AABB>(rightWallEnt, mainPlayer);
	auto& backCol = backWallEnt.Add<AABB>(backWallEnt, mainPlayer);
	auto& coilCol = coilEnt.Add<AABB>(coilEnt, mainPlayer, 4.0f, 4.0f);
	coilCol.SetIsAmbient(true);
	auto& coilCol2 = coilEnt2.Add<AABB>(coilEnt2, mainPlayer, 4.0f, 4.0f);
	coilCol2.SetIsAmbient(true);
	auto& buttonCol = buttonEnt.Add<AABB>(buttonEnt, mainPlayer, 2.0f, 2.0f);
	buttonCol.SetIsAmbient(true);
	auto& buttonCol2 = buttonEnt2.Add<AABB>(buttonEnt2, mainPlayer, 2.0f, 2.0f);
	buttonCol2.SetIsAmbient(true);

	auto& startDoorCol = startDoor.Add<AABB>(startDoor, mainPlayer);
	startDoorCol.SetComplete(false);

	auto& exitDoorCol = exitDoor.Add<AABB>(exitDoor, mainPlayer);
	exitDoorCol.SetComplete(false);

	//Buttons
	auto& button = buttonEnt.Add<Lever>(wireEnt);
	button.SetPowered(false);
	auto& button2 = buttonEnt2.Add<Lever>(wireEnt2);
	button2.SetPowered(false);

	//Wires
	auto& wire = wireEnt.Add<Wire>(buttonEnt);
	auto& wire2 = wireEnt2.Add<Wire>(buttonEnt2);

	//Doors
	auto& door = startDoor.Add<Door>();
	door.SetOpen(false);

	auto& door2 = exitDoor.Add<Door>();
	door2.SetOpen(false);

	InitAnims();

#pragma region Mesh Loading 

	//Load the meshes
	auto& playerMesh = mainPlayer.Add<MorphRenderer>(mainPlayer, *idle1, animShader);
	auto& backMesh = backWallEnt.Add<MeshRenderer>(backWallEnt, *mainMenuBackWall, shader);
	auto& leftMesh = leftWallEnt.Add<MeshRenderer>(leftWallEnt, *mainMenuLeftWall, shader);
	auto& rightMesh = rightWallEnt.Add<MeshRenderer>(rightWallEnt, *mainMenuRightWall, shader);
	auto& floorMesh = floorEnt.Add<MeshRenderer>(floorEnt, *mainMenuFloor, shader);
	auto& playMesh = startDoor.Add<MorphRenderer>(startDoor, *door1, animShader);
	auto& exitMesh = exitDoor.Add<MorphRenderer>(exitDoor, *door1, animShader);

	auto& coilMesh = coilEnt.Add<MeshRenderer>(coilEnt, *coil, shader);
	auto& coilMesh2 = coilEnt2.Add<MeshRenderer>(coilEnt2, *coil, shader);

	auto& wireMesh = wireEnt.Add<MeshRenderer>(wireEnt, *mainMenuWire1, shader);
	auto& wireMesh2 = wireEnt2.Add<MeshRenderer>(wireEnt2, *mainMenuWire2, shader);

	auto& buttonMesh = buttonEnt.Add<MorphRenderer>(buttonEnt, *buttonM, animShader);
	auto& buttonMesh2 = buttonEnt2.Add<MorphRenderer>(buttonEnt2, *buttonM, animShader);

	//auto& sMesh = startEnt.Add<MeshRenderer>(startEnt, *startWord, shader);
	//auto& oMesh = optEnt.Add<MeshRenderer>(optEnt, *optionsWord, shader);
	//auto& eMesh = exitEnt.Add<MeshRenderer>(exitEnt, *exitWord, shader);

	//Load the animations
	//auto& startAnimator = startDoor.Add<MorphAnimation>(startDoor);
	//startAnimator.SetTime(0.2f);
	//startAnimator.SetFrames(doorFrames);
	//startAnimator.SetLoop(false);

	//auto& exitAnimator = exitDoor.Add<MorphAnimation>(exitDoor);
	//exitAnimator.SetTime(0.2f);
	//exitAnimator.SetFrames(doorFrames);
	//exitAnimator.SetLoop(false);

	//auto& optAnimator = optionDoor.Add<MorphAnimation>(optionDoor);
	//optAnimator.SetTime(0.2f);
	//optAnimator.SetFrames(doorFrames);
	//optAnimator.SetLoop(false);


	entList.push_back(&mainPlayer);
	entList.push_back(&startDoor);
	entList.push_back(&exitDoor);
	entList.push_back(&buttonEnt);
	entList.push_back(&buttonEnt2);
	entList.push_back(&floorEnt);
	entList.push_back(&leftWallEnt);
	entList.push_back(&rightWallEnt);
	entList.push_back(&wireEnt);
	entList.push_back(&wireEnt2);
	entList.push_back(&coilEnt);
	entList.push_back(&coilEnt2);

#pragma endregion 

	auto& doorAnimator = startDoor.Add<MorphAnimation>(startDoor);
	doorAnimator.SetTime(0.1f);
	doorAnimator.SetFrames(doorFrames);
	doorAnimator.SetLoop(false);

	auto& doorAnimator2 = exitDoor.Add<MorphAnimation>(exitDoor);
	doorAnimator2.SetTime(0.1f);
	doorAnimator2.SetFrames(doorFrames);
	doorAnimator2.SetLoop(false);

	auto& walkAnimator = mainPlayer.Add<MorphAnimation>(mainPlayer);
	walkAnimator.SetTime(0.3f);
	walkAnimator.SetFrames(idleFrames);

	auto& buttonAnimator = buttonEnt.Add<MorphAnimation>(buttonEnt);
	buttonAnimator.SetTime(0.2f);
	buttonAnimator.SetFrames(buttonFrames);
	buttonAnimator.SetLoop(false);

	auto& buttonAnimator2 = buttonEnt2.Add<MorphAnimation>(buttonEnt2);
	buttonAnimator2.SetTime(0.2f);
	buttonAnimator2.SetFrames(buttonFrames);
	buttonAnimator2.SetLoop(false);

	//Camera Object
	auto& camera = camEnt.Add<Camera>();
	camera.SetPosition(glm::vec3(0, 25, 30)); // Set initial position
	camera.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
	camera.LookAt(glm::vec3(0.0f, 5.0f, -10.0f)); // Look at center of the screen
	camera.SetFovDegrees(90.0f); // Set an initial FOV

	//Allocates enough memory for one directional light (we can change this easily, but we only need 1 directional light)
	directionalLightBuffer.AllocateMemory(sizeof(DirectionalLight));
	//Casts our sun as "data" and sends it to the shader
	directionalLightBuffer.SendData(reinterpret_cast<void*>(&theSun), sizeof(DirectionalLight));

	directionalLightBuffer.Bind(0);

#pragma region Post-Effects
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	auto shadowBuffer = &shadowBufferEnt.Add<Framebuffer>();
	shadowBuffer->AddDepthTarget();
	shadowBuffer->Init(shadowWidth, shadowHeight);

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

void MainMenuLevel::Update(float dt)
{
	time += dt;
	shader->SetUniform("u_Time", time);
	animShader->SetUniform("u_Time", time);

	//Transforms
	auto& playerTrans = mainPlayer.Get<Transform>();
	auto& groundTrans = floorEnt.Get<Transform>();
	auto& leftTrans = leftWallEnt.Get<Transform>();
	auto& rightTrans = rightWallEnt.Get<Transform>();
	auto& backTrans = backWallEnt.Get<Transform>();
	auto& startTrans = startDoor.Get<Transform>();
	auto& exitTrans = exitDoor.Get<Transform>();

	auto& coilTrans = coilEnt.Get<Transform>();
	auto& coilTrans2 = coilEnt2.Get<Transform>();

	auto& wireTrans = wireEnt.Get<Transform>();
	auto& wireTrans2 = wireEnt2.Get<Transform>();

	auto& buttonTrans = buttonEnt.Get<Transform>();
	auto& buttonTrans2 = buttonEnt2.Get<Transform>();

	//auto& sTrans = startEnt.Get<Transform>();
	//auto& oTrans = optEnt.Get<Transform>();
	//auto& eTrans = exitEnt.Get<Transform>();

	auto& camera = camEnt.Get<Camera>();

	auto& drumMesh = mainPlayer.Get<MorphRenderer>();
	auto& floorMesh = floorEnt.Get<MeshRenderer>();
	auto& backMesh = backWallEnt.Get<MeshRenderer>();
	auto& leftMesh = leftWallEnt.Get<MeshRenderer>();
	auto& rightMesh = rightWallEnt.Get<MeshRenderer>();
	auto& startMesh = startDoor.Get<MorphRenderer>();
	auto& exitMesh = exitDoor.Get<MorphRenderer>();

	auto& coilMesh = coilEnt.Get<MeshRenderer>();
	auto& coilMesh2 = coilEnt2.Get<MeshRenderer>();

	auto& wireMesh = wireEnt.Get<MeshRenderer>();
	auto& wireMesh2 = wireEnt2.Get<MeshRenderer>();

	auto& buttonMesh = buttonEnt.Get<MorphRenderer>();
	auto& buttonMesh2 = buttonEnt2.Get<MorphRenderer>();

	//auto& sMesh = startEnt.Get<MeshRenderer>();
	//auto& oMesh = optEnt.Get<MeshRenderer>();
	//auto& eMesh = exitEnt.Get<MeshRenderer>();

	glm::mat4 transform = playerTrans.GetModelMatrix();
	glm::mat4 transformFloor = groundTrans.GetModelMatrix();
	glm::mat4 transformBack = backTrans.GetModelMatrix();
	glm::mat4 transformLeft = leftTrans.GetModelMatrix();
	glm::mat4 transformRight = rightTrans.GetModelMatrix();
	glm::mat4 transformStart = startTrans.GetModelMatrix();
	glm::mat4 transformExit = exitTrans.GetModelMatrix();

	glm::mat4 transformCoil = coilTrans.GetModelMatrix();
	glm::mat4 transformCoil2 = coilTrans2.GetModelMatrix();

	glm::mat4 transformWire = wireTrans.GetModelMatrix();
	glm::mat4 transformWire2 = wireTrans2.GetModelMatrix();

	glm::mat4 transformButton = buttonTrans.GetModelMatrix();
	glm::mat4 transformButton2 = buttonTrans2.GetModelMatrix();

	//glm::mat4 transformS = sTrans.GetModelMatrix();
	//glm::mat4 transformO = oTrans.GetModelMatrix();
	//glm::mat4 transformE = eTrans.GetModelMatrix();

	if (!buttonAnimOn && playerTrans.GetPositionX() - buttonTrans.GetPositionX() < 3.0f && playerTrans.GetPositionX() - buttonTrans.GetPositionX() > -3.0f
		&& playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() > -3.0f)
	{
		button1Watch.Poll(window);
	}

	if (!button2AnimOn && playerTrans.GetPositionX() - buttonTrans2.GetPositionX() < 3.0f && playerTrans.GetPositionX() - buttonTrans2.GetPositionX() > -3.0f
		&& playerTrans.GetPositionZ() - buttonTrans2.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans2.GetPositionZ() > -3.0f)
	{
		button2Watch.Poll(window);
	}

	pauseWatch.Poll(window);

#pragma region PlayerMovement
	if (!showLevelComplete && !isPaused)
	{
		isWalking = Input::MovePlayer(window, mainPlayer, camEnt, dt, camFar, camClose, camLeft, camRight);

		if (!peckingFramesApplied && isPecking)
		{
			mainPlayer.Get<MorphRenderer>().SetMesh(*peck1);
			mainPlayer.Get<MorphAnimation>().SetFrames(peckFrames);
			mainPlayer.Get<MorphAnimation>().SetLoop(false);
			mainPlayer.Get<MorphAnimation>().SetTime(0.15f);
			peckingFramesApplied = true;
			idleFramesApplied = false;
			walkFramesApplied = false;
		}

		if (isPecking && mainPlayer.Get<MorphAnimation>().GetIsDone())
		{
			isPecking = false;
			peckingFramesApplied = false;
		}

		if (!isPecking && isWalking && !walkFramesApplied)
		{
			mainPlayer.Get<MorphRenderer>().SetMesh(*walk1);
			mainPlayer.Get<MorphAnimation>().SetFrames(walkFrames);
			mainPlayer.Get<MorphAnimation>().SetLoop(true);
			mainPlayer.Get<MorphAnimation>().SetTime(0.05f);
			walkFramesApplied = true;
			idleFramesApplied = false;
		}

		if (!isPecking && !isWalking && !idleFramesApplied)
		{
			mainPlayer.Get<MorphRenderer>().SetMesh(*idle1);
			mainPlayer.Get<MorphAnimation>().SetFrames(idleFrames);
			mainPlayer.Get<MorphAnimation>().SetLoop(true);
			mainPlayer.Get<MorphAnimation>().SetTime(0.3f);
			idleFramesApplied = true;
			walkFramesApplied = false;
		}

		mainPlayer.Get<MorphAnimation>().Update(dt);
	}
#pragma endregion

	//Input::MoveCamera(window, camEnt, dt);
	if (buttonAnimOn)
	{
		if (buttonEnt.Get<MorphAnimation>().GetIsDone())
		{
			buttonEnt.Get<MorphAnimation>().SetFrames(buttonFrames);
			buttonEnt.Get<MorphAnimation>().SetTime(0.2f);
			buttonAnimOn = false;
		}

		buttonEnt.Get<MorphAnimation>().Update(dt);
	}


	if (button2AnimOn)
	{
		if (buttonEnt2.Get<MorphAnimation>().GetIsDone())
		{
			buttonEnt2.Get<MorphAnimation>().SetFrames(buttonFrames);
			buttonEnt2.Get<MorphAnimation>().SetTime(0.2f);
			button2AnimOn = false;
		}

		buttonEnt2.Get<MorphAnimation>().Update(dt);
	}

	if (startDoor.Get<Door>().GetOpen())
	{
		if (startDoor.Get<MorphAnimation>().GetIsDone())
		{
			startDoor.Get<MorphAnimation>().SetFrames(doorCloseFrames);
			startDoor.Get<MorphAnimation>().SetTime(0.1f);
			doorClosingApplied = true;
			doorOpenApplied = false;
		}
	}

	if (!startDoor.Get<Door>().GetOpen())
	{
		if (startDoor.Get<MorphAnimation>().GetIsDone())
		{
			startDoor.Get<MorphAnimation>().SetFrames(doorFrames);
			startDoor.Get<MorphAnimation>().SetTime(0.1f);
			doorClosingApplied = false;
			doorOpenApplied = true;
		}
	}

	if (exitDoor.Get<Door>().GetOpen())
	{
		if (exitDoor.Get<MorphAnimation>().GetIsDone())
		{
			exitDoor.Get<MorphAnimation>().SetFrames(doorCloseFrames);
			exitDoor.Get<MorphAnimation>().SetTime(0.1f);
			doorClosingApplied2 = true;
			doorOpenApplied2 = false;
		}
	}

	if (!exitDoor.Get<Door>().GetOpen())
	{
		if (exitDoor.Get<MorphAnimation>().GetIsDone())
		{
			exitDoor.Get<MorphAnimation>().SetFrames(doorFrames);
			exitDoor.Get<MorphAnimation>().SetTime(0.1f);
			doorClosingApplied2 = false;
			doorOpenApplied2 = true;
		}
	}

	GetCursorPos(&mousePos);

	ScreenToClient(hWnd, &mousePos);

	//Exits the game if exit is clicked in pause menu
	if (GetAsyncKeyState(0x01) && isPaused && mousePos.y > 403 && mousePos.y < 597 && mousePos.x > 865 && mousePos.x < 1097)
	{
		glfwSetWindowShouldClose(window, true);
	}

	//Retry the level
	if (GetAsyncKeyState(0x01) && isPaused && mousePos.y > 403 && mousePos.y < 595 && mousePos.x > 487 && mousePos.x < 714)
	{
		levelRetry = true;
	}

	if (lightOn)
		lightInt = 1;
	else
		lightInt = 0;

	untexturedShader->SetUniform("u_LightOn", lightInt);
	shader->SetUniform("u_LightOn", lightInt);
	pauseShader->SetUniform("u_LightOn", lightInt);
	animShader->SetUniform("u_LightOn", lightInt);

	auto basicEffect = &FBO.Get<PostEffect>();
	auto shadowBuffer = &shadowBufferEnt.Get<Framebuffer>();

	basicEffect->Clear();
	shadowBuffer->Clear();

	for (int i = 0; i < effects.size(); i++)
	{
		effects[i]->Clear();
	}

	glm::mat4 LightProjectionMatrix = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, -1000.0f, 1000.0f);
	glm::mat4 LightViewMatrix = glm::lookAt(glm::vec3(-theSun._lightDirection), glm::vec3(), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 LightSpaceViewProjection = LightProjectionMatrix * LightViewMatrix;

	glViewport(0, 0, shadowWidth, shadowHeight);
	shadowBuffer->Bind();

	for (int i = 0; i < entList.size(); i++)
	{
		if (i < 5)
		{
			simpleDepthShader->Bind();
			entList[i]->Get<MorphRenderer>().Render(simpleDepthShader, camera, entList[i]->Get<Transform>().GetModelMatrix(), LightSpaceViewProjection);
			simpleDepthShader->UnBind();
		}
		else
		{
			simpleDepthShader->Bind();
			entList[i]->Get<MeshRenderer>().Render(simpleDepthShader, camera, entList[i]->Get<Transform>().GetModelMatrix(), LightSpaceViewProjection);
			simpleDepthShader->UnBind();
		}
	}

	shadowBuffer->Unbind();

	glfwGetWindowSize(window, &width, &height);

	glViewport(0, 0, width, height);

	basicEffect->BindBuffer(0);

	if (wireEnt.Get<Wire>().GetIsPowered())
		startDoor.Get<Door>().SetOpen(true);
	else 
		startDoor.Get<Door>().SetOpen(false);

	if (wireEnt2.Get<Wire>().GetIsPowered())
		exitDoor.Get<Door>().SetOpen(true);
	else
		exitDoor.Get<Door>().SetOpen(false);


#pragma region Renders
	if (isTextured)
	{	
		animShader->Bind();
		animShader->SetUniform("s_Diffuse", 0);
		drumstickMat.Albedo->Bind(0);
		shadowBuffer->BindDepthAsTexture(30);
		drumMesh.Render(camera, transform);

		animShader->SetUniform("s_Diffuse", 1);

		if (!startDoor.Get<Door>().GetOpen())
		{
			doorMat.Albedo->Bind(1);
			startDoor.Get<MorphRenderer>().Render(camera, transformStart, LightSpaceViewProjection);
		}
		else
		{
			doorOnMat.Albedo->Bind(1);
			startDoor.Get<MorphRenderer>().Render(camera, transformStart, LightSpaceViewProjection);
		}

		if (!exitDoor.Get<Door>().GetOpen())
		{
			doorMat.Albedo->Bind(1);
			exitDoor.Get<MorphRenderer>().Render(camera, transformExit, LightSpaceViewProjection);
		}
		else
		{
			doorOnMat.Albedo->Bind(1);
			exitDoor.Get<MorphRenderer>().Render(camera, transformExit, LightSpaceViewProjection);
		}

		//Buttons
		animShader->SetUniform("s_Diffuse", 2);
		buttonMat.Albedo->Bind(2);
		buttonEnt.Get<MorphRenderer>().Render(camera, transformButton, LightSpaceViewProjection);
		buttonEnt2.Get<MorphRenderer>().Render(camera, transformButton2, LightSpaceViewProjection);
		shadowBuffer->UnbindTexture(30);

		shader->Bind();

		shader->SetUniform("s_Diffuse", 0);
		floorMat.Albedo->Bind(0);
		shadowBuffer->BindDepthAsTexture(30);
		floorMesh.Render(camera, transformFloor); 

		shader->SetUniform("s_Diffuse", 1);
		wallMat.Albedo->Bind(1);
		backMesh.Render(camera, transformBack);
		leftMesh.Render(camera, transformLeft);
		rightMesh.Render(camera, transformRight);

		shader->SetUniform("s_Diffuse", 3);
		if (!startDoor.Get<Door>().GetOpen())
		{
			coilMatOff.Albedo->Bind(3);
			coilEnt.Get<MeshRenderer>().Render(camera, transformCoil, LightSpaceViewProjection);
		}
		else
		{
			coilMatOn.Albedo->Bind(3);
			coilEnt.Get<MeshRenderer>().Render(camera, transformCoil, LightSpaceViewProjection);
		}

		if (!exitDoor.Get<Door>().GetOpen())
		{
			coilMatOff.Albedo->Bind(3);
			coilEnt2.Get<MeshRenderer>().Render(camera, transformCoil2, LightSpaceViewProjection);
		}
		else
		{
			coilMatOn.Albedo->Bind(3);
			coilEnt2.Get<MeshRenderer>().Render(camera, transformCoil2, LightSpaceViewProjection);
		}

		//Wires
		shader->SetUniform("s_Diffuse", 4);
		if (wireEnt.Get<Wire>().GetIsPowered())
		{
			wireMatOn.Albedo->Bind(4);
			wireEnt.Get<MeshRenderer>().Render(camera, transformWire, LightSpaceViewProjection);
		}
		else
		{
			wireMat.Albedo->Bind(4);
			wireEnt.Get<MeshRenderer>().Render(camera, transformWire, LightSpaceViewProjection);
		}

		if (wireEnt2.Get<Wire>().GetIsPowered())
		{
			wireMatOn.Albedo->Bind(4);
			wireEnt2.Get<MeshRenderer>().Render(camera, transformWire2, LightSpaceViewProjection);
		}
		else
		{
			wireMat.Albedo->Bind(4);
			wireEnt2.Get<MeshRenderer>().Render(camera, transformWire2, LightSpaceViewProjection);
		}

		shadowBuffer->UnbindTexture(30);
		//sMesh.Render(camera, transformS);
		//oMesh.Render(camera, transformO);
		//eMesh.Render(camera, transformE);
	}
	else
	{
		animShader->Bind();
		animShader->SetUniform("s_Diffuse", 0);
		clearMat.Albedo->Bind(0);
		shadowBuffer->BindDepthAsTexture(30);
		drumMesh.Render(camera, transform);
		animShader->SetUniform("s_Diffuse", 1);
		//clearMat.Albedo->Bind(1);
		//startMesh.Render(camera, transformStart);
		//exitMesh.Render(camera, transformExit);
		//optMesh.Render(camera, transformOpt);
		//clearMat.Albedo->Unbind(1); 
		shadowBuffer->UnbindTexture(30);

		shader->Bind();
		shader->SetUniform("s_Diffuse", 0);
		clearMat.Albedo->Bind(0);
		shadowBuffer->BindDepthAsTexture(30);
		floorMesh.Render(camera, transformFloor); 
		backMesh.Render(camera, transformBack);
		leftMesh.Render(camera, transformLeft);
		rightMesh.Render(camera, transformRight);
		startMesh.Render(camera, transformStart);
		exitMesh.Render(camera, transformExit);
		coilMesh.Render(camera, transformCoil);
		coilMesh2.Render(camera, transformCoil2);
		wireMesh.Render(camera, transformWire);
		wireMesh2.Render(camera, transformWire2);
		buttonMesh.Render(camera, transformButton);
		buttonMesh2.Render(camera, transformButton2);
		shadowBuffer->UnbindTexture(30);

		//leftAMesh.Render(camera, transformLeftA);
		//rightAMesh.Render(camera, transformRightA);
		//sMesh.Render(camera, transformS);
		//oMesh.Render(camera, transformO);
		//eMesh.Render(camera, transformE);
		//shader->SetUniform("s_Diffuse", 0);
		//clearMat.Albedo->Bind(1);
	}

#pragma endregion

	basicEffect->UnbindBuffer();

	effects[activeEffect]->ApplyEffect(basicEffect);

	effects[activeEffect]->DrawToScreen();

	startDoor.Get<AABB>().Update();
	exitDoor.Get<AABB>().Update();
	backWallEnt.Get<AABB>().Update();
	buttonEnt.Get<AABB>().Update();
	buttonEnt2.Get<AABB>().Update();
	coilEnt.Get<AABB>().Update();
	coilEnt2.Get<AABB>().Update();
	wireEnt.Get<Wire>().Update();
	wireEnt2.Get<Wire>().Update();
	buttonEnt.Get<Lever>().Update();
	buttonEnt2.Get<Lever>().Update();


	//Door Logic
	if (startDoor.Get<Door>().GetOpen() && doorOpenApplied)
		startDoor.Get<MorphAnimation>().Update(dt);
	if (!startDoor.Get<Door>().GetOpen() && doorClosingApplied)
		startDoor.Get<MorphAnimation>().Update(dt);

	if (exitDoor.Get<Door>().GetOpen() && doorOpenApplied2)
		exitDoor.Get<MorphAnimation>().Update(dt);
	if (!exitDoor.Get<Door>().GetOpen() && doorClosingApplied2)
		exitDoor.Get<MorphAnimation>().Update(dt);
	//if (startDoor.Get<Door>().GetOpen())
	//	startDoor.Get<MorphAnimation>().Update(dt);
	//
	//if (exitDoor.Get<Door>().GetOpen())
	//	exitDoor.Get<MorphAnimation>().Update(dt);
	//
	//if (optionDoor.Get<Door>().GetOpen())
	//	optionDoor.Get<MorphAnimation>().Update(dt);
	//
	//if (startDoor.Get<AABB>().GetComplete())
	//	levelComplete = true;
	//
	//if (exitDoor.Get<AABB>().GetComplete())
	//	glfwSetWindowShouldClose(window, true);

	if (startDoor.Get<AABB>().GetComplete())
	{
		levelComplete = true;
	}

	if (exitDoor.Get<AABB>().GetComplete())
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void MainMenuLevel::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}