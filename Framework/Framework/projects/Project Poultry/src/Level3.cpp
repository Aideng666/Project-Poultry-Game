#include "Level3.h"
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


Level3::Level3(std::string sceneName, GLFWwindow* wind)
	: Scene(sceneName, wind)
{
#pragma region Entities
	mainPlayer = Entity::Create();
	floorEnt = Entity::Create();
	leftEnt = Entity::Create();
	rightEnt = Entity::Create();
	backEnt = Entity::Create();
	optionEnt = Entity::Create();
	exitEnt = Entity::Create();
	retryEnt = Entity::Create();
	buttonEnt = Entity::Create();
	buttonEnt2 = Entity::Create();
	buttonEnt3 = Entity::Create();
	doorEnt = Entity::Create();
	andEnt = Entity::Create();
	andEnt2 = Entity::Create();
	andEnt3 = Entity::Create();
	notEnt = Entity::Create();
	wireEnt = Entity::Create();
	wireEnt2 = Entity::Create();
	wireEnt3 = Entity::Create();
	wireEnt4 = Entity::Create();
	wireEnt5 = Entity::Create();
	wireEnt6 = Entity::Create();
	wireEnt7 = Entity::Create();
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
	pipeCEnt = Entity::Create();
	pipeC2Ent = Entity::Create();
	pipeC3Ent = Entity::Create();
	pipeSEnt = Entity::Create();
	tabletEnt = Entity::Create();
	tabletScreenEnt = Entity::Create();
	pauseEnt = Entity::Create();
	tutEnt = Entity::Create();
	optionsMenuEnt = Entity::Create();

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
#pragma endregion


	InitMeshes();
}

void Level3::InitScene()
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
	//Initializes the Luts
	InitLuts();

