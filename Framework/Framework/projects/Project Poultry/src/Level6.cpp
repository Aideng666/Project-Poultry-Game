#include "Level6.h"
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

Level6::Level6(std::string sceneName, GLFWwindow* wind)
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
	wireEnt8 = Entity::Create();
	wireEnt9 = Entity::Create();

	doorEnt = Entity::Create();

	coilEnt = Entity::Create();

	panelEnt = Entity::Create();
	panelEnt2 = Entity::Create();

	buttonEnt = Entity::Create();
	buttonEnt2 = Entity::Create();
	buttonEnt3 = Entity::Create();

	columnPipeEnt = Entity::Create();
	columnPipeEnt2 = Entity::Create();

	shelfPipeEnt = Entity::Create();
	shelfPipeEnt2 = Entity::Create();

	ventEnt = Entity::Create();
	ventEnt2 = Entity::Create();
	ventEnt3 = Entity::Create();

	andEnt = Entity::Create();
	orEnt = Entity::Create();
	orEnt2 = Entity::Create();
	notEnt = Entity::Create();
	notEnt2 = Entity::Create();
	notEnt3 = Entity::Create();
	notEnt4 = Entity::Create();

	boxEnt = Entity::Create();
	boxEnt2 = Entity::Create();
	boxEnt3 = Entity::Create();
	boxEnt4 = Entity::Create();

	pauseEnt = Entity::Create();
	optionEnt = Entity::Create();
	exitEnt = Entity::Create();
	retryEnt = Entity::Create();
	completeEnt = Entity::Create();
	tutEnt = Entity::Create();

	FBO = Entity::Create();
	greyscaleEnt = Entity::Create();
	sepiaEnt = Entity::Create();
	colorCorrectEnt = Entity::Create();

	filmGrainEnt = Entity::Create();
	pixelateEnt = Entity::Create();
	bloomEnt = Entity::Create();

	camEnt = Entity::Create();
	uiCamEnt = Entity::Create();
	topViewCamEnt = Entity::Create();
#pragma endregion

	InitMeshes();
}

