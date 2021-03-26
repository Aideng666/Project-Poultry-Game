#include "Scene.h"
#include <iostream>
#include <stb_image.h>

using namespace freebird;

Scene::Scene(std::string sceneName, GLFWwindow* wind)
{
	name = sceneName;
	window = wind;

	hWnd = glfwGetWin32Window(window);
}

void Scene::InitScene()
{
	scene = new entt::registry();

	Entity::SetReg(scene);


	//Set Up Camera
	Entity camEnt = Entity::Create();
	auto& camera = camEnt.Add<Camera>();

	camera.SetPosition(glm::vec3(0, 3, 3)); // Set initial position
	camera.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
	camera.LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camera.SetFovDegrees(90.0f); // Set an initial FOV
}

void Scene::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}

void Scene::InitTextures()
{
	Texture2D::sptr diffuseButton = Texture2D::LoadFromFile("Textures/ButtonTexture.png");
	Texture2D::sptr diffuseDrum = Texture2D::LoadFromFile("Textures/DrumstickTexture.png");
	Texture2D::sptr diffuseDoor = Texture2D::LoadFromFile("Textures/DoorTex.png");
	Texture2D::sptr diffuseDoorOn = Texture2D::LoadFromFile("Textures/DoorTexOn.png");
	Texture2D::sptr diffuseFloor = Texture2D::LoadFromFile("Textures/FloorTilesetFinal.png");
	Texture2D::sptr diffuseWall = Texture2D::LoadFromFile("Textures/WallTileset.png");
	Texture2D::sptr diffuseComplete = Texture2D::LoadFromFile("Textures/LevelComplete.png");
	Texture2D::sptr diffuseAnd = Texture2D::LoadFromFile("Textures/AndGate.png");
	Texture2D::sptr diffuseNot = Texture2D::LoadFromFile("Textures/NotGate.png");
	Texture2D::sptr diffuseOr = Texture2D::LoadFromFile("Textures/OrGate.png");
	Texture2D::sptr diffuseWire = Texture2D::LoadFromFile("Textures/Wire_Off_Texture.png");
	Texture2D::sptr diffuseWireOn = Texture2D::LoadFromFile("Textures/Wire_On_Texture.png");
	Texture2D::sptr diffuseBox = Texture2D::LoadFromFile("Textures/Box_Texture.png");
	Texture2D::sptr diffusePanel = Texture2D::LoadFromFile("Textures/PanelTexture.png");
	Texture2D::sptr diffuseVent = Texture2D::LoadFromFile("Textures/VentTexture.png");
	Texture2D::sptr diffusePipeStraight = Texture2D::LoadFromFile("Textures/Pipe_Straight_Texture.png");
	Texture2D::sptr diffusePipeCurved = Texture2D::LoadFromFile("Textures/Pipe_Curved_Texture.png");
	Texture2D::sptr diffusePipeShelf = Texture2D::LoadFromFile("Textures/ShelfPipeTexture.png");
	Texture2D::sptr diffusePipeColumn = Texture2D::LoadFromFile("Textures/ColumnPipeTexture.png");
	Texture2D::sptr diffusePause = Texture2D::LoadFromFile("Textures/PauseMenu.png");
	Texture2D::sptr diffuseOptions = Texture2D::LoadFromFile("Textures/Buttons/Default/Option.png");
	Texture2D::sptr diffuseRetry = Texture2D::LoadFromFile("Textures/Buttons/Default/Replay.png");
	Texture2D::sptr diffuseExit = Texture2D::LoadFromFile("Textures/Buttons/Default/Exit.png");
	Texture2D::sptr diffusePressOptions = Texture2D::LoadFromFile("Textures/Buttons/Pressed/Option.png");
	Texture2D::sptr diffusePressRetry = Texture2D::LoadFromFile("Textures/Buttons/Pressed/Replay.png");
	Texture2D::sptr diffusePressExit = Texture2D::LoadFromFile("Textures/Buttons/Pressed/Exit.png");
	Texture2D::sptr diffuseTablet = Texture2D::LoadFromFile("Textures/TabletTexture.png");
	Texture2D::sptr diffuseAndTabletScreen = Texture2D::LoadFromFile("Textures/AndGateTablet.png");
	Texture2D::sptr diffuseNotTabletScreen = Texture2D::LoadFromFile("Textures/NotGateTablet.png");
	Texture2D::sptr diffuseOrTabletScreen = Texture2D::LoadFromFile("Textures/OrGateTablet.png");
	Texture2D::sptr diffuseCoilOff = Texture2D::LoadFromFile("Textures/Tesla_Coil_Texture_Off.png");
	Texture2D::sptr diffuseCoilOn = Texture2D::LoadFromFile("Textures/Tesla_Coil_Texture_On.png");

	Texture2DDescription desc = Texture2DDescription();
	desc.Width = 1;
	desc.Height = 1;
	desc.Format = InternalFormat::RGB8;
	Texture2D::sptr texture2 = Texture2D::Create(desc);
	texture2->Clear();

	buttonMat.Albedo = diffuseButton;
	drumstickMat.Albedo = diffuseDrum;
	doorMat.Albedo = diffuseDoor;
	doorOnMat.Albedo = diffuseDoorOn;
	floorMat.Albedo = diffuseFloor;
	wallMat.Albedo = diffuseWall;
	completeMat.Albedo = diffuseComplete;
	andMat.Albedo = diffuseAnd;
	notMat.Albedo = diffuseNot;
	orMat.Albedo = diffuseOr;
	wireMat.Albedo = diffuseWire;
	wireMatOn.Albedo = diffuseWireOn;
	boxMat.Albedo = diffuseBox;
	panelMat.Albedo = diffusePanel;
	ventMat.Albedo = diffuseVent;
	straightPipeMat.Albedo = diffusePipeStraight;
	curvedPipeMat.Albedo = diffusePipeCurved;
	shelfPipeMat.Albedo = diffusePipeShelf;
	columnPipeMat.Albedo = diffusePipeColumn;
	pauseMat.Albedo = diffusePause;
	optionMat.Albedo = diffuseOptions;
	retryMat.Albedo = diffuseRetry;
	exitMat.Albedo = diffuseExit;
	optionPressMat.Albedo = diffusePressOptions;
	exitPressMat.Albedo = diffusePressExit;
	retryPressMat.Albedo = diffusePressRetry;
	tabletMat.Albedo = diffuseTablet;
	andTabletScreenMat.Albedo = diffuseAndTabletScreen;
	notTabletScreenMat.Albedo = diffuseNotTabletScreen;
	orTabletScreenMat.Albedo = diffuseOrTabletScreen;
	coilMatOff.Albedo = diffuseCoilOff;
	coilMatOn.Albedo = diffuseCoilOn;
	clearMat.Albedo = texture2;
}

