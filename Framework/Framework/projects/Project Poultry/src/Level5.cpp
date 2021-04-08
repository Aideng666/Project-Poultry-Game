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
	completeEnt = Entity::Create();
	tutEnt = Entity::Create();
	tabletEnt = Entity::Create();
	tabletScreenEnt = Entity::Create();
	optionsMenuEnt = Entity::Create();

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
	//Initializes the Luts
	InitLuts();

#pragma region Transforms
	//Player transform
	auto& playerTrans = mainPlayer.Add<Transform>();
	playerTrans.SetPosition(glm::vec3(0.0f, 1.1f, 43.f));
	playerTrans.SetRotationY(180.0f);
	playerTrans.SetLevelSize(45.0f);

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
	ventTrans.SetPosition(glm::vec3(25.f, 25.f, -50.5f));
	ventTrans.SetScale(glm::vec3(1.2f));
	ventTrans.SetRotationY(90.f);

	auto& ventTrans2 = ventEnt2.Add<Transform>();
	ventTrans2.SetPosition(glm::vec3(-25.f, 25.f, -50.5f));
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
	buttonTrans.SetPosition(glm::vec3(-31.6f, -1.0f, 39.5f));

	auto& buttonTrans2 = buttonEnt2.Add<Transform>();
	buttonTrans2.SetPosition(glm::vec3(-10.4f, -1.0f, 39.5f));

	auto& buttonTrans3 = buttonEnt3.Add<Transform>();
	buttonTrans3.SetPosition(glm::vec3(6.5f, -1.0f, 39.5f));

	auto& buttonTrans4 = buttonEnt4.Add<Transform>();
	buttonTrans4.SetPosition(glm::vec3(27.7f, -1.0f, 39.4f));

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

	//Level complete transform
	auto& completeTrans = completeEnt.Add<Transform>();
	completeTrans.SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	completeTrans.SetScale(glm::vec3(0.22f));

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
	//optionsTrans.SetRotationY(96.0f);

	auto& retryTrans = retryEnt.Add<Transform>();
	retryTrans.SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));
	retryTrans.SetScale(glm::vec3(1.5f));
	//retryTrans.SetRotationY(96.0f);

	auto& exitTrans = exitEnt.Add<Transform>();
	exitTrans.SetPosition(glm::vec3(5.0f, 2.0f, 0.0f));
	exitTrans.SetScale(glm::vec3(1.5f));
	//exitTrans.SetRotationY(96.0f);

	//Tablet Stuff
	auto& tabletTrans = tabletEnt.Add<Transform>();
	tabletTrans.SetPosition(glm::vec3(-2.0f, 5.0f, 20.0f));
	tabletTrans.SetRotationY(180.0f);

	auto& tabletScreenTrans = tabletScreenEnt.Add<Transform>();
	tabletScreenTrans.SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	tabletScreenTrans.SetScale(glm::vec3(0.18f, 1.0f, 0.18f));

	//Interact text transform
	auto& tutTrans = tutEnt.Add<Transform>();
	tutTrans.SetPosition(glm::vec3(1.0f, 2.0f, 5.0f));
	tutTrans.SetScale(glm::vec3(1.0f));

	auto& optionsMenuTrans = optionsMenuEnt.Add<Transform>();
	optionsMenuTrans.SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	optionsMenuTrans.SetScale(glm::vec3(0.18f, 1.0f, 0.18f));