void Level6::InitScene()
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
	playerTrans.SetPosition(glm::vec3(0.0f, 1.1f, 45.f));
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

	auto& wireTrans8 = wireEnt8.Add<Transform>();
	wireTrans8.SetPosition(glm::vec3(0.f, 1.f, 0.f));

	auto& wireTrans9 = wireEnt9.Add<Transform>();
	wireTrans9.SetPosition(glm::vec3(0.f, 1.f, 0.f));

	//Coil Object
	auto& coilTrans = coilEnt.Add<Transform>();
	coilTrans.SetPosition(glm::vec3(-18.0f, 1.0f, -48.f));
	coilTrans.SetScale(glm::vec3(3.0f));
	coilTrans.SetRotationY(180.0f);

	//Panel transforms
	auto& panelTrans = panelEnt.Add<Transform>();
	panelTrans.SetScale(glm::vec3(4.0f));
	panelTrans.SetPosition(glm::vec3(27.f, 5.0f, -51.f));
	panelTrans.SetRotationY(-90.f);

	auto& panelTrans2 = panelEnt2.Add<Transform>();
	panelTrans2.SetScale(glm::vec3(4.0f));
	panelTrans2.SetPosition(glm::vec3(-27.f, 5.0f, -51.f));
	panelTrans2.SetRotationY(-90.f);

	//Button transforms
	auto& buttonTrans = buttonEnt.Add<Transform>();
	buttonTrans.SetPosition(glm::vec3(-21.6f, -1.0f, 40.f));

	auto& buttonTrans2 = buttonEnt2.Add<Transform>();
	buttonTrans2.SetPosition(glm::vec3(-1.2f, -1.0f, 40.8f));

	auto& buttonTrans3 = buttonEnt3.Add<Transform>();
	buttonTrans3.SetPosition(glm::vec3(20.1f, -1.0f, 38.f));

	//Column Pipe transforms
	auto& colPipeTrans = columnPipeEnt.Add<Transform>();
	colPipeTrans.SetPosition(glm::vec3(49.f, 1.f, 10.f));
	colPipeTrans.SetScale(glm::vec3(1.5f));

	auto& colPipeTrans2 = columnPipeEnt2.Add<Transform>();
	colPipeTrans2.SetPosition(glm::vec3(-49.f, 1.f, -30.f));
	colPipeTrans2.SetScale(glm::vec3(1.5f));

	//Shelf Pipe transforms
	auto& shelfPipeTrans = shelfPipeEnt.Add<Transform>();
	shelfPipeTrans.SetPosition(glm::vec3(-33.f, 17.f, -47.f));
	shelfPipeTrans.SetRotationY(270.f);
	shelfPipeTrans.SetScale(glm::vec3(1.5f));

	auto& shelfPipeTrans2 = shelfPipeEnt2.Add<Transform>();
	shelfPipeTrans2.SetPosition(glm::vec3(21.f, 17.f, -47.f));
	shelfPipeTrans2.SetRotationY(270.f);
	shelfPipeTrans2.SetScale(glm::vec3(1.5f));

	//Vent transforms
	auto& ventTrans = ventEnt.Add<Transform>();
	ventTrans.SetPosition(glm::vec3(50.8f, 30.f, 10.f));
	ventTrans.SetScale(glm::vec3(1.2f));
	ventTrans.SetRotationZ(180.f);

	auto& ventTrans2 = ventEnt2.Add<Transform>();
	ventTrans2.SetPosition(glm::vec3(50.8f, 15.f, -40.f));
	ventTrans2.SetScale(glm::vec3(1.2f));
	ventTrans2.SetRotationZ(180.f);

	auto& ventTrans3 = ventEnt3.Add<Transform>();
	ventTrans3.SetPosition(glm::vec3(50.8f, 15.f, -25.f));
	ventTrans3.SetScale(glm::vec3(1.2f));
	ventTrans3.SetRotationZ(180.f);

	//Gate transforms
	//And-Gate
	auto& gateTrans = andEnt.Add<Transform>();
	gateTrans.SetPosition(glm::vec3(-8.9f, 1.2f, 16.5f));
	gateTrans.SetRotationY(-90.0f);
	gateTrans.SetScale(glm::vec3(2.0f));

	//Or-Gate
	auto& gateTrans2 = orEnt.Add<Transform>();
	gateTrans2.SetPosition(glm::vec3(6.7f, 1.f, 16.5f));
	gateTrans2.SetRotationY(-90.0f);
	gateTrans2.SetScale(glm::vec3(2.0f));

	auto& gateTrans3 = orEnt2.Add<Transform>();
	gateTrans3.SetPosition(glm::vec3(-1.1f, 1.f, -6.f));
	gateTrans3.SetRotationY(-90.0f);
	gateTrans3.SetScale(glm::vec3(2.0f));

	//Not-Gate
	auto& notTrans = notEnt.Add<Transform>();
	notTrans.SetPosition(glm::vec3(-1.3f, 1.f, -18.5f));
	notTrans.SetRotationY(-90.0f);
	notTrans.SetScale(glm::vec3(2.0f));

	auto& notTrans2 = notEnt2.Add<Transform>();
	notTrans2.SetPosition(glm::vec3(-21.8f, 1.f, 9.8f));
	notTrans2.SetRotationY(-90.0f);
	notTrans2.SetScale(glm::vec3(2.0f));

	auto& notTrans3 = notEnt3.Add<Transform>();
	notTrans3.SetPosition(glm::vec3(-21.8f, 1.f, 26.f));
	notTrans3.SetRotationY(-90.0f);
	notTrans3.SetScale(glm::vec3(2.0f));

	auto& notTrans4 = notEnt4.Add<Transform>();
	notTrans4.SetPosition(glm::vec3(20.f, 1.f, 24.9f));
	notTrans4.SetRotationY(-90.0f);
	notTrans4.SetScale(glm::vec3(2.0f));

	//Boxes
	auto& boxTrans = boxEnt.Add<Transform>();
	boxTrans.SetPosition(glm::vec3(-48.f, 4.6f, 20.f));

	auto& boxTrans2 = boxEnt2.Add<Transform>();
	boxTrans2.SetPosition(glm::vec3(-48.f, 11.6f, 35.f));

	auto& boxTrans3 = boxEnt3.Add<Transform>();
	boxTrans3.SetPosition(glm::vec3(-48.f, 4.6f, 35.f));
	boxTrans3.SetRotationY(90.f);

	auto& boxTrans4 = boxEnt4.Add<Transform>();
	boxTrans4.SetPosition(glm::vec3(-41.f, 4.6f, 20.f));
	boxTrans4.SetRotationY(90.f);

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

	//Level complete transform
	auto& completeTrans = completeEnt.Add<Transform>();
	completeTrans.SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	completeTrans.SetScale(glm::vec3(0.22f));

	//Interact text transform
	auto& tutTrans = tutEnt.Add<Transform>();
	tutTrans.SetPosition(glm::vec3(1.0f, 2.0f, 5.0f));
	tutTrans.SetScale(glm::vec3(1.0f));
