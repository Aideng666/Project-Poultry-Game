#include "Level9.h"
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

Level9::Level9(std::string sceneName, GLFWwindow* wind)
	: Scene(sceneName, wind)
{
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
	wireEnt10 = Entity::Create();
	wireEnt11 = Entity::Create();
	wireEnt12 = Entity::Create();
	wireEnt13 = Entity::Create();
	wireEnt14 = Entity::Create();
	wireEnt15 = Entity::Create();
	wireEnt16 = Entity::Create();
	wireEnt17 = Entity::Create();
	wireEnt18 = Entity::Create();
	wireEnt19 = Entity::Create();
	wireEnt20 = Entity::Create();
	wireEnt21 = Entity::Create();
	wireEnt22 = Entity::Create();

	doorEnt = Entity::Create();

	coilEnt = Entity::Create();

	buttonEnt = Entity::Create();
	buttonEnt2 = Entity::Create();
	buttonEnt3 = Entity::Create();
	buttonEnt4 = Entity::Create();
	buttonEnt5 = Entity::Create();
	buttonEnt6 = Entity::Create();
	buttonEnt7 = Entity::Create();
	buttonEnt8 = Entity::Create();

	andEnt = Entity::Create();
	andEnt2 = Entity::Create();
	andEnt3 = Entity::Create();
	andEnt4 = Entity::Create();
	andEnt5 = Entity::Create();

	orEnt = Entity::Create();
	orEnt2 = Entity::Create();
	orEnt3 = Entity::Create();

	xorEnt = Entity::Create();
	xorEnt2 = Entity::Create();
	xorEnt4 = Entity::Create();

	norEnt = Entity::Create();
	xnorEnt = Entity::Create();
	xnorEnt2 = Entity::Create();

	pauseEnt = Entity::Create();
	optionEnt = Entity::Create();
	exitEnt = Entity::Create();
	retryEnt = Entity::Create();
	completeEnt = Entity::Create();
	tutEnt = Entity::Create();
	optionsMenuEnt = Entity::Create();

	muteEnt = Entity::Create();
	colorBlindEnt = Entity::Create();
	brightEnt = Entity::Create();
	musicEnt = Entity::Create();
	soundEnt = Entity::Create();
	controlsEnt = Entity::Create();

	tabletEnt = Entity::Create();
	tabletScreenEnt = Entity::Create();

	ventEnt = Entity::Create();
	ventEnt2 = Entity::Create();
	ventEnt3 = Entity::Create();
	ventEnt4 = Entity::Create();

	panelEnt = Entity::Create();
	panelEnt2 = Entity::Create();

	tableEnt = Entity::Create();
	tableEnt2 = Entity::Create();

	shelfPipeEnt = Entity::Create();
	shelfPipeEnt2 = Entity::Create();
	shelfPipeEnt3 = Entity::Create();
	shelfPipeEnt4 = Entity::Create();
	shelfPipeEnt5 = Entity::Create();
	shelfPipeEnt6 = Entity::Create();
	shelfPipeEnt7 = Entity::Create();
	shelfPipeEnt8 = Entity::Create();

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

	InitMeshes();
}

