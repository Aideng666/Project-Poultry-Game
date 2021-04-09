#include "FinalLevel.h"
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

Tree endingTree(0);

FinalLevel::FinalLevel(std::string sceneName, GLFWwindow* wind)
	: Scene(sceneName, wind)
{

	mainPlayer = Entity::Create();
	floorEnt = Entity::Create();
	leftEnt = Entity::Create();
	rightEnt = Entity::Create();
	backEnt = Entity::Create();
	doorEnt = Entity::Create();
	completeEnt = Entity::Create();
	pauseEnt = Entity::Create();
	optionsMenuEnt = Entity::Create();
	optionEnt = Entity::Create();
	exitEnt = Entity::Create();
	retryEnt = Entity::Create();
	buttonEnt = Entity::Create();
	wireEnt = Entity::Create();
	coilEnt = Entity::Create();
	coilEnt2 = Entity::Create();
	coilEnt3 = Entity::Create();
	coilEnt4 = Entity::Create();
	coilEnt5 = Entity::Create();
	coilEnt6 = Entity::Create();
	coilEnt7 = Entity::Create();
	coilEnt8 = Entity::Create();
	coilEnt9 = Entity::Create();
	coilEnt10 = Entity::Create();
	coilEnt11 = Entity::Create();
	tabletEnt = Entity::Create();
	tabletScreenEnt = Entity::Create();
	tutEnt = Entity::Create();
	orEnt = Entity::Create();

	muteEnt = Entity::Create();
	colorBlindEnt = Entity::Create();
	brightEnt = Entity::Create();
	musicEnt = Entity::Create();
	soundEnt = Entity::Create();
	controlsEnt = Entity::Create();

	FBO = Entity::Create();
	greyscaleEnt = Entity::Create();
	sepiaEnt = Entity::Create();
	colorCorrectEnt = Entity::Create();

	filmGrainEnt = Entity::Create();
	pixelateEnt = Entity::Create();
	bloomEnt = Entity::Create();

	gBufferEnt = Entity::Create();

	camEnt = Entity::Create();
	uiCamEnt = Entity::Create();
	topViewCamEnt = Entity::Create();

	InitMeshes();
}