#pragma endregion

	auto& leftCol = leftEnt.Add<AABB>(leftEnt, mainPlayer);
	auto& rightCol = rightEnt.Add<AABB>(rightEnt, mainPlayer);
	auto& backCol = backEnt.Add<AABB>(backEnt, mainPlayer);
	auto& coilCol = coilEnt.Add<AABB>(coilEnt, mainPlayer, 4.0f, 4.0f);
	coilCol.SetIsAmbient(true);
	auto& buttonCol = buttonEnt.Add<AABB>(buttonEnt, mainPlayer, 2.0f, 2.0f);
	buttonCol.SetIsAmbient(true);
	auto& buttonCol2 = buttonEnt2.Add<AABB>(buttonEnt2, mainPlayer, 2.0f, 2.0f);
	buttonCol2.SetIsAmbient(true);
	auto& buttonCol3 = buttonEnt3.Add<AABB>(buttonEnt3, mainPlayer, 2.0f, 2.0f);
	buttonCol3.SetIsAmbient(true);
	auto& columnPipeCol = columnPipeEnt.Add<AABB>(columnPipeEnt, mainPlayer, 3.0f, 14.5f);
	columnPipeCol.SetIsAmbient(true);
	auto& columnPipeCol2 = columnPipeEnt2.Add<AABB>(columnPipeEnt2, mainPlayer, 3.0f, 14.5f);
	columnPipeCol2.SetIsAmbient(true);
	auto& andCol = andEnt.Add<AABB>(andEnt, mainPlayer, 5.0f, 3.0f);
	andCol.SetIsAmbient(true);
	auto& orCol = orEnt.Add<AABB>(orEnt, mainPlayer, 5.0f, 3.0f);
	orCol.SetIsAmbient(true);
	auto& orCol2 = orEnt2.Add<AABB>(orEnt2, mainPlayer, 5.0f, 3.0f);
	orCol2.SetIsAmbient(true);
	auto& notCol = notEnt.Add<AABB>(notEnt, mainPlayer, 3.5f, 3.0f);
	notCol.SetIsAmbient(true);
	auto& notCol2 = notEnt2.Add<AABB>(notEnt2, mainPlayer, 3.5f, 3.0f);
	notCol2.SetIsAmbient(true);
	auto& notCol3 = notEnt3.Add<AABB>(notEnt3, mainPlayer, 3.5f, 3.0f);
	notCol3.SetIsAmbient(true);
	auto& notCol4 = notEnt4.Add<AABB>(notEnt4, mainPlayer, 3.5f, 3.0f);
	notCol4.SetIsAmbient(true);
	auto& boxCol = boxEnt.Add<AABB>(boxEnt, mainPlayer, 5.0f, 5.0f);
	boxCol.SetIsAmbient(true);
	auto& boxCol2 = boxEnt2.Add<AABB>(boxEnt2, mainPlayer, 5.0f, 5.0f);
	boxCol2.SetIsAmbient(true);
	auto& boxCol3 = boxEnt3.Add<AABB>(boxEnt3, mainPlayer, 5.0f, 5.0f);
	boxCol3.SetIsAmbient(true);
	auto& boxCol4 = boxEnt4.Add<AABB>(boxEnt4, mainPlayer, 5.0f, 5.0f);
	boxCol4.SetIsAmbient(true);

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
	auto& wire4 = wireEnt4.Add<Wire>(notEnt3);
	auto& wire5 = wireEnt5.Add<Wire>(notEnt4);
	auto& wire6 = wireEnt6.Add<Wire>(notEnt2);
	auto& wire7 = wireEnt7.Add<Wire>(buttonEnt);
	auto& wire8 = wireEnt8.Add<Wire>(buttonEnt2);
	auto& wire9 = wireEnt9.Add<Wire>(buttonEnt2);

	//Gates
	auto& andGate = andEnt.Add<AndGate>(wireEnt, wireEnt2, doorEnt);
	auto& orGate = orEnt.Add<OrGate>(wireEnt, wireEnt2, wireEnt5);
	auto& orGate2 = orEnt2.Add<OrGate>(wireEnt3, wireEnt4, wireEnt6);
	auto& notGate = notEnt.Add<NotGate>(wireEnt2, wireEnt5);
	auto& notGate2 = notEnt2.Add<NotGate>(wireEnt6, wireEnt8);
	auto& notGate3 = notEnt3.Add<NotGate>(wireEnt7, wireEnt9);
	auto& notGate4 = notEnt4.Add<NotGate>(wireEnt7, wireEnt9);

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

	auto& wireMesh = wireEnt.Add<MeshRenderer>(wireEnt, *wireM1L6, shader);
	auto& wireMesh2 = wireEnt2.Add<MeshRenderer>(wireEnt2, *wireM2L6, shader);
	auto& wireMesh3 = wireEnt3.Add<MeshRenderer>(wireEnt3, *wireM3L6, shader);
	auto& wireMesh4 = wireEnt4.Add<MeshRenderer>(wireEnt4, *wireM4L6, shader);
	auto& wireMesh5 = wireEnt5.Add<MeshRenderer>(wireEnt5, *wireM5L6, shader);
	auto& wireMesh6 = wireEnt6.Add<MeshRenderer>(wireEnt6, *wireM6L6, shader);
	auto& wireMesh7 = wireEnt7.Add<MeshRenderer>(wireEnt7, *wireM7L6, shader);
	auto& wireMesh8 = wireEnt8.Add<MeshRenderer>(wireEnt8, *wireM8L6, shader);
	auto& wireMesh9 = wireEnt9.Add<MeshRenderer>(wireEnt9, *wireM9L6, shader);

	auto& coilMesh = coilEnt.Add<MeshRenderer>(coilEnt, *coil, shader);

	auto& panelMesh = panelEnt.Add<MeshRenderer>(panelEnt, *panel, shader);
	auto& panelMesh2 = panelEnt2.Add<MeshRenderer>(panelEnt2, *panel, shader);

	auto& buttonMesh = buttonEnt.Add<MorphRenderer>(buttonEnt, *buttonM, animShader);
	auto& buttonMesh2 = buttonEnt2.Add<MorphRenderer>(buttonEnt2, *buttonM, animShader);
	auto& buttonMesh3 = buttonEnt3.Add<MorphRenderer>(buttonEnt3, *buttonM, animShader);

	auto& colPipeMesh = columnPipeEnt.Add<MeshRenderer>(columnPipeEnt, *columnPipe, shader);
	auto& colPipeMesh2 = columnPipeEnt2.Add<MeshRenderer>(columnPipeEnt2, *columnPipe, shader);
	
	auto& shelfPipeMesh = shelfPipeEnt.Add<MeshRenderer>(shelfPipeEnt, *shelfPipe, shader);
	auto& shelfPipeMesh2 = shelfPipeEnt2.Add<MeshRenderer>(shelfPipeEnt2, *shelfPipe, shader);

	auto& vent = ventEnt.Add<MeshRenderer>(ventEnt, *ventS, shader);
	auto& vent2 = ventEnt2.Add<MeshRenderer>(ventEnt2, *ventS, shader);
	auto& vent3 = ventEnt3.Add<MeshRenderer>(ventEnt3, *ventS, shader);

	auto& gateMesh = andEnt.Add<MeshRenderer>(andEnt, *and, shader);
	auto& gateMesh2 = orEnt.Add<MeshRenderer>(orEnt, *orMesh, shader);
	auto& gateMesh3 = orEnt2.Add<MeshRenderer>(orEnt2, *orMesh, shader);

	auto& notMesh = notEnt.Add<MeshRenderer>(notEnt, *not, shader);
	auto& notMesh2 = notEnt2.Add<MeshRenderer>(notEnt2, *not, shader);
	auto& notMesh3 = notEnt3.Add<MeshRenderer>(notEnt3, *not, shader);
	auto& notMesh4 = notEnt4.Add<MeshRenderer>(notEnt4, *not, shader);

	auto& boxMesh = boxEnt.Add<MeshRenderer>(boxEnt, *boxM, shader);
	auto& boxMesh2 = boxEnt2.Add<MeshRenderer>(boxEnt2, *boxM, shader);
	auto& boxMesh3 = boxEnt3.Add<MeshRenderer>(boxEnt3, *boxM, shader);
	auto& boxMesh4 = boxEnt4.Add<MeshRenderer>(boxEnt4, *boxM, shader);

	auto& pauseMesh = pauseEnt.Add<MeshRenderer>(pauseEnt, *screen, pauseShader);
	auto& optionMesh = optionEnt.Add<MeshRenderer>(optionEnt, *options, pauseShader);
	auto& retryMesh = retryEnt.Add<MeshRenderer>(retryEnt, *retry, pauseShader);
	auto& exitMesh = exitEnt.Add<MeshRenderer>(exitEnt, *exit, pauseShader);
	auto& completeMesh = completeEnt.Add<MeshRenderer>(completeEnt, *screen, shader);
	auto& tutMesh = tutEnt.Add<MeshRenderer>(tutEnt, *tut, untexturedShader);

	entList.push_back(&mainPlayer);
	entList.push_back(&doorEnt);
	entList.push_back(&buttonEnt);
	entList.push_back(&buttonEnt2);
	entList.push_back(&buttonEnt3);
	entList.push_back(&floorEnt);
	entList.push_back(&leftEnt);
	entList.push_back(&rightEnt);
	entList.push_back(&completeEnt);
	entList.push_back(&andEnt);
	entList.push_back(&orEnt);
	entList.push_back(&orEnt2);
	entList.push_back(&notEnt);
	entList.push_back(&notEnt2);
	entList.push_back(&notEnt3);
	entList.push_back(&notEnt4);
	entList.push_back(&wireEnt);
	entList.push_back(&wireEnt2);
	entList.push_back(&wireEnt3);
	entList.push_back(&wireEnt4);
	entList.push_back(&wireEnt5);
	entList.push_back(&wireEnt6);
	entList.push_back(&wireEnt7);
	entList.push_back(&wireEnt8);
	entList.push_back(&wireEnt9);
	entList.push_back(&boxEnt);
	entList.push_back(&boxEnt2);
	entList.push_back(&boxEnt3);
	entList.push_back(&boxEnt4);
	entList.push_back(&coilEnt);
	entList.push_back(&panelEnt);
	entList.push_back(&panelEnt2);
	entList.push_back(&columnPipeEnt);
	entList.push_back(&columnPipeEnt2);
	entList.push_back(&shelfPipeEnt);
	entList.push_back(&shelfPipeEnt2);
	entList.push_back(&ventEnt);
	entList.push_back(&ventEnt2);
	entList.push_back(&ventEnt3);

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

}

