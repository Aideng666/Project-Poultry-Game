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

	pauseEnt = Entity::Create();
	optionEnt = Entity::Create();
	exitEnt = Entity::Create();
	retryEnt = Entity::Create();

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

#pragma region Transforms
	//Player transform
	auto& playerTrans = mainPlayer.Add<Transform>();
	playerTrans.SetPosition(glm::vec3(0.0f, 1.1f, 42.0f));
	playerTrans.SetRotationY(180.0f);

	//Floor transform
	auto& groundTrans = floorEnt.Add<Transform>();
	groundTrans.SetPositionY(1.0f);

	//Wall transforms
	auto& leftTrans = leftEnt.Add<Transform>();
	auto& rightTrans = rightEnt.Add<Transform>();
	auto& backTrans = backEnt.Add<Transform>();

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
#pragma endregion

#pragma region Animation Frames
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
	auto& floorMesh = floorEnt.Add<MeshRenderer>(floorEnt, *floorLab, untexturedShader);
	auto& leftMesh = leftEnt.Add<MeshRenderer>(leftEnt, *leftWallLab, untexturedShader);
	auto& rightMesh = rightEnt.Add<MeshRenderer>(rightEnt, *rightWallLab, untexturedShader);
	auto& backMesh = backEnt.Add<MeshRenderer>(backEnt, *backWallLab, untexturedShader);

	auto& pauseMesh = pauseEnt.Add<MeshRenderer>(pauseEnt, *screen, pauseShader);
	auto& optionMesh = optionEnt.Add<MeshRenderer>(optionEnt, *options, pauseShader);
	auto& retryMesh = retryEnt.Add<MeshRenderer>(retryEnt, *retry, pauseShader);
	auto& exitMesh = exitEnt.Add<MeshRenderer>(exitEnt, *exit, pauseShader);

	auto& wireMesh = wireEnt.Add<MeshRenderer>(wireEnt, *wireM1L5, shader);
	auto& wireMesh2 = wireEnt2.Add<MeshRenderer>(wireEnt2, *wireM2L5, shader);
	auto& wireMesh3 = wireEnt3.Add<MeshRenderer>(wireEnt3, *wireM3L5, shader);
	auto& wireMesh4 = wireEnt4.Add<MeshRenderer>(wireEnt4, *wireM4L5, shader);
	auto& wireMesh5 = wireEnt5.Add<MeshRenderer>(wireEnt5, *wireM5L5, shader);
	auto& wireMesh6 = wireEnt6.Add<MeshRenderer>(wireEnt6, *wireM6L5, shader);
	auto& wireMesh7 = wireEnt7.Add<MeshRenderer>(wireEnt7, *wireM7L5, shader);

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

