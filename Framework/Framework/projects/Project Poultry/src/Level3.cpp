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
	mainPlayer = Entity::Create();
	floorEnt = Entity::Create();
	leftEnt = Entity::Create();
	rightEnt = Entity::Create();
	backEnt = Entity::Create();
	buttonEnt = Entity::Create();
	buttonEnt2 = Entity::Create();
	buttonEnt3 = Entity::Create();
	wireEnt = Entity::Create();
	wireEnt2 = Entity::Create();
	wireEnt3 = Entity::Create();
	wireEnt4 = Entity::Create();
	wireEnt5 = Entity::Create();
	wireEnt6 = Entity::Create();
	wireEnt7 = Entity::Create();
	andEnt = Entity::Create();
	andEnt2 = Entity::Create();
	andEnt3 = Entity::Create();
	notEnt = Entity::Create();
	doorEnt = Entity::Create();
	coilEnt = Entity::Create();
	coilPowered = Entity::Create();
	wirePowered = Entity::Create();
	wirePowered2 = Entity::Create();
	wirePowered3 = Entity::Create();
	wirePowered4 = Entity::Create();
	wirePowered5 = Entity::Create();
	wirePowered6 = Entity::Create();
	wirePowered7 = Entity::Create();
	completeEnt = Entity::Create();
	FBO = Entity::Create();
	greyscaleEnt = Entity::Create();
	sepiaEnt = Entity::Create();
	colorCorrectEnt = Entity::Create();
	bloomEnt = Entity::Create();
	pauseEnt = Entity::Create();

	drumstick = ModelManager::FindMesh(drumFile);
	floor = ModelManager::FindMesh(floorFile);
	wall = ModelManager::FindMesh(wallFile);
	doorM = ModelManager::FindMesh(doorFile);
	buttonM = ModelManager::FindMesh(buttonFile);
	wireM1 = ModelManager::FindMesh(wire1File, glm::vec3(1.0f, 0.0f, 0.0f));
	wireM2 = ModelManager::FindMesh(wire2File, glm::vec3(1.0f, 0.0f, 0.0f));
	wireM3 = ModelManager::FindMesh(wire3File, glm::vec3(1.0f, 0.0f, 0.0f));
	wireM4 = ModelManager::FindMesh(wire4File, glm::vec3(1.0f, 0.0f, 0.0f));
	wireM5 = ModelManager::FindMesh(wire5File, glm::vec3(1.0f, 0.0f, 0.0f));
	wireM6 = ModelManager::FindMesh(wire6File, glm::vec3(1.0f, 0.0f, 0.0f));
	wireM7 = ModelManager::FindMesh(wire7File, glm::vec3(1.0f, 0.0f, 0.0f));
	wire1Power = ModelManager::FindMesh(wire1File, glm::vec3(0.0f, 1.0f, 0.0f));
	wire2Power = ModelManager::FindMesh(wire2File, glm::vec3(0.0f, 1.0f, 0.0f));
	wire3Power = ModelManager::FindMesh(wire3File, glm::vec3(0.0f, 1.0f, 0.0f));
	wire4Power = ModelManager::FindMesh(wire4File, glm::vec3(0.0f, 1.0f, 0.0f));
	wire5Power = ModelManager::FindMesh(wire5File, glm::vec3(0.0f, 1.0f, 0.0f));
	wire6Power = ModelManager::FindMesh(wire6File, glm::vec3(0.0f, 1.0f, 0.0f));
	wire7Power = ModelManager::FindMesh(wire7File, glm::vec3(0.0f, 1.0f, 0.0f));
	gate = ModelManager::FindMesh(gateFile, glm::vec3(0.0f, 0.0f, 1.0f));
	not = ModelManager::FindMesh(notFile, glm::vec3(1.0f, 0.0f, 1.0f));
	coil = ModelManager::FindMesh(coilFile, glm::vec3(1.0f, 0.0f, 0.0f));
	coilP = ModelManager::FindMesh(coilFile, glm::vec3(0.0f, 1.0f, 0.0f));

	door1 = ModelManager::FindMesh(doorFile1);
	door2 = ModelManager::FindMesh(doorFile2);
	door3 = ModelManager::FindMesh(doorFile3);
	door4 = ModelManager::FindMesh(doorFile4);
	door5 = ModelManager::FindMesh(doorFile5);
	door6 = ModelManager::FindMesh(doorFile6);
	door7 = ModelManager::FindMesh(doorFile7);
	door8 = ModelManager::FindMesh(doorFile8);
	door9 = ModelManager::FindMesh(doorFile9);
	door10 = ModelManager::FindMesh(doorFile10);

	walk1 = ModelManager::FindMesh(walkFile1);
	walk2 = ModelManager::FindMesh(walkFile2);
	walk3 = ModelManager::FindMesh(walkFile3);
	walk4 = ModelManager::FindMesh(walkFile4);
	walk5 = ModelManager::FindMesh(walkFile5);
	walk6 = ModelManager::FindMesh(walkFile6);
	walk7 = ModelManager::FindMesh(walkFile7);
	walk8 = ModelManager::FindMesh(walkFile8);
	walk9 = ModelManager::FindMesh(walkFile9);
	walk10 = ModelManager::FindMesh(walkFile10);
	walk11 = ModelManager::FindMesh(walkFile11);
	walk12 = ModelManager::FindMesh(walkFile12);
	walk13 = ModelManager::FindMesh(walkFile13);
	walk14 = ModelManager::FindMesh(walkFile14);
}