void Scene::InitShaders()
{
	glm::vec3 lightPos = glm::vec3(0.0f, 5.0f, -5.0f);
	glm::vec3 lightDir = glm::vec3(0.0f, -1.0f, 1.0f);
	glm::vec3 lightCol = glm::vec3(1.f);
	float     lightAmbientPow = 0.25f;
	float	  pauseAmbientPow = 0.25f;
	float     lightSpecularPow = 1.0f;
	glm::vec3 ambientCol = glm::vec3(1.0f);
	float     ambientPow = 0.1f;
	float     shininess = 16.0f;
	float     lightLinearFalloff = 0.09f;
	float     lightQuadraticFalloff = 0.032f;



	//Basic shader
	shader = Shader::Create();
	shader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	shader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	shader->Link();
	SetShaderValues(shader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, ambientCol, ambientPow, shininess, lightLinearFalloff, lightQuadraticFalloff);

	//For any objects with animations
	animShader = Shader::Create();
	animShader->LoadShaderPartFromFile("Shaders/morph_shader.glsl", GL_VERTEX_SHADER);
	animShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	animShader->Link();
	SetShaderValues(animShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, ambientCol, ambientPow, shininess, lightLinearFalloff, lightQuadraticFalloff);

	//Particle shader
	particleShader = Shader::Create();
	particleShader->LoadShaderPartFromFile("Shaders/particle_vertex.glsl", GL_VERTEX_SHADER);
	particleShader->LoadShaderPartFromFile("Shaders/particle_geom.glsl", GL_GEOMETRY_SHADER);
	particleShader->LoadShaderPartFromFile("Shaders/particle_frag.glsl", GL_FRAGMENT_SHADER);
	particleShader->Link();

	//Shader for unextured objects
	untexturedShader = Shader::Create();
	untexturedShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	untexturedShader->LoadShaderPartFromFile("Shaders/frag_untextured.glsl", GL_FRAGMENT_SHADER);
	untexturedShader->Link();
	SetShaderValues(untexturedShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, ambientCol, ambientPow, shininess, lightLinearFalloff, lightQuadraticFalloff);

	//Pause UI Shader
	pauseShader = Shader::Create();
	pauseShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	pauseShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	pauseShader->Link();
	SetShaderValues(pauseShader, lightPos, lightDir, lightCol, pauseAmbientPow, lightSpecularPow, ambientCol, pauseAmbientPow, shininess, lightLinearFalloff, lightQuadraticFalloff);

	simpleDepthShader = Shader::Create();
	simpleDepthShader->LoadShaderPartFromFile("Shaders/simple_depth_vert.glsl", GL_VERTEX_SHADER);
	simpleDepthShader->LoadShaderPartFromFile("Shaders/simple_depth_frag.glsl", GL_FRAGMENT_SHADER);
	simpleDepthShader->Link();
	SetShaderValues(simpleDepthShader, lightPos, lightDir, lightCol, pauseAmbientPow, lightSpecularPow, ambientCol, pauseAmbientPow, shininess, lightLinearFalloff, lightQuadraticFalloff);

	/*Shader::sptr gBufferShader = Shader::Create();
	gBufferShader->LoadShaderPartFromFile("shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	gBufferShader->LoadShaderPartFromFile("shaders/gBuffer_pass_frag.glsl", GL_FRAGMENT_SHADER);
	gBufferShader->Link();*/
}