void Level5::Update(float dt)
{
#pragma region Transforms
	auto& playerTrans = mainPlayer.Get<Transform>();

	backEnt.Get<Transform>().SetPositionZ(0.0f);
	backEnt.Get<Transform>().SetPositionY(1.0f);

	leftEnt.Get<Transform>().SetPositionX(0.0f);
	leftEnt.Get<Transform>().SetPositionY(1.0f);

	rightEnt.Get<Transform>().SetPositionX(0.0f);
	rightEnt.Get<Transform>().SetPositionY(1.0f);
#pragma endregion

	auto& camera = camEnt.Get<Camera>();
	auto& orthoCam = uiCamEnt.Get<Camera>();

	//Get reference to the model matrix
	glm::mat4 transform = mainPlayer.Get<Transform>().GetModelMatrix();
	glm::mat4 transformGround = floorEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformLeft = leftEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformRight = rightEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformBack = backEnt.Get<Transform>().GetModelMatrix();

	glm::mat4 transformWire = wireEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire2 = wireEnt2.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire3 = wireEnt3.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire4 = wireEnt4.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire5 = wireEnt5.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire6 = wireEnt6.Get<Transform>().GetModelMatrix();
	glm::mat4 transformWire7 = wireEnt7.Get<Transform>().GetModelMatrix();

	glm::mat4 transformPause = pauseEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformOptions = optionEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformRetry = retryEnt.Get<Transform>().GetModelMatrix();
	glm::mat4 transformExit = exitEnt.Get<Transform>().GetModelMatrix();

	pauseWatch.Poll(window);

#pragma region PlayerMovement
	if (!isPaused)
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

	if (!isPaused)
	{
		Input::MoveCamera(window, camEnt, dt);
	}
#pragma endregion

	lightNum = Input::ChangeLighting(window, lightNum);

	if (lightNum < 1 || lightNum > 5)
		lightNum = 1;

	animShader->SetUniform("u_LightNum", lightNum);
	untexturedShader->SetUniform("u_LightNum", lightNum);
	pauseShader->SetUniform("u_LightNum", lightNum);
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

		untexturedShader->Bind();
		//Floor (no texture for now)
		floorEnt.Get<MeshRenderer>().Render(camera, transformGround);

		//Walls (no textures for now)
		leftEnt.Get<MeshRenderer>().Render(camera, transformLeft);
		rightEnt.Get<MeshRenderer>().Render(camera, transformRight);
		backEnt.Get<MeshRenderer>().Render(camera, transformBack);

		pauseShader->Bind();
		pauseShader->SetUniform("s_Diffuse", 0);
		pauseMat.Albedo->Bind(0);

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
		retryMat.Albedo->Bind(2);

		if (isPaused)
		{
			retryEnt.Get<MeshRenderer>().Render(orthoCam, transformRetry);
		}

		pauseShader->SetUniform("s_Diffuse", 2);
		exitMat.Albedo->Bind(2);

		if (isPaused)
		{
			exitEnt.Get<MeshRenderer>().Render(orthoCam, transformExit);
		}

		shader->Bind();
		//Wires
		shader->SetUniform("s_Diffuse", 0);
		wireMat.Albedo->Bind(0);
		wireEnt.Get<MeshRenderer>().Render(camera, transformWire);
		wireEnt2.Get<MeshRenderer>().Render(camera, transformWire2);
		wireEnt3.Get<MeshRenderer>().Render(camera, transformWire3);
		wireEnt4.Get<MeshRenderer>().Render(camera, transformWire4);
		wireEnt5.Get<MeshRenderer>().Render(camera, transformWire5);
		wireEnt6.Get<MeshRenderer>().Render(camera, transformWire6);
		wireEnt7.Get<MeshRenderer>().Render(camera, transformWire7);
	}
	else
	{
		animShader->Bind();
		animShader->SetUniform("s_Diffuse", 0);
		clearMat.Albedo->Bind(0);
		mainPlayer.Get<MorphRenderer>().Render(camera, transform);

		untexturedShader->Bind();
		floorEnt.Get<MeshRenderer>().Render(camera, transformGround);
		leftEnt.Get<MeshRenderer>().Render(camera, transformLeft);
		rightEnt.Get<MeshRenderer>().Render(camera, transformRight);
		backEnt.Get<MeshRenderer>().Render(camera, transformBack);

		pauseShader->Bind();
		pauseShader->SetUniform("s_Diffuse", 0);
		clearMat.Albedo->Bind(0);

		if (isPaused)
		{
			pauseEnt.Get<MeshRenderer>().Render(orthoCam, transformPause);
		}

		shader->Bind();
		shader->SetUniform("s_Diffuse", 0);
		clearMat.Albedo->Bind(0);
		wireEnt.Get<MeshRenderer>().Render(camera, transformWire);
		wireEnt2.Get<MeshRenderer>().Render(camera, transformWire2);
		wireEnt3.Get<MeshRenderer>().Render(camera, transformWire3);
		wireEnt4.Get<MeshRenderer>().Render(camera, transformWire4);
		wireEnt5.Get<MeshRenderer>().Render(camera, transformWire5);
		wireEnt6.Get<MeshRenderer>().Render(camera, transformWire6);
		wireEnt7.Get<MeshRenderer>().Render(camera, transformWire7);
	}
#pragma endregion

	basicEffect->UnbindBuffer();

	effects[activeEffect]->ApplyEffect(basicEffect);

	effects[activeEffect]->DrawToScreen();

}

void Level5::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}