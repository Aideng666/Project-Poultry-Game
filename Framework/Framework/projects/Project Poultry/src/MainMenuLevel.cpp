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
	optionDoor = Entity::Create();
	exitDoor = Entity::Create();
	floorEnt = Entity::Create();
	backWallEnt = Entity::Create();
	leftWallEnt = Entity::Create();
	rightWallEnt = Entity::Create();
	leftAngledWall = Entity::Create();
	rightAngledWall = Entity::Create();
	startEnt = Entity::Create();
	optEnt = Entity::Create();
	exitEnt = Entity::Create();
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

	float distance = glm::distance(point2, point1);

	totalTime = distance / speed;

	effects.clear();

	InitShaders();
	InitTextures();

#pragma region Transforms

	//Floor Transform
	auto& floorTrans = floorEnt.Add<Transform>();
	floorTrans.SetScale(glm::vec3(2.0f));

	//Wall Transforms
	auto& leftTrans = leftWallEnt.Add<Transform>();
	leftTrans.SetPositionX(-39.0f);
	leftTrans.SetRotationY(90.0f);
	leftTrans.SetPositionY(9.0f);
	leftTrans.SetScale(glm::vec3(1.0f, 5.0f, 1.0f));

	auto& leftATrans = leftAngledWall.Add<Transform>();
	leftATrans.SetRotationY(45.0f);
	leftATrans.SetPositionX(-45.0f);
	leftATrans.SetPositionZ(-10.0f);
	leftATrans.SetPositionY(9.0f);
	leftATrans.SetScale(glm::vec3(1.0f, 5.0f, 1.0f));

	auto& rightATrans = rightAngledWall.Add<Transform>();
	rightATrans.SetRotationY(-45.0f);
	rightATrans.SetPositionX(45.0f);
	rightATrans.SetPositionZ(-10.0f);
	rightATrans.SetPositionY(9.0f);
	rightATrans.SetScale(glm::vec3(1.0f, 5.0f, 1.0f));

	auto& rightTrans = rightWallEnt.Add<Transform>();
	rightTrans.SetPositionX(39.0f);
	rightTrans.SetRotationY(90.0f);
	rightTrans.SetPositionY(9.0f);
	rightTrans.SetScale(glm::vec3(1.0f, 5.0f, 1.0f));

	auto& backTrans = backWallEnt.Add<Transform>();
	backTrans.SetPositionZ(-39.0f);
	backTrans.SetPositionY(9.0f);
	backTrans.SetScale(glm::vec3(1.0f, 5.0f, 1.0f));

	//Player Transform
	auto& playerTrans = mainPlayer.Add<Transform>();
	playerTrans.SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));
	playerTrans.SetRotationY(0.0f);

	//Door Transforms
	auto& startTrans = startDoor.Add<Transform>();
	startTrans.SetPosition(glm::vec3(0.0f, -1.0f, -38.0f));
	startTrans.SetScale(glm::vec3(1.5f));

	auto& optTrans = optionDoor.Add<Transform>();
	optTrans.SetPosition(glm::vec3(-30.0f, -1.0f, -27.5f));
	optTrans.SetScale(glm::vec3(1.5f));
	optTrans.SetRotationY(45.0f);
	
	auto& exitTrans = exitDoor.Add<Transform>();
	exitTrans.SetPosition(glm::vec3(30.0f, -1.0f, -27.5f));
	exitTrans.SetScale(glm::vec3(1.5f));
	exitTrans.SetRotationY(-45.0f);

	//Text Transforms
	auto& sTrans = startEnt.Add<Transform>();
	sTrans.SetPosition(glm::vec3(-4.0f, 2.5f, -25.0f));
	sTrans.SetScale(glm::vec3(4.0f));

	auto& eTrans = exitEnt.Add<Transform>();
	eTrans.SetRotationY(-45.0f);
	eTrans.SetPosition(glm::vec3(19.0f, 2.5f, -21.0f));
	eTrans.SetScale(glm::vec3(4.0f));

	auto& oTrans = optEnt.Add<Transform>();
	oTrans.SetRotationY(45.0f);
	oTrans.SetPosition(glm::vec3(-26.0f, 2.5f, -13.0f));
	oTrans.SetScale(glm::vec3(4.0f));
