#include "Scene.h"
#include <iostream>
#include <stb_image.h>

using namespace freebird;

Scene::Scene(std::string sceneName, GLFWwindow* wind)
{
	name = sceneName;
	window = wind;
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
	Texture2D::sptr diffuseDoor = Texture2D::LoadFromFile("Textures/DoorTexture.png");
	Texture2D::sptr diffuseFloor = Texture2D::LoadFromFile("Textures/FloorTilesetFinal.png");
	Texture2D::sptr diffuseWall = Texture2D::LoadFromFile("Textures/WallTileset.png");
	Texture2D::sptr diffuseComplete = Texture2D::LoadFromFile("Textures/LevelComplete.png");
	Texture2D::sptr diffuseAnd = Texture2D::LoadFromFile("Textures/AndGate.png");
	Texture2D::sptr diffuseNot = Texture2D::LoadFromFile("Textures/NotGate.png");
	Texture2D::sptr diffuseWire = Texture2D::LoadFromFile("Textures/Wire_Off_Texture.png");
	Texture2D::sptr diffuseWireOn = Texture2D::LoadFromFile("Textures/Wire_On_Texture.png");
	Texture2D::sptr diffuseBox = Texture2D::LoadFromFile("Textures/Box_Texture.png");
	Texture2D::sptr diffusePanel = Texture2D::LoadFromFile("Textures/PanelTexture.png");
	Texture2D::sptr diffuseVent = Texture2D::LoadFromFile("Textures/VentTexture.png");
	Texture2D::sptr diffusePipeStraight = Texture2D::LoadFromFile("Textures/Pipe_Straight_Texture.png");
	Texture2D::sptr diffusePipeCurved = Texture2D::LoadFromFile("Textures/Pipe_Curved_Texture.png");
	Texture2D::sptr diffusePause = Texture2D::LoadFromFile("Textures/PauseMenu.png");
	Texture2D::sptr diffuseOptions = Texture2D::LoadFromFile("Textures/Buttons/Default/Option.png");
	Texture2D::sptr diffuseRetry = Texture2D::LoadFromFile("Textures/Buttons/Default/Replay.png");
	Texture2D::sptr diffuseExit = Texture2D::LoadFromFile("Textures/Buttons/Default/Exit.png");
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
	floorMat.Albedo = diffuseFloor;
	wallMat.Albedo = diffuseWall;
	completeMat.Albedo = diffuseComplete;
	andMat.Albedo = diffuseAnd;
	notMat.Albedo = diffuseNot;
	wireMat.Albedo = diffuseWire;
	wireMatOn.Albedo = diffuseWireOn;
	boxMat.Albedo = diffuseBox;
	panelMat.Albedo = diffusePanel;
	ventMat.Albedo = diffuseVent;
	straightPipeMat.Albedo = diffusePipeStraight;
	curvedPipeMat.Albedo = diffusePipeCurved;
	pauseMat.Albedo = diffusePause;
	optionMat.Albedo = diffuseOptions;
	retryMat.Albedo = diffuseRetry;
	exitMat.Albedo = diffuseExit;
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
	glm::vec3 lightPos = glm::vec3(0.0f, 9.5f, -35.0f);
	glm::vec3 lightDir = glm::vec3(0.0f, -1.0f, 0.0f);
	glm::vec3 lightCol = glm::vec3(1.f);
	float     lightAmbientPow = 0.05f;
	float	  pauseAmbientPow = 0.25f;
	float     lightSpecularPow = 1.0f;
	glm::vec3 ambientCol = glm::vec3(1.0f);
	float     ambientPow = 0.1f;
	float     shininess = 16.0f;

	//Basic shader
	shader = Shader::Create();
	shader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	shader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	shader->Link();
	SetShaderValues(shader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, ambientCol, ambientPow, shininess);

	//For any objects with animations
	animShader = Shader::Create();
	animShader->LoadShaderPartFromFile("Shaders/morph_shader.glsl", GL_VERTEX_SHADER);
	animShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	animShader->Link();
	SetShaderValues(animShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, ambientCol, ambientPow, shininess);

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
	SetShaderValues(untexturedShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, ambientCol, ambientPow, shininess);

	//Pause UI Shader
	pauseShader = Shader::Create();
	pauseShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	pauseShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	pauseShader->Link();
	SetShaderValues(pauseShader, lightPos, lightDir, lightCol, pauseAmbientPow, lightSpecularPow, ambientCol, pauseAmbientPow, shininess);

	//GBuffer Shader
	Shader::sptr gBufferShader = Shader::Create();
	gBufferShader->LoadShaderPartFromFile("shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	gBufferShader->LoadShaderPartFromFile("shaders/gBuffer_pass_frag.glsl", GL_FRAGMENT_SHADER);
	gBufferShader->Link();
}

void Scene::InitMeshes()
{
	//For Door Anim
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

	//Multiple Levels
	drumstick = ModelManager::FindMesh(drumFile);
	floor = ModelManager::FindMesh(floorFile);
	screen = ModelManager::FindMesh(screenFile);
	leftWall = ModelManager::FindMesh(leftWallFile);
	rightWall = ModelManager::FindMesh(rightWallFile);
	backWall = ModelManager::FindMesh(backWallFile);
	doorM = ModelManager::FindMesh(doorFile);
	doorCloseM = ModelManager::FindMesh(doorFile10);
	options = ModelManager::FindMesh(pauseButtonFile);
	exit = ModelManager::FindMesh(pauseButtonFile);
	retry = ModelManager::FindMesh(pauseButtonFile);
	and = ModelManager::FindMesh(andFile);
	not = ModelManager::FindMesh(notFile);
	buttonM = ModelManager::FindMesh(buttonFile);
	coil = ModelManager::FindMesh(coilFile);
	boxM = ModelManager::FindMesh(boxFile);
	panel = ModelManager::FindMesh(panelFile);
	ventB = ModelManager::FindMesh(ventFileB);
	ventS = ModelManager::FindMesh(ventFileS);
	pipeS = ModelManager::FindMesh(pipeFileS);
	pipeC = ModelManager::FindMesh(pipeFileC);
	tablet = ModelManager::FindMesh(tabletFile);
	tut = ModelManager::FindMesh(tutFile, glm::vec3(1.0f, 0.0f, 0.0f));

	//Main Menu Level
	startWord = ModelManager::FindMesh(startFile, glm::vec3(1.0f, 0.0f, 0.0f));
	exitWord = ModelManager::FindMesh(exitFile, glm::vec3(1.0f, 0.0f, 0.0f));
	optionsWord = ModelManager::FindMesh(optFile, glm::vec3(1.0f, 0.0f, 0.0f));
	
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
}

bool Scene::GetComplete()
{
	return levelComplete;
}

void Scene::SetComplete(bool complete)
{
	levelComplete = complete;
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

//void Scene::RenderVAO(Shader::sptr& shader, MeshRenderer& vao, Camera& camera, glm::mat4 transform)
//{
//	shader->SetUniformMatrix("u_ModelRotation", glm::mat3(transform));
//	shader->SetUniformMatrix("u_ModelViewProjection", camera.GetViewProjection() * transform);
//	shader->SetUniformMatrix("u_Model", transform);
//	vao.Render();
//}

void Scene::SetShaderValues(Shader::sptr& shader, glm::vec3 lightPos, glm::vec3 lightDir, glm::vec3 lightCol, float lightAmbientPow, float lightSpecularPow, glm::vec3 ambientCol, float ambientPow, float shininess)
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

//Entity Scene::GetFBO()
//{
//	return FBO;
//}
//
//Entity Scene::GetGreyscaleEnt()
//{
//	return greyscaleEnt;
//}

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