void FinalLevel::InitScene()
{

	Application::SetClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	scene = new entt::registry();

	Entity::SetReg(scene);

	//Initialize the shaders for the level
	InitShaders();
	//Initialize the Textures for the level
	InitTextures();
	//Initializes the Luts
	InitLuts();

	//Player transform
	auto& playerTrans = mainPlayer.Add<Transform>();
	playerTrans.SetPosition(glm::vec3(0.0f, 1.0f, 30.0f));
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

	//Door transforms
	auto& doorTrans = doorEnt.Add<Transform>();
	doorTrans.SetPosition(glm::vec3(0.0f, -1.0f, -36.0f));
	doorTrans.SetScale(glm::vec3(1.5f));

	//Button transforms
	auto& buttonTrans = buttonEnt.Add<Transform>();
	buttonTrans.SetPosition(glm::vec3(0.1f, -1.0f, 11.0f));
	buttonTrans.SetRotationY(90.0f);

	//Wire transforms
	auto& wireTrans = wireEnt.Add<Transform>();
	wireTrans.SetPosition(glm::vec3(0.0f, 1.0f, 3.0f));

	//Coil transform
	auto& coilTrans = coilEnt.Add<Transform>();
	coilTrans.SetPosition(glm::vec3(-18.2f, 1.0f, -34.f));
	coilTrans.SetScale(glm::vec3(3.0f));
	coilTrans.SetRotationY(180.0f);

	auto& coilTrans2 = coilEnt2.Add<Transform>();
	coilTrans2.SetPosition(glm::vec3(-16.0f, 30.0f, -49.f));
	coilTrans2.SetScale(glm::vec3(3.0f));
	coilTrans2.SetRotationX(90.0f);

	auto& coilTrans3 = coilEnt3.Add<Transform>();
	coilTrans3.SetPosition(glm::vec3(-12.4f, 30.0f, -49.f));
	coilTrans3.SetScale(glm::vec3(3.0f));
	coilTrans3.SetRotationX(90.0f);

	auto& coilTrans4 = coilEnt4.Add<Transform>();
	coilTrans4.SetPosition(glm::vec3(-8.8f, 30.0f, -49.f));
	coilTrans4.SetScale(glm::vec3(3.0f));
	coilTrans4.SetRotationX(90.0f);

	auto& coilTrans5 = coilEnt5.Add<Transform>();
	coilTrans5.SetPosition(glm::vec3(-5.2f, 30.0f, -49.f));
	coilTrans5.SetScale(glm::vec3(3.0f));
	coilTrans5.SetRotationX(90.0f);

	auto& coilTrans6 = coilEnt6.Add<Transform>();
	coilTrans6.SetPosition(glm::vec3(-1.6f, 30.0f, -49.f));
	coilTrans6.SetScale(glm::vec3(3.0f));
	coilTrans6.SetRotationX(90.0f);

	auto& coilTrans7 = coilEnt7.Add<Transform>();
	coilTrans7.SetPosition(glm::vec3(2.0f, 30.0f, -49.f));
	coilTrans7.SetScale(glm::vec3(3.0f));
	coilTrans7.SetRotationX(90.0f);

	auto& coilTrans8 = coilEnt8.Add<Transform>();
	coilTrans8.SetPosition(glm::vec3(5.6f, 30.0f, -49.f));
	coilTrans8.SetScale(glm::vec3(3.0f));
	coilTrans8.SetRotationX(90.0f);

	auto& coilTrans9 = coilEnt9.Add<Transform>();
	coilTrans9.SetPosition(glm::vec3(9.2f, 30.0f, -49.f));
	coilTrans9.SetScale(glm::vec3(3.0f));
	coilTrans9.SetRotationX(90.0f);

	auto& coilTrans10 = coilEnt10.Add<Transform>();
	coilTrans10.SetPosition(glm::vec3(12.8f, 30.0f, -49.f));
	coilTrans10.SetScale(glm::vec3(3.0f));
	coilTrans10.SetRotationX(90.0f);

	auto& coilTrans11 = coilEnt11.Add<Transform>();
	coilTrans11.SetPosition(glm::vec3(16.4f, 30.0f, -49.f));
	coilTrans11.SetScale(glm::vec3(3.0f));
	coilTrans11.SetRotationX(90.0f);

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
	//optionsTrans.SetRotationY(96.0f);

	auto& retryTrans = retryEnt.Add<Transform>();
	retryTrans.SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));
	retryTrans.SetScale(glm::vec3(1.5f));
	//retryTrans.SetRotationX(1.0f);

	auto& exitTrans = exitEnt.Add<Transform>();
	exitTrans.SetPosition(glm::vec3(5.0f, 2.0f, 0.0f));
	exitTrans.SetScale(glm::vec3(1.5f));
	//exitTrans.SetRotationY(96.0f);

	auto& muteTrans = muteEnt.Add<Transform>();
	muteTrans.SetPosition(glm::vec3(4.0f, 2.0f, -2.6f));
	muteTrans.SetScale(glm::vec3(0.3f, 1.0f, 0.3f));
	muteTrans.SetRotationY(180.0f);

	auto& colorBlindTrans = colorBlindEnt.Add<Transform>();
	colorBlindTrans.SetPosition(glm::vec3(4.0f, 2.0f, 3.1f));
	colorBlindTrans.SetScale(glm::vec3(0.3f, 1.0f, 0.3f));
	colorBlindTrans.SetRotationY(180.0f);

	auto& brightTrans = brightEnt.Add<Transform>();
	brightTrans.SetPosition(glm::vec3(4.0f, 2.0f, 4.6f));
	brightTrans.SetScale(glm::vec3(0.3f, 1.0f, 0.3f));
	brightTrans.SetRotationY(180.0f);

	auto& soundTrans = soundEnt.Add<Transform>();
	soundTrans.SetPosition(glm::vec3(4.0f, 2.0f, -1.1f));
	soundTrans.SetScale(glm::vec3(0.3f, 1.0f, 0.3f));
	soundTrans.SetRotationY(180.0f);

	auto& musicTrans = musicEnt.Add<Transform>();
	musicTrans.SetPosition(glm::vec3(4.0f, 2.0f, 0.4f));
	musicTrans.SetScale(glm::vec3(0.3f, 1.0f, 0.3f));
	musicTrans.SetRotationY(180.0f);

	auto& controlsTrans = controlsEnt.Add<Transform>();
	controlsTrans.SetPosition(glm::vec3(4.0f, 2.0f, 6.1f));
	controlsTrans.SetScale(glm::vec3(0.3f, 1.0f, 0.3f));
	controlsTrans.SetRotationY(180.0f);


	auto& tabletTrans = tabletEnt.Add<Transform>();
	tabletTrans.SetPosition(glm::vec3(-6.0f, 5.0f, 10.0f));
	tabletTrans.SetRotationY(180.0f);

	auto& tabletScreenTrans = tabletScreenEnt.Add<Transform>();
	tabletScreenTrans.SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	tabletScreenTrans.SetScale(glm::vec3(0.18f, 1.0f, 0.18f));

	auto& optionsMenuTrans = optionsMenuEnt.Add<Transform>();
	optionsMenuTrans.SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	optionsMenuTrans.SetScale(glm::vec3(0.18f, 1.0f, 0.18f));

	//Interact text transform
	auto& tutTrans = tutEnt.Add<Transform>();
	tutTrans.SetPosition(glm::vec3(1.0f, 2.0f, 5.0f));
	tutTrans.SetScale(glm::vec3(1.0f));

	//AABB
	auto& leftCol = leftEnt.Add<AABB>(leftEnt, mainPlayer);
	auto& rightCol = rightEnt.Add<AABB>(rightEnt, mainPlayer);
	auto& backCol = backEnt.Add<AABB>(backEnt, mainPlayer);
	auto& coilCol = coilEnt.Add<AABB>(coilEnt, mainPlayer, 4.0f, 4.0f);
	coilCol.SetIsAmbient(true);
	auto& buttonCol = buttonEnt.Add<AABB>(buttonEnt, mainPlayer, 2.0f, 2.0f);
	buttonCol.SetIsAmbient(true);

	auto& doorCol = doorEnt.Add<AABB>(doorEnt, mainPlayer);
	doorCol.SetComplete(false);

	//Buttons
	auto& button = buttonEnt.Add<Lever>(wireEnt);
	button.SetPowered(false);

	//Wires
	auto& wire = wireEnt.Add<Wire>(buttonEnt);

	//Gates 
	auto& gate = orEnt.Add<OrGate>(wireEnt, wireEnt, doorEnt);

	//Door
	auto& door = doorEnt.Add<Door>();
	door.SetOpen(false);

	InitAnims();