#pragma endregion

	auto& leftCol = leftEnt.Add<AABB>(leftEnt, mainPlayer);
	auto& rightCol = rightEnt.Add<AABB>(rightEnt, mainPlayer);
	auto& backCol = backEnt.Add<AABB>(backEnt, mainPlayer);
	auto& andCol = andEnt.Add<AABB>(andEnt, mainPlayer, 5.0f, 3.0f);
	andCol.SetIsAmbient(true);
	auto& orCol = orEnt.Add<AABB>(orEnt, mainPlayer, 5.0f, 3.0f);
	orCol.SetIsAmbient(true);
	auto& orCol2 = orEnt2.Add<AABB>(orEnt2, mainPlayer, 5.0f, 3.0f);
	orCol2.SetIsAmbient(true);
	auto& buttonCol = buttonEnt.Add<AABB>(buttonEnt, mainPlayer, 2.0f, 2.0f);
	buttonCol.SetIsAmbient(true);
	auto& buttonCol2 = buttonEnt2.Add<AABB>(buttonEnt2, mainPlayer, 2.0f, 2.0f);
	buttonCol2.SetIsAmbient(true);
	auto& buttonCol3 = buttonEnt3.Add<AABB>(buttonEnt3, mainPlayer, 2.0f, 2.0f);
	buttonCol3.SetIsAmbient(true);
	auto& buttonCol4 = buttonEnt4.Add<AABB>(buttonEnt4, mainPlayer, 2.0f, 2.0f);
	buttonCol4.SetIsAmbient(true);
	auto& coilCol = coilEnt.Add<AABB>(coilEnt, mainPlayer, 4.0f, 4.0f);
	coilCol.SetIsAmbient(true);
	auto& columnPipeCol = columnPipeEnt.Add<AABB>(columnPipeEnt, mainPlayer, 3.0f, 14.5f);
	columnPipeCol.SetIsAmbient(true);
	auto& columnPipeCol2 = columnPipeEnt2.Add<AABB>(columnPipeEnt2, mainPlayer, 3.0f, 14.5f);
	columnPipeCol2.SetIsAmbient(true);
	auto& pipeCol = pipeEntS.Add<AABB>(pipeEntS, mainPlayer, 2.5f, 2.5f);
	pipeCol.SetIsAmbient(true);
	auto& pipeCol2 = pipeEntS2.Add<AABB>(pipeEntS2, mainPlayer, 2.5f, 2.5f);
	pipeCol2.SetIsAmbient(true);

	auto& doorCol = doorEnt.Add<AABB>(doorEnt, mainPlayer);
	doorCol.SetComplete(false);

	//Buttons
	auto& button = buttonEnt.Add<Lever>(wireEnt);
	button.SetPowered(false);
	auto& button2 = buttonEnt2.Add<Lever>(wireEnt2);
	button2.SetPowered(false);
	auto& button3 = buttonEnt3.Add<Lever>(wireEnt3);
	button3.SetPowered(false);
	auto& button4 = buttonEnt4.Add<Lever>(wireEnt4);
	button4.SetPowered(false);

	//Wires
	auto& wire = wireEnt.Add<Wire>(buttonEnt);
	auto& wire2 = wireEnt2.Add<Wire>(buttonEnt2);
	auto& wire3 = wireEnt3.Add<Wire>(buttonEnt3);
	auto& wire4 = wireEnt4.Add<Wire>(buttonEnt4);
	auto& wire5 = wireEnt5.Add<Wire>(orEnt);
	auto& wire6 = wireEnt6.Add<Wire>(orEnt2);
	auto& wire7 = wireEnt7.Add<Wire>(andEnt);

	//Gates
	auto& andGate = andEnt.Add<AndGate>(wireEnt5, wireEnt6, doorEnt);
	auto& orGate = orEnt.Add<OrGate>(wireEnt, wireEnt2, wireEnt5);
	auto& orGate2 = orEnt2.Add<OrGate>(wireEnt3, wireEnt4, wireEnt6);

	//Door
	auto& door = doorEnt.Add<Door>();
	door.SetOpen(false);

	InitAnims();