#pragma region Transforms
	//Player transforms
	auto& playerTrans = mainPlayer.Add<Transform>();
	playerTrans.SetPosition(glm::vec3(0.0f, 1.0f, 32.0f));
	playerTrans.SetRotationY(180.0f);

	//Floor transform
	auto& groundTrans = floorEnt.Add<Transform>();
	groundTrans.SetPositionY(1.0f);

	//Wall transforms
	auto& leftTrans = leftEnt.Add<Transform>();
	leftTrans.SetScale(glm::vec3(2.0f, 2.0f, 1.0f));
	auto& rightTrans = rightEnt.Add<Transform>();
	rightTrans.SetScale(glm::vec3(2.0f, 2.0f, 1.0f));
	auto& backTrans = backEnt.Add<Transform>();
	backTrans.SetScale(glm::vec3(1.0f, 2.0f, 1.0f));

	//Door transform
	auto& doorTrans = doorEnt.Add<Transform>();
	doorTrans.SetPosition(glm::vec3(0.0f, -1.0f, -36.0f));
	doorTrans.SetScale(glm::vec3(1.5f));

	//Wire transforms
	auto& wireTrans = wireEnt.Add<Transform>();
	wireTrans.SetPosition(glm::vec3(-1.f, 1.0f, 1.2f));
	
	auto& wireTrans2 = wireEnt2.Add<Transform>();
	wireTrans2.SetPosition(glm::vec3(-1.f, 1.0f, 2.3f));
	
	auto& wireTrans3 = wireEnt3.Add<Transform>();
	wireTrans3.SetPosition(glm::vec3(-1.1f, 1.0f, 1.3f));
	
	auto& wireTrans4 = wireEnt4.Add<Transform>();
	wireTrans4.SetPosition(glm::vec3(-1.f, 1.0f, 1.1f));
	
	auto& wireTrans5 = wireEnt5.Add<Transform>();
	wireTrans5.SetPosition(glm::vec3(-1.f, 1.0f, 1.0f));
	
	auto& wireTrans6 = wireEnt6.Add<Transform>();
	wireTrans6.SetPosition(glm::vec3(-1.f, 1.0f, 1.0f));
	
	auto& wireTrans7 = wireEnt7.Add<Transform>();
	wireTrans7.SetPosition(glm::vec3(-1.f, 1.0f, 0.0f));

	//Gate transforms
	//And Gate
	auto& gateTrans = andEnt.Add<Transform>();
	gateTrans.SetPosition(glm::vec3(-10.4f, 1.0f, 3.6f));
	gateTrans.SetRotationY(-90.0f);
	gateTrans.SetScale(glm::vec3(2.0f));
	
	auto& gateTrans2 = andEnt2.Add<Transform>();
	gateTrans2.SetPosition(glm::vec3(10.9f, 1.0f, 3.6f));
	gateTrans2.SetRotationY(-90.0f);
	gateTrans2.SetScale(glm::vec3(2.0f));
	
	auto& gateTrans3 = andEnt3.Add<Transform>();
	gateTrans3.SetPosition(glm::vec3(0.3f, 1.0f, -5.5f));
	gateTrans3.SetRotationY(-90.0f);
	gateTrans3.SetScale(glm::vec3(2.0f));
	
	//Not Gate
	auto& notTrans = notEnt.Add<Transform>();
	notTrans.SetPosition(glm::vec3(0.0f, 0.5f, 13.0f));
	notTrans.SetRotationY(-90.0f);
	notTrans.SetScale(glm::vec3(2.0f));

	//Button transforms
	auto& buttonTrans = buttonEnt.Add<Transform>();
	buttonTrans.SetPosition(glm::vec3(-12.5f, -1.0f, 27.f));

	auto& buttonTrans2 = buttonEnt2.Add<Transform>();
	buttonTrans2.SetPosition(glm::vec3(0.1f, -1.0f, 28.f));

	auto& buttonTrans3 = buttonEnt3.Add<Transform>();
	buttonTrans3.SetPosition(glm::vec3(12.7f, -1.0f, 27.f));

	//Coil transform
	auto& coilTrans = coilEnt.Add<Transform>();
	coilTrans.SetPosition(glm::vec3(-17.0f, 1.0f, -31.f));
	coilTrans.SetScale(glm::vec3(3.0f));
	coilTrans.SetRotationY(180.0f);

	//Box transforms
	auto& boxTrans = boxEnt.Add<Transform>();
	boxTrans.SetPosition(glm::vec3(22.f, 4.5f, -33.f));

	auto& boxTrans2 = boxEnt2.Add<Transform>();
	boxTrans2.SetPosition(glm::vec3(34.f, 4.5f, 0.f));

	auto& boxTrans3 = boxEnt3.Add<Transform>();
	boxTrans3.SetPosition(glm::vec3(-35.f, 4.5f, 10.f));
	boxTrans3.SetRotationY(90.f);

	auto& boxTrans4 = boxEnt4.Add<Transform>();
	boxTrans4.SetPosition(glm::vec3(-35.f, 4.5f, 20.f));
	boxTrans4.SetRotationY(90.f);

	//Vent transforms
	auto& ventTrans = ventEnt.Add<Transform>();
	ventTrans.SetPosition(glm::vec3(-38.3f, 15.f, -22.f));
	ventTrans.SetScale(glm::vec3(0.8f));
	ventTrans.SetRotationY(180.f);

	auto& ventTrans2 = ventEnt2.Add<Transform>();
	ventTrans2.SetPosition(glm::vec3(-38.3f, 15.f, 22.f));
	ventTrans2.SetScale(glm::vec3(0.8f));
	ventTrans2.SetRotationY(180.f);

	//Panel transforms
	auto& panelTrans = panelEnt.Add<Transform>();
	panelTrans.SetPosition(glm::vec3(-30.f, 7.0f, -39.f));
	panelTrans.SetScale(glm::vec3(2.0f));
	panelTrans.SetRotationY(-90.0f);

	auto& panelTrans2 = panelEnt2.Add<Transform>();
	panelTrans2.SetPosition(glm::vec3(39.f, 7.0f, 18.f));
	panelTrans2.SetScale(glm::vec3(2.0f));
	panelTrans2.SetRotationY(180.0f);

	auto& panelTrans3 = panelEnt3.Add<Transform>();
	panelTrans3.SetPosition(glm::vec3(39.f, 7.0f, 22.f));
	panelTrans3.SetScale(glm::vec3(2.0f));
	panelTrans3.SetRotationY(180.0f);

	//Pipe transforms
	auto& pipeTrans = pipeCEnt.Add<Transform>();
	pipeTrans.SetPosition(glm::vec3(12.f, 1.f, -33.f));
	pipeTrans.SetRotationY(90.0f);

	auto& pipeTrans2 = pipeC2Ent.Add<Transform>();
	pipeTrans2.SetPosition(glm::vec3(22.2f, 12.5f, -33.f));
	pipeTrans2.SetRotationZ(-90.0f);
	
	auto& pipeTrans3 = pipeC3Ent.Add<Transform>();
	pipeTrans3.SetPosition(glm::vec3(34.f, 1.f, 23.f));
	pipeTrans3.SetRotationY(180.0f);

	auto& pipeTrans4 = pipeSEnt.Add<Transform>();
	pipeTrans4.SetPosition(glm::vec3(34.f, 12.5f, -8.f));

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
	//retryTrans.SetRotationY(96.0f);

	auto& exitTrans = exitEnt.Add<Transform>();
	exitTrans.SetPosition(glm::vec3(5.0f, 2.0f, 0.0f));
	exitTrans.SetScale(glm::vec3(1.5f));
	//exitTrans.SetRotationY(96.0f);

	//Tablet Stuff
	auto& tabletTrans = tabletEnt.Add<Transform>();
	tabletTrans.SetPosition(glm::vec3(8.0f, 5.0f, 13.0f));
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
#pragma endregion

	//AABB
	auto& leftCol = leftEnt.Add<AABB>(leftEnt, mainPlayer);
	auto& rightCol = rightEnt.Add<AABB>(rightEnt, mainPlayer);
	auto& backCol = backEnt.Add<AABB>(backEnt, mainPlayer);
	auto& gateCol = andEnt.Add<AABB>(andEnt, mainPlayer, 5.0f, 3.0f);
	gateCol.SetIsAmbient(true);
	auto& gateCol2 = andEnt2.Add<AABB>(andEnt2, mainPlayer, 5.0f, 3.0f);
	gateCol2.SetIsAmbient(true);
	auto& gateCol3 = andEnt3.Add<AABB>(andEnt3, mainPlayer, 5.0f, 3.0f);
	gateCol3.SetIsAmbient(true);
	auto& gateCol4 = notEnt.Add<AABB>(notEnt, mainPlayer, 3.0f, 3.0f);
	gateCol4.SetIsAmbient(true);
	auto& coilCol = coilEnt.Add<AABB>(coilEnt, mainPlayer, 4.0f, 4.0f);
	coilCol.SetIsAmbient(true);
	auto& boxCol = boxEnt.Add<AABB>(boxEnt, mainPlayer, 5.0f, 5.0f);
	boxCol.SetIsAmbient(true);
	auto& boxCol2 = boxEnt2.Add<AABB>(boxEnt2, mainPlayer, 5.0f, 5.0f);
	boxCol2.SetIsAmbient(true);
	auto& boxCol3 = boxEnt3.Add<AABB>(boxEnt3, mainPlayer, 5.0f, 5.0f);
	boxCol3.SetIsAmbient(true);
	auto& boxCol4 = boxEnt4.Add<AABB>(boxEnt4, mainPlayer, 5.0f, 5.0f);
	boxCol4.SetIsAmbient(true);
	auto& pipeCol = pipeCEnt.Add<AABB>(pipeCEnt, mainPlayer, 2.5f, 2.5f);
	pipeCol.SetIsAmbient(true);
	auto& pipeCol2 = pipeC2Ent.Add<AABB>(pipeC2Ent, mainPlayer, 2.5f, 2.5f);
	pipeCol2.SetIsAmbient(true);
	auto& pipeCol3 = pipeC3Ent.Add<AABB>(pipeC3Ent, mainPlayer, 2.5f, 2.5f);
	pipeCol3.SetIsAmbient(true);
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
	auto& wire4 = wireEnt4.Add<Wire>(notEnt);
	auto& wire5 = wireEnt5.Add<Wire>(andEnt);
	auto& wire6 = wireEnt6.Add<Wire>(andEnt2);
	auto& wire7 = wireEnt7.Add<Wire>(andEnt3);

	//Gates
	auto& andGate = andEnt.Add<AndGate>(wireEnt, wireEnt4, wireEnt5);
	auto& andGate2 = andEnt2.Add<AndGate>(wireEnt4, wireEnt3, wireEnt6);
	auto& andGate3 = andEnt3.Add<AndGate>(wireEnt5, wireEnt6, doorEnt);
	auto& notGate = notEnt.Add<NotGate>(wireEnt2, wireEnt4);

	//Door
	auto& door = doorEnt.Add<Door>();
	door.SetOpen(false);

	InitAnims();