#pragma region Mesh Loading 
	auto& playerMesh = mainPlayer.Add<MorphRenderer>(mainPlayer, *idle1, animShader);
	auto& floorMesh = floorEnt.Add<MeshRenderer>(floorEnt, *floorL1, shader);
	auto& leftMesh = leftEnt.Add<MeshRenderer>(leftEnt, *leftWall, shader);
	auto& rightMesh = rightEnt.Add<MeshRenderer>(rightEnt, *rightWall, shader);
	auto& backMesh = backEnt.Add<MeshRenderer>(backEnt, *backWall, shader);
	auto& doorMesh = doorEnt.Add<MorphRenderer>(doorEnt, *door1, animShader);
	auto& completeMesh = completeEnt.Add<MeshRenderer>(completeEnt, *screen, shader);
	auto& buttonMesh = buttonEnt.Add<MorphRenderer>(buttonEnt, *buttonM, animShader);
	auto& wireMesh = wireEnt.Add<MeshRenderer>(wireEnt, *finalWire, shader);
	auto& coilMesh = coilEnt.Add<MeshRenderer>(coilEnt, *coil, shader);
	auto& coilMesh2 = coilEnt2.Add<MeshRenderer>(coilEnt2, *coil, shader);
	auto& coilMesh3 = coilEnt3.Add<MeshRenderer>(coilEnt3, *coil, shader);
	auto& coilMesh4 = coilEnt4.Add<MeshRenderer>(coilEnt4, *coil, shader);
	auto& coilMesh5 = coilEnt5.Add<MeshRenderer>(coilEnt5, *coil, shader);
	auto& coilMesh6 = coilEnt6.Add<MeshRenderer>(coilEnt6, *coil, shader);
	auto& coilMesh7 = coilEnt7.Add<MeshRenderer>(coilEnt7, *coil, shader);
	auto& coilMesh8 = coilEnt8.Add<MeshRenderer>(coilEnt8, *coil, shader);
	auto& coilMesh9 = coilEnt9.Add<MeshRenderer>(coilEnt9, *coil, shader);
	auto& coilMesh10 = coilEnt10.Add<MeshRenderer>(coilEnt10, *coil, shader);
	auto& coilMesh11 = coilEnt11.Add<MeshRenderer>(coilEnt11, *coil, shader);
	auto& tutMesh = tutEnt.Add<MeshRenderer>(tutEnt, *tut, untexturedShader);
	auto& pauseMesh = pauseEnt.Add<MeshRenderer>(pauseEnt, *screen, pauseShader);
	auto& optionMesh = optionEnt.Add<MeshRenderer>(optionEnt, *options, pauseShader);
	auto& retryMesh = retryEnt.Add<MeshRenderer>(retryEnt, *retry, pauseShader);
	auto& exitMesh = exitEnt.Add<MeshRenderer>(exitEnt, *exit, pauseShader);
	auto& tabletScreenMesh = tabletScreenEnt.Add<MeshRenderer>(tabletScreenEnt, *screen, pauseShader);
	auto& tabletMesh = tabletEnt.Add<MeshRenderer>(tabletEnt, *tablet, rimLightShader);
	auto& optionsMenuMesh = optionsMenuEnt.Add<MeshRenderer>(optionsMenuEnt, *screen, pauseShader);
	auto& muteMesh = muteEnt.Add<MeshRenderer>(muteEnt, *optionsButton, pauseShader);
	auto& musicMesh = musicEnt.Add<MeshRenderer>(musicEnt, *optionsButton, pauseShader);
	auto& soundMesh = soundEnt.Add<MeshRenderer>(soundEnt, *optionsButton, pauseShader);
	auto& brightMesh = brightEnt.Add<MeshRenderer>(brightEnt, *optionsButton, pauseShader);
	auto& colorBlindMesh = colorBlindEnt.Add<MeshRenderer>(colorBlindEnt, *optionsButton, pauseShader);
	auto& controlsMesh = controlsEnt.Add<MeshRenderer>(controlsEnt, *optionsButton, pauseShader);
#pragma endregion

	entList.push_back(&mainPlayer);
	entList.push_back(&doorEnt);
	entList.push_back(&buttonEnt);
	entList.push_back(&floorEnt);
	entList.push_back(&leftEnt);
	entList.push_back(&rightEnt);
	entList.push_back(&completeEnt);
	entList.push_back(&wireEnt);
	entList.push_back(&coilEnt);
	entList.push_back(&tabletEnt);

	auto& doorAnimator = doorEnt.Add<MorphAnimation>(doorEnt);
	doorAnimator.SetTime(0.1f);
	doorAnimator.SetFrames(doorFrames);
	doorAnimator.SetLoop(false);

	auto& walkAnimator = mainPlayer.Add<MorphAnimation>(mainPlayer);
	walkAnimator.SetTime(0.3f);
	walkAnimator.SetFrames(idleFrames);

	auto& buttonAnimator = buttonEnt.Add<MorphAnimation>(buttonEnt);
	buttonAnimator.SetTime(0.2f);
	buttonAnimator.SetFrames(buttonFrames);
	buttonAnimator.SetLoop(false);

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

	auto& topCam = topViewCamEnt.Add<Camera>();
	topCam.SetPosition(glm::vec3(0, 45, 0)); // Set initial position
	topCam.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
	topCam.LookAt(glm::vec3(0.0f)); // Look at center of the screen
	topCam.SetFovDegrees(90.0f); // Set an initial FOV

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

	auto gBuffer = &gBufferEnt.Add<GBuffer>();
	gBuffer->Init(width, height);

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

	AudioEvent& music = AudioEngine::Instance().GetEvent("BG");
	music.Play();

	endingTree.AddNode(0);
	endingTree.AddNode(0);

	endingTree.BFT();
}