#pragma region Mesh Loading
	auto& playerMesh = mainPlayer.Add<MorphRenderer>(mainPlayer, *idle1, animShader);
	auto& floorMesh = floorEnt.Add<MeshRenderer>(floorEnt, *floorLab, shader);
	auto& leftMesh = leftEnt.Add<MeshRenderer>(leftEnt, *leftWallLab, shader);
	auto& rightMesh = rightEnt.Add<MeshRenderer>(rightEnt, *rightWallLab, shader);
	auto& backMesh = backEnt.Add<MeshRenderer>(backEnt, *backWallLab, shader);

	auto& doorMesh = doorEnt.Add<MorphRenderer>(doorEnt, *door1, animShader);

	auto& pauseMesh = pauseEnt.Add<MeshRenderer>(pauseEnt, *screen, pauseShader);
	auto& optionMesh = optionEnt.Add<MeshRenderer>(optionEnt, *options, pauseShader);
	auto& retryMesh = retryEnt.Add<MeshRenderer>(retryEnt, *retry, pauseShader);
	auto& exitMesh = exitEnt.Add<MeshRenderer>(exitEnt, *exit, pauseShader);
	auto& tutMesh = tutEnt.Add<MeshRenderer>(tutEnt, *tut, untexturedShader);
	auto& completeMesh = completeEnt.Add<MeshRenderer>(completeEnt, *screen, shader);

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

	auto& buttonMesh = buttonEnt.Add<MorphRenderer>(buttonEnt, *buttonM, animShader);
	auto& buttonMesh2 = buttonEnt2.Add<MorphRenderer>(buttonEnt2, *buttonM, animShader);
	auto& buttonMesh3 = buttonEnt3.Add<MorphRenderer>(buttonEnt3, *buttonM, animShader);
	auto& buttonMesh4 = buttonEnt4.Add<MorphRenderer>(buttonEnt4, *buttonM, animShader);

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

	auto& tabletScreenMesh = tabletScreenEnt.Add<MeshRenderer>(tabletScreenEnt, *screen, pauseShader);
	auto& tabletMesh = tabletEnt.Add<MeshRenderer>(tabletEnt, *tablet, rimLightShader);
	auto& optionsMenuMesh = optionsMenuEnt.Add<MeshRenderer>(optionsMenuEnt, *screen, pauseShader);

	entList.push_back(&mainPlayer);
	entList.push_back(&doorEnt);
	entList.push_back(&buttonEnt);
	entList.push_back(&buttonEnt2);
	entList.push_back(&buttonEnt3);
	entList.push_back(&buttonEnt4);
	entList.push_back(&floorEnt);
	entList.push_back(&leftEnt);
	entList.push_back(&rightEnt);
	entList.push_back(&andEnt);
	entList.push_back(&orEnt);
	entList.push_back(&orEnt2);
	entList.push_back(&shelfPipeEnt);
	entList.push_back(&shelfPipeEnt2);
	entList.push_back(&shelfPipeEnt3);
	entList.push_back(&shelfPipeEnt4);
	entList.push_back(&columnPipeEnt);
	entList.push_back(&columnPipeEnt2);
	entList.push_back(&panelEnt);
	entList.push_back(&wireEnt);
	entList.push_back(&wireEnt2);
	entList.push_back(&wireEnt3);
	entList.push_back(&wireEnt4);
	entList.push_back(&wireEnt5);
	entList.push_back(&wireEnt6);
	entList.push_back(&wireEnt7);
	entList.push_back(&coilEnt);
	entList.push_back(&pipeEntC);
	entList.push_back(&pipeEntC2);
	entList.push_back(&pipeEntS);
	entList.push_back(&pipeEntS2);
	entList.push_back(&ventEnt);
	entList.push_back(&ventEnt2);
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

	auto& buttonAnimator2 = buttonEnt2.Add<MorphAnimation>(buttonEnt2);
	buttonAnimator2.SetTime(0.2f);
	buttonAnimator2.SetFrames(buttonFrames);
	buttonAnimator2.SetLoop(false);

	auto& buttonAnimator3 = buttonEnt3.Add<MorphAnimation>(buttonEnt3);
	buttonAnimator3.SetTime(0.2f);
	buttonAnimator3.SetFrames(buttonFrames);
	buttonAnimator3.SetLoop(false);

	auto& buttonAnimator4 = buttonEnt4.Add<MorphAnimation>(buttonEnt4);
	buttonAnimator4.SetTime(0.2f);
	buttonAnimator4.SetFrames(buttonFrames);
	buttonAnimator4.SetLoop(false);
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
}