void Level3::InitScene()
{
	Application::SetClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	scene = new entt::registry();

	Entity::SetReg(scene);

	float distance = glm::distance(point2, point1);

	totalTime = distance / speed;

	glm::vec3 lightPos = glm::vec3(0.0f, 9.5f, -45.0f);
	glm::vec3 lightDir = glm::vec3(0.0f, -1.0f, 0.0f);
	glm::vec3 lightCol = glm::vec3(1.f, 1.f, 1.f);
	float     lightAmbientPow = 0.05f;
	float	  pauseAmbientPow = 0.25f;
	float     lightSpecularPow = 1.0f;
	float     lightSpecularPow2 = 0.2f;
	glm::vec3 ambientCol = glm::vec3(1.0f);
	float     ambientPow = 0.1f;
	float     shininess = 16.0f;

#pragma region Shader Stuff

	animShader = Shader::Create();
	animShader->LoadShaderPartFromFile("Shaders/morph_shader.glsl", GL_VERTEX_SHADER);
	animShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	animShader->Link();
	SetShaderValues(animShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, ambientCol, ambientPow, shininess);

	shader = Shader::Create();
	shader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	shader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	shader->Link();
	SetShaderValues(shader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, ambientCol, ambientPow, shininess);

	untexturedShader = Shader::Create();
	untexturedShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	untexturedShader->LoadShaderPartFromFile("Shaders/frag_untextured.glsl", GL_FRAGMENT_SHADER);
	untexturedShader->Link();
	SetShaderValues(untexturedShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, ambientCol, ambientPow, shininess);

	pauseShader = Shader::Create();
	pauseShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	pauseShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	pauseShader->Link();
	SetShaderValues(pauseShader, lightPos, lightDir, lightCol, pauseAmbientPow, lightSpecularPow, ambientCol, pauseAmbientPow, shininess);
#pragma endregion

#pragma region Texture Stuff
	Texture2D::sptr diffuseButton = Texture2D::LoadFromFile("Textures/ButtonTexture.png");
	Texture2D::sptr diffuseDrum = Texture2D::LoadFromFile("Textures/DrumstickTexture.png");
	Texture2D::sptr diffuseDoor = Texture2D::LoadFromFile("Textures/DoorTexture.png");
	Texture2D::sptr diffuseFloor = Texture2D::LoadFromFile("Textures/FloorTexture.jpg");
	Texture2D::sptr diffuseWall = Texture2D::LoadFromFile("Textures/WallTexture.jpg");
	Texture2D::sptr diffuseWire = Texture2D::LoadFromFile("Textures/WireTexture.png");
	Texture2D::sptr diffusePart = Texture2D::LoadFromFile("Textures/Particle.png");
	Texture2D::sptr diffuseComplete = Texture2D::LoadFromFile("Textures/LevelComplete.png");
	Texture2D::sptr diffuseAnd = Texture2D::LoadFromFile("Textures/AndGate.png");
	Texture2D::sptr diffusePause = Texture2D::LoadFromFile("Textures/PauseMenu.png");

	Texture2DDescription desc = Texture2DDescription();
	desc.Width = 1;
	desc.Height = 1;
	desc.Format = InternalFormat::RGB8;
	Texture2D::sptr texture2 = Texture2D::Create(desc);
	texture2->Clear();

	buttonMat.Albedo = diffuseButton;
	drumstickMat.Albedo = diffuseDrum;
	doorMat.Albedo = diffuseDoor;
	floorMat.Albedo = diffuseFloor;
	wallMat.Albedo = diffuseWall;
	wireMat.Albedo = diffuseWire;
	partMat.Albedo = diffusePart;
	completeMat.Albedo = diffuseComplete;
	clearMat.Albedo = texture2;
	gateMat.Albedo = diffuseAnd;
	pauseMat.Albedo = diffusePause;

#pragma endregion

	//Transforms
	auto& playerTrans = mainPlayer.Add<Transform>();
	playerTrans.SetPosition(glm::vec3(0.0f, 1.0f, 30.0f));
	playerTrans.SetRotationY(0.0f);

	auto& groundTrans = floorEnt.Add<Transform>();

	auto& leftTrans = leftEnt.Add<Transform>();

	auto& rightTrans = rightEnt.Add<Transform>();

	auto& backTrans = backEnt.Add<Transform>();

	auto& wireTrans = wireEnt.Add<Transform>();
	wireTrans.SetPosition(glm::vec3(-230.5f, 0.5f, -3.0f));

	auto& wireTrans2 = wireEnt2.Add<Transform>();
	wireTrans2.SetPosition(glm::vec3(-230.5f, 0.5f, -3.5f));

	auto& wireTrans3 = wireEnt3.Add<Transform>();
	wireTrans3.SetPosition(glm::vec3(-230.5f, 0.5f, -3.0f));

	auto& wireTrans4 = wireEnt4.Add<Transform>();
	wireTrans4.SetPosition(glm::vec3(-230.5f, 0.5f, -3.0f));

	auto& wireTrans5 = wireEnt5.Add<Transform>();
	wireTrans5.SetPosition(glm::vec3(-230.5f, 0.5f, -3.0f));

	auto& wireTrans6 = wireEnt6.Add<Transform>();
	wireTrans6.SetPosition(glm::vec3(-230.5f, 0.5f, -3.0f));

	auto& wireTrans7 = wireEnt7.Add<Transform>();
	wireTrans7.SetPosition(glm::vec3(-230.5f, 0.5f, -3.0f));

	auto& buttonTrans = buttonEnt.Add<Transform>();
	buttonTrans.SetPosition(glm::vec3(-32.7f, -2.0f, 28.5f));

	auto& buttonTrans2 = buttonEnt2.Add<Transform>();
	buttonTrans2.SetPosition(glm::vec3(0.0f, -2.0f, 33.0f));

	auto& buttonTrans3 = buttonEnt3.Add<Transform>();
	buttonTrans3.SetPosition(glm::vec3(32.7f, -2.0f, 28.5f));

	auto& doorTrans = doorEnt.Add<Transform>();
	doorTrans.SetPosition(glm::vec3(0.0f, -1.0f, -46.0f));
	doorTrans.SetScale(glm::vec3(1.5f));

	auto& gateTrans = andEnt.Add<Transform>();
	gateTrans.SetPosition(glm::vec3(-22.0f, 1.0f, 5.0f));
	gateTrans.SetRotationY(-90.0f);

	auto& gateTrans2 = andEnt2.Add<Transform>();
	gateTrans2.SetPosition(glm::vec3(22.0f, 1.0f, 5.0f));
	gateTrans2.SetRotationY(-90.0f);

	auto& gateTrans3 = andEnt3.Add<Transform>();
	gateTrans3.SetPosition(glm::vec3(0.0f, 1.0f, -12.0f));
	gateTrans3.SetRotationY(-90.0f);

	auto& notTrans = notEnt.Add<Transform>();
	notTrans.SetPosition(glm::vec3(0.0f, 0.5f, 13.0f));

	auto& coilTrans = coilEnt.Add<Transform>();
	coilTrans.SetPosition(glm::vec3(-17.0f, 2.0f, -34.0f));
	coilTrans.SetScale(glm::vec3(3.0f));

	auto& completeTrans = completeEnt.Add<Transform>();
	completeTrans.SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	completeTrans.SetScale(glm::vec3(0.22f));

	auto& pauseTrans = pauseEnt.Add<Transform>();
	pauseTrans.SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	pauseTrans.SetScale(glm::vec3(0.22f));

	//AABB
	auto& leftCol = leftEnt.Add<AABB>(leftEnt, mainPlayer);
	auto& rightCol = rightEnt.Add<AABB>(rightEnt, mainPlayer);
	auto& backCol = backEnt.Add<AABB>(backEnt, mainPlayer);
	auto& gateCol = andEnt.Add<AABB>(andEnt, mainPlayer);
	auto& gateCol2 = andEnt2.Add<AABB>(andEnt2, mainPlayer);
	auto& gateCol3 = andEnt3.Add<AABB>(andEnt3, mainPlayer);
	auto& gateCol4 = notEnt.Add<AABB>(notEnt, mainPlayer);
	auto& coilCol = coilEnt.Add<AABB>(coilEnt, mainPlayer);
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

	auto& playerMesh = mainPlayer.Add<MorphRenderer>(mainPlayer, *drumstick, animShader);
	auto& floorMesh = floorEnt.Add<MeshRenderer>(floorEnt, *floor, shader);
	auto& leftMesh = leftEnt.Add<MeshRenderer>(leftEnt, *wall, shader);
	auto& rightMesh = rightEnt.Add<MeshRenderer>(rightEnt, *wall, shader);
	auto& backMesh = backEnt.Add<MeshRenderer>(backEnt, *wall, shader);
	auto& notMesh = notEnt.Add<MeshRenderer>(notEnt, *not, untexturedShader);
	auto& gateMesh = andEnt.Add<MeshRenderer>(andEnt, *gate, untexturedShader);
	auto& gateMesh2 = andEnt2.Add<MeshRenderer>(andEnt2, *gate, untexturedShader);
	auto& gateMesh3 = andEnt3.Add<MeshRenderer>(andEnt3, *gate, untexturedShader);
	auto& buttonMesh = buttonEnt.Add<MeshRenderer>(buttonEnt, *buttonM, shader);
	auto& buttonMesh2 = buttonEnt2.Add<MeshRenderer>(buttonEnt2, *buttonM, shader);
	auto& buttonMesh3 = buttonEnt3.Add<MeshRenderer>(buttonEnt3, *buttonM, shader);
	auto& wireMesh = wireEnt.Add<MeshRenderer>(wireEnt, *wireM1, shader);
	auto& wireMesh2 = wireEnt2.Add<MeshRenderer>(wireEnt2, *wireM2, shader);
	auto& wireMesh3 = wireEnt3.Add<MeshRenderer>(wireEnt3, *wireM3, shader);
	auto& wireMesh4 = wireEnt4.Add<MeshRenderer>(wireEnt4, *wireM4, shader);
	auto& wireMesh5 = wireEnt5.Add<MeshRenderer>(wireEnt5, *wireM5, shader);
	auto& wireMesh6 = wireEnt6.Add<MeshRenderer>(wireEnt6, *wireM6, shader);
	auto& wireMesh7 = wireEnt7.Add<MeshRenderer>(wireEnt7, *wireM7, shader);
	auto& wireMeshP = wirePowered.Add<MeshRenderer>(wirePowered, *wire1Power, shader);
	auto& wireMeshP2 = wirePowered2.Add<MeshRenderer>(wirePowered2, *wire2Power, shader);
	auto& wireMeshP3 = wirePowered3.Add<MeshRenderer>(wirePowered3, *wire3Power, shader);
	auto& wireMeshP4 = wirePowered4.Add<MeshRenderer>(wirePowered4, *wire4Power, shader);
	auto& wireMeshP5 = wirePowered5.Add<MeshRenderer>(wirePowered5, *wire5Power, shader);
	auto& wireMeshP6 = wirePowered6.Add<MeshRenderer>(wirePowered6, *wire6Power, shader);
	auto& wireMeshP7 = wirePowered7.Add<MeshRenderer>(wirePowered7, *wire7Power, shader);
	auto& doorMesh = doorEnt.Add<MorphRenderer>(doorEnt, *doorM, animShader);
	auto& coilMesh = coilEnt.Add<MeshRenderer>(coilEnt, *coil, untexturedShader);
	auto& coilMeshP = coilPowered.Add<MeshRenderer>(coilPowered, *coilP, untexturedShader);
	auto& completeMesh = completeEnt.Add<MeshRenderer>(completeEnt, *floor, shader);
	auto& pauseMesh = pauseEnt.Add<MeshRenderer>(pauseEnt, *floor, pauseShader);

	auto& doorAnimator = doorEnt.Add<MorphAnimation>(doorEnt);
	doorAnimator.SetTime(0.2f);
	doorAnimator.SetFrames(doorFrames);
	doorAnimator.SetLoop(false);

	auto& walkAnimator = mainPlayer.Add<MorphAnimation>(mainPlayer);
	walkAnimator.SetTime(0.05f);
	walkAnimator.SetFrames(walkFrames);

	auto& camera = camEnt.Add<Camera>();

	camera.SetPosition(glm::vec3(0, 15, mainPlayer.Get<Transform>().GetPositionZ() + 12)); // Set initial position
	camera.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
	camera.LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camera.SetFovDegrees(90.0f); // Set an initial FOV

	auto& orthoCam = uiCamEnt.Add<Camera>();
	orthoCam.SetPosition(glm::vec3(0, 10, 0)); // Set initial position
	orthoCam.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
	orthoCam.LookAt(glm::vec3(0.0f)); // Look at center of the screen
	orthoCam.SetFovDegrees(90.0f); // Set an initial FOV

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

	auto bloomEffect = &bloomEnt.Add<Bloom>();
	bloomEffect->Init(width, height);

	effects.push_back(bloomEffect);

	auto colorCorrectEffect = &colorCorrectEnt.Add<ColorCorrect>();
	colorCorrectEffect->Init(width, height);

	effects.push_back(colorCorrectEffect);

	points.push_back(glm::vec3(3.0f, 15.0f, 6.0f));
	points.push_back(glm::vec3(-3.0f, 15.0f, 6.0f));
	points.push_back(glm::vec3(-3.0f, 15.0f, 0.0f));
	points.push_back(glm::vec3(3.0f, 15.0f, 0.0f));
	
	segmentTime = 1.0f;
	
	if (points.size() > 0)
		currentPos = points[0];
	
	StartSegment(0);

}