#pragma region Mesh Loading
	auto& playerMesh = mainPlayer.Add<MorphRenderer>(mainPlayer, *idle1, animShader);
	auto& floorMesh = floorEnt.Add<MeshRenderer>(floorEnt, *floorL3, shader);
	auto& leftMesh = leftEnt.Add<MeshRenderer>(leftEnt, *leftWall, shader);
	auto& rightMesh = rightEnt.Add<MeshRenderer>(rightEnt, *rightWall, shader);
	auto& backMesh = backEnt.Add<MeshRenderer>(backEnt, *backWall, shader);
	auto& doorMesh = doorEnt.Add<MorphRenderer>(doorEnt, *door1, animShader);
	auto& buttonMesh = buttonEnt.Add<MorphRenderer>(buttonEnt, *buttonM, animShader);
	auto& buttonMesh2 = buttonEnt2.Add<MorphRenderer>(buttonEnt2, *buttonM, animShader);
	auto& buttonMesh3 = buttonEnt3.Add<MorphRenderer>(buttonEnt3, *buttonM, animShader);
	auto& gateMesh = andEnt.Add<MeshRenderer>(andEnt, *and, shader);
	auto& gateMesh2 = andEnt2.Add<MeshRenderer>(andEnt2, *and, shader);
	auto& gateMesh3 = andEnt3.Add<MeshRenderer>(andEnt3, *and, shader);
	auto& notMesh = notEnt.Add<MeshRenderer>(notEnt, *not, shader);
	auto& wireMesh = wireEnt.Add<MeshRenderer>(wireEnt, *wireM1L3, shader);
	auto& wireMesh2 = wireEnt2.Add<MeshRenderer>(wireEnt2, *wireM2L3, shader);
	auto& wireMesh3 = wireEnt3.Add<MeshRenderer>(wireEnt3, *wireM3L3, shader);
	auto& wireMesh4 = wireEnt4.Add<MeshRenderer>(wireEnt4, *wireM4L3, shader);
	auto& wireMesh5 = wireEnt5.Add<MeshRenderer>(wireEnt5, *wireM5L3, shader);
	auto& wireMesh6 = wireEnt6.Add<MeshRenderer>(wireEnt6, *wireM6L3, shader);
	auto& wireMesh7 = wireEnt7.Add<MeshRenderer>(wireEnt7, *wireM7L3, shader);
	auto& coilMesh = coilEnt.Add<MeshRenderer>(coilEnt, *coil, shader);
	auto& completeMesh = completeEnt.Add<MeshRenderer>(completeEnt, *screen, shader);
	auto& pauseMesh = pauseEnt.Add<MeshRenderer>(pauseEnt, *screen, pauseShader);
	auto& optionMesh = optionEnt.Add<MeshRenderer>(optionEnt, *options, pauseShader);
	auto& retryMesh = retryEnt.Add<MeshRenderer>(retryEnt, *retry, pauseShader);
	auto& exitMesh = exitEnt.Add<MeshRenderer>(exitEnt, *exit, pauseShader);
	auto& boxMesh = boxEnt.Add<MeshRenderer>(boxEnt, *boxM, shader);
	auto& boxMesh2 = boxEnt2.Add<MeshRenderer>(boxEnt2, *boxM, shader);
	auto& boxMesh3 = boxEnt3.Add<MeshRenderer>(boxEnt3, *boxM, shader);
	auto& boxMesh4 = boxEnt4.Add<MeshRenderer>(boxEnt4, *boxM, shader);
	auto& panelMesh = panelEnt.Add<MeshRenderer>(panelEnt, *panel, shader);
	auto& panelMesh2 = panelEnt2.Add<MeshRenderer>(panelEnt2, *panel, shader);
	auto& panelMesh3 = panelEnt3.Add<MeshRenderer>(panelEnt3, *panel, shader);
	auto& vent = ventEnt.Add<MeshRenderer>(ventEnt, *ventB, shader);
	auto& vent2 = ventEnt2.Add<MeshRenderer>(ventEnt2, *ventB, shader);
	auto& pipeCM = pipeCEnt.Add<MeshRenderer>(pipeCEnt, *pipeC, shader);
	auto& pipeCM2 = pipeC2Ent.Add<MeshRenderer>(pipeC2Ent, *pipeC, shader);
	auto& pipeCM3 = pipeC3Ent.Add<MeshRenderer>(pipeC3Ent, *pipeC, shader);
	auto& pipeSM = pipeSEnt.Add<MeshRenderer>(pipeSEnt, *pipeS, shader);
	auto& tabletScreenMesh = tabletScreenEnt.Add<MeshRenderer>(tabletScreenEnt, *screen, pauseShader);
	auto& tabletMesh = tabletEnt.Add<MeshRenderer>(tabletEnt, *tablet, rimLightShader);
	auto& tutMesh = tutEnt.Add<MeshRenderer>(tutEnt, *tut, untexturedShader);
	auto& optionsMenuMesh = optionsMenuEnt.Add<MeshRenderer>(optionsMenuEnt, *screen, pauseShader);
	auto& muteMesh = muteEnt.Add<MeshRenderer>(muteEnt, *optionsButton, pauseShader);
	auto& musicMesh = musicEnt.Add<MeshRenderer>(musicEnt, *optionsButton, pauseShader);
	auto& soundMesh = soundEnt.Add<MeshRenderer>(soundEnt, *optionsButton, pauseShader);
	auto& brightMesh = brightEnt.Add<MeshRenderer>(brightEnt, *optionsButton, pauseShader);
	auto& colorBlindMesh = colorBlindEnt.Add<MeshRenderer>(colorBlindEnt, *optionsButton, pauseShader);
	auto& controlsMesh = controlsEnt.Add<MeshRenderer>(controlsEnt, *optionsButton, pauseShader);

	entList.push_back(&mainPlayer);
	entList.push_back(&doorEnt);
	entList.push_back(&buttonEnt);
	entList.push_back(&buttonEnt2);
	entList.push_back(&buttonEnt3);
	entList.push_back(&floorEnt);
	entList.push_back(&leftEnt);
	entList.push_back(&rightEnt);
	entList.push_back(&notEnt);
	entList.push_back(&andEnt);
	entList.push_back(&andEnt2);
	entList.push_back(&andEnt3);
	entList.push_back(&wireEnt);
	entList.push_back(&wireEnt2);
	entList.push_back(&wireEnt3);
	entList.push_back(&wireEnt4);
	entList.push_back(&wireEnt5);
	entList.push_back(&wireEnt6);
	entList.push_back(&wireEnt7);
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
	entList.push_back(&pipeCEnt);
	entList.push_back(&pipeSEnt);
	entList.push_back(&pipeC2Ent);
	entList.push_back(&pipeC3Ent);
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

	//Interpolation Stuff
	points.push_back(glm::vec3(3.0f, 15.0f, 6.0f));
	points.push_back(glm::vec3(-3.0f, 15.0f, 6.0f));
	points.push_back(glm::vec3(-3.0f, 15.0f, 0.0f));
	points.push_back(glm::vec3(3.0f, 15.0f, 0.0f));
	
	segmentTime = 1.0f;
	
	if (points.size() > 0)
		currentPos = points[0];
	
	StartSegment(0);

	AudioEvent& music = AudioEngine::Instance().GetEvent("BG");
	music.Play();
}