void Scene::InitMeshes()
{
	//For Door Anim
	door1 = ModelManager::FindMesh(doorFile1);
	door2 = ModelManager::FindMesh(doorFile2);
	door3 = ModelManager::FindMesh(doorFile3);
	door4 = ModelManager::FindMesh(doorFile4);
	/*door5 = ModelManager::FindMesh(doorFile5);
	door6 = ModelManager::FindMesh(doorFile6);
	door7 = ModelManager::FindMesh(doorFile7);
	door8 = ModelManager::FindMesh(doorFile8);
	door9 = ModelManager::FindMesh(doorFile9);
	door10 = ModelManager::FindMesh(doorFile10);*/

	//For Walking Anim
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

	//For Idle Anims
	idle1 = ModelManager::FindMesh(idleFile1);
	idle2 = ModelManager::FindMesh(idleFile2);
	idle3 = ModelManager::FindMesh(idleFile3);
	idle4 = ModelManager::FindMesh(idleFile4);
	idle5 = ModelManager::FindMesh(idleFile5);
	idle6 = ModelManager::FindMesh(idleFile6);
	idle7 = ModelManager::FindMesh(idleFile7);
	idle8 = ModelManager::FindMesh(idleFile8);
	idle9 = ModelManager::FindMesh(idleFile9);
	idle10 = ModelManager::FindMesh(idleFile10);
	idle11 = ModelManager::FindMesh(idleFile11);
	idle12 = ModelManager::FindMesh(idleFile12);
	idle13 = ModelManager::FindMesh(idleFile13);
	idle14 = ModelManager::FindMesh(idleFile14);
	idle15 = ModelManager::FindMesh(idleFile15);
	idle16 = ModelManager::FindMesh(idleFile16);
	idle17 = ModelManager::FindMesh(idleFile17);
	idle18 = ModelManager::FindMesh(idleFile18);

	//For Button Anims
	button1 = ModelManager::FindMesh(buttonFile1);
	button2 = ModelManager::FindMesh(buttonFile2);
	button3 = ModelManager::FindMesh(buttonFile3);

	//Multiple Levels
	//drumstick = ModelManager::FindMesh(drumFile);
	floor = ModelManager::FindMesh(floorFile);
	screen = ModelManager::FindMesh(screenFile);
	leftWall = ModelManager::FindMesh(leftWallFile);
	rightWall = ModelManager::FindMesh(rightWallFile);
	backWall = ModelManager::FindMesh(backWallFile);
	options = ModelManager::FindMesh(pauseButtonFile);
	exit = ModelManager::FindMesh(pauseButtonFile);
	retry = ModelManager::FindMesh(pauseButtonFile);
	and = ModelManager::FindMesh(andFile);
	not = ModelManager::FindMesh(notFile);
	orMesh = ModelManager::FindMesh(orFile);
	buttonM = ModelManager::FindMesh(buttonFile);
	coil = ModelManager::FindMesh(coilFile);
	boxM = ModelManager::FindMesh(boxFile);
	panel = ModelManager::FindMesh(panelFile);
	ventB = ModelManager::FindMesh(ventFileB);
	ventS = ModelManager::FindMesh(ventFileS);
	pipeS = ModelManager::FindMesh(pipeFileS);
	pipeC = ModelManager::FindMesh(pipeFileC);
	shelfPipe = ModelManager::FindMesh(shelfPipeFile);
	columnPipe = ModelManager::FindMesh(columnPipeFile);
	tablet = ModelManager::FindMesh(tabletFile);
	tut = ModelManager::FindMesh(tutFile, glm::vec3(1.0f, 0.0f, 0.0f));

	//Lab Levels(tentative)
	floorLab = ModelManager::FindMesh(floorL4File, glm::vec3(0.2f, 0.7f, 0.0f));
	leftWallLab = ModelManager::FindMesh(labLeftWallFile);
	rightWallLab = ModelManager::FindMesh(labRightWallFile);
	backWallLab = ModelManager::FindMesh(labBackWallFile);

	//Main Menu Level
	startWord = ModelManager::FindMesh(startFile, glm::vec3(1.0f, 0.0f, 0.0f));
	exitWord = ModelManager::FindMesh(exitFile, glm::vec3(1.0f, 0.0f, 0.0f));
	optionsWord = ModelManager::FindMesh(optFile, glm::vec3(1.0f, 0.0f, 0.0f));
	mainMenuFloor = ModelManager::FindMesh(mainMenuFloorFile);

	//Level 1
	wireM1L1 = ModelManager::FindMesh(wire1L1File);
	wireM2L1 = ModelManager::FindMesh(wire2L1File);
	wireM3L1 = ModelManager::FindMesh(wire3L1File);
	floorL1 = ModelManager::FindMesh(floorL1File);

	//Level 2
	wireM1L2 = ModelManager::FindMesh(wire1L2File);
	wireM2L2 = ModelManager::FindMesh(wire2L2File);
	wireM3L2 = ModelManager::FindMesh(wire3L2File);
	wireM4L2 = ModelManager::FindMesh(wire4L2File);
	wireM5L2 = ModelManager::FindMesh(wire5L2File);
	floorL2 = ModelManager::FindMesh(floorL2File);

	//Level 3
	wireM1L3 = ModelManager::FindMesh(wire1L3File);
	wireM2L3 = ModelManager::FindMesh(wire2L3File);
	wireM3L3 = ModelManager::FindMesh(wire3L3File);
	wireM4L3 = ModelManager::FindMesh(wire4L3File);
	wireM5L3 = ModelManager::FindMesh(wire5L3File);
	wireM6L3 = ModelManager::FindMesh(wire6L3File);
	wireM7L3 = ModelManager::FindMesh(wire7L3File);
	floorL3 = ModelManager::FindMesh(floorL3File);

	//Level4
	wireM1L4 = ModelManager::FindMesh(wire1L4File);
	wireM2L4 = ModelManager::FindMesh(wire2L4File);
	wireM3L4 = ModelManager::FindMesh(wire3L4File);
	wireM4L4 = ModelManager::FindMesh(wire4L4File);
	wireM5L4 = ModelManager::FindMesh(wire5L4File);
	wireM6L4 = ModelManager::FindMesh(wire6L4File);
	wireM7L4 = ModelManager::FindMesh(wire7L4File);
	wireM8L4 = ModelManager::FindMesh(wire8L4File);
	wireM9L4 = ModelManager::FindMesh(wire9L4File);
	wireM10L4 = ModelManager::FindMesh(wire10L4File);

	//Level5
	wireM1L5 = ModelManager::FindMesh(wire1L5File);
	wireM2L5 = ModelManager::FindMesh(wire2L5File);
	wireM3L5 = ModelManager::FindMesh(wire3L5File);
	wireM4L5 = ModelManager::FindMesh(wire4L5File);
	wireM5L5 = ModelManager::FindMesh(wire5L5File);
	wireM6L5 = ModelManager::FindMesh(wire6L5File);
	wireM7L5 = ModelManager::FindMesh(wire7L5File);

	//Level6
	wireM1L6 = ModelManager::FindMesh(wire1L6File);
	wireM2L6 = ModelManager::FindMesh(wire2L6File);
	wireM3L6 = ModelManager::FindMesh(wire3L6File);
	wireM4L6 = ModelManager::FindMesh(wire4L6File);
	wireM5L6 = ModelManager::FindMesh(wire5L6File);
	wireM6L6 = ModelManager::FindMesh(wire6L6File);
	wireM7L6 = ModelManager::FindMesh(wire7L6File);
	wireM8L6 = ModelManager::FindMesh(wire8L6File);
	wireM9L6 = ModelManager::FindMesh(wire9L6File);

	entList.clear();
}

