#include "Level4.h"
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

Level4::Level4(std::string sceneName, GLFWwindow* wind)
	: Scene(sceneName, wind)
{
#pragma region Entities
	mainPlayer = Entity::Create();
	floorEnt = Entity::Create();
	leftEnt = Entity::Create();
	rightEnt = Entity::Create();
	backEnt = Entity::Create();
	doorEnt = Entity::Create();
	buttonEnt = Entity::Create();
	buttonEnt2 = Entity::Create();
	buttonEnt3 = Entity::Create();
	buttonEnt4 = Entity::Create();
	colPipeEnt = Entity::Create();
	colPipeEnt2 = Entity::Create();
	panelEnt = Entity::Create();
	panelEnt2 = Entity::Create();
	ventEntL = Entity::Create();
	ventEntS = Entity::Create();

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

void Level4::InitScene()
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
	playerTrans.SetPosition(glm::vec3(0.0f, 1.0f, 30.0f));
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

	//Button transforms
	auto& buttonTrans = buttonEnt.Add<Transform>();
	buttonTrans.SetPosition(glm::vec3(0.f, -1.0f, 0.f));

	auto& buttonTrans2 = buttonEnt2.Add<Transform>();
	buttonTrans2.SetPosition(glm::vec3(0.f, -1.0f, 0.f));

	auto& buttonTrans3 = buttonEnt3.Add<Transform>();
	buttonTrans3.SetPosition(glm::vec3(0.f, -1.0f, 0.f));

	auto& buttonTrans4 = buttonEnt4.Add<Transform>();
	buttonTrans4.SetPosition(glm::vec3(0.f, -1.0f, 0.f));

	//Column Pipe transforms
	auto& colPipeTrans = colPipeEnt.Add<Transform>();
	colPipeTrans.SetPosition(glm::vec3(30.f, 1.f, -48.f));
	colPipeTrans.SetRotationY(90.f);
	colPipeTrans.SetScale(glm::vec3(1.5f));

	auto& colPipeTrans2 = colPipeEnt2.Add<Transform>();
	colPipeTrans2.SetPosition(glm::vec3(-30.f, 1.f, -48.f));
	colPipeTrans2.SetRotationY(90.f);
	colPipeTrans2.SetScale(glm::vec3(1.5f));

	//Panel transforms
	auto& panelTrans = panelEnt.Add<Transform>();
	panelTrans.SetScale(glm::vec3(4.0f));
	panelTrans.SetPosition(glm::vec3(-51.f, 7.0f, 0.f));

	auto& panelTrans2 = panelEnt2.Add<Transform>();
	panelTrans2.SetScale(glm::vec3(4.0f));
	panelTrans2.SetPosition(glm::vec3(-51.f, 7.0f, 8.f));

	//Vent transforms
	auto& ventTrans = ventEntL.Add<Transform>();
	ventTrans.SetPosition(glm::vec3(48.f, 20.f, -22.f));
	//ventTrans.SetScale(glm::vec3(0.8f));
	//ventTrans.SetRotationY(180.f);

#pragma endregion
	
	//AABB
	//auto& leftCol = leftEnt.Add<AABB>(leftEnt, mainPlayer);
	//auto& rightCol = rightEnt.Add<AABB>(rightEnt, mainPlayer);
	//auto& backCol = backEnt.Add<AABB>(backEnt, mainPlayer);

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
	auto& floorMesh = floorEnt.Add<MeshRenderer>(floorEnt, *floorL4, untexturedShader);
	auto& leftMesh = leftEnt.Add<MeshRenderer>(leftEnt, *leftWallL4, untexturedShader);
	auto& rightMesh = rightEnt.Add<MeshRenderer>(rightEnt, *rightWallL4, untexturedShader);
	auto& backMesh = backEnt.Add<MeshRenderer>(backEnt, *backWallL4, untexturedShader);
	auto& doorMesh = doorEnt.Add<MorphRenderer>(doorEnt, *doorM, animShader);
	auto& buttonMesh = buttonEnt.Add<MeshRenderer>(buttonEnt, *buttonM, shader);
	auto& buttonMesh2 = buttonEnt2.Add<MeshRenderer>(buttonEnt2, *buttonM, shader);
	auto& buttonMesh3 = buttonEnt3.Add<MeshRenderer>(buttonEnt3, *buttonM, shader);
	auto& buttonMesh4 = buttonEnt4.Add<MeshRenderer>(buttonEnt4, *buttonM, shader);
	auto& colPipeMesh = colPipeEnt.Add<MeshRenderer>(colPipeEnt, *columnPipe, shader);
	auto& colPipeMesh2 = colPipeEnt2.Add<MeshRenderer>(colPipeEnt2, *columnPipe, shader);
	auto& panelMesh = panelEnt.Add<MeshRenderer>(panelEnt, *panel, shader);
	auto& panelMesh2 = panelEnt2.Add<MeshRenderer>(panelEnt2, *panel, shader);
	auto& vent = ventEntL.Add<MeshRenderer>(ventEntL, *ventB, shader);

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
	
#pragma region Post-Effects
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

void Level4::Update(float dt)
{
#pragma region Transforms
	auto& playerTrans = mainPlayer.Get<Transform>();
	auto& buttonTrans = buttonEnt.Get<Transform>();
	auto& buttonTrans2 = buttonEnt2.Get<Transform>();
	auto& buttonTrans3 = buttonEnt3.Get<Transform>();
	auto& buttonTrans4 = buttonEnt4.Get<Transform>();

	backEnt.Get<Transform>().SetPositionZ(0.0f);
	backEnt.Get<Transform>().SetPositionY(1.0f);

	leftEnt.Get<Transform>().SetPositionX(0.0f);
	leftEnt.Get<Transform>().SetPositionY(1.0f);

	rightEnt.Get<Transform>().SetPositionX(0.0f);
	rightEnt.Get<Transform>().SetPositionY(1.0f);
#pragma endregion

	auto& camera = camEnt.Get<Camera>();

	//Get reference to the model matrix
	glm::mat4 transform = mainPlayer.Get<Transform>().GetModelMatrix();
	glm::mat4 transformGround = floorEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformLeft = leftEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformRight = rightEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformBack = backEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformDoor = doorEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformButton = buttonTrans.GetModelMatrix();
	glm::mat4 transformButton2 = buttonTrans2.GetModelMatrix();
	glm::mat4 transformButton3 = buttonTrans3.GetModelMatrix();
	glm::mat4 transformButton4 = buttonTrans4.GetModelMatrix();
	glm::mat4 transformColPipe = colPipeEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformColPipe2 = colPipeEnt2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformPanel = panelEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformPanel2 = panelEnt2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformVent = ventEntL.Get<Transform>().GetModelMatrix();

#pragma region PlayerMovement
	Input::MovePlayer(window, mainPlayer, camEnt, dt, camFar, camClose, camLeft, camRight);
#pragma endregion

#pragma region Camera Movement
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

	Input::MoveCamera(window, camEnt, dt);
#pragma endregion

	lightNum = Input::ChangeLighting(window, lightNum);

	if (lightNum < 1 || lightNum > 5)
		lightNum = 1;

	animShader->SetUniform("u_LightNum", lightNum);
	untexturedShader->SetUniform("u_LightNum", lightNum);
	shader->SetUniform("u_LightNum", lightNum);

	//Post-Effect Stuff
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
		//Bind and render the player and door using the animation shader
		animShader->Bind();
		animShader->SetUniform("s_Diffuse", 0);
		drumstickMat.Albedo->Bind(0);
		mainPlayer.Get<MorphRenderer>().Render(camera, transform);

		animShader->SetUniform("s_Diffuse", 1);
		doorMat.Albedo->Bind(1);	
		doorEnt.Get<MorphRenderer>().Render(camera, transformDoor);	
		doorMat.Albedo->Unbind(1);

		untexturedShader->Bind();
		//Floor (no texture for now)
		floorEnt.Get<MeshRenderer>().Render(camera, transformGround);

		//Walls (no textures for now)
		leftEnt.Get<MeshRenderer>().Render(camera, transformLeft);
		rightEnt.Get<MeshRenderer>().Render(camera, transformRight);
		backEnt.Get<MeshRenderer>().Render(camera, transformBack);

		shader->Bind();
		shader->SetUniform("s_Diffuse", 0);
		columnPipeMat.Albedo->Bind(0);
		colPipeEnt.Get<MeshRenderer>().Render(camera, transformColPipe);
		colPipeEnt2.Get<MeshRenderer>().Render(camera, transformColPipe2);

		//Panels
		shader->SetUniform("s_Diffuse", 1);
		panelMat.Albedo->Bind(1);
		panelEnt.Get<MeshRenderer>().Render(camera, transformPanel);
		panelEnt2.Get<MeshRenderer>().Render(camera, transformPanel2);

		//Vents
		shader->SetUniform("s_Diffuse", 2);
		ventMat.Albedo->Bind(2);
		ventEntL.Get<MeshRenderer>().Render(camera, transformVent);

		//shader->SetUniform("s_Diffuse", 0);
		//buttonMat.Albedo->Bind(0);
		//buttonEnt.Get<MeshRenderer>().Render(camera, transformButton);
		//buttonEnt2.Get<MeshRenderer>().Render(camera, transformButton2);
		//buttonEnt3.Get<MeshRenderer>().Render(camera, transformButton3);
		//buttonEnt4.Get<MeshRenderer>().Render(camera, transformButton4);
	}
	else
	{
		animShader->Bind();
		animShader->SetUniform("s_Diffuse", 0);
		clearMat.Albedo->Bind(0);
		mainPlayer.Get<MorphRenderer>().Render(camera, transform);

		animShader->SetUniform("s_Diffuse", 1);
		clearMat.Albedo->Bind(1);
		doorEnt.Get<MorphRenderer>().Render(camera, transformDoor);
		clearMat.Albedo->Unbind(1);

		untexturedShader->Bind();
		floorEnt.Get<MeshRenderer>().Render(camera, transformGround);
		leftEnt.Get<MeshRenderer>().Render(camera, transformLeft);
		rightEnt.Get<MeshRenderer>().Render(camera, transformRight);
		backEnt.Get<MeshRenderer>().Render(camera, transformBack);

		shader->Bind();
		shader->SetUniform("s_Diffuse", 0);
		clearMat.Albedo->Bind(0);
		colPipeEnt.Get<MeshRenderer>().Render(camera, transformColPipe);
		colPipeEnt2.Get<MeshRenderer>().Render(camera, transformColPipe2);
		panelEnt.Get<MeshRenderer>().Render(camera, transformPanel);
		panelEnt2.Get<MeshRenderer>().Render(camera, transformPanel2);
		ventEntL.Get<MeshRenderer>().Render(camera, transformVent);

		//buttonEnt.Get<MeshRenderer>().Render(camera, transformButton);
		//buttonEnt2.Get<MeshRenderer>().Render(camera, transformButton2);
		//buttonEnt3.Get<MeshRenderer>().Render(camera, transformButton3);
		//buttonEnt4.Get<MeshRenderer>().Render(camera, transformButton4);
	}
#pragma endregion

	basicEffect->UnbindBuffer();

	effects[activeEffect]->ApplyEffect(basicEffect);

	effects[activeEffect]->DrawToScreen();

	//Update the collisions
	//leftEnt.Get<AABB>().Update();
	//rightEnt.Get<AABB>().Update();
	//backEnt.Get<AABB>().Update();
	
}

void Level4::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}