void Level9::InitScene()
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
	playerTrans.SetPosition(glm::vec3(0.0f, 1.1f, 45.f));
	playerTrans.SetRotationY(180.0f);
	playerTrans.SetLevelSize(52.5f);

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

	auto& wireTrans10 = wireEnt10.Add<Transform>();
	wireTrans10.SetPosition(glm::vec3(0.f, 1.f, 0.f));

	auto& wireTrans11 = wireEnt11.Add<Transform>();
	wireTrans11.SetPosition(glm::vec3(0.f, 1.f, 0.f));

	auto& wireTrans12 = wireEnt12.Add<Transform>();
	wireTrans12.SetPosition(glm::vec3(0.f, 1.f, 0.f));

	auto& wireTrans13 = wireEnt13.Add<Transform>();
	wireTrans13.SetPosition(glm::vec3(0.f, 1.f, 0.f));

	auto& wireTrans14 = wireEnt14.Add<Transform>();
	wireTrans14.SetPosition(glm::vec3(0.f, 1.f, 0.f));

	auto& wireTrans15 = wireEnt15.Add<Transform>();
	wireTrans15.SetPosition(glm::vec3(0.f, 1.f, 0.f));

	auto& wireTrans16 = wireEnt16.Add<Transform>();
	wireTrans16.SetPosition(glm::vec3(0.f, 1.f, 0.f));

	auto& wireTrans17 = wireEnt17.Add<Transform>();
	wireTrans17.SetPosition(glm::vec3(0.f, 1.f, 0.f));

	auto& wireTrans18 = wireEnt18.Add<Transform>();
	wireTrans18.SetPosition(glm::vec3(0.f, 1.f, 0.f));

	auto& wireTrans19 = wireEnt19.Add<Transform>();
	wireTrans19.SetPosition(glm::vec3(0.f, 1.f, 0.f));

	auto& wireTrans20 = wireEnt20.Add<Transform>();
	wireTrans20.SetPosition(glm::vec3(0.f, 1.f, 0.f));

	auto& wireTrans21 = wireEnt21.Add<Transform>();
	wireTrans21.SetPosition(glm::vec3(0.f, 1.f, 0.f));

	auto& wireTrans22 = wireEnt22.Add<Transform>();
	wireTrans22.SetPosition(glm::vec3(0.f, 1.f, 0.f));

	//Coil Object
	auto& coilTrans = coilEnt.Add<Transform>();
	coilTrans.SetPosition(glm::vec3(-19.3f, 1.0f, -48.f));
	coilTrans.SetScale(glm::vec3(3.0f));
	coilTrans.SetRotationY(180.0f);

	//Table transform
	auto& tableTrans = tableEnt.Add<Transform>();
	tableTrans.SetPosition(glm::vec3(-40.f, 3.5f, 25.f));
	tableTrans.SetRotationY(180.f);
	tableTrans.SetScale(glm::vec3(2.2f));

	auto& tableTrans2 = tableEnt2.Add<Transform>();
	tableTrans2.SetPosition(glm::vec3(-40.f, 3.5f, 40.f));
	tableTrans2.SetRotationY(180.f);
	tableTrans2.SetScale(glm::vec3(2.2f));

	//Shelf Pipe transforms
	auto& shelfPipeTrans = shelfPipeEnt.Add<Transform>();
	shelfPipeTrans.SetPosition(glm::vec3(-40.f, 28.f, -47.f));
	shelfPipeTrans.SetRotationY(270.f);
	shelfPipeTrans.SetScale(glm::vec3(1.5f));

	auto& shelfPipeTrans2 = shelfPipeEnt2.Add<Transform>();
	shelfPipeTrans2.SetPosition(glm::vec3(-30.f, 28.f, -47.f));
	shelfPipeTrans2.SetRotationY(270.f);
	shelfPipeTrans2.SetScale(glm::vec3(1.5f));

	auto& shelfPipeTrans3 = shelfPipeEnt3.Add<Transform>();
	shelfPipeTrans3.SetPosition(glm::vec3(-20.f, 28.f, -47.f));
	shelfPipeTrans3.SetRotationY(270.f);
	shelfPipeTrans3.SetScale(glm::vec3(1.5f));

	auto& shelfPipeTrans4 = shelfPipeEnt4.Add<Transform>();
	shelfPipeTrans4.SetPosition(glm::vec3(-10.f, 28.f, -47.f));
	shelfPipeTrans4.SetRotationY(270.f);
	shelfPipeTrans4.SetScale(glm::vec3(1.5f));

	auto& shelfPipeTrans5 = shelfPipeEnt5.Add<Transform>();
	shelfPipeTrans5.SetPosition(glm::vec3(0.f, 28.f, -47.f));
	shelfPipeTrans5.SetRotationY(270.f);
	shelfPipeTrans5.SetScale(glm::vec3(1.5f));

	auto& shelfPipeTrans6 = shelfPipeEnt6.Add<Transform>();
	shelfPipeTrans6.SetPosition(glm::vec3(10.f, 28.f, -47.f));
	shelfPipeTrans6.SetRotationY(270.f);
	shelfPipeTrans6.SetScale(glm::vec3(1.5f));

	auto& shelfPipeTrans7 = shelfPipeEnt7.Add<Transform>();
	shelfPipeTrans7.SetPosition(glm::vec3(20.f, 28.f, -47.f));
	shelfPipeTrans7.SetRotationY(270.f);
	shelfPipeTrans7.SetScale(glm::vec3(1.5f));

	auto& shelfPipeTrans8 = shelfPipeEnt8.Add<Transform>();
	shelfPipeTrans8.SetPosition(glm::vec3(30.f, 28.f, -47.f));
	shelfPipeTrans8.SetRotationY(270.f);
	shelfPipeTrans8.SetScale(glm::vec3(1.5f));

	//Button transforms
	auto& buttonTrans = buttonEnt.Add<Transform>();
	buttonTrans.SetPosition(glm::vec3(-22.5f, -1.0f, 46.f));

	auto& buttonTrans2 = buttonEnt2.Add<Transform>();
	buttonTrans2.SetPosition(glm::vec3(-18.5f, -1.0f, 46.0f));

	auto& buttonTrans3 = buttonEnt3.Add<Transform>();
	buttonTrans3.SetPosition(glm::vec3(-9.0f, -1.0f, 46.f));

	auto& buttonTrans4 = buttonEnt4.Add<Transform>();
	buttonTrans4.SetPosition(glm::vec3(-5.0f, -1.0f, 46.f));

	auto& buttonTrans5 = buttonEnt5.Add<Transform>();
	buttonTrans5.SetPosition(glm::vec3(6.7f, -1.0f, 46.f));

	auto& buttonTrans6 = buttonEnt6.Add<Transform>();
	buttonTrans6.SetPosition(glm::vec3(10.7f, -1.0f, 46.f));

	auto& buttonTrans7 = buttonEnt7.Add<Transform>();
	buttonTrans7.SetPosition(glm::vec3(21.0f, -1.0f, 46.f));

	auto& buttonTrans8 = buttonEnt8.Add<Transform>();
	buttonTrans8.SetPosition(glm::vec3(24.9f, -1.0f, 46.f));

	auto& gateTrans = andEnt.Add<Transform>();
	gateTrans.SetPosition(glm::vec3(-20.0f, 1.f, 26.5f));
	gateTrans.SetRotationY(-90.0f);
	gateTrans.SetScale(glm::vec3(2.0f));

	auto& gateTrans2 = andEnt2.Add<Transform>();
	gateTrans2.SetPosition(glm::vec3(1.1f, 1.f, 8.0f));
	gateTrans2.SetRotationY(-90.0f);
	gateTrans2.SetScale(glm::vec3(2.0f));

	auto& gateTrans3 = andEnt3.Add<Transform>();
	gateTrans3.SetPosition(glm::vec3(9.2f, 1.2f, -6.0f));
	gateTrans3.SetRotationY(-90.0f);
	gateTrans3.SetScale(glm::vec3(2.0f));

	auto& gateTrans4 = andEnt4.Add<Transform>();
	gateTrans4.SetPosition(glm::vec3(21.3f, 1.f, -26.0f));
	gateTrans4.SetRotationY(-90.0f);
	gateTrans4.SetScale(glm::vec3(2.0f));

	auto& gateTrans5 = andEnt5.Add<Transform>();
	gateTrans5.SetPosition(glm::vec3(0.5f, 1.f, -35.0f));
	gateTrans5.SetRotationY(-90.0f);
	gateTrans5.SetScale(glm::vec3(2.0f));

	//Vent transforms
	auto& ventTrans = ventEnt.Add<Transform>();
	ventTrans.SetPosition(glm::vec3(50.2f, 25.f, 0.f));
	ventTrans.SetScale(glm::vec3(1.2f));
	ventTrans.SetRotationZ(180.f);

	auto& ventTrans2 = ventEnt2.Add<Transform>();
	ventTrans2.SetPosition(glm::vec3(50.2f, 25.f, 20.f));
	ventTrans2.SetScale(glm::vec3(1.2f));
	ventTrans2.SetRotationZ(180.f);

	auto& ventTrans3 = ventEnt3.Add<Transform>();
	ventTrans3.SetPosition(glm::vec3(-50.2f, 25.f, 0.f));
	ventTrans3.SetScale(glm::vec3(1.2f));

	auto& ventTrans4 = ventEnt4.Add<Transform>();
	ventTrans4.SetPosition(glm::vec3(-50.2f, 25.f, 20.f));
	ventTrans4.SetScale(glm::vec3(1.2f));

	//Panel transforms
	auto& panelTrans = panelEnt.Add<Transform>();
	panelTrans.SetScale(glm::vec3(4.0f));
	panelTrans.SetPosition(glm::vec3(30.f, 7.0f, -51.f));
	panelTrans.SetRotationY(-90.f);

	auto& panelTrans2 = panelEnt2.Add<Transform>();
	panelTrans2.SetScale(glm::vec3(4.0f));
	panelTrans2.SetPosition(glm::vec3(-30.f, 7.0f, -51.f));
	panelTrans2.SetRotationY(-90.f);

	//Or-Gates
	auto& orTrans = orEnt.Add<Transform>();
	orTrans.SetPosition(glm::vec3(-6.7f, 1.2f, 27.0f));
	orTrans.SetRotationY(-90.0f);
	orTrans.SetScale(glm::vec3(2.0f));

	auto& orTrans2 = orEnt2.Add<Transform>();
	orTrans2.SetPosition(glm::vec3(16.8f, 1.2f, 8.0f));
	orTrans2.SetRotationY(-90.0f);
	orTrans2.SetScale(glm::vec3(2.0f));

	auto& orTrans3 = orEnt3.Add<Transform>();
	orTrans3.SetPosition(glm::vec3(29.3f, 1.f, -8.5f));
	orTrans3.SetRotationY(-90.0f);
	orTrans3.SetScale(glm::vec3(2.0f));

	//Xor-Gate
	auto& xorTrans = xorEnt.Add<Transform>();
	xorTrans.SetPosition(glm::vec3(8.8f, 1.2f, 26.5f));

	auto& xorTrans2 = xorEnt2.Add<Transform>();
	xorTrans2.SetPosition(glm::vec3(22.3f, 1.f, 27.0f));

	auto& xorTrans4 = xorEnt4.Add<Transform>();
	xorTrans4.SetPosition(glm::vec3(-16.0f, 1.f, -26.0f));

	//Nor-Gates
	auto& norTrans = norEnt.Add<Transform>();
	norTrans.SetPosition(glm::vec3(-6.5f, 1.2f, -6.0f));

	//XNor Gate
	auto& xnorTrans = xnorEnt.Add<Transform>();
	xnorTrans.SetPosition(glm::vec3(-14.4f, 1.f, 8.0f));

	auto& xnorTrans2 = xnorEnt2.Add<Transform>();
	xnorTrans2.SetPosition(glm::vec3(-26.7f, 1.f, -8.5f));
	
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

	//Level complete transform
	auto& completeTrans = completeEnt.Add<Transform>();
	completeTrans.SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	completeTrans.SetScale(glm::vec3(0.22f));

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

	auto& tabletTrans = tabletEnt.Add<Transform>();
	tabletTrans.SetPosition(glm::vec3(0.0f, 5.0f, 30.0f));
	tabletTrans.SetRotationY(180.0f);

	auto& tabletScreenTrans = tabletScreenEnt.Add<Transform>();
	tabletScreenTrans.SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	tabletScreenTrans.SetScale(glm::vec3(0.18f, 1.0f, 0.18f));

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
	auto& buttonCol4 = buttonEnt4.Add<AABB>(buttonEnt4, mainPlayer, 2.0f, 2.0f);
	buttonCol4.SetIsAmbient(true);
	auto& buttonCol5 = buttonEnt5.Add<AABB>(buttonEnt5, mainPlayer, 2.0f, 2.0f);
	buttonCol5.SetIsAmbient(true);
	auto& buttonCol6 = buttonEnt6.Add<AABB>(buttonEnt6, mainPlayer, 2.0f, 2.0f);
	buttonCol6.SetIsAmbient(true);
	auto& buttonCol7 = buttonEnt7.Add<AABB>(buttonEnt7, mainPlayer, 2.0f, 2.0f);
	buttonCol7.SetIsAmbient(true);
	auto& buttonCol8 = buttonEnt8.Add<AABB>(buttonEnt8, mainPlayer, 2.0f, 2.0f);
	buttonCol8.SetIsAmbient(true);
	auto& andCol = andEnt.Add<AABB>(andEnt, mainPlayer, 5.0f, 3.0f);
	andCol.SetIsAmbient(true);
	auto& andCol2 = andEnt2.Add<AABB>(andEnt2, mainPlayer, 5.0f, 3.0f);
	andCol2.SetIsAmbient(true);
	auto& andCol3 = andEnt3.Add<AABB>(andEnt3, mainPlayer, 5.0f, 3.0f);
	andCol3.SetIsAmbient(true);
	auto& andCol4 = andEnt4.Add<AABB>(andEnt4, mainPlayer, 5.0f, 3.0f);
	andCol4.SetIsAmbient(true);
	auto& andCol5 = andEnt5.Add<AABB>(andEnt5, mainPlayer, 5.0f, 3.0f);
	andCol5.SetIsAmbient(true);
	auto& orCol = orEnt.Add<AABB>(orEnt, mainPlayer, 5.0f, 3.0f);
	orCol.SetIsAmbient(true);
	auto& orCol2 = orEnt2.Add<AABB>(orEnt2, mainPlayer, 5.0f, 3.0f);
	orCol2.SetIsAmbient(true);
	auto& orCol3 = orEnt3.Add<AABB>(orEnt3, mainPlayer, 5.0f, 3.0f);
	orCol3.SetIsAmbient(true);
	auto& xorCol = xorEnt.Add<AABB>(xorEnt, mainPlayer, 5.0f, 3.0f);
	xorCol.SetIsAmbient(true);
	auto& xorCol2 = xorEnt2.Add<AABB>(xorEnt2, mainPlayer, 5.0f, 3.0f);
	xorCol2.SetIsAmbient(true);
	auto& xorCol4 = xorEnt4.Add<AABB>(xorEnt4, mainPlayer, 5.0f, 3.0f);
	xorCol4.SetIsAmbient(true);
	auto& norCol = norEnt.Add<AABB>(norEnt, mainPlayer, 5.0f, 3.0f);
	norCol.SetIsAmbient(true);
	auto& xnorCol = xnorEnt.Add<AABB>(xnorEnt, mainPlayer, 5.0f, 3.0f);
	xnorCol.SetIsAmbient(true);
	auto& xnorCol2 = xnorEnt2.Add<AABB>(xnorEnt2, mainPlayer, 5.0f, 3.0f);
	xnorCol2.SetIsAmbient(true);
	auto& tableCol = tableEnt.Add<AABB>(tableEnt, mainPlayer, 5.0f, 8.5f);
	tableCol.SetIsAmbient(true);
	auto& tableCol2 = tableEnt2.Add<AABB>(tableEnt2, mainPlayer, 5.0f, 8.5f);
	tableCol2.SetIsAmbient(true);

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
	auto& button5 = buttonEnt5.Add<Lever>(wireEnt5);
	button5.SetPowered(false);
	auto& button6 = buttonEnt6.Add<Lever>(wireEnt6);
	button6.SetPowered(false);
	auto& button7 = buttonEnt7.Add<Lever>(wireEnt7);
	button7.SetPowered(false);
	auto& button8 = buttonEnt8.Add<Lever>(wireEnt8);
	button8.SetPowered(false);

	//Wires
	auto& wire = wireEnt.Add<Wire>(buttonEnt);
	auto& wire2 = wireEnt2.Add<Wire>(buttonEnt2);
	auto& wire3 = wireEnt3.Add<Wire>(buttonEnt3);
	auto& wire4 = wireEnt4.Add<Wire>(buttonEnt4);
	auto& wire5 = wireEnt5.Add<Wire>(buttonEnt5);
	auto& wire6 = wireEnt6.Add<Wire>(buttonEnt6);
	auto& wire7 = wireEnt7.Add<Wire>(buttonEnt7);
	auto& wire8 = wireEnt8.Add<Wire>(buttonEnt8);
	auto& wire9 = wireEnt9.Add<Wire>(andEnt);
	auto& wire10 = wireEnt10.Add<Wire>(orEnt);
	auto& wire11 = wireEnt11.Add<Wire>(xorEnt);
	auto& wire12 = wireEnt12.Add<Wire>(xorEnt2);
	auto& wire13 = wireEnt13.Add<Wire>(xnorEnt);
	auto& wire14 = wireEnt14.Add<Wire>(andEnt2);
	auto& wire15 = wireEnt15.Add<Wire>(orEnt2);
	auto& wire16 = wireEnt16.Add<Wire>(xnorEnt2);
	auto& wire17 = wireEnt17.Add<Wire>(norEnt);
	auto& wire18 = wireEnt18.Add<Wire>(andEnt3);
	auto& wire19 = wireEnt19.Add<Wire>(orEnt3);
	auto& wire20 = wireEnt20.Add<Wire>(xorEnt4);
	auto& wire21 = wireEnt21.Add<Wire>(andEnt4);
	auto& wire22 = wireEnt22.Add<Wire>(andEnt5);

	//Gates
	auto& andGate = andEnt.Add<AndGate>(wireEnt, wireEnt2, wireEnt9);
	auto& andGate2 = andEnt2.Add<AndGate>(wireEnt10, wireEnt11, wireEnt14);
	auto& andGate3 = andEnt3.Add<AndGate>(wireEnt14, wireEnt15, wireEnt18);
	auto& andGate4 = andEnt4.Add<AndGate>(wireEnt18, wireEnt19, wireEnt21);
	auto& andGate5 = andEnt5.Add<AndGate>(wireEnt20, wireEnt21, doorEnt);
	auto& orGate = orEnt.Add<OrGate>(wireEnt3, wireEnt4, wireEnt10);
	auto& orGate2 = orEnt2.Add<OrGate>(wireEnt11, wireEnt12, wireEnt15);
	auto& orGate3 = orEnt3.Add<OrGate>(wireEnt15, wireEnt12, wireEnt19);
	auto& xorGate = xorEnt.Add<XorGate>(wireEnt5, wireEnt6, wireEnt11);
	auto& xorGate2 = xorEnt2.Add<XorGate>(wireEnt7, wireEnt8, wireEnt12);
	auto& xorGate4 = xorEnt4.Add<XorGate>(wireEnt16, wireEnt17, wireEnt20);
	auto& norGate = norEnt.Add<NorGate>(wireEnt13, wireEnt14, wireEnt17);
	auto& xnorGate = xnorEnt.Add<XNorGate>(wireEnt9, wireEnt10, wireEnt13);
	auto& xnorGate2 = xnorEnt2.Add<XNorGate>(wireEnt9, wireEnt13, wireEnt16);

	//Door
	auto& door = doorEnt.Add<Door>();
	door.SetOpen(false);

	InitAnims();

	auto& playerMesh = mainPlayer.Add<MorphRenderer>(mainPlayer, *idle1, animShader);
	auto& floorMesh = floorEnt.Add<MeshRenderer>(floorEnt, *floorLab, shader);
	auto& leftMesh = leftEnt.Add<MeshRenderer>(leftEnt, *leftWallLab, shader);
	auto& rightMesh = rightEnt.Add<MeshRenderer>(rightEnt, *rightWallLab, shader);
	auto& backMesh = backEnt.Add<MeshRenderer>(backEnt, *backWallLab, shader);

	auto& doorMesh = doorEnt.Add<MorphRenderer>(doorEnt, *door1, animShader);

	auto& wireMesh = wireEnt.Add<MeshRenderer>(wireEnt, *wireM1L9, shader);
	auto& wireMesh2 = wireEnt2.Add<MeshRenderer>(wireEnt2, *wireM2L9, shader);
	auto& wireMesh3 = wireEnt3.Add<MeshRenderer>(wireEnt3, *wireM3L9, shader);
	auto& wireMesh4 = wireEnt4.Add<MeshRenderer>(wireEnt4, *wireM4L9, shader);
	auto& wireMesh5 = wireEnt5.Add<MeshRenderer>(wireEnt5, *wireM5L9, shader);
	auto& wireMesh6 = wireEnt6.Add<MeshRenderer>(wireEnt6, *wireM6L9, shader);
	auto& wireMesh7 = wireEnt7.Add<MeshRenderer>(wireEnt7, *wireM7L9, shader);
	auto& wireMesh8 = wireEnt8.Add<MeshRenderer>(wireEnt8, *wireM8L9, shader);
	auto& wireMesh9 = wireEnt9.Add<MeshRenderer>(wireEnt9, *wireM9L9, shader);
	auto& wireMesh10 = wireEnt10.Add<MeshRenderer>(wireEnt10, *wireM10L9, shader);
	auto& wireMesh11 = wireEnt11.Add<MeshRenderer>(wireEnt11, *wireM11L9, shader);
	auto& wireMesh12 = wireEnt12.Add<MeshRenderer>(wireEnt12, *wireM12L9, shader);
	auto& wireMesh13 = wireEnt13.Add<MeshRenderer>(wireEnt13, *wireM13L9, shader);
	auto& wireMesh14 = wireEnt14.Add<MeshRenderer>(wireEnt14, *wireM14L9, shader);
	auto& wireMesh15 = wireEnt15.Add<MeshRenderer>(wireEnt15, *wireM15L9, shader);
	auto& wireMesh16 = wireEnt16.Add<MeshRenderer>(wireEnt16, *wireM16L9, shader);
	auto& wireMesh17 = wireEnt17.Add<MeshRenderer>(wireEnt17, *wireM17L9, shader);
	auto& wireMesh18 = wireEnt18.Add<MeshRenderer>(wireEnt18, *wireM18L9, shader);
	auto& wireMesh19 = wireEnt19.Add<MeshRenderer>(wireEnt19, *wireM19L9, shader);
	auto& wireMesh20 = wireEnt20.Add<MeshRenderer>(wireEnt20, *wireM20L9, shader);
	auto& wireMesh21 = wireEnt21.Add<MeshRenderer>(wireEnt21, *wireM21L9, shader);
	auto& wireMesh22 = wireEnt22.Add<MeshRenderer>(wireEnt22, *wireM22L9, shader);

	auto& coilMesh = coilEnt.Add<MeshRenderer>(coilEnt, *coil, shader);

	auto& buttonMesh = buttonEnt.Add<MorphRenderer>(buttonEnt, *buttonM, animShader);
	auto& buttonMesh2 = buttonEnt2.Add<MorphRenderer>(buttonEnt2, *buttonM, animShader);
	auto& buttonMesh3 = buttonEnt3.Add<MorphRenderer>(buttonEnt3, *buttonM, animShader);
	auto& buttonMesh4 = buttonEnt4.Add<MorphRenderer>(buttonEnt4, *buttonM, animShader);
	auto& buttonMesh5 = buttonEnt5.Add<MorphRenderer>(buttonEnt5, *buttonM, animShader);
	auto& buttonMesh6 = buttonEnt6.Add<MorphRenderer>(buttonEnt6, *buttonM, animShader);
	auto& buttonMesh7 = buttonEnt7.Add<MorphRenderer>(buttonEnt7, *buttonM, animShader);
	auto& buttonMesh8 = buttonEnt8.Add<MorphRenderer>(buttonEnt8, *buttonM, animShader);

	auto& andMesh = andEnt.Add<MeshRenderer>(andEnt, *and, shader);
	auto& andMesh2 = andEnt2.Add<MeshRenderer>(andEnt2, *and, shader);
	auto& andMesh3 = andEnt3.Add<MeshRenderer>(andEnt3, *and, shader);
	auto& andMesh4 = andEnt4.Add<MeshRenderer>(andEnt4, *and, shader);
	auto& andMesh5 = andEnt5.Add<MeshRenderer>(andEnt5, *and, shader);

	auto& orGateMesh = orEnt.Add<MeshRenderer>(orEnt, *orMesh, shader);
	auto& orGateMesh2 = orEnt2.Add<MeshRenderer>(orEnt2, *orMesh, shader);
	auto& orGateMesh3 = orEnt3.Add<MeshRenderer>(orEnt3, *orMesh, shader);

	auto& xorMesh = xorEnt.Add<MeshRenderer>(xorEnt, *xor, shader);
	auto& xorMesh2 = xorEnt2.Add<MeshRenderer>(xorEnt2, *xor, shader);
	auto& xorMesh4 = xorEnt4.Add<MeshRenderer>(xorEnt4, *xor, shader);

	auto& norMesh = norEnt.Add<MeshRenderer>(norEnt, *nor, shader);

	auto& xnorMesh = xnorEnt.Add<MeshRenderer>(xnorEnt, *xnor, shader);
	auto& xnorMesh2 = xnorEnt2.Add<MeshRenderer>(xnorEnt2, *xnor, shader);

	auto& pauseMesh = pauseEnt.Add<MeshRenderer>(pauseEnt, *screen, pauseShader);
	auto& optionMesh = optionEnt.Add<MeshRenderer>(optionEnt, *options, pauseShader);
	auto& retryMesh = retryEnt.Add<MeshRenderer>(retryEnt, *retry, pauseShader);
	auto& exitMesh = exitEnt.Add<MeshRenderer>(exitEnt, *exit, pauseShader);
	auto& completeMesh = completeEnt.Add<MeshRenderer>(completeEnt, *screen, shader);
	auto& tutMesh = tutEnt.Add<MeshRenderer>(tutEnt, *tut, untexturedShader);
	auto& optionsMenuMesh = optionsMenuEnt.Add<MeshRenderer>(optionsMenuEnt, *screen, pauseShader);

	auto& muteMesh = muteEnt.Add<MeshRenderer>(muteEnt, *optionsButton, pauseShader);
	auto& musicMesh = musicEnt.Add<MeshRenderer>(musicEnt, *optionsButton, pauseShader);
	auto& soundMesh = soundEnt.Add<MeshRenderer>(soundEnt, *optionsButton, pauseShader);
	auto& brightMesh = brightEnt.Add<MeshRenderer>(brightEnt, *optionsButton, pauseShader);
	auto& colorBlindMesh = colorBlindEnt.Add<MeshRenderer>(colorBlindEnt, *optionsButton, pauseShader);
	auto& controlsMesh = controlsEnt.Add<MeshRenderer>(controlsEnt, *optionsButton, pauseShader);

	auto& tabletScreenMesh = tabletScreenEnt.Add<MeshRenderer>(tabletScreenEnt, *screen, pauseShader);
	auto& tabletMesh = tabletEnt.Add<MeshRenderer>(tabletEnt, *tablet, rimLightShader);

	auto& vent = ventEnt.Add<MeshRenderer>(ventEnt, *ventS, shader);
	auto& vent2 = ventEnt2.Add<MeshRenderer>(ventEnt2, *ventS, shader);
	auto& vent3 = ventEnt3.Add<MeshRenderer>(ventEnt3, *ventS, shader);
	auto& vent4 = ventEnt4.Add<MeshRenderer>(ventEnt4, *ventS, shader);

	auto& panelMesh = panelEnt.Add<MeshRenderer>(panelEnt, *panel, shader);
	auto& panelMesh2 = panelEnt2.Add<MeshRenderer>(panelEnt2, *panel, shader);

	auto& tableMesh = tableEnt.Add<MeshRenderer>(tableEnt, *table, shader);
	auto& tableMesh2 = tableEnt2.Add<MeshRenderer>(tableEnt2, *table, shader);

	auto& shelfPipeMesh = shelfPipeEnt.Add<MeshRenderer>(shelfPipeEnt, *shelfPipe, shader);
	auto& shelfPipeMesh2 = shelfPipeEnt2.Add<MeshRenderer>(shelfPipeEnt2, *shelfPipe, shader);
	auto& shelfPipeMesh3 = shelfPipeEnt3.Add<MeshRenderer>(shelfPipeEnt3, *shelfPipe, shader);
	auto& shelfPipeMesh4 = shelfPipeEnt4.Add<MeshRenderer>(shelfPipeEnt4, *shelfPipe, shader);
	auto& shelfPipeMesh5 = shelfPipeEnt5.Add<MeshRenderer>(shelfPipeEnt5, *shelfPipe, shader);
	auto& shelfPipeMesh6 = shelfPipeEnt6.Add<MeshRenderer>(shelfPipeEnt6, *shelfPipe, shader);
	auto& shelfPipeMesh7 = shelfPipeEnt7.Add<MeshRenderer>(shelfPipeEnt7, *shelfPipe, shader);
	auto& shelfPipeMesh8 = shelfPipeEnt8.Add<MeshRenderer>(shelfPipeEnt8, *shelfPipe, shader);

	entList.push_back(&mainPlayer);
	entList.push_back(&doorEnt);
	entList.push_back(&buttonEnt);
	entList.push_back(&buttonEnt2);
	entList.push_back(&buttonEnt3);
	entList.push_back(&buttonEnt4);
	entList.push_back(&buttonEnt5);
	entList.push_back(&buttonEnt6);
	entList.push_back(&buttonEnt7);
	entList.push_back(&buttonEnt8);
	entList.push_back(&floorEnt);
	entList.push_back(&leftEnt);
	entList.push_back(&rightEnt);
	entList.push_back(&andEnt);
	entList.push_back(&andEnt2);
	entList.push_back(&andEnt3);
	entList.push_back(&andEnt4);
	entList.push_back(&andEnt5);
	entList.push_back(&orEnt);
	entList.push_back(&orEnt2);
	entList.push_back(&orEnt3);
	entList.push_back(&xorEnt);
	entList.push_back(&xorEnt2);
	entList.push_back(&xorEnt4);
	entList.push_back(&norEnt);
	entList.push_back(&xnorEnt);
	entList.push_back(&xnorEnt2);
	entList.push_back(&wireEnt);
	entList.push_back(&wireEnt2);
	entList.push_back(&wireEnt3);
	entList.push_back(&wireEnt4);
	entList.push_back(&wireEnt5);
	entList.push_back(&wireEnt6);
	entList.push_back(&wireEnt7);
	entList.push_back(&wireEnt8);
	entList.push_back(&wireEnt9);
	entList.push_back(&wireEnt10);
	entList.push_back(&wireEnt11);
	entList.push_back(&wireEnt12);
	entList.push_back(&wireEnt13);
	entList.push_back(&wireEnt14);
	entList.push_back(&wireEnt15);
	entList.push_back(&wireEnt16);
	entList.push_back(&wireEnt17);
	entList.push_back(&wireEnt18);
	entList.push_back(&wireEnt19);
	entList.push_back(&wireEnt20);
	entList.push_back(&wireEnt21);
	entList.push_back(&wireEnt22);
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

	auto& buttonAnimator5 = buttonEnt5.Add<MorphAnimation>(buttonEnt5);
	buttonAnimator5.SetTime(0.2f);
	buttonAnimator5.SetFrames(buttonFrames);
	buttonAnimator5.SetLoop(false);

	auto& buttonAnimator6 = buttonEnt6.Add<MorphAnimation>(buttonEnt6);
	buttonAnimator6.SetTime(0.2f);
	buttonAnimator6.SetFrames(buttonFrames);
	buttonAnimator6.SetLoop(false);

	auto& buttonAnimator7 = buttonEnt7.Add<MorphAnimation>(buttonEnt7);
	buttonAnimator7.SetTime(0.2f);
	buttonAnimator7.SetFrames(buttonFrames);
	buttonAnimator7.SetLoop(false);

	auto& buttonAnimator8 = buttonEnt8.Add<MorphAnimation>(buttonEnt8);
	buttonAnimator8.SetTime(0.2f);
	buttonAnimator8.SetFrames(buttonFrames);
	buttonAnimator8.SetLoop(false);

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
	topCam.SetPosition(glm::vec3(0, 58, 0)); // Set initial position
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