void Level3::Update(float dt)
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

	if (points.size() >= 4)
	{
		t = glm::min(t + dt / segmentTime, 1.0f);
	
		int p1 = currentIndex;
	
		int p0 = currentIndex - 1;
	
		if (p0 < 0)
		{
			p0 = points.size() - 1;
		}
	
		int p2 = currentIndex + 1;
	
		if (p2 >= points.size())
			p2 = 0;
	
		int p3 = p2 + 1;
	
		if (p3 >= points.size())
			p3 = 0;
	
		currentPos = Catmull(points[p0], points[p1], points[p2], points[p3], t);
	
		if (t >= 1.0f)
			StartSegment(currentIndex + 1);
	}

	animShader->SetUniform("u_Position", currentPos);
	shader->SetUniform("u_Position", currentPos);
	pauseShader->SetUniform("u_Position", currentPos);
	untexturedShader->SetUniform("u_Position", currentPos);
	rimLightShader->SetUniform("u_Position", currentPos);

#pragma region Transforms
	auto& playerTrans = mainPlayer.Get<Transform>();
	auto& buttonTrans = buttonEnt.Get<Transform>();
	auto& buttonTrans2 = buttonEnt2.Get<Transform>();
	auto& buttonTrans3 = buttonEnt3.Get<Transform>();

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
	//camera.LookAt(glm::vec3(playerTrans.GetPositionX(), playerTrans.GetPositionY() + 5.0f, playerTrans.GetPositionZ()));

	
	//Get reference to the model matrix
	glm::mat4 transform = playerTrans.GetModelMatrix();
	glm::mat4 transformGround = floorEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformLeft = leftEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformRight = rightEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformBack = backEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformDoor = doorEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformButton = buttonTrans.GetModelMatrix();
	glm::mat4 transformButton2 = buttonTrans2.GetModelMatrix();
	glm::mat4 transformButton3 = buttonTrans3.GetModelMatrix();
	glm::mat4 transformGate = andEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformGate2 = andEnt2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformGate3 = andEnt3.Get<Transform>().GetModelMatrix();
	glm::mat4 transformNot = notEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire = wireEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire2 = wireEnt2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire3 = wireEnt3.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire4 = wireEnt4.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire5 = wireEnt5.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire6 = wireEnt6.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire7 = wireEnt7.Get<Transform>().GetModelMatrix();
	glm::mat4 transformCoil = coilEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformComplete = completeEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformOptions = optionEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformRetry = retryEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformExit = exitEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformTablet = tabletEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformTabletScreen = tabletScreenEnt.Get<Transform>().GetModelMatrix();
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
	glm::mat4 transformPipeC = pipeCEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformPipeC2 = pipeC2Ent.Get<Transform>().GetModelMatrix();
	glm::mat4 transformPipeC3 = pipeC3Ent.Get<Transform>().GetModelMatrix();
	glm::mat4 transformPipeS = pipeSEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformTut = tutEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformMute = muteEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformMusic = musicEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformSound = soundEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformBright = brightEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformColorBlind = colorBlindEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformControls = controlsEnt.Get<Transform>().GetModelMatrix();

	if (!buttonAnimOn && playerTrans.GetPositionX() - buttonTrans.GetPositionX() < 3.0f && playerTrans.GetPositionX() - buttonTrans.GetPositionX() > -3.0f
		&& playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() > -3.0f)
		button1Watch.Poll(window);
	
	if (!button2AnimOn && playerTrans.GetPositionX() - buttonTrans2.GetPositionX() < 3.0f && playerTrans.GetPositionX() - buttonTrans2.GetPositionX() > -3.0f
		&& playerTrans.GetPositionZ() - buttonTrans2.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans2.GetPositionZ() > -3.0f)
		button2Watch.Poll(window);
	
	if (!button3AnimOn && playerTrans.GetPositionX() - buttonTrans3.GetPositionX() < 3.0f && playerTrans.GetPositionX() - buttonTrans3.GetPositionX() > -3.0f
		&& playerTrans.GetPositionZ() - buttonTrans3.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans3.GetPositionZ() > -3.0f)
		button3Watch.Poll(window);

	if ((playerTrans.GetPositionX() > 5.0f && playerTrans.GetPositionX() < 11.0f
		&& playerTrans.GetPositionZ() > 10.0f && playerTrans.GetPositionZ() < 16.0f
		&& !tabletOpen) || tabletOpen)
		tabletWatch.Poll(window);

	if (!optionsOpen)
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
	if (!showLevelComplete && !isPaused && !tabletOpen)
	{
		isWalking = Input::MovePlayer(window, mainPlayer, camEnt, dt, camFar, camClose, camLeft, camRight, isArrow);

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
		//Input::MoveCamera(window, camEnt, dt);
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
		//Bind and render the player and door using the animation shader
		if (!showLevelComplete)
		{
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
			notTabletScreenMat.Albedo->Bind(4);

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

			//Buttons
			/*shader->SetUniform("s_Diffuse", 2);
			buttonMat.Albedo->Bind(2);
			buttonEnt.Get<MeshRenderer>().Render(camera, transformButton, LightSpaceViewProjection);
			buttonEnt2.Get<MeshRenderer>().Render(camera, transformButton2, LightSpaceViewProjection);
			buttonEnt3.Get<MeshRenderer>().Render(camera, transformButton3, LightSpaceViewProjection);*/

			//Gates
			//And-Gate
			shader->SetUniform("s_Diffuse", 3);
			andMat.Albedo->Bind(3);
			andEnt.Get<MeshRenderer>().Render(camera, transformGate, LightSpaceViewProjection);
			andEnt2.Get<MeshRenderer>().Render(camera, transformGate2, LightSpaceViewProjection);
			andEnt3.Get<MeshRenderer>().Render(camera, transformGate3, LightSpaceViewProjection);
			
			//Not-Gate
			shader->SetUniform("s_Diffuse", 4);
			notMat.Albedo->Bind(4);
			notEnt.Get<MeshRenderer>().Render(camera, transformNot, LightSpaceViewProjection);

			//Wires
			shader->SetUniform("s_Diffuse", 5);

			if (wireEnt.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(5);
				wireEnt.Get<MeshRenderer>().Render(camera, transformWire, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(5);
				wireEnt.Get<MeshRenderer>().Render(camera, transformWire, LightSpaceViewProjection);
			}

			if (wireEnt2.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(5);
				wireEnt2.Get<MeshRenderer>().Render(camera, transformWire2, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(5);
				wireEnt2.Get<MeshRenderer>().Render(camera, transformWire2, LightSpaceViewProjection);
			}

			if (wireEnt3.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(5);
				wireEnt3.Get<MeshRenderer>().Render(camera, transformWire3, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(5);
				wireEnt3.Get<MeshRenderer>().Render(camera, transformWire3, LightSpaceViewProjection);
			}

			if (wireEnt4.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(5);
				wireEnt4.Get<MeshRenderer>().Render(camera, transformWire4, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(5);
				wireEnt4.Get<MeshRenderer>().Render(camera, transformWire4, LightSpaceViewProjection);
			}

			if (wireEnt5.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(5);
				wireEnt5.Get<MeshRenderer>().Render(camera, transformWire5, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(5);
				wireEnt5.Get<MeshRenderer>().Render(camera, transformWire5, LightSpaceViewProjection);
			}

			if (wireEnt6.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(5);
				wireEnt6.Get<MeshRenderer>().Render(camera, transformWire6, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(5);
				wireEnt6.Get<MeshRenderer>().Render(camera, transformWire6, LightSpaceViewProjection);
			}

			if (wireEnt7.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(5);
				wireEnt7.Get<MeshRenderer>().Render(camera, transformWire7, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(5);
				wireEnt7.Get<MeshRenderer>().Render(camera, transformWire7, LightSpaceViewProjection);
			}

			//Tesla Coil
			shader->SetUniform("s_Diffuse", 6);

			if (!doorEnt.Get<Door>().GetOpen())
			{
				coilMatOff.Albedo->Bind(6);
				coilEnt.Get<MeshRenderer>().Render(camera, transformCoil, LightSpaceViewProjection);
			}
			else
			{
				coilMatOn.Albedo->Bind(6);
				coilEnt.Get<MeshRenderer>().Render(camera, transformCoil, LightSpaceViewProjection);
			}

			//Boxes
			shader->SetUniform("s_Diffuse", 7);
			boxMat.Albedo->Bind(7);
			boxEnt.Get<MeshRenderer>().Render(camera, transformBox, LightSpaceViewProjection);
			boxEnt2.Get<MeshRenderer>().Render(camera, transformBox2, LightSpaceViewProjection);
			boxEnt3.Get<MeshRenderer>().Render(camera, transformBox3, LightSpaceViewProjection);
			boxEnt4.Get<MeshRenderer>().Render(camera, transformBox4, LightSpaceViewProjection);
			
			//Vents
			shader->SetUniform("s_Diffuse", 8);
			ventMat.Albedo->Bind(8);
			ventEnt.Get<MeshRenderer>().Render(camera, transformVent, LightSpaceViewProjection);
			ventEnt2.Get<MeshRenderer>().Render(camera, transformVent2, LightSpaceViewProjection);

			//Panels
			shader->SetUniform("s_Diffuse", 9);
			panelMat.Albedo->Bind(9);
			panelEnt.Get<MeshRenderer>().Render(camera, transformPanel, LightSpaceViewProjection);
			panelEnt2.Get<MeshRenderer>().Render(camera, transformPanel2, LightSpaceViewProjection);
			panelEnt3.Get<MeshRenderer>().Render(camera, transformPanel3, LightSpaceViewProjection);

			//Pipes
			//Curved Pipe
			shader->SetUniform("s_Diffuse", 10);
			curvedPipeMat.Albedo->Bind(10);
			pipeCEnt.Get<MeshRenderer>().Render(camera, transformPipeC, LightSpaceViewProjection);
			pipeC2Ent.Get<MeshRenderer>().Render(camera, transformPipeC2, LightSpaceViewProjection);
			pipeC3Ent.Get<MeshRenderer>().Render(camera, transformPipeC3, LightSpaceViewProjection);

			//Straight Pipe
			shader->SetUniform("s_Diffuse", 11);
			straightPipeMat.Albedo->Bind(11);
			pipeSEnt.Get<MeshRenderer>().Render(camera, transformPipeS, LightSpaceViewProjection);

			shadowBuffer->UnbindTexture(30);

			//Bind and render the objects with no textures
			untexturedShader->Bind();
			shadowBuffer->BindDepthAsTexture(30);

			if (playerTrans.GetPositionX() > 5.0f && playerTrans.GetPositionX() < 11.0f
					&& playerTrans.GetPositionZ() > 10.0f && playerTrans.GetPositionZ() < 16.0f
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
					&& playerTrans.GetPositionZ() - buttonTrans3.GetPositionZ() > -3.0f))
			{
				if (!tabletOpen && !optionsOpen && !isPaused)
					tutEnt.Get<MeshRenderer>().Render(orthoCam, transformTut);
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

			animShader->SetUniform("s_Diffuse", 1);
			clearMat.Albedo->Bind(1);
			doorEnt.Get<MorphRenderer>().Render(camera, transformDoor, LightSpaceViewProjection);
			buttonEnt.Get<MorphRenderer>().Render(camera, transformButton, LightSpaceViewProjection);
			buttonEnt2.Get<MorphRenderer>().Render(camera, transformButton2, LightSpaceViewProjection);
			buttonEnt3.Get<MorphRenderer>().Render(camera, transformButton3, LightSpaceViewProjection);
			clearMat.Albedo->Unbind(1);
			shadowBuffer->UnbindTexture(30);

			pauseShader->Bind();
			pauseShader->SetUniform("s_Diffuse", 0);
			pauseMat.Albedo->Bind(0);
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
			floorEnt.Get<MeshRenderer>().Render(camera, transformGround, LightSpaceViewProjection);
			leftEnt.Get<MeshRenderer>().Render(camera, transformLeft, LightSpaceViewProjection);
			rightEnt.Get<MeshRenderer>().Render(camera, transformRight, LightSpaceViewProjection);
			backEnt.Get<MeshRenderer>().Render(camera, transformBack, LightSpaceViewProjection);
			andEnt.Get<MeshRenderer>().Render(camera, transformGate, LightSpaceViewProjection);
			andEnt2.Get<MeshRenderer>().Render(camera, transformGate2, LightSpaceViewProjection);
			andEnt3.Get<MeshRenderer>().Render(camera, transformGate3, LightSpaceViewProjection);
			notEnt.Get<MeshRenderer>().Render(camera, transformNot, LightSpaceViewProjection);
			wireEnt.Get<MeshRenderer>().Render(camera, transformWire, LightSpaceViewProjection);
			wireEnt2.Get<MeshRenderer>().Render(camera, transformWire2, LightSpaceViewProjection);
			wireEnt3.Get<MeshRenderer>().Render(camera, transformWire3, LightSpaceViewProjection);
			wireEnt4.Get<MeshRenderer>().Render(camera, transformWire4, LightSpaceViewProjection);
			wireEnt5.Get<MeshRenderer>().Render(camera, transformWire5, LightSpaceViewProjection);
			wireEnt6.Get<MeshRenderer>().Render(camera, transformWire6, LightSpaceViewProjection);
			wireEnt7.Get<MeshRenderer>().Render(camera, transformWire7, LightSpaceViewProjection);
			coilEnt.Get<MeshRenderer>().Render(camera, transformCoil, LightSpaceViewProjection);
			boxEnt.Get<MeshRenderer>().Render(camera, transformBox, LightSpaceViewProjection);
			boxEnt2.Get<MeshRenderer>().Render(camera, transformBox2, LightSpaceViewProjection);
			boxEnt3.Get<MeshRenderer>().Render(camera, transformBox3, LightSpaceViewProjection);
			boxEnt4.Get<MeshRenderer>().Render(camera, transformBox4, LightSpaceViewProjection);
			ventEnt.Get<MeshRenderer>().Render(camera, transformVent, LightSpaceViewProjection);
			ventEnt2.Get<MeshRenderer>().Render(camera, transformVent2, LightSpaceViewProjection);
			panelEnt.Get<MeshRenderer>().Render(camera, transformPanel, LightSpaceViewProjection);
			panelEnt2.Get<MeshRenderer>().Render(camera, transformPanel2, LightSpaceViewProjection);
			panelEnt3.Get<MeshRenderer>().Render(camera, transformPanel3, LightSpaceViewProjection);
			pipeCEnt.Get<MeshRenderer>().Render(camera, transformPipeC, LightSpaceViewProjection);
			pipeC2Ent.Get<MeshRenderer>().Render(camera, transformPipeC2, LightSpaceViewProjection);
			pipeC3Ent.Get<MeshRenderer>().Render(camera, transformPipeC3, LightSpaceViewProjection);
			pipeSEnt.Get<MeshRenderer>().Render(camera, transformPipeS, LightSpaceViewProjection);
			tabletEnt.Get<MeshRenderer>().Render(camera, transformTablet, LightSpaceViewProjection);

			shadowBuffer->UnbindTexture(30);

			rimLightShader->Bind();
			rimLightShader->SetUniform("s_Diffuse", 1);
			clearMat.Albedo->Bind(1);
			shadowBuffer->BindDepthAsTexture(30);
			tabletEnt.Get<MeshRenderer>().Render(camera, transformTablet, LightSpaceViewProjection);
			shadowBuffer->UnbindTexture(30);
			//untexturedShader->Bind();	
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
	andEnt.Get<AABB>().Update();
	andEnt2.Get<AABB>().Update();
	andEnt3.Get<AABB>().Update();
	notEnt.Get<AABB>().Update();
	boxEnt.Get<AABB>().Update();
	boxEnt2.Get<AABB>().Update();
	boxEnt3.Get<AABB>().Update();
	boxEnt4.Get<AABB>().Update();
	pipeCEnt.Get<AABB>().Update();
	pipeC2Ent.Get<AABB>().Update();
	pipeC3Ent.Get<AABB>().Update();
	buttonEnt.Get<AABB>().Update();
	buttonEnt2.Get<AABB>().Update();
	buttonEnt3.Get<AABB>().Update();
	andEnt.Get<AndGate>().Update();
	andEnt2.Get<AndGate>().Update();
	andEnt3.Get<AndGate>().Update();
	notEnt.Get<NotGate>().Update();
	buttonEnt.Get<Lever>().Update();
	buttonEnt2.Get<Lever>().Update();
	buttonEnt3.Get<Lever>().Update();
	wireEnt.Get<Wire>().Update();
	wireEnt2.Get<Wire>().Update();
	wireEnt3.Get<Wire>().Update();
	wireEnt4.Get<Wire>().Update();
	wireEnt5.Get<Wire>().Update();
	wireEnt6.Get<Wire>().Update();
	wireEnt7.Get<Wire>().Update();
	coilEnt.Get<AABB>().Update();
	
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

void Level3::Unload()
{
	//AudioEngine::Instance().Shutdown();

	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}

glm::vec3 Level3::Catmull(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float t)
{
	return 0.5f * (2.0f * p1 + t * (-p0 + p2)
		+ t * t * (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3)
		+ t * t * t * (-p0 + 3.0f * p1 - 3.0f * p2 + p3));
}

void Level3::StartSegment(int startInd)
{
	currentIndex = startInd;

	if (currentIndex >= points.size())
		currentIndex = 0;

	t = 0.0f;
}