void Level6::Update(float dt)
{
	time += dt;
	untexturedShader->SetUniform("u_Time", time);
	shader->SetUniform("u_Time", time);
	pauseShader->SetUniform("u_Time", time);
	animShader->SetUniform("u_Time", time);

#pragma region Transforms
	auto& playerTrans = mainPlayer.Get<Transform>();
	auto& buttonTrans = buttonEnt.Get<Transform>();
	auto& buttonTrans2 = buttonEnt2.Get<Transform>();
	auto& buttonTrans3 = buttonEnt3.Get<Transform>();

	backEnt.Get<Transform>().SetPositionZ(-51.5f);
	backEnt.Get<Transform>().SetPositionY(0.0f);

	leftEnt.Get<Transform>().SetPositionX(-51.5f);
	leftEnt.Get<Transform>().SetRotationY(90.0f);
	leftEnt.Get<Transform>().SetPositionY(0.0f);

	rightEnt.Get<Transform>().SetPositionX(51.5f);
	rightEnt.Get<Transform>().SetRotationY(90.0f);
	rightEnt.Get<Transform>().SetPositionY(0.0f);
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
	glm::mat4 transformWire8 = wireEnt8.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire9 = wireEnt9.Get<Transform>().GetModelMatrix();

	glm::mat4 transformCoil = coilEnt.Get<Transform>().GetModelMatrix();

	glm::mat4 transformPanel = panelEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformPanel2 = panelEnt2.Get<Transform>().GetModelMatrix();

	glm::mat4 transformButton = buttonTrans.GetModelMatrix();
	glm::mat4 transformButton2 = buttonTrans2.GetModelMatrix();
	glm::mat4 transformButton3 = buttonTrans3.GetModelMatrix();

	glm::mat4 transformColPipe = columnPipeEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformColPipe2 = columnPipeEnt2.Get<Transform>().GetModelMatrix();

	glm::mat4 transformShelfPipe = shelfPipeEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformShelfPipe2 = shelfPipeEnt2.Get<Transform>().GetModelMatrix();


	glm::mat4 transformVent = ventEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformVent2 = ventEnt2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformVent3 = ventEnt3.Get<Transform>().GetModelMatrix();

	glm::mat4 transformGate = andEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformGate2 = orEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformGate3 = orEnt2.Get<Transform>().GetModelMatrix();

	glm::mat4 transformNot = notEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformNot2 = notEnt2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformNot3 = notEnt3.Get<Transform>().GetModelMatrix();
	glm::mat4 transformNot4 = notEnt4.Get<Transform>().GetModelMatrix();

	glm::mat4 transformBox = boxEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformBox2 = boxEnt2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformBox3 = boxEnt3.Get<Transform>().GetModelMatrix();
	glm::mat4 transformBox4 = boxEnt4.Get<Transform>().GetModelMatrix();

	glm::mat4 transformPause = pauseEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformOptions = optionEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformRetry = retryEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformExit = exitEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformComplete = completeEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformTut = tutEnt.Get<Transform>().GetModelMatrix();

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

	if (!button3AnimOn && playerTrans.GetPositionX() - buttonTrans3.GetPositionX() < 3.0f && playerTrans.GetPositionX() - buttonTrans3.GetPositionX() > -3.0f
		&& playerTrans.GetPositionZ() - buttonTrans3.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans3.GetPositionZ() > -3.0f)
	{
		button3Watch.Poll(window);
	}

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
			buttonEnt2.Get<MorphRenderer>().Render(camera, transformButton2, LightSpaceViewProjection);
			buttonEnt3.Get<MorphRenderer>().Render(camera, transformButton3, LightSpaceViewProjection);
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
			optionMat.Albedo->Bind(1);

			if (isPaused)
			{
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
			shadowBuffer->UnbindTexture(30);

			shader->Bind();

			//Wires
			shader->SetUniform("s_Diffuse", 0);

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

			if (wireEnt8.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(0);
				wireEnt8.Get<MeshRenderer>().Render(camera, transformWire3, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt8.Get<MeshRenderer>().Render(camera, transformWire3, LightSpaceViewProjection);
			}

			if (wireEnt9.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(0);
				wireEnt9.Get<MeshRenderer>().Render(camera, transformWire3, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt9.Get<MeshRenderer>().Render(camera, transformWire3, LightSpaceViewProjection);
			}
			//Tesla Coil
			shader->SetUniform("s_Diffuse", 1);
			if (!doorEnt.Get<Door>().GetOpen())
			{
				coilMatOff.Albedo->Bind(1);
				coilEnt.Get<MeshRenderer>().Render(camera, transformCoil, LightSpaceViewProjection);
			}
			else
			{
				coilMatOn.Albedo->Bind(1);
				coilEnt.Get<MeshRenderer>().Render(camera, transformCoil, LightSpaceViewProjection);
			}

			//Panels
			shader->SetUniform("s_Diffuse", 2);
			panelMat.Albedo->Bind(2);
			panelEnt.Get<MeshRenderer>().Render(camera, transformPanel, LightSpaceViewProjection);
			panelEnt2.Get<MeshRenderer>().Render(camera, transformPanel2, LightSpaceViewProjection);

			//Walls
			shader->SetUniform("s_Diffuse", 3);
			labWallMat.Albedo->Bind(3);
			leftEnt.Get<MeshRenderer>().Render(camera, transformLeft, LightSpaceViewProjection);
			rightEnt.Get<MeshRenderer>().Render(camera, transformRight, LightSpaceViewProjection);
			backEnt.Get<MeshRenderer>().Render(camera, transformBack, LightSpaceViewProjection);
			
			//Column Pipes
			shader->SetUniform("s_Diffuse", 4);
			columnPipeMat.Albedo->Bind(4);
			columnPipeEnt.Get<MeshRenderer>().Render(camera, transformColPipe, LightSpaceViewProjection);
			columnPipeEnt2.Get<MeshRenderer>().Render(camera, transformColPipe2, LightSpaceViewProjection);

			//Shelf Pipes
			shader->SetUniform("s_Diffuse", 5);
			shelfPipeMat.Albedo->Bind(5);
			shelfPipeEnt.Get<MeshRenderer>().Render(camera, transformShelfPipe, LightSpaceViewProjection);
			shelfPipeEnt2.Get<MeshRenderer>().Render(camera, transformShelfPipe2, LightSpaceViewProjection);

			//Vents
			shader->SetUniform("s_Diffuse", 6);
			ventMat.Albedo->Bind(6);
			ventEnt.Get<MeshRenderer>().Render(camera, transformVent, LightSpaceViewProjection);
			ventEnt2.Get<MeshRenderer>().Render(camera, transformVent2, LightSpaceViewProjection);
			ventEnt3.Get<MeshRenderer>().Render(camera, transformVent3, LightSpaceViewProjection);

			//Gates
			//And-Gate
			shader->SetUniform("s_Diffuse", 7);
			andMat.Albedo->Bind(7);
			andEnt.Get<MeshRenderer>().Render(camera, transformGate, LightSpaceViewProjection);

			//Or-Gate
			shader->SetUniform("s_Diffuse", 8);
			orMat.Albedo->Bind(8);
			orEnt.Get<MeshRenderer>().Render(camera, transformGate2, LightSpaceViewProjection);
			orEnt2.Get<MeshRenderer>().Render(camera, transformGate3, LightSpaceViewProjection);

			//Not-Gate
			shader->SetUniform("s_Diffuse", 9);
			notMat.Albedo->Bind(9);
			notEnt.Get<MeshRenderer>().Render(camera, transformNot, LightSpaceViewProjection);
			notEnt2.Get<MeshRenderer>().Render(camera, transformNot2, LightSpaceViewProjection);
			notEnt3.Get<MeshRenderer>().Render(camera, transformNot3, LightSpaceViewProjection);
			notEnt4.Get<MeshRenderer>().Render(camera, transformNot4, LightSpaceViewProjection);

			//Boxes
			shader->SetUniform("s_Diffuse", 10);
			boxMat.Albedo->Bind(10);
			boxEnt.Get<MeshRenderer>().Render(camera, transformBox, LightSpaceViewProjection);
			boxEnt2.Get<MeshRenderer>().Render(camera, transformBox2, LightSpaceViewProjection);
			boxEnt3.Get<MeshRenderer>().Render(camera, transformBox3, LightSpaceViewProjection);
			boxEnt4.Get<MeshRenderer>().Render(camera, transformBox4, LightSpaceViewProjection);
			
			//Floor
			shader->SetUniform("s_Diffuse", 11);
			labFloorMat.Albedo->Bind(11);
			floorEnt.Get<MeshRenderer>().Render(camera, transformGround, LightSpaceViewProjection);
			shadowBuffer->UnbindTexture(30);

			untexturedShader->Bind();
			shadowBuffer->BindDepthAsTexture(30);

			if ((playerTrans.GetPositionX() - buttonTrans.GetPositionX() < 3.0f
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
					&& playerTrans.GetPositionZ() - buttonTrans3.GetPositionZ() > -3.0f))
			{
				if (!tabletOpen)
					tutEnt.Get<MeshRenderer>().Render(orthoCam, transformTut, LightSpaceViewProjection);
				else
				{

				}
			}
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

			animShader->SetUniform("s_Diffuse", 1);
			clearMat.Albedo->Bind(1);
			doorEnt.Get<MorphRenderer>().Render(camera, transformDoor, LightSpaceViewProjection);
			clearMat.Albedo->Unbind(1);

			animShader->SetUniform("s_Diffuse", 2);
			clearMat.Albedo->Bind(2);
			buttonEnt.Get<MorphRenderer>().Render(camera, transformButton, LightSpaceViewProjection);
			buttonEnt2.Get<MorphRenderer>().Render(camera, transformButton2, LightSpaceViewProjection);
			buttonEnt3.Get<MorphRenderer>().Render(camera, transformButton3, LightSpaceViewProjection);

			untexturedShader->Bind();
			floorEnt.Get<MeshRenderer>().Render(camera, transformGround, LightSpaceViewProjection);
			leftEnt.Get<MeshRenderer>().Render(camera, transformLeft, LightSpaceViewProjection);
			rightEnt.Get<MeshRenderer>().Render(camera, transformRight, LightSpaceViewProjection);
			backEnt.Get<MeshRenderer>().Render(camera, transformBack, LightSpaceViewProjection);
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
			wireEnt.Get<MeshRenderer>().Render(camera, transformWire, LightSpaceViewProjection);
			wireEnt2.Get<MeshRenderer>().Render(camera, transformWire2, LightSpaceViewProjection);
			wireEnt3.Get<MeshRenderer>().Render(camera, transformWire3, LightSpaceViewProjection);
			wireEnt4.Get<MeshRenderer>().Render(camera, transformWire4, LightSpaceViewProjection);
			wireEnt5.Get<MeshRenderer>().Render(camera, transformWire5, LightSpaceViewProjection);
			wireEnt6.Get<MeshRenderer>().Render(camera, transformWire6, LightSpaceViewProjection);
			wireEnt7.Get<MeshRenderer>().Render(camera, transformWire7, LightSpaceViewProjection);
			wireEnt8.Get<MeshRenderer>().Render(camera, transformWire8, LightSpaceViewProjection);
			wireEnt9.Get<MeshRenderer>().Render(camera, transformWire9, LightSpaceViewProjection);
			coilEnt.Get<MeshRenderer>().Render(camera, transformCoil, LightSpaceViewProjection);
			panelEnt.Get<MeshRenderer>().Render(camera, transformPanel, LightSpaceViewProjection);
			panelEnt2.Get<MeshRenderer>().Render(camera, transformPanel2, LightSpaceViewProjection);
			columnPipeEnt.Get<MeshRenderer>().Render(camera, transformColPipe, LightSpaceViewProjection);
			columnPipeEnt2.Get<MeshRenderer>().Render(camera, transformColPipe2, LightSpaceViewProjection);
			shelfPipeEnt.Get<MeshRenderer>().Render(camera, transformShelfPipe, LightSpaceViewProjection);
			shelfPipeEnt2.Get<MeshRenderer>().Render(camera, transformShelfPipe2, LightSpaceViewProjection);
			ventEnt.Get<MeshRenderer>().Render(camera, transformVent, LightSpaceViewProjection);
			ventEnt2.Get<MeshRenderer>().Render(camera, transformVent2, LightSpaceViewProjection);
			ventEnt3.Get<MeshRenderer>().Render(camera, transformVent3, LightSpaceViewProjection);
			andEnt.Get<MeshRenderer>().Render(camera, transformGate, LightSpaceViewProjection);
			orEnt.Get<MeshRenderer>().Render(camera, transformGate2, LightSpaceViewProjection);
			orEnt2.Get<MeshRenderer>().Render(camera, transformGate3, LightSpaceViewProjection);
			notEnt.Get<MeshRenderer>().Render(camera, transformNot, LightSpaceViewProjection);
			notEnt2.Get<MeshRenderer>().Render(camera, transformNot2, LightSpaceViewProjection);
			notEnt3.Get<MeshRenderer>().Render(camera, transformNot3, LightSpaceViewProjection);
			notEnt4.Get<MeshRenderer>().Render(camera, transformNot4, LightSpaceViewProjection);
			boxEnt.Get<MeshRenderer>().Render(camera, transformBox, LightSpaceViewProjection);
			boxEnt2.Get<MeshRenderer>().Render(camera, transformBox2, LightSpaceViewProjection);
			boxEnt3.Get<MeshRenderer>().Render(camera, transformBox3, LightSpaceViewProjection);
			boxEnt4.Get<MeshRenderer>().Render(camera, transformBox4, LightSpaceViewProjection);
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
		completeEnt.Get<MeshRenderer>().Render(orthoCam, transformComplete);

		shadowBuffer->UnbindTexture(30);
	}
#pragma endregion

	basicEffect->UnbindBuffer();

	effects[activeEffect]->ApplyEffect(basicEffect);

	effects[activeEffect]->DrawToScreen();

	//Door Logic
	if (doorEnt.Get<Door>().GetOpen() && doorOpenApplied)
		doorEnt.Get<MorphAnimation>().Update(dt);
	if (!doorEnt.Get<Door>().GetOpen() && doorClosingApplied)
		doorEnt.Get<MorphAnimation>().Update(dt);

	backEnt.Get<AABB>().Update();
	leftEnt.Get<AABB>().Update();
	rightEnt.Get<AABB>().Update();
	doorEnt.Get<AABB>().Update();
	andEnt.Get<AABB>().Update();
	orEnt.Get<AABB>().Update();
	orEnt2.Get<AABB>().Update();
	notEnt.Get<AABB>().Update();
	notEnt2.Get<AABB>().Update();
	notEnt3.Get<AABB>().Update();
	notEnt4.Get<AABB>().Update();
	boxEnt.Get<AABB>().Update();
	boxEnt2.Get<AABB>().Update();
	boxEnt3.Get<AABB>().Update();
	boxEnt4.Get<AABB>().Update();
	coilEnt.Get<AABB>().Update();
	buttonEnt.Get<AABB>().Update();
	buttonEnt2.Get<AABB>().Update();
	buttonEnt3.Get<AABB>().Update();
	columnPipeEnt.Get<AABB>().Update();
	columnPipeEnt2.Get<AABB>().Update();
	buttonEnt.Get<Lever>().Update();
	buttonEnt2.Get<Lever>().Update();
	buttonEnt3.Get<Lever>().Update();
	//wireEnt.Get<Wire>().Update();
	//wireEnt2.Get<Wire>().Update();
	//wireEnt3.Get<Wire>().Update();
	//wireEnt4.Get<Wire>().Update();
	//wireEnt5.Get<Wire>().Update();
	//wireEnt6.Get<Wire>().Update();
	//wireEnt7.Get<Wire>().Update();
	//wireEnt8.Get<Wire>().Update();
	//wireEnt9.Get<Wire>().Update();
	//andEnt.Get<AndGate>().Update();
	//orEnt.Get<OrGate>().Update();
	//orEnt2.Get<OrGate>().Update();
	//notEnt.Get<NotGate>().Update();
	//notEnt2.Get<NotGate>().Update();
	//notEnt3.Get<NotGate>().Update();
	//notEnt4.Get<NotGate>().Update();
}

void Level6::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}