void Level9::Update(float dt)
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
		AudioEngine::Instance().GetEvent("XNOR Tablet").Play();
		isTalking = true;
	}

	auto& playerTrans = mainPlayer.Get<Transform>();
	auto& buttonTrans = buttonEnt.Get<Transform>();
	auto& buttonTrans2 = buttonEnt2.Get<Transform>();
	auto& buttonTrans3 = buttonEnt3.Get<Transform>();
	auto& buttonTrans4 = buttonEnt4.Get<Transform>();
	auto& buttonTrans5 = buttonEnt5.Get<Transform>();
	auto& buttonTrans6 = buttonEnt6.Get<Transform>();
	auto& buttonTrans7 = buttonEnt7.Get<Transform>();
	auto& buttonTrans8 = buttonEnt8.Get<Transform>();

	backEnt.Get<Transform>().SetPositionZ(-51.5f);
	backEnt.Get<Transform>().SetPositionY(0.0f);

	leftEnt.Get<Transform>().SetPositionX(-51.5f);
	leftEnt.Get<Transform>().SetRotationY(90.0f);
	leftEnt.Get<Transform>().SetPositionY(0.0f);
	leftEnt.Get<Transform>().SetPositionZ(2.0f);

	rightEnt.Get<Transform>().SetPositionX(51.5f);
	rightEnt.Get<Transform>().SetRotationY(90.0f);
	rightEnt.Get<Transform>().SetPositionY(0.0f);
	rightEnt.Get<Transform>().SetPositionZ(2.0f);

	tabletEnt.Get<Transform>().SetRotationY(tabletEnt.Get<Transform>().GetRotation().y + 100 * dt);

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
	glm::mat4 transformWire10 = wireEnt10.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire11 = wireEnt11.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire12 = wireEnt12.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire13 = wireEnt13.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire14 = wireEnt14.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire15 = wireEnt15.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire16 = wireEnt16.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire17 = wireEnt17.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire18 = wireEnt18.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire19 = wireEnt19.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire20 = wireEnt20.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire21 = wireEnt21.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire22 = wireEnt22.Get<Transform>().GetModelMatrix();

	glm::mat4 transformCoil = coilEnt.Get<Transform>().GetModelMatrix();

	glm::mat4 transformButton = buttonTrans.GetModelMatrix();
	glm::mat4 transformButton2 = buttonTrans2.GetModelMatrix();
	glm::mat4 transformButton3 = buttonTrans3.GetModelMatrix();
	glm::mat4 transformButton4 = buttonTrans4.GetModelMatrix();
	glm::mat4 transformButton5 = buttonTrans5.GetModelMatrix();
	glm::mat4 transformButton6 = buttonTrans6.GetModelMatrix();
	glm::mat4 transformButton7 = buttonTrans7.GetModelMatrix();
	glm::mat4 transformButton8 = buttonTrans8.GetModelMatrix();

	glm::mat4 transformAnd = andEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformAnd2 = andEnt2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformAnd3 = andEnt3.Get<Transform>().GetModelMatrix();
	glm::mat4 transformAnd4 = andEnt4.Get<Transform>().GetModelMatrix();
	glm::mat4 transformAnd5 = andEnt5.Get<Transform>().GetModelMatrix();

	glm::mat4 transformOr = orEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformOr2 = orEnt2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformOr3 = orEnt3.Get<Transform>().GetModelMatrix();

	glm::mat4 transformXor = xorEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformXor2 = xorEnt2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformXor4 = xorEnt4.Get<Transform>().GetModelMatrix();

	glm::mat4 transformNor = norEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformXNor = xnorEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformXNor2 = xnorEnt2.Get<Transform>().GetModelMatrix();

	glm::mat4 transformPause = pauseEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformOptions = optionEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformRetry = retryEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformExit = exitEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformComplete = completeEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformTut = tutEnt.Get<Transform>().GetModelMatrix();

	glm::mat4 transformMute = muteEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformMusic = musicEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformSound = soundEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformBright = brightEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformColorBlind = colorBlindEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformControls = controlsEnt.Get<Transform>().GetModelMatrix();

	glm::mat4 transformTablet = tabletEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformTabletScreen = tabletScreenEnt.Get<Transform>().GetModelMatrix();

	glm::mat4 transformVent = ventEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformVent2 = ventEnt2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformVent3 = ventEnt3.Get<Transform>().GetModelMatrix();
	glm::mat4 transformVent4 = ventEnt4.Get<Transform>().GetModelMatrix();

	glm::mat4 transformPanel = panelEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformPanel2 = panelEnt2.Get<Transform>().GetModelMatrix();

	glm::mat4 transformTable = tableEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformTable2 = tableEnt2.Get<Transform>().GetModelMatrix();

	glm::mat4 transformShelfPipe = shelfPipeEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformShelfPipe2 = shelfPipeEnt2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformShelfPipe3 = shelfPipeEnt3.Get<Transform>().GetModelMatrix();
	glm::mat4 transformShelfPipe4 = shelfPipeEnt4.Get<Transform>().GetModelMatrix();
	glm::mat4 transformShelfPipe5 = shelfPipeEnt5.Get<Transform>().GetModelMatrix();
	glm::mat4 transformShelfPipe6 = shelfPipeEnt6.Get<Transform>().GetModelMatrix();
	glm::mat4 transformShelfPipe7 = shelfPipeEnt7.Get<Transform>().GetModelMatrix();
	glm::mat4 transformShelfPipe8 = shelfPipeEnt8.Get<Transform>().GetModelMatrix();

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

	if (!button4AnimOn && playerTrans.GetPositionX() - buttonTrans4.GetPositionX() < 3.0f && playerTrans.GetPositionX() - buttonTrans4.GetPositionX() > -3.0f
		&& playerTrans.GetPositionZ() - buttonTrans4.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans4.GetPositionZ() > -3.0f)
	{
		button4Watch.Poll(window);
	}

	if (!button5AnimOn && playerTrans.GetPositionX() - buttonTrans5.GetPositionX() < 3.0f && playerTrans.GetPositionX() - buttonTrans5.GetPositionX() > -3.0f
		&& playerTrans.GetPositionZ() - buttonTrans5.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans5.GetPositionZ() > -3.0f)
	{
		button5Watch.Poll(window);
	}

	if (!button6AnimOn && playerTrans.GetPositionX() - buttonTrans6.GetPositionX() < 3.0f && playerTrans.GetPositionX() - buttonTrans6.GetPositionX() > -3.0f
		&& playerTrans.GetPositionZ() - buttonTrans6.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans6.GetPositionZ() > -3.0f)
	{
		button6Watch.Poll(window);
	}

	if (!button7AnimOn && playerTrans.GetPositionX() - buttonTrans7.GetPositionX() < 3.0f && playerTrans.GetPositionX() - buttonTrans7.GetPositionX() > -3.0f
		&& playerTrans.GetPositionZ() - buttonTrans7.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans7.GetPositionZ() > -3.0f)
	{
		button7Watch.Poll(window);
	}

	if (!button8AnimOn && playerTrans.GetPositionX() - buttonTrans8.GetPositionX() < 3.0f && playerTrans.GetPositionX() - buttonTrans8.GetPositionX() > -3.0f
		&& playerTrans.GetPositionZ() - buttonTrans8.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans8.GetPositionZ() > -3.0f)
	{
		button8Watch.Poll(window);
	}

	if ((playerTrans.GetPositionX() > -3.0f && playerTrans.GetPositionX() < 3.0f
		&& playerTrans.GetPositionZ() > 27.0f && playerTrans.GetPositionZ() < 33.0f
		&& !tabletOpen) || tabletOpen)
		tabletWatch.Poll(window);

	if (!optionsOpen)
		pauseWatch.Poll(window);

	if (showLevelComplete)
	{
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			AudioEngine::Instance().GetEvent("Level Complete").Stop();
			levelComplete = true;
		}
	}

	if (showLevelComplete && !completeSoundPlaying)
	{
		AudioEngine::Instance().GetEvent("Level Complete").Play();
		completeSoundPlaying = true;
	}