#pragma endregion
	
	//DOORS
	auto& doorS = startDoor.Add<Door>();
	doorS.SetOpen(true);
	auto& doorO = optionDoor.Add<Door>();
	doorO.SetOpen(true);
	auto& doorE = exitDoor.Add<Door>();
	doorE.SetOpen(true);

	//AABB
	auto& leftCol = leftWallEnt.Add<AABB>(leftWallEnt, mainPlayer);
	auto& leftACol = leftAngledWall.Add<AABB>(leftAngledWall, mainPlayer);
	auto& rightCol = rightWallEnt.Add<AABB>(rightWallEnt, mainPlayer);
	auto& rightACol = rightAngledWall.Add<AABB>(rightAngledWall, mainPlayer);
	auto& backCol = backWallEnt.Add<AABB>(backWallEnt, mainPlayer);
	auto& startCol = startDoor.Add<AABB>(startDoor, mainPlayer);
	auto& optCol = optionDoor.Add<AABB>(optionDoor, mainPlayer);
	auto& exitCol = exitDoor.Add<AABB>(exitDoor, mainPlayer);

	doorFrames.push_back(std::unique_ptr<Mesh>(door1));
	doorFrames.push_back(std::unique_ptr<Mesh>(door2));
	doorFrames.push_back(std::unique_ptr<Mesh>(door3));
	doorFrames.push_back(std::unique_ptr<Mesh>(door4));
	/*doorFrames.push_back(std::unique_ptr<Mesh>(door5));
	doorFrames.push_back(std::unique_ptr<Mesh>(door6));
	doorFrames.push_back(std::unique_ptr<Mesh>(door7));
	doorFrames.push_back(std::unique_ptr<Mesh>(door8));
	doorFrames.push_back(std::unique_ptr<Mesh>(door9));
	doorFrames.push_back(std::unique_ptr<Mesh>(door10));*/

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
	//InitAnims();

	//Load the meshes
	auto& playerMesh = mainPlayer.Add<MorphRenderer>(mainPlayer, *drumstick, animShader);
	auto& backMesh = backWallEnt.Add<MeshRenderer>(backWallEnt, *backWall, shader);
	auto& leftMesh = leftWallEnt.Add<MeshRenderer>(leftWallEnt, *leftWall, shader);
	auto& rightMesh = rightWallEnt.Add<MeshRenderer>(rightWallEnt, *rightWall, shader);
	auto& leftAMesh = leftAngledWall.Add<MeshRenderer>(leftAngledWall, *leftWall, shader);
	auto& rightAMesh = rightAngledWall.Add<MeshRenderer>(rightAngledWall, *rightWall, shader);
	auto& floorMesh = floorEnt.Add<MeshRenderer>(floorEnt, *floor, shader);
	auto& playMesh = startDoor.Add<MorphRenderer>(startDoor, *door1, animShader);
	auto& exitMesh = exitDoor.Add<MorphRenderer>(exitDoor, *door1, animShader);
	auto& optMesh = optionDoor.Add<MorphRenderer>(optionDoor, *door1, animShader);
	auto& sMesh = startEnt.Add<MeshRenderer>(startEnt, *startWord, shader);
	auto& oMesh = optEnt.Add<MeshRenderer>(optEnt, *optionsWord, shader);
	auto& eMesh = exitEnt.Add<MeshRenderer>(exitEnt, *exitWord, shader);

	entList.push_back(&mainPlayer);
	entList.push_back(&startDoor);
	entList.push_back(&exitDoor);
	entList.push_back(&optionDoor);
	entList.push_back(&floorEnt);
	entList.push_back(&leftWallEnt);
	entList.push_back(&leftAngledWall);
	entList.push_back(&rightWallEnt);
	entList.push_back(&rightAngledWall);
	entList.push_back(&startEnt);
	entList.push_back(&optEnt);
	entList.push_back(&exitEnt);

	//Load the animations
	auto& startAnimator = startDoor.Add<MorphAnimation>(startDoor);
	startAnimator.SetTime(0.2f);
	startAnimator.SetFrames(doorFrames);
	startAnimator.SetLoop(false);

	auto& exitAnimator = exitDoor.Add<MorphAnimation>(exitDoor);
	exitAnimator.SetTime(0.2f);
	exitAnimator.SetFrames(doorFrames);
	exitAnimator.SetLoop(false);

	auto& optAnimator = optionDoor.Add<MorphAnimation>(optionDoor);
	optAnimator.SetTime(0.2f);
	optAnimator.SetFrames(doorFrames);
	optAnimator.SetLoop(false);

	auto& walkAnimator = mainPlayer.Add<MorphAnimation>(mainPlayer);
	walkAnimator.SetTime(0.05f);
	walkAnimator.SetFrames(walkFrames);

	//Camera Object
	auto& camera = camEnt.Add<Camera>();
	camera.SetPosition(glm::vec3(0, 15, 15)); // Set initial position
	camera.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
	camera.LookAt(glm::vec3(0.0f)); // Look at center of the screen
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

	shader->SetUniform("u_Position", currentPos);
	animShader->SetUniform("u_Position", currentPos);

	//Transforms
	auto& playerTrans = mainPlayer.Get<Transform>();
	auto& groundTrans = floorEnt.Get<Transform>();
	auto& leftTrans = leftWallEnt.Get<Transform>();
	auto& leftATrans = leftAngledWall.Get<Transform>();
	auto& rightATrans = rightAngledWall.Get<Transform>();
	auto& rightTrans = rightWallEnt.Get<Transform>();
	auto& backTrans = backWallEnt.Get<Transform>();
	auto& startTrans = startDoor.Get<Transform>();
	auto& exitTrans = exitDoor.Get<Transform>();
	auto& optTrans = optionDoor.Get<Transform>();
	auto& sTrans = startEnt.Get<Transform>();
	auto& oTrans = optEnt.Get<Transform>();
	auto& eTrans = exitEnt.Get<Transform>();

	auto& camera = camEnt.Get<Camera>();

	//camera.LookAt(glm::vec3(playerTrans.GetPosition()));

	auto& drumMesh = mainPlayer.Get<MorphRenderer>();
	auto& floorMesh = floorEnt.Get<MeshRenderer>();
	auto& backMesh = backWallEnt.Get<MeshRenderer>();
	auto& leftMesh = leftWallEnt.Get<MeshRenderer>();
	auto& rightMesh = rightWallEnt.Get<MeshRenderer>();
	auto& leftAMesh = leftAngledWall.Get<MeshRenderer>();
	auto& rightAMesh = rightAngledWall.Get<MeshRenderer>();
	auto& startMesh = startDoor.Get<MorphRenderer>();
	auto& exitMesh = exitDoor.Get<MorphRenderer>();
	auto& optMesh = optionDoor.Get<MorphRenderer>();
	auto& sMesh = startEnt.Get<MeshRenderer>();
	auto& oMesh = optEnt.Get<MeshRenderer>();
	auto& eMesh = exitEnt.Get<MeshRenderer>();

	glm::mat4 transform = playerTrans.GetModelMatrix();
	glm::mat4 transformFloor = groundTrans.GetModelMatrix();
	glm::mat4 transformBack = backTrans.GetModelMatrix();
	glm::mat4 transformLeft = leftTrans.GetModelMatrix();
	glm::mat4 transformRight = rightTrans.GetModelMatrix();
	glm::mat4 transformLeftA = leftATrans.GetModelMatrix();
	glm::mat4 transformRightA = rightATrans.GetModelMatrix();
	glm::mat4 transformStart = startTrans.GetModelMatrix();
	glm::mat4 transformExit = exitTrans.GetModelMatrix();
	glm::mat4 transformOpt = optTrans.GetModelMatrix();
	glm::mat4 transformS = sTrans.GetModelMatrix();
	glm::mat4 transformO = oTrans.GetModelMatrix();
	glm::mat4 transformE = eTrans.GetModelMatrix();