void Scene::InitAnims()
{
	doorFrames.clear();
	doorCloseFrames.clear();
	walkFrames.clear();
	idleFrames.clear();

	//Door Animations
	doorFrames.push_back(std::unique_ptr<Mesh>(door1));
	doorFrames.push_back(std::unique_ptr<Mesh>(door2));
	doorFrames.push_back(std::unique_ptr<Mesh>(door3));
	doorFrames.push_back(std::unique_ptr<Mesh>(door4));
	

	doorCloseFrames.push_back(std::unique_ptr<Mesh>(door4));
	doorCloseFrames.push_back(std::unique_ptr<Mesh>(door3));
	doorCloseFrames.push_back(std::unique_ptr<Mesh>(door2));
	doorCloseFrames.push_back(std::unique_ptr<Mesh>(door1));

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

	//Idle Animations
	idleFrames.push_back(std::unique_ptr<Mesh>(idle1));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle2));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle3));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle4));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle5));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle6));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle7));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle8));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle9));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle10));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle11));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle12));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle13));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle14));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle15));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle16));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle17));
	idleFrames.push_back(std::unique_ptr<Mesh>(idle18));

	buttonFrames.push_back(std::unique_ptr<Mesh>(button1));
	buttonFrames.push_back(std::unique_ptr<Mesh>(button2));
	buttonFrames.push_back(std::unique_ptr<Mesh>(button3));
}