void Level3::Update(float dt)
{

	time += dt;
	animShader->SetUniform("u_Time", time);
	shader->SetUniform("u_Time", time);
	pauseShader->SetUniform("u_Time", time);
	untexturedShader->SetUniform("u_Time", time);

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

	//Transforms
	auto& playerTrans = mainPlayer.Get<Transform>();
	auto& groundTrans = floorEnt.Get<Transform>();
	auto& leftTrans = leftEnt.Get<Transform>();
	auto& rightTrans = rightEnt.Get<Transform>();
	auto& backTrans = backEnt.Get<Transform>();
	auto& doorTrans = doorEnt.Get<Transform>();
	auto& buttonTrans = buttonEnt.Get<Transform>();
	auto& buttonTrans2 = buttonEnt2.Get<Transform>();
	auto& buttonTrans3 = buttonEnt3.Get<Transform>();
	auto& wireTrans = wireEnt.Get<Transform>();
	auto& wireTrans2 = wireEnt2.Get<Transform>();
	auto& wireTrans3 = wireEnt3.Get<Transform>();
	auto& wireTrans4 = wireEnt4.Get<Transform>();
	auto& wireTrans5 = wireEnt5.Get<Transform>();
	auto& wireTrans6 = wireEnt6.Get<Transform>();
	auto& wireTrans7 = wireEnt7.Get<Transform>();
	auto& notTrans = notEnt.Get<Transform>();
	auto& gateTrans = andEnt.Get<Transform>();
	auto& gateTrans2 = andEnt2.Get<Transform>();
	auto& gateTrans3 = andEnt3.Get<Transform>();
	auto& coilTrans = coilEnt.Get<Transform>();
	auto& completeTrans = completeEnt.Get<Transform>();
	auto& pauseTrans = pauseEnt.Get<Transform>();

	groundTrans.SetScale(glm::vec3(1.2f));

	backTrans.SetPositionZ(-49.0f);
	backTrans.SetPositionY(9.0f);
	backTrans.SetScale(glm::vec3(1.2f));

	leftTrans.SetPositionX(-49.0f);
	leftTrans.SetRotationY(90.0f);
	leftTrans.SetPositionY(9.0f);
	leftTrans.SetScale(glm::vec3(1.2f));

	rightTrans.SetPositionX(49.0f);
	rightTrans.SetRotationY(90.0f);
	rightTrans.SetPositionY(9.0f);
	rightTrans.SetScale(glm::vec3(1.2f));

	auto& camera = camEnt.Get<Camera>();
	auto& orthoCam = uiCamEnt.Get<Camera>();

	auto& meshMain = mainPlayer.Get<MorphRenderer>();
	auto& groundMesh = floorEnt.Get<MeshRenderer>();
	auto& leftMesh = leftEnt.Get<MeshRenderer>();
	auto& rightMesh = rightEnt.Get<MeshRenderer>();
	auto& backMesh = backEnt.Get<MeshRenderer>();
	auto& doorMesh = doorEnt.Get<MorphRenderer>();
	auto& buttonMesh = buttonEnt.Get<MeshRenderer>();
	auto& buttonMesh2 = buttonEnt2.Get<MeshRenderer>();
	auto& buttonMesh3 = buttonEnt3.Get<MeshRenderer>();
	auto& wireMesh = wireEnt.Get<MeshRenderer>();
	auto& wireMesh2 = wireEnt2.Get<MeshRenderer>();
	auto& wireMesh3 = wireEnt3.Get<MeshRenderer>();
	auto& wireMesh4 = wireEnt4.Get<MeshRenderer>();
	auto& wireMesh5 = wireEnt5.Get<MeshRenderer>();
	auto& wireMesh6 = wireEnt6.Get<MeshRenderer>();
	auto& wireMesh7 = wireEnt7.Get<MeshRenderer>();
	auto& wireMeshP = wirePowered.Get<MeshRenderer>();
	auto& wireMeshP2 = wirePowered2.Get<MeshRenderer>();
	auto& wireMeshP3 = wirePowered3.Get<MeshRenderer>();
	auto& wireMeshP4 = wirePowered4.Get<MeshRenderer>();
	auto& wireMeshP5 = wirePowered5.Get<MeshRenderer>();
	auto& wireMeshP6 = wirePowered6.Get<MeshRenderer>();
	auto& wireMeshP7 = wirePowered7.Get<MeshRenderer>();
	auto& notMesh = notEnt.Get<MeshRenderer>();
	auto& gateMesh = andEnt.Get<MeshRenderer>();
	auto& gateMesh2 = andEnt2.Get<MeshRenderer>();
	auto& gateMesh3 = andEnt3.Get<MeshRenderer>();
	auto& coilMesh = coilEnt.Get<MeshRenderer>();
	auto& coilMeshP = coilPowered.Get<MeshRenderer>();
	auto& completeMesh = completeEnt.Get<MeshRenderer>();
	auto& pauseMesh = pauseEnt.Get<MeshRenderer>();

	camera.LookAt(glm::vec3(playerTrans.GetPositionX(), playerTrans.GetPositionY() + 5.0f, playerTrans.GetPositionZ()));

	glm::mat4 transform = playerTrans.GetModelMatrix();
	glm::mat4 transformGround = groundTrans.GetModelMatrix();
	glm::mat4 transformLeft = leftTrans.GetModelMatrix();
	glm::mat4 transformRight = rightTrans.GetModelMatrix();
	glm::mat4 transformBack = backTrans.GetModelMatrix();
	glm::mat4 transformDoor = doorTrans.GetModelMatrix();
	glm::mat4 transformButton = buttonTrans.GetModelMatrix();
	glm::mat4 transformButton2 = buttonTrans2.GetModelMatrix();
	glm::mat4 transformButton3 = buttonTrans3.GetModelMatrix();
	glm::mat4 transformWire = wireTrans.GetModelMatrix();
	glm::mat4 transformWire2 = wireTrans2.GetModelMatrix();
	glm::mat4 transformWire3 = wireTrans3.GetModelMatrix();
	glm::mat4 transformWire4 = wireTrans4.GetModelMatrix();
	glm::mat4 transformWire5 = wireTrans5.GetModelMatrix();
	glm::mat4 transformWire6 = wireTrans6.GetModelMatrix();
	glm::mat4 transformWire7 = wireTrans7.GetModelMatrix();
	glm::mat4 transformNot = notTrans.GetModelMatrix();
	glm::mat4 transformGate = gateTrans.GetModelMatrix();
	glm::mat4 transformGate2 = gateTrans2.GetModelMatrix();
	glm::mat4 transformGate3 = gateTrans3.GetModelMatrix();
	glm::mat4 transformCoil = coilTrans.GetModelMatrix();
	glm::mat4 transformComplete = completeTrans.GetModelMatrix();
	glm::mat4 transformPause = pauseTrans.GetModelMatrix();

	if (playerTrans.GetPositionX() - buttonTrans.GetPositionX() < 2.0f && playerTrans.GetPositionX() - buttonTrans.GetPositionX() > -2.0f
		&& playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() > -3.0f)
		button1Watch.Poll(window);

	if (playerTrans.GetPositionX() - buttonTrans2.GetPositionX() < 2.0f && playerTrans.GetPositionX() - buttonTrans2.GetPositionX() > -2.0f
		&& playerTrans.GetPositionZ() - buttonTrans2.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans2.GetPositionZ() > -3.0f)
		button2Watch.Poll(window);

	if (playerTrans.GetPositionX() - buttonTrans3.GetPositionX() < 2.0f && playerTrans.GetPositionX() - buttonTrans3.GetPositionX() > -2.0f
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
		Input::MovePlayer(window, mainPlayer, camEnt, dt, camFar, camClose);
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

	if (!showLevelComplete && !isPaused)
	{
		Input::MoveCamera(window, camEnt, dt);
	}
#pragma endregion

	lightNum = Input::ChangeLighting(window, lightNum);

	if (lightNum < 1 || lightNum > 5)
		lightNum = 1;

	animShader->SetUniform("u_LightNum", lightNum);
	untexturedShader->SetUniform("u_LightNum", lightNum);
	shader->SetUniform("u_LightNum", lightNum);
	pauseShader->SetUniform("u_LightNum", lightNum);


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
		if (!showLevelComplete)
		{
			animShader->Bind();
			animShader->SetUniform("s_Diffuse", 0);
			drumstickMat.Albedo->Bind(0);
			meshMain.Render(camera, transform);

			animShader->SetUniform("s_Diffuse", 1);
			doorMat.Albedo->Bind(1);
			doorMesh.Render(camera, transformDoor);
			doorMat.Albedo->Unbind(1);

			pauseShader->Bind();
			pauseShader->SetUniform("s_Diffuse", 0);
			pauseMat.Albedo->Bind(0);

			if (isPaused)
			{
				pauseMesh.Render(orthoCam, transformPause);
			}

			shader->Bind();
			shader->SetUniform("s_Diffuse", 0);
			floorMat.Albedo->Bind(0);
			groundMesh.Render(camera, transformGround);

			shader->SetUniform("s_Diffuse", 1);
			wireMat.Albedo->Bind(1);

			if (wireEnt.Get<Wire>().GetIsPowered())
				wireMeshP.Render(camera, transformWire);
			else
				wireMesh.Render(camera, transformWire);

			if (wireEnt2.Get<Wire>().GetIsPowered())
				wireMeshP2.Render(camera, transformWire2);
			else
				wireMesh2.Render(camera, transformWire2);

			if (wireEnt3.Get<Wire>().GetIsPowered())
				wireMeshP3.Render(camera, transformWire3);
			else
				wireMesh3.Render(camera, transformWire3);

			if (wireEnt4.Get<Wire>().GetIsPowered())
				wireMeshP4.Render(camera, transformWire4);
			else
				wireMesh4.Render(camera, transformWire4);

			if (wireEnt5.Get<Wire>().GetIsPowered())
				wireMeshP5.Render(camera, transformWire5);
			else
				wireMesh5.Render(camera, transformWire5);

			if (wireEnt6.Get<Wire>().GetIsPowered())
				wireMeshP6.Render(camera, transformWire6);
			else
				wireMesh6.Render(camera, transformWire6);

			if (wireEnt7.Get<Wire>().GetIsPowered())
				wireMeshP7.Render(camera, transformWire7);
			else
				wireMesh7.Render(camera, transformWire7);

			shader->SetUniform("s_Diffuse", 2);
			buttonMat.Albedo->Bind(2);
			buttonMesh.Render(camera, transformButton);
			buttonMesh2.Render(camera, transformButton2);
			buttonMesh3.Render(camera, transformButton3);

			shader->SetUniform("s_Diffuse", 3);
			wallMat.Albedo->Bind(3);
			leftMesh.Render(camera, transformLeft);
			rightMesh.Render(camera, transformRight);
			backMesh.Render(camera, transformBack);

			shader->SetUniform("s_Diffuse", 4);
			gateMat.Albedo->Bind(4);
			gateMesh.Render(camera, transformGate);

			untexturedShader->Bind();
			if (wireEnt7.Get<Wire>().GetIsPowered())
				coilMeshP.Render(camera, transformCoil);
			else
				coilMesh.Render(camera, transformCoil);
			gateMesh.Render(camera, transformGate);
			gateMesh2.Render(camera, transformGate2);
			gateMesh3.Render(camera, transformGate3);
			notMesh.Render(camera, transformNot);
		}
	}
	else
	{
		if (!showLevelComplete)
		{
			animShader->Bind();
			animShader->SetUniform("s_Diffuse", 0);
			clearMat.Albedo->Bind(0);
			meshMain.Render(camera, transform);

			animShader->SetUniform("s_Diffuse", 1);
			clearMat.Albedo->Bind(1);
			doorMesh.Render(camera, transformDoor);
			clearMat.Albedo->Unbind(1);

			pauseShader->Bind();
			pauseShader->SetUniform("s_Diffuse", 0);
			pauseMat.Albedo->Bind(0);

			if (isPaused)
			{
				pauseMesh.Render(orthoCam, transformPause);
			}

			shader->Bind();
			shader->SetUniform("s_Diffuse", 0);
			clearMat.Albedo->Bind(0);
			groundMesh.Render(camera, transformGround);		

			shader->SetUniform("s_Diffuse", 1);
			clearMat.Albedo->Bind(1);

			if (wireEnt.Get<Wire>().GetIsPowered())
				wireMeshP.Render(camera, transformWire);
			else
				wireMesh.Render(camera, transformWire);

			if (wireEnt2.Get<Wire>().GetIsPowered())
				wireMeshP2.Render(camera, transformWire2);
			else
				wireMesh2.Render(camera, transformWire2);

			if (wireEnt3.Get<Wire>().GetIsPowered())
				wireMeshP3.Render(camera, transformWire3);
			else
				wireMesh3.Render(camera, transformWire3);

			if (wireEnt4.Get<Wire>().GetIsPowered())
				wireMeshP4.Render(camera, transformWire4);
			else
				wireMesh4.Render(camera, transformWire4);

			if (wireEnt5.Get<Wire>().GetIsPowered())
				wireMeshP5.Render(camera, transformWire5);
			else
				wireMesh5.Render(camera, transformWire5);

			if (wireEnt6.Get<Wire>().GetIsPowered())
				wireMeshP6.Render(camera, transformWire6);
			else
				wireMesh6.Render(camera, transformWire6);

			if (wireEnt7.Get<Wire>().GetIsPowered())
				wireMeshP7.Render(camera, transformWire7);
			else
				wireMesh7.Render(camera, transformWire7);

			shader->SetUniform("s_Diffuse", 2);
			clearMat.Albedo->Bind(2);
			buttonMesh.Render(camera, transformButton);
			buttonMesh2.Render(camera, transformButton2);
			buttonMesh3.Render(camera, transformButton3);

			shader->SetUniform("s_Diffuse", 3);
			clearMat.Albedo->Bind(3);
			leftMesh.Render(camera, transformLeft);
			rightMesh.Render(camera, transformRight);
			backMesh.Render(camera, transformBack);

			shader->SetUniform("s_Diffuse", 4);
			clearMat.Albedo->Bind(4);
			gateMesh.Render(camera, transformGate);

			untexturedShader->Bind();
			if (wireEnt7.Get<Wire>().GetIsPowered())
				coilMeshP.Render(camera, transformCoil);
			else
				coilMesh.Render(camera, transformCoil);
			gateMesh.Render(camera, transformGate);
			gateMesh2.Render(camera, transformGate2);
			gateMesh3.Render(camera, transformGate3);
			notMesh.Render(camera, transformNot);
		}
	}

	if (showLevelComplete)
	{
		lightNum = 1;
		shader->Bind();
		shader->SetUniform("s_Diffuse", 0);
		completeMat.Albedo->Bind(0);
		completeMesh.Render(orthoCam, transformComplete);
	}
#pragma endregion

	basicEffect->UnbindBuffer();

	effects[activeEffect]->ApplyEffect(basicEffect);

	effects[activeEffect]->DrawToScreen();

	leftEnt.Get<AABB>().Update();
	rightEnt.Get<AABB>().Update();
	backEnt.Get<AABB>().Update();
	doorEnt.Get<AABB>().Update();
	coilEnt.Get<AABB>().Update();
	andEnt.Get<AABB>().Update();
	andEnt2.Get<AABB>().Update();
	andEnt3.Get<AABB>().Update();
	notEnt.Get<AABB>().Update();
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
	notEnt.Get<NotGate>().Update();
	andEnt.Get<AndGate>().Update();
	andEnt2.Get<AndGate>().Update();
	andEnt3.Get<AndGate>().Update();
	
	if (doorEnt.Get<Door>().GetOpen())
		doorEnt.Get<MorphAnimation>().Update(dt);

	if (doorEnt.Get<AABB>().GetComplete())
		showLevelComplete = true;

}

void Level3::Unload()
{
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