void FinalLevel::Update(float dt)
{
	time += dt;

	if (!tabletOpen && !isPaused && !optionsOpen)
	{
		untexturedShader->SetUniform("u_Time", time);
		shader->SetUniform("u_Time", time);
		pauseShader->SetUniform("u_Time", time);
		animShader->SetUniform("u_Time", time);
		rimLightShader->SetUniform("u_Time", time);
	} 

	if (tabletOpen && !isTalking)
	{
		AudioEngine::Instance().GetEvent("Final").Play();
		isTalking = true;
	}

	if (time >= 80.0f)
	{
		AudioEngine::Instance().GetEvent("BG").StopImmediately();
		endingTree.GetRootNode()->rightNode->_data = 1;
	}

	/*if (time >= 85.0f)
	{
		glfwSetWindowShouldClose(window, true);
	}*/

	if (endingTree.GetRootNode()->leftNode->_data == 1)
	{
		ending1 = true;
	}

	if (endingTree.GetRootNode()->rightNode->_data == 1)
	{
		ending2 = true;
	}

#pragma region Transforms
	auto& playerTrans = mainPlayer.Get<Transform>();
	auto& buttonTrans = buttonEnt.Get<Transform>();

	backEnt.Get<Transform>().SetPositionZ(-39.0f);
	backEnt.Get<Transform>().SetPositionY(22.0f);

	leftEnt.Get<Transform>().SetPositionX(-39.0f);
	leftEnt.Get<Transform>().SetRotationY(90.0f);
	leftEnt.Get<Transform>().SetPositionY(21.0f);

	rightEnt.Get<Transform>().SetPositionX(39.0f);
	rightEnt.Get<Transform>().SetRotationY(90.0f);
	rightEnt.Get<Transform>().SetPositionY(21.0f);

	tabletEnt.Get<Transform>().SetRotationY(tabletEnt.Get<Transform>().GetRotation().y + 100 * dt);
#pragma endregion

	auto& camera = camEnt.Get<Camera>();
	auto& orthoCam = uiCamEnt.Get<Camera>();

	if (!showLevelComplete)
		topViewToggle.Poll(window);

	camera = Input::ToggleCam(mainPlayer, camEnt, topViewCamEnt, topView, camChanged, topChanged);

	glm::mat4 transform = mainPlayer.Get<Transform>().GetModelMatrix();
	glm::mat4 transformGround = floorEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformLeft = leftEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformRight = rightEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformBack = backEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformDoor = doorEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformComplete = completeEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformButton = buttonEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire = wireEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformCoil = coilEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformCoil2 = coilEnt2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformCoil3 = coilEnt3.Get<Transform>().GetModelMatrix();
	glm::mat4 transformCoil4 = coilEnt4.Get<Transform>().GetModelMatrix();
	glm::mat4 transformCoil5 = coilEnt5.Get<Transform>().GetModelMatrix();
	glm::mat4 transformCoil6 = coilEnt6.Get<Transform>().GetModelMatrix();
	glm::mat4 transformCoil7 = coilEnt7.Get<Transform>().GetModelMatrix();
	glm::mat4 transformCoil8 = coilEnt8.Get<Transform>().GetModelMatrix();
	glm::mat4 transformCoil9 = coilEnt9.Get<Transform>().GetModelMatrix();
	glm::mat4 transformCoil10 = coilEnt10.Get<Transform>().GetModelMatrix();
	glm::mat4 transformCoil11 = coilEnt11.Get<Transform>().GetModelMatrix();
	glm::mat4 transformTut = tutEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformPause = pauseEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformOptions = optionEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformRetry = retryEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformExit = exitEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformTablet = tabletEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformTabletScreen = tabletScreenEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformMute = muteEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformMusic = musicEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformSound = soundEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformBright = brightEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformColorBlind = colorBlindEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformControls = controlsEnt.Get<Transform>().GetModelMatrix();

	if (!buttonAnimOn && playerTrans.GetPositionX() - buttonTrans.GetPositionX() < 3.0f && playerTrans.GetPositionX() - buttonTrans.GetPositionX() > -3.0f
		&& playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() > -3.0f)
	{
		button1Watch.Poll(window);
	}

	if ((playerTrans.GetPositionX() > -9.0f && playerTrans.GetPositionX() < -3.0f
		&& playerTrans.GetPositionZ() > 7.0f && playerTrans.GetPositionZ() < 13.0f
		&& !tabletOpen) || tabletOpen)
		tabletWatch.Poll(window);

	if (!optionsOpen)
		pauseWatch.Poll(window);

	if (ending1 || ending2)
	{
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
	}

#pragma region PlayerMovement
	if (!showLevelComplete && !isPaused && !optionsOpen && !tabletOpen)
	{
		isWalking = Input::MovePlayer(window, mainPlayer, camEnt, dt, camFar, camClose, camLeft, camRight, isArrow);

		if (isWalking)
		{
			AudioEngine::Instance().GetEvent("Walk").Play();
		}
		else
			AudioEngine::Instance().GetEvent("Walk").StopImmediately();

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

	if (!showLevelComplete && !isPaused && !optionsOpen)
	{
		//Input::MoveCamera(window, camEnt, dt);
	}
#pragma endregion

	if (buttonAnimOn)
	{
		AudioEngine::Instance().GetEvent("Button").Play();
		if (buttonEnt.Get<MorphAnimation>().GetIsDone())
		{
			buttonEnt.Get<MorphAnimation>().SetFrames(buttonFrames);
			buttonEnt.Get<MorphAnimation>().SetTime(0.2f);
			buttonAnimOn = false;
		}

		buttonEnt.Get<MorphAnimation>().Update(dt);
	}

	if (doorEnt.Get<Door>().GetOpen())
	{
		if (doorEnt.Get<MorphAnimation>().GetIsDone())
		{
			doorEnt.Get<MorphAnimation>().SetFrames(doorCloseFrames);
			doorEnt.Get<MorphAnimation>().SetTime(0.1f);
			doorClosingApplied = true;
			doorOpenApplied = false;
		}
	}

	if (!doorEnt.Get<Door>().GetOpen())
	{
		if (doorEnt.Get<MorphAnimation>().GetIsDone())
		{
			doorEnt.Get<MorphAnimation>().SetFrames(doorFrames);
			doorEnt.Get<MorphAnimation>().SetTime(0.1f);
			doorClosingApplied = false;
			doorOpenApplied = true;
		}
	}

	if (isPaused || optionsOpen)
	{
		PauseInput();
	}


	if (pauseLighting)
		lightInt = 2;
	else if (lightOn)
		lightInt = 1;
	else
		lightInt = 0;

	untexturedShader->SetUniform("u_LightOn", lightInt);
	shader->SetUniform("u_LightOn", lightInt);
	pauseShader->SetUniform("u_LightOn", lightInt);
	animShader->SetUniform("u_LightOn", lightInt);
	rimLightShader->SetUniform("u_LightOn", lightInt);

	//Post-Effect Stuff
	auto basicEffect = &FBO.Get<PostEffect>();
	auto shadowBuffer = &shadowBufferEnt.Get<Framebuffer>();
	//auto gBuffer = &gBufferEnt.Get<GBuffer>();

	basicEffect->Clear();
	shadowBuffer->Clear();
	//gBuffer->Clear();

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
		if (i < 3)
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
		if (!showLevelComplete)
		{
			//Bind and render the player and door using the animation shader
			animShader->Bind();
			animShader->SetUniform("s_Diffuse", 0);
			drumstickMat.Albedo->Bind(0);
			shadowBuffer->BindDepthAsTexture(30);
			mainPlayer.Get<MorphRenderer>().Render(camera, transform, LightSpaceViewProjection);

			animShader->SetUniform("s_Diffuse", 1);

			if (!doorEnt.Get<Door>().GetOpen())
			{
				doorMat.Albedo->Bind(1);
				doorEnt.Get<MorphRenderer>().Render(camera, transformDoor, LightSpaceViewProjection);
			}
			else
			{
				doorOnMat.Albedo->Bind(1);
				doorEnt.Get<MorphRenderer>().Render(camera, transformDoor, LightSpaceViewProjection);
			}
			doorMat.Albedo->Unbind(1);

			//Buttons
			animShader->SetUniform("s_Diffuse", 3);
			buttonMat.Albedo->Bind(3);
			buttonEnt.Get<MorphRenderer>().Render(camera, transformButton, LightSpaceViewProjection);

			shadowBuffer->UnbindTexture(30);

			//Bind and render the pause UI using the pause shader
			pauseShader->Bind();
			pauseShader->SetUniform("s_Diffuse", 0);
			pauseMat.Albedo->Bind(0);

			shadowBuffer->BindDepthAsTexture(30);

			if (isPaused)
			{
				pauseEnt.Get<MeshRenderer>().Render(orthoCam, transformPause);
			}

			pauseShader->SetUniform("s_Diffuse", 1);

			if (isPaused && mousePos.y > 403 && mousePos.y < 594 && mousePos.x > 104 && mousePos.x < 336)
			{
				optionPressMat.Albedo->Bind(1);
				optionEnt.Get<MeshRenderer>().Render(orthoCam, transformOptions);
			}
			else if (isPaused)
			{
				optionMat.Albedo->Bind(1);
				optionEnt.Get<MeshRenderer>().Render(orthoCam, transformOptions);
			}

			pauseShader->SetUniform("s_Diffuse", 2);

			if (isPaused && mousePos.y > 403 && mousePos.y < 595 && mousePos.x > 487 && mousePos.x < 714)
			{
				retryPressMat.Albedo->Bind(2);
				retryEnt.Get<MeshRenderer>().Render(orthoCam, transformRetry);
			}
			else if (isPaused)
			{
				retryMat.Albedo->Bind(2);
				retryEnt.Get<MeshRenderer>().Render(orthoCam, transformRetry);
			}

			pauseShader->SetUniform("s_Diffuse", 3);

			if (isPaused && mousePos.y > 403 && mousePos.y < 597 && mousePos.x > 865 && mousePos.x < 1097)
			{
				exitPressMat.Albedo->Bind(3);
				exitEnt.Get<MeshRenderer>().Render(orthoCam, transformExit);
			}
			else if (isPaused)
			{
				exitMat.Albedo->Bind(3);
				exitEnt.Get<MeshRenderer>().Render(orthoCam, transformExit);
			}

			pauseShader->SetUniform("s_Diffuse", 4);
			finalTabletMat.Albedo->Bind(4);

			if (tabletOpen)
			{
				tabletScreenEnt.Get<MeshRenderer>().Render(orthoCam, transformTabletScreen);
			}

			pauseShader->SetUniform("s_Diffuse", 5);
			optionMenuMat.Albedo->Bind(5);

			if (optionsOpen)
			{
				optionsMenuEnt.Get<MeshRenderer>().Render(orthoCam, optionsMenuEnt.Get<Transform>().GetModelMatrix());
			}

			pauseShader->SetUniform("s_Diffuse", 6);

			if (optionsOpen && !isMute)
			{
				toggleOffMat.Albedo->Bind(6);
				muteEnt.Get<MeshRenderer>().Render(orthoCam, muteEnt.Get<Transform>().GetModelMatrix());
			}
			else if (optionsOpen && isMute)
			{
				toggleOnMat.Albedo->Bind(6);
				muteEnt.Get<MeshRenderer>().Render(orthoCam, muteEnt.Get<Transform>().GetModelMatrix());
			}

			pauseShader->SetUniform("s_Diffuse", 7);

			if (optionsOpen && !isBright)
			{
				toggleOffMat.Albedo->Bind(7);
				brightEnt.Get<MeshRenderer>().Render(orthoCam, brightEnt.Get<Transform>().GetModelMatrix());
			}
			else if (optionsOpen && isBright)
			{
				toggleOnMat.Albedo->Bind(7);
				brightEnt.Get<MeshRenderer>().Render(orthoCam, brightEnt.Get<Transform>().GetModelMatrix());
			}

			pauseShader->SetUniform("s_Diffuse", 8);

			if (optionsOpen && !isCorrected)
			{
				toggleOffMat.Albedo->Bind(8);
				colorBlindEnt.Get<MeshRenderer>().Render(orthoCam, colorBlindEnt.Get<Transform>().GetModelMatrix());
			}
			else if (optionsOpen && isCorrected)
			{
				toggleOnMat.Albedo->Bind(8);
				colorBlindEnt.Get<MeshRenderer>().Render(orthoCam, colorBlindEnt.Get<Transform>().GetModelMatrix());
			}

			pauseShader->SetUniform("s_Diffuse", 9);

			if (optionsOpen && !isArrow)
			{
				toggleOffMat.Albedo->Bind(9);
				controlsEnt.Get<MeshRenderer>().Render(orthoCam, controlsEnt.Get<Transform>().GetModelMatrix());
			}
			else if (optionsOpen && isArrow)
			{
				toggleOnMat.Albedo->Bind(9);
				controlsEnt.Get<MeshRenderer>().Render(orthoCam, controlsEnt.Get<Transform>().GetModelMatrix());
			}

			pauseShader->SetUniform("s_Diffuse", 10);
			if (optionsOpen)
			{
				switch (soundVol)
				{
				case 1:
					volumeMat1.Albedo->Bind(10);
					soundEnt.Get<MeshRenderer>().Render(orthoCam, soundEnt.Get<Transform>().GetModelMatrix());
					break;

				case 2:
					volumeMat2.Albedo->Bind(10);
					soundEnt.Get<MeshRenderer>().Render(orthoCam, soundEnt.Get<Transform>().GetModelMatrix());
					break;

				case 3:
					volumeMat3.Albedo->Bind(10);
					soundEnt.Get<MeshRenderer>().Render(orthoCam, soundEnt.Get<Transform>().GetModelMatrix());
					break;

				case 4:
					volumeMat4.Albedo->Bind(10);
					soundEnt.Get<MeshRenderer>().Render(orthoCam, soundEnt.Get<Transform>().GetModelMatrix());
					break;

				case 5:
					volumeMat5.Albedo->Bind(10);
					soundEnt.Get<MeshRenderer>().Render(orthoCam, soundEnt.Get<Transform>().GetModelMatrix());
					break;

				case 6:
					volumeMat6.Albedo->Bind(10);
					soundEnt.Get<MeshRenderer>().Render(orthoCam, soundEnt.Get<Transform>().GetModelMatrix());
					break;

				case 7:
					volumeMat7.Albedo->Bind(10);
					soundEnt.Get<MeshRenderer>().Render(orthoCam, soundEnt.Get<Transform>().GetModelMatrix());
					break;

				case 8:
					volumeMat8.Albedo->Bind(10);
					soundEnt.Get<MeshRenderer>().Render(orthoCam, soundEnt.Get<Transform>().GetModelMatrix());
					break;

				case 9:
					volumeMat9.Albedo->Bind(10);
					soundEnt.Get<MeshRenderer>().Render(orthoCam, soundEnt.Get<Transform>().GetModelMatrix());
					break;

				case 10:
					volumeMat10.Albedo->Bind(10);
					soundEnt.Get<MeshRenderer>().Render(orthoCam, soundEnt.Get<Transform>().GetModelMatrix());
					break;
				}
			}

			pauseShader->SetUniform("s_Diffuse", 11);
			if (optionsOpen)
			{
				switch (musicVol)
				{
				case 1:
					volumeMat1.Albedo->Bind(11);
					musicEnt.Get<MeshRenderer>().Render(orthoCam, musicEnt.Get<Transform>().GetModelMatrix());
					break;

				case 2:
					volumeMat2.Albedo->Bind(11);
					musicEnt.Get<MeshRenderer>().Render(orthoCam, musicEnt.Get<Transform>().GetModelMatrix());
					break;

				case 3:
					volumeMat3.Albedo->Bind(11);
					musicEnt.Get<MeshRenderer>().Render(orthoCam, musicEnt.Get<Transform>().GetModelMatrix());
					break;

				case 4:
					volumeMat4.Albedo->Bind(11);
					musicEnt.Get<MeshRenderer>().Render(orthoCam, musicEnt.Get<Transform>().GetModelMatrix());
					break;

				case 5:
					volumeMat5.Albedo->Bind(11);
					musicEnt.Get<MeshRenderer>().Render(orthoCam, musicEnt.Get<Transform>().GetModelMatrix());
					break;

				case 6:
					volumeMat6.Albedo->Bind(11);
					musicEnt.Get<MeshRenderer>().Render(orthoCam, musicEnt.Get<Transform>().GetModelMatrix());
					break;

				case 7:
					volumeMat7.Albedo->Bind(11);
					musicEnt.Get<MeshRenderer>().Render(orthoCam, musicEnt.Get<Transform>().GetModelMatrix());
					break;

				case 8:
					volumeMat8.Albedo->Bind(11);
					musicEnt.Get<MeshRenderer>().Render(orthoCam, musicEnt.Get<Transform>().GetModelMatrix());
					break;

				case 9:
					volumeMat9.Albedo->Bind(11);
					musicEnt.Get<MeshRenderer>().Render(orthoCam, musicEnt.Get<Transform>().GetModelMatrix());
					break;

				case 10:
					volumeMat10.Albedo->Bind(11);
					musicEnt.Get<MeshRenderer>().Render(orthoCam, musicEnt.Get<Transform>().GetModelMatrix());
					break;
				}
			}

			shadowBuffer->UnbindTexture(30);

			//Bind and render the other objects using the basic shader
			shader->Bind();

			shadowBuffer->BindDepthAsTexture(30);
			//Floor
			shader->SetUniform("s_Diffuse", 0);
			floorMat.Albedo->Bind(0);
			floorEnt.Get<MeshRenderer>().Render(camera, transformGround, LightSpaceViewProjection);

			//Walls
			shader->SetUniform("s_Diffuse", 1);
			wallMat.Albedo->Bind(1);
			leftEnt.Get<MeshRenderer>().Render(camera, transformLeft, LightSpaceViewProjection);
			rightEnt.Get<MeshRenderer>().Render(camera, transformRight, LightSpaceViewProjection);
			backEnt.Get<MeshRenderer>().Render(camera, transformBack, LightSpaceViewProjection);


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

			//Tesla Coil
			shader->SetUniform("s_Diffuse", 5);

			if (!doorEnt.Get<Door>().GetOpen())
			{
				coilMatOff.Albedo->Bind(5);
				coilEnt.Get<MeshRenderer>().Render(camera, transformCoil, LightSpaceViewProjection);
			}
			else
			{
				coilMatOn.Albedo->Bind(5);
				coilEnt.Get<MeshRenderer>().Render(camera, transformCoil, LightSpaceViewProjection);
			}

			if (time < 8.0f)
			{
				coilMatOff.Albedo->Bind(5);
				coilEnt2.Get<MeshRenderer>().Render(camera, transformCoil2, LightSpaceViewProjection);
			}
			else
			{
				coilMatOn.Albedo->Bind(5);
				coilEnt2.Get<MeshRenderer>().Render(camera, transformCoil2, LightSpaceViewProjection);
			}

			if (time < 16.0f)
			{
				coilMatOff.Albedo->Bind(5);
				coilEnt3.Get<MeshRenderer>().Render(camera, transformCoil3, LightSpaceViewProjection);
			}
			else
			{
				coilMatOn.Albedo->Bind(5);
				coilEnt3.Get<MeshRenderer>().Render(camera, transformCoil3, LightSpaceViewProjection);
			}

			if (time < 24.0f)
			{
				coilMatOff.Albedo->Bind(5);
				coilEnt4.Get<MeshRenderer>().Render(camera, transformCoil4, LightSpaceViewProjection);
			}
			else
			{
				coilMatOn.Albedo->Bind(5);
				coilEnt4.Get<MeshRenderer>().Render(camera, transformCoil4, LightSpaceViewProjection);
			}

			if (time < 32.0f)
			{
				coilMatOff.Albedo->Bind(5);
				coilEnt5.Get<MeshRenderer>().Render(camera, transformCoil5, LightSpaceViewProjection);
			}
			else
			{
				coilMatOn.Albedo->Bind(5);
				coilEnt5.Get<MeshRenderer>().Render(camera, transformCoil5, LightSpaceViewProjection);
			}

			if (time < 40.0f)
			{
				coilMatOff.Albedo->Bind(5);
				coilEnt6.Get<MeshRenderer>().Render(camera, transformCoil6, LightSpaceViewProjection);
			}
			else
			{
				coilMatOn.Albedo->Bind(5);
				coilEnt6.Get<MeshRenderer>().Render(camera, transformCoil6, LightSpaceViewProjection);
			}

			if (time < 48.0f)
			{
				coilMatOff.Albedo->Bind(5);
				coilEnt7.Get<MeshRenderer>().Render(camera, transformCoil7, LightSpaceViewProjection);
			}
			else
			{
				coilMatOn.Albedo->Bind(5);
				coilEnt7.Get<MeshRenderer>().Render(camera, transformCoil7, LightSpaceViewProjection);
			}

			if (time < 56.0f)
			{
				coilMatOff.Albedo->Bind(5);
				coilEnt8.Get<MeshRenderer>().Render(camera, transformCoil8, LightSpaceViewProjection);
			}
			else
			{
				coilMatOn.Albedo->Bind(5);
				coilEnt8.Get<MeshRenderer>().Render(camera, transformCoil8, LightSpaceViewProjection);
			}

			if (time < 64.0f)
			{
				coilMatOff.Albedo->Bind(5);
				coilEnt9.Get<MeshRenderer>().Render(camera, transformCoil9, LightSpaceViewProjection);
			}
			else
			{
				coilMatOn.Albedo->Bind(5);
				coilEnt9.Get<MeshRenderer>().Render(camera, transformCoil9, LightSpaceViewProjection);
			}

			if (time < 72.0f)
			{
				coilMatOff.Albedo->Bind(5);
				coilEnt10.Get<MeshRenderer>().Render(camera, transformCoil10, LightSpaceViewProjection);
			}
			else
			{
				coilMatOn.Albedo->Bind(5);
				coilEnt10.Get<MeshRenderer>().Render(camera, transformCoil10, LightSpaceViewProjection);
			}

			if (time < 80.0f)
			{
				coilMatOff.Albedo->Bind(5);
				coilEnt11.Get<MeshRenderer>().Render(camera, transformCoil11, LightSpaceViewProjection);
			}
			else
			{
				coilMatOn.Albedo->Bind(5);
				coilEnt11.Get<MeshRenderer>().Render(camera, transformCoil11, LightSpaceViewProjection);
			}

			shadowBuffer->UnbindTexture(30);

			//Bind and render the objects with no textures
			untexturedShader->Bind();
			shadowBuffer->BindDepthAsTexture(30);

			if ((playerTrans.GetPositionX() > -9.0f && playerTrans.GetPositionX() < -3.0f
				&& playerTrans.GetPositionZ() > 7.0f && playerTrans.GetPositionZ() < 13.0f)
				|| (playerTrans.GetPositionX() - buttonTrans.GetPositionX() < 3.0f
					&& playerTrans.GetPositionX() - buttonTrans.GetPositionX() > -3.0f
					&& playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() < 3.0f
					&& playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() > -3.0f))
			{
				if (!tabletOpen && !optionsOpen && !isPaused)
					tutEnt.Get<MeshRenderer>().Render(orthoCam, transformTut, LightSpaceViewProjection);
				else
				{

				}
			}

			shadowBuffer->UnbindTexture(30);

			rimLightShader->Bind();
			rimLightShader->SetUniform("s_Diffuse", 1);
			tabletMat.Albedo->Bind(1);
			shadowBuffer->BindDepthAsTexture(30);
			tabletEnt.Get<MeshRenderer>().Render(camera, transformTablet, LightSpaceViewProjection);
			shadowBuffer->UnbindTexture(30);
		}
	}
	else
	{
		if (!showLevelComplete)
		{
			animShader->Bind();
			animShader->SetUniform("s_Diffuse", 0);
			clearMat.Albedo->Bind(0);
			shadowBuffer->BindDepthAsTexture(30);
			mainPlayer.Get<MorphRenderer>().Render(camera, transform, LightSpaceViewProjection);
			doorEnt.Get<MorphRenderer>().Render(camera, transformDoor, LightSpaceViewProjection);
			buttonEnt.Get<MorphRenderer>().Render(camera, transformButton, LightSpaceViewProjection);

			shadowBuffer->UnbindTexture(30);

			pauseShader->Bind();
			pauseShader->SetUniform("s_Diffuse", 0);
			clearMat.Albedo->Bind(0);
			shadowBuffer->BindDepthAsTexture(30);

			if (isPaused)
			{
				pauseEnt.Get<MeshRenderer>().Render(orthoCam, transformPause, LightSpaceViewProjection);
			}

			if (optionsOpen)
			{
				pauseEnt.Get<MeshRenderer>().Render(orthoCam, transformPause, LightSpaceViewProjection);
			}

			shadowBuffer->UnbindTexture(30);

			shader->Bind();
			shader->SetUniform("s_Diffuse", 0);
			clearMat.Albedo->Bind(0);
			shadowBuffer->BindDepthAsTexture(30);
			floorEnt.Get<MeshRenderer>().Render(camera, transformGround, LightSpaceViewProjection);
			leftEnt.Get<MeshRenderer>().Render(camera, transformLeft, LightSpaceViewProjection);
			rightEnt.Get<MeshRenderer>().Render(camera, transformRight, LightSpaceViewProjection);
			backEnt.Get<MeshRenderer>().Render(camera, transformBack, LightSpaceViewProjection);
			wireEnt.Get<MeshRenderer>().Render(camera, transformWire, LightSpaceViewProjection);
			coilEnt.Get<MeshRenderer>().Render(camera, transformCoil, LightSpaceViewProjection);

			shadowBuffer->UnbindTexture(30);

			rimLightShader->Bind();
			rimLightShader->SetUniform("s_Diffuse", 1);
			clearMat.Albedo->Bind(1);
			shadowBuffer->BindDepthAsTexture(30);
			tabletEnt.Get<MeshRenderer>().Render(camera, transformTablet, LightSpaceViewProjection);
			shadowBuffer->UnbindTexture(30);
		}
	}

	if (ending1)
	{
		AudioEngine::Instance().GetEvent("Level Complete").Play();
		shader->Bind();
		shader->SetUniform("s_Diffuse", 0);
		goodEndMat.Albedo->Bind(0);
		shadowBuffer->BindDepthAsTexture(30);
		completeEnt.Get<MeshRenderer>().Render(orthoCam, transformComplete);

		shadowBuffer->UnbindTexture(30);
	}

	if (ending2)
	{
		AudioEngine::Instance().GetEvent("Bad Ending").Play();
		shader->Bind();
		shader->SetUniform("s_Diffuse", 0);
		badEndMat.Albedo->Bind(0);
		shadowBuffer->BindDepthAsTexture(30);
		completeEnt.Get<MeshRenderer>().Render(orthoCam, transformComplete);

		shadowBuffer->UnbindTexture(30);
	}
#pragma endregion

	basicEffect->UnbindBuffer();

	if (activeEffect == 3 && isBright)
	{
		colorCorrectEnt.Get<ColorCorrect>().SetLUT(brightLut);
	}
	else if (activeEffect == 3 && isCorrected)
	{
		colorCorrectEnt.Get<ColorCorrect>().SetLUT(colorCorrectLut);
	}
	else if (activeEffect == 3 && !isBright && !isCorrected)
	{
		colorCorrectEnt.Get<ColorCorrect>().SetLUT(lut);
	}

	effects[activeEffect]->ApplyEffect(basicEffect);

	effects[activeEffect]->DrawToScreen();


	//Update the collisions
	leftEnt.Get<AABB>().Update();
	rightEnt.Get<AABB>().Update();
	backEnt.Get<AABB>().Update();
	doorEnt.Get<AABB>().Update();
	coilEnt.Get<AABB>().Update();
	buttonEnt.Get<AABB>().Update();
	buttonEnt.Get<Lever>().Update();
	wireEnt.Get<Wire>().Update();
	orEnt.Get<OrGate>().Update();

	AudioEngine::Instance().Update();

	//Door Logic
	if (doorEnt.Get<Door>().GetOpen() && doorOpenApplied)
	{
		doorEnt.Get<MorphAnimation>().Update(dt);
		AudioEngine::Instance().GetEvent("Door").Play();
	}
	if (!doorEnt.Get<Door>().GetOpen() && doorClosingApplied)
	{
		doorEnt.Get<MorphAnimation>().Update(dt);
		AudioEngine::Instance().GetEvent("Door").Play();
	}

	if (doorEnt.Get<AABB>().GetComplete())
	{
		lightOn = false;
		AudioEngine::Instance().GetEvent("BG").StopImmediately();
		AudioEngine::Instance().GetEvent("Walk").StopImmediately();
		AudioEngine::Instance().GetEvent("Final").StopImmediately();
		endingTree.GetRootNode()->leftNode->_data = 1;
	}
}

void FinalLevel::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}