#pragma region PlayerMovement
	isWalking = Input::MovePlayer(window, mainPlayer, camEnt, dt, camFar, camClose, camLeft, camRight);

	if (isWalking)
	{
		mainPlayer.Get<MorphAnimation>().Update(dt);
	}
#pragma endregion

#pragma region CameraMovement
	Input::MoveCamera(window, camEnt, dt);
#pragma endregion

	GetCursorPos(&mousePos);

	ScreenToClient(hWnd, &mousePos);

	if (GetAsyncKeyState(0x01) && isPaused && mousePos.y > 323 && mousePos.y < 476 && mousePos.x > 575 && mousePos.x < 730)
	{
		std::cout << mousePos.x << " " << mousePos.y << std::endl;
		glfwSetWindowShouldClose(window, true);
	}

	lightNum = Input::ChangeLighting(window, lightNum);

	if (lightNum < 1 || lightNum > 5)
		lightNum = 1;

	shader->SetUniform("u_LightNum", lightNum);
	animShader->SetUniform("u_LightNum", lightNum);

	if (lightOn)
		lightInt = 1;
	else
		lightInt = 0;

	shader->SetUniform("u_LightOn", lightInt);
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
		if (i < 4)
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

#pragma region Renders
	if (isTextured)
	{	
		animShader->Bind();
		animShader->SetUniform("s_Diffuse", 0);
		drumstickMat.Albedo->Bind(0);
		shadowBuffer->BindDepthAsTexture(30);
		drumMesh.Render(camera, transform);
		animShader->SetUniform("s_Diffuse", 1);
		doorMat.Albedo->Bind(1);
		startMesh.Render(camera, transformStart);
		exitMesh.Render(camera, transformExit);
		optMesh.Render(camera, transformOpt);
		doorMat.Albedo->Unbind(1);	
		shadowBuffer->UnbindTexture(30);

		shader->Bind();
		shader->SetUniform("s_Diffuse", 0);
		wallMat.Albedo->Bind(0);
		shadowBuffer->BindDepthAsTexture(30);
		leftMesh.Render(camera, transformLeft);
		rightMesh.Render(camera, transformRight);
		backMesh.Render(camera, transformBack);
		leftAMesh.Render(camera, transformLeftA);
		rightAMesh.Render(camera, transformRightA);
		sMesh.Render(camera, transformS);
		oMesh.Render(camera, transformO);
		eMesh.Render(camera, transformE);
		shader->SetUniform("s_Diffuse", 1);
		floorMat.Albedo->Bind(1);
		floorMesh.Render(camera, transformFloor); 
		shadowBuffer->UnbindTexture(30);
	}
	else
	{
		animShader->Bind();
		animShader->SetUniform("s_Diffuse", 0);
		clearMat.Albedo->Bind(0);
		shadowBuffer->BindDepthAsTexture(30);
		drumMesh.Render(camera, transform);
		animShader->SetUniform("s_Diffuse", 1);
		clearMat.Albedo->Bind(1);
		startMesh.Render(camera, transformStart);
		exitMesh.Render(camera, transformExit);
		optMesh.Render(camera, transformOpt);
		clearMat.Albedo->Unbind(1); 
		shadowBuffer->UnbindTexture(30);

		shader->Bind();
		shader->SetUniform("s_Diffuse", 0);
		clearMat.Albedo->Bind(0);
		shadowBuffer->BindDepthAsTexture(30);
		leftMesh.Render(camera, transformLeft);
		rightMesh.Render(camera, transformRight);
		backMesh.Render(camera, transformBack);
		leftAMesh.Render(camera, transformLeftA);
		rightAMesh.Render(camera, transformRightA);
		sMesh.Render(camera, transformS);
		oMesh.Render(camera, transformO);
		eMesh.Render(camera, transformE);
		shader->SetUniform("s_Diffuse", 1);
		clearMat.Albedo->Bind(1);
		floorMesh.Render(camera, transformFloor); 
		shadowBuffer->UnbindTexture(30);
	}

#pragma endregion

	basicEffect->UnbindBuffer();

	effects[activeEffect]->ApplyEffect(basicEffect);

	effects[activeEffect]->DrawToScreen();

	startDoor.Get<AABB>().Update();
	optionDoor.Get<AABB>().Update();
	exitDoor.Get<AABB>().Update();
	leftWallEnt.Get<AABB>().Update();
	rightWallEnt.Get<AABB>().Update();
	backWallEnt.Get<AABB>().Update();
	leftAngledWall.Get<AABB>().Update();
	rightAngledWall.Get<AABB>().Update();

	if (startDoor.Get<Door>().GetOpen())
		startDoor.Get<MorphAnimation>().Update(dt);

	if (exitDoor.Get<Door>().GetOpen())
		exitDoor.Get<MorphAnimation>().Update(dt);

	if (optionDoor.Get<Door>().GetOpen())
		optionDoor.Get<MorphAnimation>().Update(dt);

	if (startDoor.Get<AABB>().GetComplete())
		levelComplete = true;

	if (exitDoor.Get<AABB>().GetComplete())
		glfwSetWindowShouldClose(window, true);

}

void MainMenuLevel::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}
