#include "Level2.h"
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

Level2::Level2(std::string sceneName, GLFWwindow* wind)
	: Scene(sceneName, wind)
{
#pragma region Entities
	mainPlayer = Entity::Create();
	floorEnt = Entity::Create();
	leftEnt = Entity::Create();
	rightEnt = Entity::Create();
	backEnt = Entity::Create();
	doorEnt = Entity::Create();
	optionEnt = Entity::Create();
	exitEnt = Entity::Create();
	retryEnt = Entity::Create();
	pipeEntS = Entity::Create();
	pipeEntS2 = Entity::Create();
	pipeEntC = Entity::Create();
	pipeEntC2 = Entity::Create();
	andEnt = Entity::Create();
	andEnt2 = Entity::Create();
	buttonEnt = Entity::Create();
	buttonEnt2 = Entity::Create();
	buttonEnt3 = Entity::Create();
	wireEnt = Entity::Create();
	wireEnt2 = Entity::Create();
	wireEnt3 = Entity::Create();
	wireEnt4 = Entity::Create();
	wireEnt5 = Entity::Create();
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
	pauseEnt = Entity::Create();

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

void Level2::InitScene()
{
	Application::SetClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	scene = new entt::registry();

	Entity::SetReg(scene);

	float distance = glm::distance(point2, point1);

	totalTime = distance / speed;

	//Initialize the shaders for the level
	InitShaders();
	//Initialize the Textures for the level
	InitTextures();

#pragma region Transforms
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

	//Pipe transforms
	auto& pipeTrans = pipeEntS.Add<Transform>();
	pipeTrans.SetPosition(glm::vec3(-33.5f, 12.5f, -23.f));

	auto& pipeTrans2 = pipeEntS2.Add<Transform>();
	pipeTrans2.SetPosition(glm::vec3(33.5f, 12.5f, -23.f));

	auto& pipeTrans3 = pipeEntC.Add<Transform>();
	pipeTrans3.SetPosition(glm::vec3(-33.5f, 1.f, 8.5f));
	pipeTrans3.SetRotationY(180.0f);

	auto& pipeTrans4 = pipeEntC2.Add<Transform>();
	pipeTrans4.SetPosition(glm::vec3(33.5f, 1.f, 8.5f));
	pipeTrans4.SetRotationY(180.0f);

	//Gate transforms
	auto& gateTrans = andEnt.Add<Transform>();
	gateTrans.SetPosition(glm::vec3(-19.0f, 1.0f, 1.0f));
	gateTrans.SetRotationY(-90.0f);
	gateTrans.SetScale(glm::vec3(2.0f));
	
	auto& gateTrans2 = andEnt2.Add<Transform>();
	gateTrans2.SetPosition(glm::vec3(2.0f, 1.0f, -9.0f));
	gateTrans2.SetRotationY(-90.0f);
	gateTrans2.SetScale(glm::vec3(2.0f));

	//Button transforms
	auto& buttonTrans = buttonEnt.Add<Transform>();
	buttonTrans.SetPosition(glm::vec3(-29.8f, -1.0f, 26.f));
	
	auto& buttonTrans2 = buttonEnt2.Add<Transform>();
	buttonTrans2.SetPosition(glm::vec3(-8.5f, -1.0f, 26.f));
	
	auto& buttonTrans3 = buttonEnt3.Add<Transform>();
	buttonTrans3.SetPosition(glm::vec3(11.7f, -1.0f, 25.f));

	//Wire Transforms
	auto& wireTrans = wireEnt.Add<Transform>();
	wireTrans.SetPosition(glm::vec3(2.8f, 1.0f, -2.8f));

	auto& wireTrans2 = wireEnt2.Add<Transform>();
	wireTrans2.SetPosition(glm::vec3(2.8f, 1.0f, -2.8f));

	auto& wireTrans3 = wireEnt3.Add<Transform>();
	wireTrans3.SetPosition(glm::vec3(2.8f, 1.0f, -3.8f));

	auto& wireTrans4 = wireEnt4.Add<Transform>();
	wireTrans4.SetPosition(glm::vec3(2.6f, 1.0f, -3.8f));

	auto& wireTrans5 = wireEnt5.Add<Transform>();
	wireTrans5.SetPosition(glm::vec3(2.6f, 1.0f, -4.5f));

	//Coil transform
	auto& coilTrans = coilEnt.Add<Transform>();
	coilTrans.SetPosition(glm::vec3(-13.7f, 1.0f, -32.7f));
	coilTrans.SetScale(glm::vec3(3.0f));
	coilTrans.SetRotationY(180.0f);

	//Level complete transform
	auto& completeTrans = completeEnt.Add<Transform>();
	completeTrans.SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	completeTrans.SetScale(glm::vec3(0.22f));

	//Pause UI transforms
	auto& pauseTrans = pauseEnt.Add<Transform>();
	pauseTrans.SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	pauseTrans.SetScale(glm::vec3(0.20f, 1.0f, 0.12f));

	//Box transforms
	auto& boxTrans = boxEnt.Add<Transform>();
	boxTrans.SetPosition(glm::vec3(35.f, 4.5f, -34.f));

	auto& boxTrans2 = boxEnt2.Add<Transform>();
	boxTrans2.SetPosition(glm::vec3(-35.f, 4.5f, -22.f));

	auto& boxTrans3 = boxEnt3.Add<Transform>();
	boxTrans3.SetPosition(glm::vec3(-35.f, 3.f, -15.f));
	boxTrans3.SetRotationY(90.f);
	boxTrans3.SetScale(glm::vec3(0.5f));

	auto& boxTrans4 = boxEnt4.Add<Transform>();
	boxTrans4.SetPosition(glm::vec3(35.f, 3.5f, -20.f));
	boxTrans4.SetRotationY(-90.f);
	boxTrans4.SetScale(glm::vec3(0.684f));

	//Panel transforms
	auto& panelTrans = panelEnt.Add<Transform>();
	panelTrans.SetPosition(glm::vec3(20.f, 7.0f, -39.f));
	panelTrans.SetScale(glm::vec3(2.0f));
	panelTrans.SetRotationY(-90.0f);

	auto& panelTrans2 = panelEnt2.Add<Transform>();
	panelTrans2.SetPosition(glm::vec3(24.f, 7.0f, -39.f));
	panelTrans2.SetScale(glm::vec3(2.0f));
	panelTrans2.SetRotationY(-90.0f);

	auto& panelTrans3 = panelEnt3.Add<Transform>();
	panelTrans3.SetPosition(glm::vec3(-39.f, 7.0f, 17.f));
	panelTrans3.SetScale(glm::vec3(2.0f));

	//Vent transforms
	auto& ventTrans = ventEnt.Add<Transform>();
	ventTrans.SetPosition(glm::vec3(38.f, 16.0f, 17.f));
	ventTrans.SetRotationY(180.f);

	auto& ventTrans2 = ventEnt2.Add<Transform>();
	ventTrans2.SetPosition(glm::vec3(38.f, 16.0f, 28.f));
	ventTrans2.SetRotationY(180.f);

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

	//AABB
	auto& leftCol = leftEnt.Add<AABB>(leftEnt, mainPlayer);
	auto& rightCol = rightEnt.Add<AABB>(rightEnt, mainPlayer);
	auto& backCol = backEnt.Add<AABB>(backEnt, mainPlayer);
	auto& gateCol = andEnt.Add<AABB>(andEnt, mainPlayer, 5.0f, 3.0f);
	gateCol.SetIsAmbient(true);
	auto& gateCol2 = andEnt2.Add<AABB>(andEnt2, mainPlayer, 5.0f, 3.0f);
	gateCol2.SetIsAmbient(true);
	auto& coilCol = coilEnt.Add<AABB>(coilEnt, mainPlayer, 4.0f, 4.0f);
	coilCol.SetIsAmbient(true);
	auto& boxCol = boxEnt.Add<AABB>(boxEnt, mainPlayer, 5.0f, 5.0f);
	boxCol.SetIsAmbient(true);
	auto& boxCol2 = boxEnt2.Add<AABB>(boxEnt2, mainPlayer, 5.0f, 5.0f);
	boxCol2.SetIsAmbient(true);
	auto& boxCol3 = boxEnt3.Add<AABB>(boxEnt3, mainPlayer, 2.5f, 2.5f);
	boxCol3.SetIsAmbient(true);
	auto& boxCol4 = boxEnt4.Add<AABB>(boxEnt4, mainPlayer, 3.42f, 3.42f);
	boxCol4.SetIsAmbient(true);
	auto& pipeCol = pipeEntC.Add<AABB>(pipeEntC, mainPlayer, 2.5f, 2.5f);
	pipeCol.SetIsAmbient(true);
	auto& pipeCol2 = pipeEntC2.Add<AABB>(pipeEntC2, mainPlayer, 2.5f, 2.5f);
	pipeCol2.SetIsAmbient(true);
	auto& buttonCol = buttonEnt.Add<AABB>(buttonEnt, mainPlayer, 2.0f, 2.0f);
	buttonCol.SetIsAmbient(true);
	auto& buttonCol2 = buttonEnt2.Add<AABB>(buttonEnt2, mainPlayer, 2.0f, 2.0f);
	buttonCol2.SetIsAmbient(true);
	auto& buttonCol3 = buttonEnt3.Add<AABB>(buttonEnt3, mainPlayer, 2.0f, 2.0f);
	buttonCol3.SetIsAmbient(true);

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
	auto& wire4 = wireEnt4.Add<Wire>(andEnt);
	auto& wire5 = wireEnt5.Add<Wire>(andEnt2);

	//Gates
	auto& andGate = andEnt.Add<AndGate>(wireEnt, wireEnt2, wireEnt4);
	auto& andGate2 = andEnt2.Add<AndGate>(wireEnt4, wireEnt3, doorEnt);

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
	auto& floorMesh = floorEnt.Add<MeshRenderer>(floorEnt, *floorL2, shader);
	auto& leftMesh = leftEnt.Add<MeshRenderer>(leftEnt, *leftWall, shader);
	auto& rightMesh = rightEnt.Add<MeshRenderer>(rightEnt, *rightWall, shader);
	auto& backMesh = backEnt.Add<MeshRenderer>(backEnt, *backWall, shader);
	auto& pipeMesh = pipeEntS.Add<MeshRenderer>(pipeEntS, *pipeS, shader);
	auto& pipeMesh2 = pipeEntS2.Add<MeshRenderer>(pipeEntS2, *pipeS, shader);
	auto& pipeMesh3 = pipeEntC.Add<MeshRenderer>(pipeEntC, *pipeC, shader);
	auto& pipeMesh4 = pipeEntC2.Add<MeshRenderer>(pipeEntC2, *pipeC, shader);
	auto& gateMesh = andEnt.Add<MeshRenderer>(andEnt, *and, shader);
	auto& gateMesh2 = andEnt2.Add<MeshRenderer>(andEnt2, *and, shader);
	auto& buttonMesh = buttonEnt.Add<MeshRenderer>(buttonEnt, *buttonM, shader);
	auto& buttonMesh2 = buttonEnt2.Add<MeshRenderer>(buttonEnt2, *buttonM, shader);
	auto& buttonMesh3 = buttonEnt3.Add<MeshRenderer>(buttonEnt3, *buttonM, shader);
	auto& wireMesh = wireEnt.Add<MeshRenderer>(wireEnt, *wireM1L2, shader);
	auto& wireMesh2 = wireEnt2.Add<MeshRenderer>(wireEnt2, *wireM2L2, shader);
	auto& wireMesh3 = wireEnt3.Add<MeshRenderer>(wireEnt3, *wireM3L2, shader);
	auto& wireMesh4 = wireEnt4.Add<MeshRenderer>(wireEnt4, *wireM4L2, shader);
	auto& wireMesh5 = wireEnt5.Add<MeshRenderer>(wireEnt5, *wireM5L2, shader);
	auto& doorMesh = doorEnt.Add<MorphRenderer>(doorEnt, *doorM, animShader);
	auto& coilMesh = coilEnt.Add<MeshRenderer>(coilEnt, *coil, shader);
	auto& completeMesh = completeEnt.Add<MeshRenderer>(completeEnt, *screen, shader);
	auto& pauseMesh = pauseEnt.Add<MeshRenderer>(pauseEnt, *screen, pauseShader);
	auto& boxMesh = boxEnt.Add<MeshRenderer>(boxEnt, *boxM, shader);
	auto& boxMesh2 = boxEnt2.Add<MeshRenderer>(boxEnt2, *boxM, shader);
	auto& boxMesh3 = boxEnt3.Add<MeshRenderer>(boxEnt3, *boxM, shader);
	auto& boxMesh4 = boxEnt4.Add<MeshRenderer>(boxEnt4, *boxM, shader);
	auto& panelMesh = panelEnt.Add<MeshRenderer>(panelEnt, *panel, shader);
	auto& panelMesh2 = panelEnt2.Add<MeshRenderer>(panelEnt2, *panel, shader);
	auto& panelMesh3 = panelEnt3.Add<MeshRenderer>(panelEnt3, *panel, shader);
	auto& ventMesh = ventEnt.Add<MeshRenderer>(ventEnt, *ventS, shader);
	auto& ventMesh2 = ventEnt2.Add<MeshRenderer>(ventEnt2, *ventS, shader);
	auto& optionMesh = optionEnt.Add<MeshRenderer>(optionEnt, *options, pauseShader);
	auto& retryMesh = retryEnt.Add<MeshRenderer>(retryEnt, *retry, pauseShader);
	auto& exitMesh = exitEnt.Add<MeshRenderer>(exitEnt, *exit, pauseShader);

	entList.push_back(&mainPlayer);
	entList.push_back(&doorEnt);
	entList.push_back(&floorEnt);
	entList.push_back(&leftEnt);
	entList.push_back(&rightEnt);
	entList.push_back(&completeEnt);
	entList.push_back(&andEnt);
	entList.push_back(&andEnt2);
	entList.push_back(&buttonEnt);
	entList.push_back(&buttonEnt2);
	entList.push_back(&buttonEnt3);
	entList.push_back(&wireEnt);
	entList.push_back(&wireEnt2);
	entList.push_back(&wireEnt3);
	entList.push_back(&wireEnt4);
	entList.push_back(&wireEnt5);
	entList.push_back(&boxEnt);
	entList.push_back(&boxEnt2);
	entList.push_back(&boxEnt3);
	entList.push_back(&boxEnt4);
	entList.push_back(&coilEnt);
	entList.push_back(&panelEnt);
	entList.push_back(&panelEnt2);
	entList.push_back(&panelEnt3);
	entList.push_back(&ventEnt);
	entList.push_back(&ventEnt2);
	entList.push_back(&pipeEntC);
	entList.push_back(&pipeEntC2);
	entList.push_back(&pipeEntS);
	entList.push_back(&pipeEntS2);

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

void Level2::Update(float dt)
{
	time += dt;
	shader->SetUniform("u_Time", time);
	pauseShader->SetUniform("u_Time", time);
	animShader->SetUniform("u_Time", time);
	untexturedShader->SetUniform("u_Time", time);

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
	pauseShader->SetUniform("u_Position", currentPos);
	animShader->SetUniform("u_Position", currentPos);
	untexturedShader->SetUniform("u_Position", currentPos);

#pragma region Transforms
	auto& playerTrans = mainPlayer.Get<Transform>();
	auto& buttonTrans = buttonEnt.Get<Transform>();
	auto& buttonTrans2 = buttonEnt2.Get<Transform>();
	auto& buttonTrans3 = buttonEnt3.Get<Transform>();
	/*auto& groundTrans = floorEnt.Get<Transform>();
	auto& leftTrans = leftEnt.Get<Transform>();
	auto& rightTrans = rightEnt.Get<Transform>();
	auto& backTrans = backEnt.Get<Transform>();
	auto& doorTrans = doorEnt.Get<Transform>();
	auto& pipeTrans = pipeEntS.Get<Transform>();
	auto& pipeTrans2 = pipeEntS2.Get<Transform>();
	auto& pipeTrans3 = pipeEntC.Get<Transform>();
	auto& pipeTrans4 = pipeEntC2.Get<Transform>();
	auto& gateTrans = andEnt.Get<Transform>();
	auto& gateTrans2 = andEnt2.Get<Transform>();
	auto& wireTrans = wireEnt.Get<Transform>();
	auto& wireTrans2 = wireEnt2.Get<Transform>();
	auto& wireTrans3 = wireEnt3.Get<Transform>();
	auto& wireTrans4 = wireEnt4.Get<Transform>();
	auto& wireTrans5 = wireEnt5.Get<Transform>();
	auto& coilTrans = coilEnt.Get<Transform>();
	auto& completeTrans = completeEnt.Get<Transform>();
	auto& pauseTrans = pauseEnt.Get<Transform>();
	auto& boxTrans = boxEnt.Get<Transform>();
	auto& boxTrans2 = boxEnt2.Get<Transform>();
	auto& boxTrans3 = boxEnt3.Get<Transform>();
	auto& boxTrans4 = boxEnt4.Get<Transform>();
	auto& panelTrans = panelEnt.Get<Transform>();
	auto& panelTrans2 = panelEnt2.Get<Transform>();
	auto& panelTrans3 = panelEnt3.Get<Transform>();
	auto& ventTrans = ventEnt.Get<Transform>();
	auto& ventTrans2 = ventEnt2.Get<Transform>();
	auto& optionsTrans = optionEnt.Get<Transform>();
	auto& retryTrans = retryEnt.Get<Transform>();
	auto& exitTrans = exitEnt.Get<Transform>();*/

	//floorEnt.Get<Transform>().SetPositionY(-0.9f);

	backEnt.Get<Transform>().SetPositionZ(-39.0f);
	backEnt.Get<Transform>().SetPositionY(9.0f);

	leftEnt.Get<Transform>().SetPositionX(-39.0f);
	leftEnt.Get<Transform>().SetRotationY(90.0f);
	leftEnt.Get<Transform>().SetPositionY(9.0f);

	rightEnt.Get<Transform>().SetPositionX(39.0f);
	rightEnt.Get<Transform>().SetRotationY(90.0f);
	rightEnt.Get<Transform>().SetPositionY(9.0f);
#pragma endregion

	auto& camera = camEnt.Get<Camera>();
	auto& orthoCam = uiCamEnt.Get<Camera>();
	//camera.LookAt(glm::vec3(playerTrans.GetPositionX(), playerTrans.GetPositionY() + 5.0f, playerTrans.GetPositionZ()));

	//Get references to the meshes
	/*auto& meshMain = mainPlayer.Get<MorphRenderer>();
	auto& groundMesh = floorEnt.Get<MeshRenderer>();
	auto& leftMesh = leftEnt.Get<MeshRenderer>();
	auto& rightMesh = rightEnt.Get<MeshRenderer>();
	auto& backMesh = backEnt.Get<MeshRenderer>();
	auto& doorMesh = doorEnt.Get<MorphRenderer>();
	auto& pipeMesh = pipeEntS.Get<MeshRenderer>();
	auto& pipeMesh2 = pipeEntS2.Get<MeshRenderer>();
	auto& pipeMesh3 = pipeEntC.Get<MeshRenderer>();
	auto& pipeMesh4 = pipeEntC2.Get<MeshRenderer>();
	auto& gateMesh = andEnt.Get<MeshRenderer>();
	auto& gateMesh2 = andEnt2.Get<MeshRenderer>();
	auto& buttonMesh = buttonEnt.Get<MeshRenderer>();
	auto& buttonMesh2 = buttonEnt2.Get<MeshRenderer>();
	auto& buttonMesh3 = buttonEnt3.Get<MeshRenderer>();
	auto& wireMesh = wireEnt.Get<MeshRenderer>();
	auto& wireMesh2 = wireEnt2.Get<MeshRenderer>();
	auto& wireMesh3 = wireEnt3.Get<MeshRenderer>();
	auto& wireMesh4 = wireEnt4.Get<MeshRenderer>();
	auto& wireMesh5 = wireEnt5.Get<MeshRenderer>();
	auto& coilMesh = coilEnt.Get<MeshRenderer>();
	auto& completeMesh = completeEnt.Get<MeshRenderer>();
	auto& pauseMesh = pauseEnt.Get<MeshRenderer>();
	auto& boxMesh = boxEnt.Get<MeshRenderer>();
	auto& boxMesh2 = boxEnt2.Get<MeshRenderer>();
	auto& boxMesh3 = boxEnt3.Get<MeshRenderer>();
	auto& boxMesh4 = boxEnt4.Get<MeshRenderer>();
	auto& panelMesh = panelEnt.Get<MeshRenderer>();
	auto& panelMesh2 = panelEnt2.Get<MeshRenderer>();
	auto& panelMesh3 = panelEnt3.Get<MeshRenderer>();
	auto& ventMesh = ventEnt.Get<MeshRenderer>();
	auto& optionMesh = optionEnt.Get<MeshRenderer>();
	auto& retryMesh = retryEnt.Get<MeshRenderer>();
	auto& exitMesh = exitEnt.Get<MeshRenderer>();
	auto& ventMesh2 = ventEnt2.Get<MeshRenderer>();*/

	//Get reference to the model matrix
	glm::mat4 transform = playerTrans.GetModelMatrix();
	glm::mat4 transformGround = floorEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformLeft = leftEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformRight = rightEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformBack = backEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformDoor = doorEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformPipe = pipeEntS.Get<Transform>().GetModelMatrix();
	glm::mat4 transformPipe2 = pipeEntS2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformPipe3 = pipeEntC.Get<Transform>().GetModelMatrix();
	glm::mat4 transformPipe4 = pipeEntC2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformGate = andEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformGate2 = andEnt2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformButton = buttonTrans.GetModelMatrix();
	glm::mat4 transformButton2 = buttonTrans2.GetModelMatrix();
	glm::mat4 transformButton3 = buttonTrans3.GetModelMatrix();
	glm::mat4 transformWire = wireEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire2 = wireEnt2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire3 = wireEnt3.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire4 = wireEnt4.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire5 = wireEnt5.Get<Transform>().GetModelMatrix();
	glm::mat4 transformCoil = coilEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformComplete = completeEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformPause = pauseEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformBox = boxEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformBox2 = boxEnt2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformBox3 = boxEnt3.Get<Transform>().GetModelMatrix();
	glm::mat4 transformBox4 = boxEnt4.Get<Transform>().GetModelMatrix();
	glm::mat4 transformPanel = panelEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformPanel2 = panelEnt2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformPanel3 = panelEnt3.Get<Transform>().GetModelMatrix();
	glm::mat4 transformVent = ventEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformVent2 = ventEnt2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformOptions = optionEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformRetry = retryEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformExit = exitEnt.Get<Transform>().GetModelMatrix();

	if (playerTrans.GetPositionX() - buttonTrans.GetPositionX() < 3.0f && playerTrans.GetPositionX() - buttonTrans.GetPositionX() > -3.0f
		&& playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() > -3.0f)
		button1Watch.Poll(window);
	
	if (playerTrans.GetPositionX() - buttonTrans2.GetPositionX() < 3.0f && playerTrans.GetPositionX() - buttonTrans2.GetPositionX() > -3.0f
		&& playerTrans.GetPositionZ() - buttonTrans2.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans2.GetPositionZ() > -3.0f)
		button2Watch.Poll(window);
	
	if (playerTrans.GetPositionX() - buttonTrans3.GetPositionX() < 3.0f && playerTrans.GetPositionX() - buttonTrans3.GetPositionX() > -3.0f
		&& playerTrans.GetPositionZ() - buttonTrans3.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans3.GetPositionZ() > -3.0f)
		button3Watch.Poll(window);

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

	GetCursorPos(&mousePos);

	ScreenToClient(hWnd, &mousePos);

	if (GetAsyncKeyState(0x01) && isPaused && mousePos.y > 323 && mousePos.y < 476 && mousePos.x > 575 && mousePos.x < 730)
	{
		glfwSetWindowShouldClose(window, true);
	}

	lightNum = Input::ChangeLighting(window, lightNum);

	if (lightNum < 1 || lightNum > 5)
		lightNum = 1;

	animShader->SetUniform("u_LightNum", lightNum);
	shader->SetUniform("u_LightNum", lightNum);
	pauseShader->SetUniform("u_LightNum", lightNum);
	untexturedShader->SetUniform("u_LightNum", lightNum);

	if (lightOn)
		lightInt = 1;
	else
		lightInt = 0;

	untexturedShader->SetUniform("u_LightOn", lightInt);
	shader->SetUniform("u_LightOn", lightInt);
	pauseShader->SetUniform("u_LightOn", lightInt);
	animShader->SetUniform("u_LightOn", lightInt);

	//Post-Effect stuff
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
		if (i < 2)
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
			doorMat.Albedo->Bind(1);
			doorEnt.Get<MorphRenderer>().Render(camera, transformDoor, LightSpaceViewProjection);
			doorMat.Albedo->Unbind(1);

			shadowBuffer->UnbindTexture(30);

			//Bind and render the pause UI using the pause shader
			pauseShader->Bind();
			pauseShader->SetUniform("s_Diffuse", 0);
			pauseMat.Albedo->Bind(0);

			shadowBuffer->BindDepthAsTexture(30);

			if (isPaused)
			{
				pauseEnt.Get<MeshRenderer>().Render(orthoCam, transformPause, LightSpaceViewProjection);
			}

			pauseShader->SetUniform("s_Diffuse", 1);
			optionMat.Albedo->Bind(1);

			if (isPaused)
			{
				optionEnt.Get<MeshRenderer>().Render(orthoCam, transformOptions, LightSpaceViewProjection);
			}

			pauseShader->SetUniform("s_Diffuse", 2);
			retryMat.Albedo->Bind(2);

			if (isPaused)
			{
				retryEnt.Get<MeshRenderer>().Render(orthoCam, transformRetry, LightSpaceViewProjection);
			}

			pauseShader->SetUniform("s_Diffuse", 2);
			exitMat.Albedo->Bind(2);

			if (isPaused)
			{
				exitEnt.Get<MeshRenderer>().Render(orthoCam, transformExit, LightSpaceViewProjection);
			}

			shadowBuffer->UnbindTexture(30);

			//Bind and render the objects using the basic shader
			shader->Bind();

			//Floor
			shader->SetUniform("s_Diffuse", 0);
			floorMat.Albedo->Bind(0);
			shadowBuffer->BindDepthAsTexture(30);
			floorEnt.Get<MeshRenderer>().Render(camera, transformGround, LightSpaceViewProjection);

			//Walls
			shader->SetUniform("s_Diffuse", 1);
			wallMat.Albedo->Bind(1);
			leftEnt.Get<MeshRenderer>().Render(camera, transformLeft, LightSpaceViewProjection);
			rightEnt.Get<MeshRenderer>().Render(camera, transformRight, LightSpaceViewProjection);
			backEnt.Get<MeshRenderer>().Render(camera, transformBack, LightSpaceViewProjection);

			//Pipes
			//Straight Pipe
			shader->SetUniform("s_Diffuse", 2);
			straightPipeMat.Albedo->Bind(2);
			pipeEntS.Get<MeshRenderer>().Render(camera, transformPipe, LightSpaceViewProjection);
			pipeEntS2.Get<MeshRenderer>().Render(camera, transformPipe2, LightSpaceViewProjection);

			//Curved Pipe
			shader->SetUniform("s_Diffuse", 3);
			curvedPipeMat.Albedo->Bind(3);
			pipeEntC.Get<MeshRenderer>().Render(camera, transformPipe3, LightSpaceViewProjection);
			pipeEntC2.Get<MeshRenderer>().Render(camera, transformPipe4, LightSpaceViewProjection);

			//Gates
			shader->SetUniform("s_Diffuse", 4);
			andMat.Albedo->Bind(4);
			andEnt.Get<MeshRenderer>().Render(camera, transformGate, LightSpaceViewProjection);
			andEnt2.Get<MeshRenderer>().Render(camera, transformGate2, LightSpaceViewProjection);

			//Button
			shader->SetUniform("s_Diffuse", 5);
			buttonMat.Albedo->Bind(5);
			buttonEnt.Get<MeshRenderer>().Render(camera, transformButton, LightSpaceViewProjection);
			buttonEnt2.Get<MeshRenderer>().Render(camera, transformButton2, LightSpaceViewProjection);
			buttonEnt3.Get<MeshRenderer>().Render(camera, transformButton3, LightSpaceViewProjection);

			//Wires
			shader->SetUniform("s_Diffuse", 6);

			if (wireEnt.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(6);
				wireEnt.Get<MeshRenderer>().Render(camera, transformWire, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(6);
				wireEnt.Get<MeshRenderer>().Render(camera, transformWire, LightSpaceViewProjection);
			}

			if (wireEnt2.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(6);
				wireEnt2.Get<MeshRenderer>().Render(camera, transformWire2, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(6);
				wireEnt2.Get<MeshRenderer>().Render(camera, transformWire2, LightSpaceViewProjection);
			}

			if (wireEnt3.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(6);
				wireEnt3.Get<MeshRenderer>().Render(camera, transformWire3, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(6);
				wireEnt3.Get<MeshRenderer>().Render(camera, transformWire3, LightSpaceViewProjection);
			}

			if (wireEnt4.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(6);
				wireEnt4.Get<MeshRenderer>().Render(camera, transformWire4, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(6);
				wireEnt4.Get<MeshRenderer>().Render(camera, transformWire4, LightSpaceViewProjection);
			}

			if (wireEnt5.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(6);
				wireEnt5.Get<MeshRenderer>().Render(camera, transformWire5, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(6);
				wireEnt5.Get<MeshRenderer>().Render(camera, transformWire5, LightSpaceViewProjection);
			}		

			//Boxes
			shader->SetUniform("s_Diffuse", 7);
			boxMat.Albedo->Bind(7);
			boxEnt.Get<MeshRenderer>().Render(camera, transformBox, LightSpaceViewProjection);
			boxEnt2.Get<MeshRenderer>().Render(camera, transformBox2, LightSpaceViewProjection);
			boxEnt3.Get<MeshRenderer>().Render(camera, transformBox3, LightSpaceViewProjection);
			boxEnt4.Get<MeshRenderer>().Render(camera, transformBox4, LightSpaceViewProjection);

			//Panels
			shader->SetUniform("s_Diffuse", 8);
			panelMat.Albedo->Bind(8);
			panelEnt.Get<MeshRenderer>().Render(camera, transformPanel, LightSpaceViewProjection);
			panelEnt2.Get<MeshRenderer>().Render(camera, transformPanel2, LightSpaceViewProjection);
			panelEnt3.Get<MeshRenderer>().Render(camera, transformPanel3, LightSpaceViewProjection);

			//Vents
			shader->SetUniform("s_Diffuse", 9);
			ventMat.Albedo->Bind(9);
			ventEnt.Get<MeshRenderer>().Render(camera, transformVent, LightSpaceViewProjection);
			ventEnt2.Get<MeshRenderer>().Render(camera, transformVent2, LightSpaceViewProjection);

			//Tesla Coil
			shader->SetUniform("s_Diffuse", 10);

			if (!doorEnt.Get<Door>().GetOpen())
			{
				coilMatOff.Albedo->Bind(10);
				coilEnt.Get<MeshRenderer>().Render(camera, transformCoil, LightSpaceViewProjection);
			}
			else
			{
				coilMatOn.Albedo->Bind(10);
				coilEnt.Get<MeshRenderer>().Render(camera, transformCoil, LightSpaceViewProjection);
			}

			shadowBuffer->UnbindTexture(30);
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
			shadowBuffer->BindDepthAsTexture(30);
			mainPlayer.Get<MorphRenderer>().Render(camera, transform, LightSpaceViewProjection);

			animShader->SetUniform("s_Diffuse", 1);
			clearMat.Albedo->Bind(1);
			doorEnt.Get<MorphRenderer>().Render(camera, transformDoor, LightSpaceViewProjection);
			clearMat.Albedo->Unbind(1);
			shadowBuffer->UnbindTexture(30);

			pauseShader->Bind();
			pauseShader->SetUniform("s_Diffuse", 0);
			pauseMat.Albedo->Bind(0);
			shadowBuffer->BindDepthAsTexture(30);

			if (isPaused)
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
			pipeEntS.Get<MeshRenderer>().Render(camera, transformPipe, LightSpaceViewProjection);
			pipeEntS2.Get<MeshRenderer>().Render(camera, transformPipe2, LightSpaceViewProjection);
			pipeEntC.Get<MeshRenderer>().Render(camera, transformPipe3, LightSpaceViewProjection);
			pipeEntC2.Get<MeshRenderer>().Render(camera, transformPipe4, LightSpaceViewProjection);
			andEnt.Get<MeshRenderer>().Render(camera, transformGate, LightSpaceViewProjection);
			andEnt2.Get<MeshRenderer>().Render(camera, transformGate2, LightSpaceViewProjection);
			buttonEnt.Get<MeshRenderer>().Render(camera, transformButton, LightSpaceViewProjection);
			buttonEnt2.Get<MeshRenderer>().Render(camera, transformButton2, LightSpaceViewProjection);
			buttonEnt3.Get<MeshRenderer>().Render(camera, transformButton3, LightSpaceViewProjection);
			wireEnt.Get<MeshRenderer>().Render(camera, transformWire, LightSpaceViewProjection);
			wireEnt2.Get<MeshRenderer>().Render(camera, transformWire2, LightSpaceViewProjection);
			wireEnt3.Get<MeshRenderer>().Render(camera, transformWire3, LightSpaceViewProjection);
			wireEnt4.Get<MeshRenderer>().Render(camera, transformWire4, LightSpaceViewProjection);
			wireEnt5.Get<MeshRenderer>().Render(camera, transformWire5, LightSpaceViewProjection);
			boxEnt.Get<MeshRenderer>().Render(camera, transformBox, LightSpaceViewProjection);
			boxEnt2.Get<MeshRenderer>().Render(camera, transformBox2, LightSpaceViewProjection);
			boxEnt3.Get<MeshRenderer>().Render(camera, transformBox3, LightSpaceViewProjection);
			boxEnt4.Get<MeshRenderer>().Render(camera, transformBox4, LightSpaceViewProjection);
			panelEnt.Get<MeshRenderer>().Render(camera, transformPanel, LightSpaceViewProjection);
			panelEnt2.Get<MeshRenderer>().Render(camera, transformPanel2, LightSpaceViewProjection);
			panelEnt3.Get<MeshRenderer>().Render(camera, transformPanel3, LightSpaceViewProjection);
			ventEnt.Get<MeshRenderer>().Render(camera, transformVent, LightSpaceViewProjection);
			ventEnt2.Get<MeshRenderer>().Render(camera, transformVent2, LightSpaceViewProjection);
			coilEnt.Get<MeshRenderer>().Render(camera, transformCoil, LightSpaceViewProjection);
			//untexturedShader->Bind();
			shadowBuffer->UnbindTexture(30);
		}
	}

	if (showLevelComplete)
	{
		lightNum = 1;
		shader->Bind();
		shader->SetUniform("s_Diffuse", 0);
		completeMat.Albedo->Bind(0);
		shadowBuffer->BindDepthAsTexture(30);
		completeEnt.Get<MeshRenderer>().Render(orthoCam, transformComplete, LightSpaceViewProjection);
		shadowBuffer->UnbindTexture(30);
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
	andEnt.Get<AndGate>().Update();
	andEnt2.Get<AndGate>().Update();
	coilEnt.Get<AABB>().Update();
	pipeEntC.Get<AABB>().Update();
	pipeEntC2.Get<AABB>().Update();
	buttonEnt.Get<AABB>().Update();
	buttonEnt2.Get<AABB>().Update();
	buttonEnt3.Get<AABB>().Update();
	buttonEnt.Get<Lever>().Update();
	buttonEnt2.Get<Lever>().Update();
	buttonEnt3.Get<Lever>().Update();
	wireEnt.Get<Wire>().Update();
	wireEnt2.Get<Wire>().Update();
	wireEnt3.Get<Wire>().Update();
	wireEnt4.Get<Wire>().Update();
	wireEnt5.Get<Wire>().Update();
	boxEnt.Get<AABB>().Update();
	boxEnt2.Get<AABB>().Update();
	boxEnt3.Get<AABB>().Update();
	boxEnt4.Get<AABB>().Update();

	//Door Logic
	if (doorEnt.Get<Door>().GetOpen())
		doorEnt.Get<MorphAnimation>().Update(dt);

	if (doorEnt.Get<AABB>().GetComplete())
		showLevelComplete = true;
}

void Level2::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}