void Level5::Update(float dt)
{
	// Get a ref to the engine
	AudioEngine& audioEngine = AudioEngine::Instance();

	AudioEvent& walkSound = AudioEngine::Instance().GetEvent("Walk");
	AudioEvent& doorSound = AudioEngine::Instance().GetEvent("Door");
	AudioEvent& levelCompleteSound = AudioEngine::Instance().GetEvent("Level Complete");

	time += dt;

	if (!tabletOpen && !isPaused && !optionsOpen)
	{
		untexturedShader->SetUniform("u_Time", time);
		shader->SetUniform("u_Time", time);
		pauseShader->SetUniform("u_Time", time);
		animShader->SetUniform("u_Time", time);
		rimLightShader->SetUniform("u_Time", time);
	}



#pragma region Transforms
	auto& playerTrans = mainPlayer.Get<Transform>();
	auto& buttonTrans = buttonEnt.Get<Transform>();
	auto& buttonTrans2 = buttonEnt2.Get<Transform>();
	auto& buttonTrans3 = buttonEnt3.Get<Transform>();
	auto& buttonTrans4 = buttonEnt4.Get<Transform>();

	backEnt.Get<Transform>().SetPositionZ(-51.5f);
	backEnt.Get<Transform>().SetPositionY(0.0f);

	leftEnt.Get<Transform>().SetPositionX(-51.5f);
	leftEnt.Get<Transform>().SetRotationY(90.0f);
	leftEnt.Get<Transform>().SetPositionY(0.0f);

	rightEnt.Get<Transform>().SetPositionX(51.5f);
	rightEnt.Get<Transform>().SetRotationY(90.0f);
	rightEnt.Get<Transform>().SetPositionY(0.0f);

	tabletEnt.Get<Transform>().SetRotationY(tabletEnt.Get<Transform>().GetRotation().y + 100 * dt);
#pragma endregion

	auto& camera = camEnt.Get<Camera>();
	auto& orthoCam = uiCamEnt.Get<Camera>();

	if (!showLevelComplete)
		topViewToggle.Poll(window);

	camera = Input::ToggleCam(mainPlayer, camEnt, topViewCamEnt, topView, camChanged, topChanged);

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
	glm::mat4 transformComplete = completeEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformTut = tutEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformTablet = tabletEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformTabletScreen = tabletScreenEnt.Get<Transform>().GetModelMatrix();

	if (!buttonAnimOn && playerTrans.GetPositionX() - buttonTrans.GetPositionX() < 3.0f && playerTrans.GetPositionX() - buttonTrans.GetPositionX() > -3.0f
		&& playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() > -3.0f)
		button1Watch.Poll(window);

	if (!button2AnimOn && playerTrans.GetPositionX() - buttonTrans2.GetPositionX() < 3.0f && playerTrans.GetPositionX() - buttonTrans2.GetPositionX() > -3.0f
		&& playerTrans.GetPositionZ() - buttonTrans2.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans2.GetPositionZ() > -3.0f)
		button2Watch.Poll(window);

	if (!button3AnimOn && playerTrans.GetPositionX() - buttonTrans3.GetPositionX() < 3.0f && playerTrans.GetPositionX() - buttonTrans3.GetPositionX() > -3.0f
		&& playerTrans.GetPositionZ() - buttonTrans3.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans3.GetPositionZ() > -3.0f)
		button3Watch.Poll(window);

	if (!button4AnimOn && playerTrans.GetPositionX() - buttonTrans4.GetPositionX() < 3.0f && playerTrans.GetPositionX() - buttonTrans4.GetPositionX() > -3.0f
		&& playerTrans.GetPositionZ() - buttonTrans4.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans4.GetPositionZ() > -3.0f)
		button4Watch.Poll(window);

	if ((playerTrans.GetPositionX() > -5.0f && playerTrans.GetPositionX() < 1.0f
		&& playerTrans.GetPositionZ() > 17.0f && playerTrans.GetPositionZ() < 23.0f
		&& !tabletOpen) || tabletOpen)
		tabletWatch.Poll(window);

	if (!optionsOpen)
		pauseWatch.Poll(window);

	if (showLevelComplete)
	{
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			levelComplete = true;
		}
	}