bool Scene::GetComplete()
{
	return levelComplete;
}

void Scene::SetComplete(bool complete)
{
	levelComplete = complete;
}

bool Scene::GetRetry()
{
	return levelRetry;
}

void Scene::SetRetry(bool retry)
{
	levelRetry = retry;
}

Entity Scene::GetCamera()
{
	return camEnt;
}

entt::registry* Scene::GetScene()
{
	return scene;
}

Shader::sptr Scene::GetShader()
{
	return shader;
}

bool Scene::GetLoad()
{
	return loadModels;
}

void Scene::SetShaderValues(Shader::sptr& shader, glm::vec3 lightPos, glm::vec3 lightDir, glm::vec3 lightCol, float lightAmbientPow, float lightSpecularPow, glm::vec3 ambientCol, float ambientPow, float shininess, float lightLinearFalloff, float lightQuadraticFalloff)
{
	shader->SetUniform("u_LightPos", lightPos);
	shader->SetUniform("u_LightDir", lightDir);
	shader->SetUniform("u_LightCol", lightCol);
	shader->SetUniform("u_AmbientLightStrength", lightAmbientPow);
	shader->SetUniform("u_SpecularLightStrength", lightSpecularPow);
	shader->SetUniform("u_AmbientCol", ambientCol);
	shader->SetUniform("u_AmbientStrength", ambientPow);
	shader->SetUniform("u_Shininess", shininess);
	shader->SetUniform("u_AmbientLightStrength2", 0.01f);
	shader->SetUniform("u_LightAttenuationConstant", 1.0f);
	shader->SetUniform("u_LightAttenuationLinear", lightLinearFalloff);
	shader->SetUniform("u_LightAttenuationQuadratic", lightQuadraticFalloff);
}

void Scene::LoadTexImage()
{
		int channels;
		stbi_set_flip_vertically_on_load(true);

		image = stbi_load(fileName, &width, &height, &channels, 0);

		if (image)
			std::cout << "Image loaded: " << width << " x " << height << std::endl;
		else std::cout << "Failed to load image" << std::endl;
}

std::vector<PostEffect*> Scene::GetEffects()
{
	return effects;
}

bool Scene::GetTextured()
{
	return isTextured;
}

void Scene::SetTextured(bool isTex)
{
	isTextured = isTex;
}

int Scene::GetActiveEffect()
{
	return activeEffect;
}

void Scene::SetActiveEffect(int activeEffect)
{
	this->activeEffect = activeEffect;
}

bool Scene::GetLightOn()
{
	return lightOn;
}

void Scene::SetLightOn(bool isOn)
{
	lightOn = isOn;
}

bool Scene::GetTopView()
{
	return topView;
}

void Scene::SetTopView(bool isTop)
{
	topView = isTop;
}