#pragma region PlayerMovement
	if (!showLevelComplete && !isPaused && !tabletOpen)
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

	if (!showLevelComplete && !isPaused)
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


	if (button2AnimOn)
	{
		AudioEngine::Instance().GetEvent("Button").Play();
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
		AudioEngine::Instance().GetEvent("Button").Play();
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
		AudioEngine::Instance().GetEvent("Button").Play();
		if (buttonEnt4.Get<MorphAnimation>().GetIsDone())
		{
			buttonEnt4.Get<MorphAnimation>().SetFrames(buttonFrames);
			buttonEnt4.Get<MorphAnimation>().SetTime(0.2f);
			button4AnimOn = false;
		}

		buttonEnt4.Get<MorphAnimation>().Update(dt);
	}

	if (button5AnimOn)
	{
		AudioEngine::Instance().GetEvent("Button").Play();
		if (buttonEnt5.Get<MorphAnimation>().GetIsDone())
		{
			buttonEnt5.Get<MorphAnimation>().SetFrames(buttonFrames);
			buttonEnt5.Get<MorphAnimation>().SetTime(0.2f);
			button5AnimOn = false;
		}

		buttonEnt5.Get<MorphAnimation>().Update(dt);
	}

	if (button6AnimOn)
	{
		AudioEngine::Instance().GetEvent("Button").Play();
		if (buttonEnt6.Get<MorphAnimation>().GetIsDone())
		{
			buttonEnt6.Get<MorphAnimation>().SetFrames(buttonFrames);
			buttonEnt6.Get<MorphAnimation>().SetTime(0.2f);
			button6AnimOn = false;
		}

		buttonEnt6.Get<MorphAnimation>().Update(dt);
	}

	if (button7AnimOn)
	{
		AudioEngine::Instance().GetEvent("Button").Play();
		if (buttonEnt7.Get<MorphAnimation>().GetIsDone())
		{
			buttonEnt7.Get<MorphAnimation>().SetFrames(buttonFrames);
			buttonEnt7.Get<MorphAnimation>().SetTime(0.2f);
			button7AnimOn = false;
		}

		buttonEnt7.Get<MorphAnimation>().Update(dt);
	}

	if (button8AnimOn)
	{
		AudioEngine::Instance().GetEvent("Button").Play();
		if (buttonEnt8.Get<MorphAnimation>().GetIsDone())
		{
			buttonEnt8.Get<MorphAnimation>().SetFrames(buttonFrames);
			buttonEnt8.Get<MorphAnimation>().SetTime(0.2f);
			button8AnimOn = false;
		}

		buttonEnt8.Get<MorphAnimation>().Update(dt);
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
		if (i < 10)
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
			buttonEnt4.Get<MorphRenderer>().Render(camera, transformButton4, LightSpaceViewProjection);
			buttonEnt5.Get<MorphRenderer>().Render(camera, transformButton5, LightSpaceViewProjection);
			buttonEnt6.Get<MorphRenderer>().Render(camera, transformButton6, LightSpaceViewProjection);
			buttonEnt7.Get<MorphRenderer>().Render(camera, transformButton7, LightSpaceViewProjection);
			buttonEnt8.Get<MorphRenderer>().Render(camera, transformButton8, LightSpaceViewProjection);
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
			xnorTabletScreenMat.Albedo->Bind(4);

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
				wireEnt4.Get<MeshRenderer>().Render(camera, transformWire4, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt4.Get<MeshRenderer>().Render(camera, transformWire4, LightSpaceViewProjection);
			}

			if (wireEnt5.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(0);
				wireEnt5.Get<MeshRenderer>().Render(camera, transformWire5, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt5.Get<MeshRenderer>().Render(camera, transformWire5, LightSpaceViewProjection);
			}

			if (wireEnt6.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(0);
				wireEnt6.Get<MeshRenderer>().Render(camera, transformWire6, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt6.Get<MeshRenderer>().Render(camera, transformWire6, LightSpaceViewProjection);
			}

			if (wireEnt7.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(0);
				wireEnt7.Get<MeshRenderer>().Render(camera, transformWire7, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt7.Get<MeshRenderer>().Render(camera, transformWire7, LightSpaceViewProjection);
			}

			if (wireEnt8.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(0);
				wireEnt8.Get<MeshRenderer>().Render(camera, transformWire8, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt8.Get<MeshRenderer>().Render(camera, transformWire8, LightSpaceViewProjection);
			}

			if (wireEnt9.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(0);
				wireEnt9.Get<MeshRenderer>().Render(camera, transformWire9, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt9.Get<MeshRenderer>().Render(camera, transformWire9, LightSpaceViewProjection);
			}

			if (wireEnt10.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(0);
				wireEnt10.Get<MeshRenderer>().Render(camera, transformWire10, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt10.Get<MeshRenderer>().Render(camera, transformWire10, LightSpaceViewProjection);
			}

			if (wireEnt11.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(0);
				wireEnt11.Get<MeshRenderer>().Render(camera, transformWire11, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt11.Get<MeshRenderer>().Render(camera, transformWire11, LightSpaceViewProjection);
			}

			if (wireEnt12.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(0);
				wireEnt12.Get<MeshRenderer>().Render(camera, transformWire12, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt12.Get<MeshRenderer>().Render(camera, transformWire12, LightSpaceViewProjection);
			}

			if (wireEnt13.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(0);
				wireEnt13.Get<MeshRenderer>().Render(camera, transformWire13, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt13.Get<MeshRenderer>().Render(camera, transformWire13, LightSpaceViewProjection);
			}

			if (wireEnt14.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(0);
				wireEnt14.Get<MeshRenderer>().Render(camera, transformWire14, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt14.Get<MeshRenderer>().Render(camera, transformWire14, LightSpaceViewProjection);
			}

			if (wireEnt15.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(0);
				wireEnt15.Get<MeshRenderer>().Render(camera, transformWire15, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt15.Get<MeshRenderer>().Render(camera, transformWire15, LightSpaceViewProjection);
			}

			if (wireEnt16.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(0);
				wireEnt16.Get<MeshRenderer>().Render(camera, transformWire16, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt16.Get<MeshRenderer>().Render(camera, transformWire16, LightSpaceViewProjection);
			}

			if (wireEnt17.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(0);
				wireEnt17.Get<MeshRenderer>().Render(camera, transformWire17, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt17.Get<MeshRenderer>().Render(camera, transformWire17, LightSpaceViewProjection);
			}

			if (wireEnt18.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(0);
				wireEnt18.Get<MeshRenderer>().Render(camera, transformWire18, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt18.Get<MeshRenderer>().Render(camera, transformWire18, LightSpaceViewProjection);
			}

			if (wireEnt19.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(0);
				wireEnt19.Get<MeshRenderer>().Render(camera, transformWire19, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt19.Get<MeshRenderer>().Render(camera, transformWire19, LightSpaceViewProjection);
			}

			if (wireEnt20.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(0);
				wireEnt20.Get<MeshRenderer>().Render(camera, transformWire20, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt20.Get<MeshRenderer>().Render(camera, transformWire20, LightSpaceViewProjection);
			}

			if (wireEnt21.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(0);
				wireEnt21.Get<MeshRenderer>().Render(camera, transformWire21, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt21.Get<MeshRenderer>().Render(camera, transformWire21, LightSpaceViewProjection);
			}

			if (wireEnt22.Get<Wire>().GetIsPowered())
			{
				wireMatOn.Albedo->Bind(0);
				wireEnt22.Get<MeshRenderer>().Render(camera, transformWire22, LightSpaceViewProjection);
			}
			else
			{
				wireMat.Albedo->Bind(0);
				wireEnt22.Get<MeshRenderer>().Render(camera, transformWire22, LightSpaceViewProjection);
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

			//Walls
			shader->SetUniform("s_Diffuse", 2);
			labWallMat.Albedo->Bind(2);
			leftEnt.Get<MeshRenderer>().Render(camera, transformLeft, LightSpaceViewProjection);
			rightEnt.Get<MeshRenderer>().Render(camera, transformRight, LightSpaceViewProjection);
			backEnt.Get<MeshRenderer>().Render(camera, transformBack, LightSpaceViewProjection);

			//Floor
			shader->SetUniform("s_Diffuse", 3);
			labFloorMat.Albedo->Bind(3);
			floorEnt.Get<MeshRenderer>().Render(camera, transformGround, LightSpaceViewProjection);

			//And-Gate
			shader->SetUniform("s_Diffuse", 4);
			andMat.Albedo->Bind(4);
			andEnt.Get<MeshRenderer>().Render(camera, transformAnd, LightSpaceViewProjection);
			andEnt2.Get<MeshRenderer>().Render(camera, transformAnd2, LightSpaceViewProjection);
			andEnt3.Get<MeshRenderer>().Render(camera, transformAnd3, LightSpaceViewProjection);
			andEnt4.Get<MeshRenderer>().Render(camera, transformAnd4, LightSpaceViewProjection);
			andEnt5.Get<MeshRenderer>().Render(camera, transformAnd5, LightSpaceViewProjection);

			//Or-Gate
			shader->SetUniform("s_Diffuse", 5);
			orMat.Albedo->Bind(5);
			orEnt.Get<MeshRenderer>().Render(camera, transformOr, LightSpaceViewProjection);
			orEnt2.Get<MeshRenderer>().Render(camera, transformOr2, LightSpaceViewProjection);
			orEnt3.Get<MeshRenderer>().Render(camera, transformOr3, LightSpaceViewProjection);

			//Xor-Gates
			shader->SetUniform("s_Diffuse", 6);
			xorMat.Albedo->Bind(6);
			xorEnt.Get<MeshRenderer>().Render(camera, transformXor, LightSpaceViewProjection);
			xorEnt2.Get<MeshRenderer>().Render(camera, transformXor2, LightSpaceViewProjection);
			xorEnt4.Get<MeshRenderer>().Render(camera, transformXor4, LightSpaceViewProjection);

			//Nor-Gates
			shader->SetUniform("s_Diffuse", 7);
			norMat.Albedo->Bind(7);
			norEnt.Get<MeshRenderer>().Render(camera, transformNor, LightSpaceViewProjection);
			shadowBuffer->UnbindTexture(30);

			//XNor-Gates
			shader->SetUniform("s_Diffuse", 8);
			xnorMat.Albedo->Bind(8);
			xnorEnt.Get<MeshRenderer>().Render(camera, transformXNor, LightSpaceViewProjection);
			xnorEnt2.Get<MeshRenderer>().Render(camera, transformXNor2, LightSpaceViewProjection);
			shadowBuffer->UnbindTexture(30);

			//Vents
			shader->SetUniform("s_Diffuse", 9);
			ventMat.Albedo->Bind(9);
			ventEnt.Get<MeshRenderer>().Render(camera, transformVent, LightSpaceViewProjection);
			ventEnt2.Get<MeshRenderer>().Render(camera, transformVent2, LightSpaceViewProjection);
			ventEnt3.Get<MeshRenderer>().Render(camera, transformVent3, LightSpaceViewProjection);
			ventEnt4.Get<MeshRenderer>().Render(camera, transformVent4, LightSpaceViewProjection);

			//Panels
			shader->SetUniform("s_Diffuse", 10);
			panelMat.Albedo->Bind(10);
			panelEnt.Get<MeshRenderer>().Render(camera, transformPanel, LightSpaceViewProjection);
			panelEnt2.Get<MeshRenderer>().Render(camera, transformPanel2, LightSpaceViewProjection);

			//Table
			shader->SetUniform("s_Diffuse", 11);
			tableMat.Albedo->Bind(11);
			tableEnt.Get<MeshRenderer>().Render(camera, transformTable, LightSpaceViewProjection);
			tableEnt2.Get<MeshRenderer>().Render(camera, transformTable2, LightSpaceViewProjection);

			//Shelf Pipes
			shader->SetUniform("s_Diffuse", 12);
			shelfPipeMat.Albedo->Bind(12);
			shelfPipeEnt.Get<MeshRenderer>().Render(camera, transformShelfPipe, LightSpaceViewProjection);
			shelfPipeEnt2.Get<MeshRenderer>().Render(camera, transformShelfPipe2, LightSpaceViewProjection);
			shelfPipeEnt3.Get<MeshRenderer>().Render(camera, transformShelfPipe3, LightSpaceViewProjection);
			shelfPipeEnt4.Get<MeshRenderer>().Render(camera, transformShelfPipe4, LightSpaceViewProjection);
			shelfPipeEnt5.Get<MeshRenderer>().Render(camera, transformShelfPipe5, LightSpaceViewProjection);
			shelfPipeEnt6.Get<MeshRenderer>().Render(camera, transformShelfPipe6, LightSpaceViewProjection);
			shelfPipeEnt7.Get<MeshRenderer>().Render(camera, transformShelfPipe7, LightSpaceViewProjection);
			shelfPipeEnt8.Get<MeshRenderer>().Render(camera, transformShelfPipe8, LightSpaceViewProjection);

			untexturedShader->Bind();
			shadowBuffer->BindDepthAsTexture(30);

			if ((playerTrans.GetPositionX() > -3.0f && playerTrans.GetPositionX() < 3.0f
					&& playerTrans.GetPositionZ() > 27.0f && playerTrans.GetPositionZ() < 33.0f)
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
					&& playerTrans.GetPositionZ() - buttonTrans4.GetPositionZ() > -3.0f)
				|| (playerTrans.GetPositionX() - buttonTrans5.GetPositionX() < 3.0f
					&& playerTrans.GetPositionX() - buttonTrans5.GetPositionX() > -3.0f
					&& playerTrans.GetPositionZ() - buttonTrans5.GetPositionZ() < 3.0f
					&& playerTrans.GetPositionZ() - buttonTrans5.GetPositionZ() > -3.0f)
				|| (playerTrans.GetPositionX() - buttonTrans6.GetPositionX() < 3.0f
					&& playerTrans.GetPositionX() - buttonTrans6.GetPositionX() > -3.0f
					&& playerTrans.GetPositionZ() - buttonTrans6.GetPositionZ() < 3.0f
					&& playerTrans.GetPositionZ() - buttonTrans6.GetPositionZ() > -3.0f)
				|| (playerTrans.GetPositionX() - buttonTrans7.GetPositionX() < 3.0f
					&& playerTrans.GetPositionX() - buttonTrans7.GetPositionX() > -3.0f
					&& playerTrans.GetPositionZ() - buttonTrans7.GetPositionZ() < 3.0f
					&& playerTrans.GetPositionZ() - buttonTrans7.GetPositionZ() > -3.0f)
				|| (playerTrans.GetPositionX() - buttonTrans8.GetPositionX() < 3.0f
					&& playerTrans.GetPositionX() - buttonTrans8.GetPositionX() > -3.0f
					&& playerTrans.GetPositionZ() - buttonTrans8.GetPositionZ() < 3.0f
					&& playerTrans.GetPositionZ() - buttonTrans8.GetPositionZ() > -3.0f))
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

			animShader->SetUniform("s_Diffuse", 1);
			clearMat.Albedo->Bind(1);
			doorEnt.Get<MorphRenderer>().Render(camera, transformDoor, LightSpaceViewProjection);
			clearMat.Albedo->Unbind(1);

			animShader->SetUniform("s_Diffuse", 2);
			clearMat.Albedo->Bind(2);
			buttonEnt.Get<MorphRenderer>().Render(camera, transformButton, LightSpaceViewProjection);
			buttonEnt2.Get<MorphRenderer>().Render(camera, transformButton2, LightSpaceViewProjection);
			buttonEnt3.Get<MorphRenderer>().Render(camera, transformButton3, LightSpaceViewProjection);
			buttonEnt4.Get<MorphRenderer>().Render(camera, transformButton4, LightSpaceViewProjection);
			buttonEnt5.Get<MorphRenderer>().Render(camera, transformButton5, LightSpaceViewProjection);
			buttonEnt6.Get<MorphRenderer>().Render(camera, transformButton6, LightSpaceViewProjection);
			buttonEnt7.Get<MorphRenderer>().Render(camera, transformButton7, LightSpaceViewProjection);
			buttonEnt8.Get<MorphRenderer>().Render(camera, transformButton8, LightSpaceViewProjection);
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
			floorEnt.Get<MeshRenderer>().Render(camera, transformGround, LightSpaceViewProjection);
			leftEnt.Get<MeshRenderer>().Render(camera, transformLeft, LightSpaceViewProjection);
			rightEnt.Get<MeshRenderer>().Render(camera, transformRight, LightSpaceViewProjection);
			backEnt.Get<MeshRenderer>().Render(camera, transformBack, LightSpaceViewProjection);
			wireEnt.Get<MeshRenderer>().Render(camera, transformWire, LightSpaceViewProjection);
			wireEnt2.Get<MeshRenderer>().Render(camera, transformWire2, LightSpaceViewProjection);
			wireEnt3.Get<MeshRenderer>().Render(camera, transformWire3, LightSpaceViewProjection);
			wireEnt4.Get<MeshRenderer>().Render(camera, transformWire4, LightSpaceViewProjection);
			wireEnt5.Get<MeshRenderer>().Render(camera, transformWire5, LightSpaceViewProjection);
			wireEnt6.Get<MeshRenderer>().Render(camera, transformWire6, LightSpaceViewProjection);
			wireEnt7.Get<MeshRenderer>().Render(camera, transformWire7, LightSpaceViewProjection);
			wireEnt8.Get<MeshRenderer>().Render(camera, transformWire8, LightSpaceViewProjection);
			wireEnt9.Get<MeshRenderer>().Render(camera, transformWire9, LightSpaceViewProjection);
			wireEnt10.Get<MeshRenderer>().Render(camera, transformWire10, LightSpaceViewProjection);
			wireEnt11.Get<MeshRenderer>().Render(camera, transformWire11, LightSpaceViewProjection);
			wireEnt12.Get<MeshRenderer>().Render(camera, transformWire12, LightSpaceViewProjection);
			wireEnt13.Get<MeshRenderer>().Render(camera, transformWire13, LightSpaceViewProjection);
			wireEnt14.Get<MeshRenderer>().Render(camera, transformWire14, LightSpaceViewProjection);
			wireEnt15.Get<MeshRenderer>().Render(camera, transformWire15, LightSpaceViewProjection);
			wireEnt16.Get<MeshRenderer>().Render(camera, transformWire16, LightSpaceViewProjection);
			wireEnt17.Get<MeshRenderer>().Render(camera, transformWire17, LightSpaceViewProjection);
			wireEnt18.Get<MeshRenderer>().Render(camera, transformWire18, LightSpaceViewProjection);
			coilEnt.Get<MeshRenderer>().Render(camera, transformCoil, LightSpaceViewProjection);
			andEnt.Get<MeshRenderer>().Render(camera, transformAnd, LightSpaceViewProjection);
			andEnt2.Get<MeshRenderer>().Render(camera, transformAnd2, LightSpaceViewProjection);
			andEnt3.Get<MeshRenderer>().Render(camera, transformAnd3, LightSpaceViewProjection);
			andEnt4.Get<MeshRenderer>().Render(camera, transformAnd4, LightSpaceViewProjection);
			andEnt5.Get<MeshRenderer>().Render(camera, transformAnd5, LightSpaceViewProjection);
			xorEnt.Get<MeshRenderer>().Render(camera, transformXor, LightSpaceViewProjection);
			xorEnt2.Get<MeshRenderer>().Render(camera, transformXor2, LightSpaceViewProjection);
			xorEnt4.Get<MeshRenderer>().Render(camera, transformXor4, LightSpaceViewProjection);
			orEnt.Get<MeshRenderer>().Render(camera, transformOr, LightSpaceViewProjection);
			orEnt2.Get<MeshRenderer>().Render(camera, transformOr2, LightSpaceViewProjection);
			orEnt3.Get<MeshRenderer>().Render(camera, transformOr3, LightSpaceViewProjection);
			norEnt.Get<MeshRenderer>().Render(camera, transformNor, LightSpaceViewProjection);
			xnorEnt.Get<MeshRenderer>().Render(camera, transformXNor, LightSpaceViewProjection);
			xnorEnt2.Get<MeshRenderer>().Render(camera, transformXNor2, LightSpaceViewProjection);
			ventEnt.Get<MeshRenderer>().Render(camera, transformVent, LightSpaceViewProjection);
			ventEnt2.Get<MeshRenderer>().Render(camera, transformVent2, LightSpaceViewProjection);
			ventEnt3.Get<MeshRenderer>().Render(camera, transformVent3, LightSpaceViewProjection);
			ventEnt4.Get<MeshRenderer>().Render(camera, transformVent4, LightSpaceViewProjection);
			panelEnt.Get<MeshRenderer>().Render(camera, transformPanel, LightSpaceViewProjection);
			panelEnt2.Get<MeshRenderer>().Render(camera, transformPanel2, LightSpaceViewProjection);
			tableEnt.Get<MeshRenderer>().Render(camera, transformTable, LightSpaceViewProjection);
			tableEnt2.Get<MeshRenderer>().Render(camera, transformTable2, LightSpaceViewProjection);
			shelfPipeEnt.Get<MeshRenderer>().Render(camera, transformShelfPipe, LightSpaceViewProjection);
			shelfPipeEnt2.Get<MeshRenderer>().Render(camera, transformShelfPipe2, LightSpaceViewProjection);
			shelfPipeEnt3.Get<MeshRenderer>().Render(camera, transformShelfPipe3, LightSpaceViewProjection);
			shelfPipeEnt4.Get<MeshRenderer>().Render(camera, transformShelfPipe4, LightSpaceViewProjection);
			shelfPipeEnt5.Get<MeshRenderer>().Render(camera, transformShelfPipe5, LightSpaceViewProjection);
			shelfPipeEnt6.Get<MeshRenderer>().Render(camera, transformShelfPipe6, LightSpaceViewProjection);
			shelfPipeEnt7.Get<MeshRenderer>().Render(camera, transformShelfPipe7, LightSpaceViewProjection);
			shelfPipeEnt8.Get<MeshRenderer>().Render(camera, transformShelfPipe8, LightSpaceViewProjection);
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

	//Collision Updates
	backEnt.Get<AABB>().Update();
	leftEnt.Get<AABB>().Update();
	rightEnt.Get<AABB>().Update();
	doorEnt.Get<AABB>().Update();
	andEnt.Get<AABB>().Update();
	andEnt2.Get<AABB>().Update();
	andEnt3.Get<AABB>().Update();
	andEnt4.Get<AABB>().Update();
	andEnt5.Get<AABB>().Update();
	orEnt.Get<AABB>().Update();
	orEnt2.Get<AABB>().Update();
	orEnt3.Get<AABB>().Update();
	xorEnt.Get<AABB>().Update();
	xorEnt2.Get<AABB>().Update();
	xorEnt4.Get<AABB>().Update();
	norEnt.Get<AABB>().Update();
	xnorEnt.Get<AABB>().Update();
	xnorEnt2.Get<AABB>().Update();
	coilEnt.Get<AABB>().Update();
	buttonEnt.Get<AABB>().Update();
	buttonEnt2.Get<AABB>().Update();
	buttonEnt3.Get<AABB>().Update();
	buttonEnt4.Get<AABB>().Update();
	buttonEnt5.Get<AABB>().Update();
	buttonEnt6.Get<AABB>().Update();
	buttonEnt7.Get<AABB>().Update();
	buttonEnt8.Get<AABB>().Update();
	tableEnt.Get<AABB>().Update();
	tableEnt2.Get<AABB>().Update();

	//Button Updates
	buttonEnt.Get<Lever>().Update();
	buttonEnt2.Get<Lever>().Update();
	buttonEnt3.Get<Lever>().Update();
	buttonEnt4.Get<Lever>().Update();
	buttonEnt5.Get<Lever>().Update();
	buttonEnt6.Get<Lever>().Update();
	buttonEnt7.Get<Lever>().Update();
	buttonEnt8.Get<Lever>().Update();

	//Wire Updates
	wireEnt.Get<Wire>().Update();
	wireEnt2.Get<Wire>().Update();
	wireEnt3.Get<Wire>().Update();
	wireEnt4.Get<Wire>().Update();
	wireEnt5.Get<Wire>().Update();
	wireEnt6.Get<Wire>().Update();
	wireEnt7.Get<Wire>().Update();
	wireEnt8.Get<Wire>().Update();
	wireEnt9.Get<Wire>().Update();
	wireEnt10.Get<Wire>().Update();
	wireEnt11.Get<Wire>().Update();
	wireEnt12.Get<Wire>().Update();
	wireEnt13.Get<Wire>().Update();
	wireEnt14.Get<Wire>().Update();
	wireEnt15.Get<Wire>().Update();
	wireEnt16.Get<Wire>().Update();
	wireEnt17.Get<Wire>().Update();
	wireEnt18.Get<Wire>().Update();
	wireEnt19.Get<Wire>().Update();
	wireEnt20.Get<Wire>().Update();
	wireEnt21.Get<Wire>().Update();
	wireEnt22.Get<Wire>().Update();

	//Gate Updates
	andEnt.Get<AndGate>().Update();
	orEnt.Get<OrGate>().Update();
	xorEnt.Get<XorGate>().Update();
	xorEnt2.Get<XorGate>().Update();
	xnorEnt.Get<XNorGate>().Update();
	andEnt2.Get<AndGate>().Update();
	orEnt2.Get<OrGate>().Update();
	xnorEnt2.Get<XNorGate>().Update();
	norEnt.Get<NorGate>().Update();
	andEnt3.Get<AndGate>().Update();
	orEnt3.Get<OrGate>().Update();
	xorEnt4.Get<XorGate>().Update();
	andEnt4.Get<AndGate>().Update();
	andEnt5.Get<AndGate>().Update();

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
		AudioEngine::Instance().GetEvent("XNOR Tablet").StopImmediately();
		showLevelComplete = true;
	}
}

void Level9::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}