#pragma region PlayerMovement
	if (!showLevelComplete && !isPaused)
	{
		isWalking = Input::MovePlayer(window, mainPlayer, camEnt, dt, camFar, camClose, camLeft, camRight);

		if (isWalking)
			walkSound.Play();
		else
			walkSound.StopImmediately();

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

	if (!showLevelComplete && !isPaused)
	{
		Input::MoveCamera(window, camEnt, dt);
	}
#pragma endregion

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

	if (button3AnimOn)
	{
		if (buttonEnt3.Get<MorphAnimation>().GetIsDone())
		{
			buttonEnt3.Get<MorphAnimation>().SetFrames(buttonFrames);
			buttonEnt3.Get<MorphAnimation>().SetTime(0.2f);
			button3AnimOn = false;
		}

		buttonEnt3.Get<MorphAnimation>().Update(dt);
	}

	if (button4AnimOn)
	{
		if (buttonEnt4.Get<MorphAnimation>().GetIsDone())
		{
			buttonEnt4.Get<MorphAnimation>().SetFrames(buttonFrames);
			buttonEnt4.Get<MorphAnimation>().SetTime(0.2f);
			button4AnimOn = false;
		}

		buttonEnt4.Get<MorphAnimation>().Update(dt);
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
		if (i < 6)
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
			mainPlayer.Get<MorphRenderer>().Render(camera, transform);

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
			buttonEnt2.Get<MorphRenderer>().Render(camera, transformButton2, LightSpaceViewProjection);
			buttonEnt3.Get<MorphRenderer>().Render(camera, transformButton3, LightSpaceViewProjection);
			buttonEnt4.Get<MorphRenderer>().Render(camera, transformButton4, LightSpaceViewProjection);
			shadowBuffer->UnbindTexture(30);

			untexturedShader->Bind();
			//Floor (no texture for now)
			shadowBuffer->BindDepthAsTexture(30);


			if ((playerTrans.GetPositionX() > -5.0f && playerTrans.GetPositionX() < 1.0f
					&& playerTrans.GetPositionZ() > 17.0f && playerTrans.GetPositionZ() < 23.0f
					&& !tabletOpen) 
				|| (playerTrans.GetPositionX() - buttonTrans.GetPositionX() < 3.0f
					&& playerTrans.GetPositionX() - buttonTrans.GetPositionX() > -3.0f
					&& playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() < 3.0f
					&& playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() > -3.0f)
				|| (playerTrans.GetPositionX() - buttonTrans2.GetPositionX() < 3.0f
					&& playerTrans.GetPositionX() - buttonTrans2.GetPositionX() > -3.0f
					&& playerTrans.GetPositionZ() - buttonTrans2.GetPositionZ() < 3.0f
					&& playerTrans.GetPositionZ() - buttonTrans2.GetPositionZ() > -3.0f)
				|| (playerTrans.GetPositionX() - buttonTrans3.GetPositionX() < 3.0f
					&& playerTrans.GetPositionX() - buttonTrans3.GetPositionX() > -3.0f
					&& playerTrans.GetPositionZ() - buttonTrans3.GetPositionZ() < 3.0f
					&& playerTrans.GetPositionZ() - buttonTrans3.GetPositionZ() > -3.0f)
				|| (playerTrans.GetPositionX() - buttonTrans4.GetPositionX() < 3.0f
					&& playerTrans.GetPositionX() - buttonTrans4.GetPositionX() > -3.0f
					&& playerTrans.GetPositionZ() - buttonTrans4.GetPositionZ() < 3.0f
					&& playerTrans.GetPositionZ() - buttonTrans4.GetPositionZ() > -3.0f))
			{
				if (!tabletOpen)
					tutEnt.Get<MeshRenderer>().Render(orthoCam, transformTut, LightSpaceViewProjection);
				else
				{

				}
			}
			shadowBuffer->UnbindTexture(30);

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
			orTabletScreenMat.Albedo->Bind(4);

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
			shadowBuffer->UnbindTexture(30);

			shader->Bind();
			//Wires
			shader->SetUniform("s_Diffuse", 0);
			shadowBuffer->BindDepthAsTexture(30);
			if (wireEnt.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(0);
				wireEnt.Get<MeshRenderer>().Render(camera, transformWire, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt.Get<MeshRenderer>().Render(camera, transformWire, LightSpaceViewProjection);
			}

			if (wireEnt2.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(0);
				wireEnt2.Get<MeshRenderer>().Render(camera, transformWire2, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt2.Get<MeshRenderer>().Render(camera, transformWire2, LightSpaceViewProjection);
			}

			if (wireEnt3.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(0);
				wireEnt3.Get<MeshRenderer>().Render(camera, transformWire3, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt3.Get<MeshRenderer>().Render(camera, transformWire3, LightSpaceViewProjection);
			}

			if (wireEnt4.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(0);
				wireEnt4.Get<MeshRenderer>().Render(camera, transformWire3, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt4.Get<MeshRenderer>().Render(camera, transformWire3, LightSpaceViewProjection);
			}

			if (wireEnt5.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(0);
				wireEnt5.Get<MeshRenderer>().Render(camera, transformWire3, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt5.Get<MeshRenderer>().Render(camera, transformWire3, LightSpaceViewProjection);
			}

			if (wireEnt6.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(0);
				wireEnt6.Get<MeshRenderer>().Render(camera, transformWire3, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt6.Get<MeshRenderer>().Render(camera, transformWire3, LightSpaceViewProjection);
			}

			if (wireEnt7.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(0);
				wireEnt7.Get<MeshRenderer>().Render(camera, transformWire3, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt7.Get<MeshRenderer>().Render(camera, transformWire3, LightSpaceViewProjection);
			}

			//Vents
			shader->SetUniform("s_Diffuse", 1);
			ventMat.Albedo->Bind(1);
			ventEnt.Get<MeshRenderer>().Render(camera, transformVent, LightSpaceViewProjection);
			ventEnt2.Get<MeshRenderer>().Render(camera, transformVent2, LightSpaceViewProjection);

			//Gates
			//And-Gate
			shader->SetUniform("s_Diffuse", 2);
			andMat.Albedo->Bind(2);
			andEnt.Get<MeshRenderer>().Render(camera, transformGate, LightSpaceViewProjection);

			//Or-Gate
			shader->SetUniform("s_Diffuse", 3);
			orMat.Albedo->Bind(3);
			orEnt.Get<MeshRenderer>().Render(camera, transformOr, LightSpaceViewProjection);
			orEnt2.Get<MeshRenderer>().Render(camera, transformOr2, LightSpaceViewProjection);

			//Walls
			shader->SetUniform("s_Diffuse", 4);
			labWallMat.Albedo->Bind(4);

			leftEnt.Get<MeshRenderer>().Render(camera, transformLeft, LightSpaceViewProjection);
			rightEnt.Get<MeshRenderer>().Render(camera, transformRight, LightSpaceViewProjection);
			backEnt.Get<MeshRenderer>().Render(camera, transformBack, LightSpaceViewProjection);

			//Tesla Coil (remember to add the other texture)
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

			//Shelf Pipes
			shader->SetUniform("s_Diffuse", 6);
			shelfPipeMat.Albedo->Bind(6);
			shelfPipeEnt.Get<MeshRenderer>().Render(camera, transformShelfPipe, LightSpaceViewProjection);
			shelfPipeEnt2.Get<MeshRenderer>().Render(camera, transformShelfPipe2, LightSpaceViewProjection);
			shelfPipeEnt3.Get<MeshRenderer>().Render(camera, transformShelfPipe3, LightSpaceViewProjection);
			shelfPipeEnt4.Get<MeshRenderer>().Render(camera, transformShelfPipe4, LightSpaceViewProjection);

			//Column Pipes
			shader->SetUniform("s_Diffuse", 7);
			columnPipeMat.Albedo->Bind(7);
			columnPipeEnt.Get<MeshRenderer>().Render(camera, transformColPipe, LightSpaceViewProjection);
			columnPipeEnt2.Get<MeshRenderer>().Render(camera, transformColPipe2, LightSpaceViewProjection);

			//Panels
			shader->SetUniform("s_Diffuse", 8);
			panelMat.Albedo->Bind(8);
			panelEnt.Get<MeshRenderer>().Render(camera, transformPanel, LightSpaceViewProjection);

			//Curved Pipe
			shader->SetUniform("s_Diffuse", 9);
			curvedPipeMat.Albedo->Bind(9);
			pipeEntC.Get<MeshRenderer>().Render(camera, transformPipe, LightSpaceViewProjection);
			pipeEntC2.Get<MeshRenderer>().Render(camera, transformPipe2, LightSpaceViewProjection);

			//Straight Pipe
			shader->SetUniform("s_Diffuse", 10);
			straightPipeMat.Albedo->Bind(10);
			pipeEntS.Get<MeshRenderer>().Render(camera, transformPipe3, LightSpaceViewProjection);
			pipeEntS2.Get<MeshRenderer>().Render(camera, transformPipe4, LightSpaceViewProjection);

			shader->SetUniform("s_Diffuse", 11);
			labFloorMat.Albedo->Bind(11);
			floorEnt.Get<MeshRenderer>().Render(camera, transformGround, LightSpaceViewProjection);
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
			mainPlayer.Get<MorphRenderer>().Render(camera, transform);

			animShader->SetUniform("s_Diffuse", 1);
			clearMat.Albedo->Bind(1);
			doorEnt.Get<MorphRenderer>().Render(camera, transformDoor);
			clearMat.Albedo->Unbind(1);
			shadowBuffer->UnbindTexture(30);

			untexturedShader->Bind();
			shadowBuffer->BindDepthAsTexture(30);
			floorEnt.Get<MeshRenderer>().Render(camera, transformGround);
			leftEnt.Get<MeshRenderer>().Render(camera, transformLeft);
			rightEnt.Get<MeshRenderer>().Render(camera, transformRight);
			backEnt.Get<MeshRenderer>().Render(camera, transformBack);
			shadowBuffer->UnbindTexture(30);

			pauseShader->Bind();
			pauseShader->SetUniform("s_Diffuse", 0);
			clearMat.Albedo->Bind(0);
			shadowBuffer->BindDepthAsTexture(30);

			if (isPaused)
			{
				pauseEnt.Get<MeshRenderer>().Render(orthoCam, transformPause);
			}
			shadowBuffer->UnbindTexture(30);

			shader->Bind();
			shader->SetUniform("s_Diffuse", 0);
			clearMat.Albedo->Bind(0);
			shadowBuffer->BindDepthAsTexture(30);
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
			tabletEnt.Get<MeshRenderer>().Render(camera, transformTablet, LightSpaceViewProjection);
			shadowBuffer->UnbindTexture(30);

			rimLightShader->Bind();
			rimLightShader->SetUniform("s_Diffuse", 1);
			clearMat.Albedo->Bind(1);
			shadowBuffer->BindDepthAsTexture(30);
			tabletEnt.Get<MeshRenderer>().Render(camera, transformTablet, LightSpaceViewProjection);
			shadowBuffer->UnbindTexture(30);
		}
	}

	if (showLevelComplete)
	{
		shader->Bind();
		shader->SetUniform("s_Diffuse", 0);
		completeMat.Albedo->Bind(0);
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

	backEnt.Get<AABB>().Update();
	leftEnt.Get<AABB>().Update();
	rightEnt.Get<AABB>().Update();
	doorEnt.Get<AABB>().Update();
	andEnt.Get<AABB>().Update();
	orEnt.Get<AABB>().Update();
	orEnt2.Get<AABB>().Update();
	coilEnt.Get<AABB>().Update();
	buttonEnt.Get<AABB>().Update();
	buttonEnt2.Get<AABB>().Update();
	buttonEnt3.Get<AABB>().Update();
	buttonEnt4.Get<AABB>().Update();
	columnPipeEnt.Get<AABB>().Update();
	columnPipeEnt2.Get<AABB>().Update();
	pipeEntS.Get<AABB>().Update();
	pipeEntS2.Get<AABB>().Update();
	andEnt.Get<AndGate>().Update();
	orEnt.Get<OrGate>().Update();
	orEnt2.Get<OrGate>().Update();
	buttonEnt.Get<Lever>().Update();
	buttonEnt2.Get<Lever>().Update();
	buttonEnt3.Get<Lever>().Update();
	buttonEnt4.Get<Lever>().Update();
	wireEnt.Get<Wire>().Update();
	wireEnt2.Get<Wire>().Update();
	wireEnt3.Get<Wire>().Update();
	wireEnt4.Get<Wire>().Update();
	wireEnt5.Get<Wire>().Update();
	wireEnt6.Get<Wire>().Update();
	wireEnt7.Get<Wire>().Update();

	audioEngine.Update();

	//Door Logic
	if (doorEnt.Get<Door>().GetOpen() && doorOpenApplied)
		doorEnt.Get<MorphAnimation>().Update(dt);
	if (!doorEnt.Get<Door>().GetOpen() && doorClosingApplied)
		doorEnt.Get<MorphAnimation>().Update(dt);

	if (doorEnt.Get<AABB>().GetComplete())
	{
		lightOn = false;
		AudioEngine::Instance().GetEvent("BG").StopImmediately();
		levelCompleteSound.Play();
		showLevelComplete = true;
	}
}

void Level5::Unload()
{
	//AudioEngine::Instance().Shutdown();
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}