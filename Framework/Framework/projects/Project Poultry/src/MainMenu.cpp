#include "MainMenu.h"
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


MainMenu::MainMenu(std::string sceneName, GLFWwindow* wind)
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
	andEnt = Entity::Create();
	andEnt2 = Entity::Create();
	doorEnt = Entity::Create();
	coilEnt = Entity::Create();
}

void MainMenu::InitScene()
{
	Application::SetClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	scene = new entt::registry();

	Entity::SetReg(scene);

	float distance = glm::distance(point2, point1);

	totalTime = distance / speed;

	glm::vec3 lightPos = glm::vec3(0.0f, 9.5f, -35.0f);
	glm::vec3 lightDir = glm::vec3(0.0f, -1.0f, 0.0f);
	glm::vec3 lightCol = glm::vec3(1.f, 1.f, 1.f);
	float     lightAmbientPow = 0.05f;
	float     lightSpecularPow = 1.0f;
	float     lightSpecularPow2 = 0.2f;
	glm::vec3 ambientCol = glm::vec3(1.0f);
	float     ambientPow = 0.1f;
	float     shininess = 16.0f;

#pragma region Shader Stuff

	playerShader = Shader::Create();
	playerShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	playerShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	playerShader->Link();

	SetShaderValues(playerShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

	levelShader = Shader::Create();
	levelShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	levelShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	levelShader->Link();

	SetShaderValues(levelShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

	wireShader = Shader::Create();
	wireShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	wireShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	wireShader->Link();

	SetShaderValues(wireShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

	gateShader = Shader::Create();
	gateShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	gateShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	gateShader->Link();

	SetShaderValues(gateShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

	buttonShader = Shader::Create();
	buttonShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	buttonShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	buttonShader->Link();

	SetShaderValues(buttonShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

	doorShader = Shader::Create();
	doorShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	doorShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	doorShader->Link();

	SetShaderValues(doorShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

#pragma endregion

#pragma region Texture Stuff
	Texture2DData::sptr buttonMap = Texture2DData::LoadFromFile("Textures/ButtonTexture.png");
	Texture2DData::sptr drumstickMap = Texture2DData::LoadFromFile("Textures/ButtonTexture.png");

	Texture2D::sptr diffuseButton = Texture2D::Create();
	diffuseButton->LoadData(buttonMap);

	Texture2D::sptr diffuseDrum = Texture2D::Create();
	diffuseDrum->LoadData(drumstickMap);

	Texture2DDescription desc = Texture2DDescription();
	desc.Width = 1;
	desc.Height = 1;
	desc.Format = InternalFormat::RGB8;
	Texture2D::sptr texture2 = Texture2D::Create(desc);
	texture2->Clear();

	buttonMat.Albedo = diffuseButton;
	drumstickMat.Albedo = diffuseDrum;

#pragma endregion

	//Transforms
	auto& playerTrans = mainPlayer.Add<Transform>();
	playerTrans.SetPosition(glm::vec3(0.0f, 1.0f, 5.0f));
	playerTrans.SetRotationY(0.0f);

	auto& groundTrans = floorEnt.Add<Transform>();

	auto& leftTrans = leftEnt.Add<Transform>();

	auto& rightTrans = rightEnt.Add<Transform>();

	auto& backTrans = backEnt.Add<Transform>();

	auto& wireTrans = wireEnt.Add<Transform>();
	wireTrans.SetPosition(glm::vec3(-115.5f, 1.0f, -3.0f));

	auto& wireTrans2 = wireEnt2.Add<Transform>();
	wireTrans2.SetPosition(glm::vec3(-115.5f, 1.0f, -3.0f));

	auto& wireTrans3 = wireEnt3.Add<Transform>();
	wireTrans3.SetPosition(glm::vec3(-115.5f, 1.0f, -3.0f));

	auto& wireTrans4 = wireEnt4.Add<Transform>();
	wireTrans4.SetPosition(glm::vec3(-115.5f, 1.0f, -3.0f));

	auto& wireTrans5 = wireEnt5.Add<Transform>();
	wireTrans5.SetPosition(glm::vec3(-115.5f, 1.0f, -3.0f));

	auto& buttonTrans = buttonEnt.Add<Transform>();
	buttonTrans.SetPosition(glm::vec3(-31.5f, -2.0f, 25.5f));

	auto& buttonTrans2 = buttonEnt2.Add<Transform>();
	buttonTrans2.SetPosition(glm::vec3(-10.5f, -2.0f, 25.5f));

	auto& buttonTrans3 = buttonEnt3.Add<Transform>();
	buttonTrans3.SetPosition(glm::vec3(18.7f, -2.0f, 25.5f));

	auto& doorTrans = doorEnt.Add<Transform>();
	doorTrans.SetPosition(glm::vec3(0.0f, 5.0f, -36.0f));
	doorTrans.SetScale(glm::vec3(1.5f));

	auto& gateTrans = andEnt.Add<Transform>();
	gateTrans.SetPosition(glm::vec3(-21.0f, 1.0f, 1.0f));
	gateTrans.SetRotationY(-90.0f);

	auto& gateTrans2 = andEnt2.Add<Transform>();
	gateTrans2.SetPosition(glm::vec3(0.0f, 1.0f, -8.0f));
	gateTrans2.SetRotationY(-90.0f);

	auto& coilTrans = coilEnt.Add<Transform>();
	coilTrans.SetPosition(glm::vec3(-15.0f, 1.0f, -36.0f));

	//AABB
	auto& leftCol = leftEnt.Add<AABB>(leftEnt, mainPlayer);
	auto& rightCol = rightEnt.Add<AABB>(rightEnt, mainPlayer);
	auto& backCol = backEnt.Add<AABB>(backEnt, mainPlayer);
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

	Mesh drumstick("Models/Drumstick.obj", glm::vec3(1.0f, 0.0f, 0.0f));
	Mesh floor("Models/Floor.obj", glm::vec3(0.1f, 0.1f, 0.1f));
	Mesh wall("Models/Wall.obj");
	Mesh doorM("Models/Door.obj");
	Mesh pipe("Models/Level1Pipe.obj", glm::vec3(1.0f, 1.0f, 0.0f));
	Mesh buttonM("Models/Button.obj");
	Mesh wireM1("Models/Level2Wire1.obj", glm::vec3(1.0f, 1.0f, 0.0f));
	Mesh wireM2("Models/Level2Wire2.obj", glm::vec3(1.0f, 1.0f, 0.0f));
	Mesh wireM3("Models/Level2Wire3.obj", glm::vec3(1.0f, 1.0f, 0.0f));
	Mesh wireM4("Models/Level2Wire4.obj", glm::vec3(1.0f, 1.0f, 0.0f));
	Mesh wireM5("Models/Level2Wire5.obj", glm::vec3(1.0f, 1.0f, 0.0f));
	Mesh gate("Models/AndGate.obj", glm::vec3(0.0f, 0.0f, 1.0f));
	Mesh coil("Models/Coil.obj", glm::vec3(0.0f, 1.0f, 0.0f));

	auto& playerMesh = mainPlayer.Add<MorphRenderer>(mainPlayer, drumstick, playerShader);
	auto& floorMesh = floorEnt.Add<MeshRenderer>(floorEnt, floor, levelShader);
	auto& leftMesh = leftEnt.Add<MeshRenderer>(leftEnt, wall, levelShader);
	auto& rightMesh = rightEnt.Add<MeshRenderer>(rightEnt, wall, levelShader);
	auto& backMesh = backEnt.Add<MeshRenderer>(backEnt, wall, levelShader);
	auto& gateMesh = andEnt.Add<MeshRenderer>(andEnt, gate, gateShader);
	auto& gateMesh2 = andEnt2.Add<MeshRenderer>(andEnt2, gate, gateShader);
	auto& buttonMesh = buttonEnt.Add<MeshRenderer>(buttonEnt, buttonM, buttonShader);
	auto& buttonMesh2 = buttonEnt2.Add<MeshRenderer>(buttonEnt2, buttonM, buttonShader);
	auto& buttonMesh3 = buttonEnt3.Add<MeshRenderer>(buttonEnt3, buttonM, buttonShader);
	auto& wireMesh = wireEnt.Add<MeshRenderer>(wireEnt, wireM1, wireShader);
	auto& wireMesh2 = wireEnt2.Add<MeshRenderer>(wireEnt2, wireM2, wireShader);
	auto& wireMesh3 = wireEnt3.Add<MeshRenderer>(wireEnt3, wireM3, wireShader);
	auto& wireMesh4 = wireEnt4.Add<MeshRenderer>(wireEnt4, wireM4, wireShader);
	auto& wireMesh5 = wireEnt5.Add<MeshRenderer>(wireEnt5, wireM5, wireShader);
	auto& doorMesh = doorEnt.Add<MeshRenderer>(doorEnt, doorM, doorShader);
	auto& coilMesh = coilEnt.Add<MeshRenderer>(coilEnt, coil, doorShader);

	auto& camera = camEnt.Add<Camera>();

	camera.SetPosition(glm::vec3(0, 15, mainPlayer.Get<Transform>().GetPositionZ() + 8)); // Set initial position
	camera.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
	camera.LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camera.SetFovDegrees(90.0f); // Set an initial FOV
	/*
#pragma region Entity ImGui Editor
	glm::vec3 position = playerTrans.GetPosition();
	glm::vec3 rotation = playerTrans.GetRotation();
	glm::vec3 positionGround = groundTrans.GetPosition();
	glm::vec3 rotationGround = groundTrans.GetRotation();
	glm::vec3 positionLeft = leftTrans.GetPosition();
	glm::vec3 rotationLeft = leftTrans.GetRotation();
	glm::vec3 positionRight = rightTrans.GetPosition();
	glm::vec3 rotationRight = rightTrans.GetRotation();
	glm::vec3 positionBack = backTrans.GetPosition();
	glm::vec3 rotationBack = backTrans.GetRotation();
	glm::vec3 positionWire = wireTrans.GetPosition();
	glm::vec3 rotationWire = wireTrans.GetRotation();
	glm::vec3 positionWire2 = wireTrans2.GetPosition();
	glm::vec3 rotationWire2 = wireTrans2.GetRotation();
	glm::vec3 positionWire3 = wireTrans3.GetPosition();
	glm::vec3 rotationWire3 = wireTrans3.GetRotation();
	glm::vec3 positionWire4 = wireTrans4.GetPosition();
	glm::vec3 rotationWire4 = wireTrans4.GetRotation();
	glm::vec3 positionWire5 = wireTrans5.GetPosition();
	glm::vec3 rotationWire5 = wireTrans5.GetRotation();
	glm::vec3 positionLever = buttonTrans.GetPosition();
	glm::vec3 rotationLever = buttonTrans.GetRotation();
	glm::vec3 positionLever2 = buttonTrans2.GetPosition();
	glm::vec3 rotationLever2 = buttonTrans2.GetRotation();
	glm::vec3 positionLever3 = buttonTrans3.GetPosition();
	glm::vec3 rotationLever3 = buttonTrans3.GetRotation();
	glm::vec3 positionGate = gateTrans.GetPosition();
	glm::vec3 rotationGate = gateTrans.GetRotation();

	imGuiCallbacks.push_back([&]() {
		if (ImGui::CollapsingHeader("Entities"))
		{
			if (ImGui::CollapsingHeader("Chicken"))
			{
				if (ImGui::SliderFloat("PosX", &position.x, -10.0f, 10.0f))
				{
					mainPlayer.Get<Transform>().SetPositionX(position.x);
				}
				if (ImGui::SliderFloat("PosY", &position.y, -10.0f, 10.0f))
				{
					mainPlayer.Get<Transform>().SetPositionY(position.y);
				}
				if (ImGui::SliderFloat("PosZ", &position.z, -10.0f, 10.0f))
				{
					mainPlayer.Get<Transform>().SetPositionZ(position.z);
				}
				if (ImGui::SliderFloat("RotX", &rotation.x, -360.0f, 360.0f))
				{
					mainPlayer.Get<Transform>().SetRotationX(rotation.x);
				}
				if (ImGui::SliderFloat("RotY", &rotation.y, -360.0f, 360.0f))
				{
					mainPlayer.Get<Transform>().SetRotationY(rotation.y);
				}
				if (ImGui::SliderFloat("RotZ", &rotation.z, -360.0f, 360.0f))
				{
					mainPlayer.Get<Transform>().SetRotationZ(rotation.z);
				}
			}
			if (ImGui::CollapsingHeader("Ground"))
			{
				if (ImGui::SliderFloat("PosX", &positionGround.x, -10.0f, 10.0f))
				{
					floorEnt.Get<Transform>().SetPositionX(positionGround.x);
				}
				if (ImGui::SliderFloat("PosY", &positionGround.y, -10.0f, 10.0f))
				{
					floorEnt.Get<Transform>().SetPositionY(positionGround.y);
				}
				if (ImGui::SliderFloat("PosZ", &positionGround.z, -10.0f, 10.0f))
				{
					floorEnt.Get<Transform>().SetPositionZ(positionGround.z);
				}
				if (ImGui::SliderFloat("RotX", &rotationGround.x, -360.0f, 360.0f))
				{
					floorEnt.Get<Transform>().SetRotationX(rotationGround.x);
				}
				if (ImGui::SliderFloat("RotY", &rotationGround.y, -360.0f, 360.0f))
				{
					floorEnt.Get<Transform>().SetRotationY(rotationGround.y);
				}
				if (ImGui::SliderFloat("RotZ", &rotationGround.z, -360.0f, 360.0f))
				{
					floorEnt.Get<Transform>().SetRotationZ(rotationGround.z);
				}
			}
			if (ImGui::CollapsingHeader("Left Wall"))
			{
				if (ImGui::SliderFloat("PosX", &positionLeft.x, -10.0f, 10.0f))
				{
					leftEnt.Get<Transform>().SetPositionX(positionLeft.x);
				}
				if (ImGui::SliderFloat("PosY", &positionLeft.y, -10.0f, 10.0f))
				{
					leftEnt.Get<Transform>().SetPositionY(positionLeft.y);
				}
				if (ImGui::SliderFloat("PosZ", &positionLeft.z, -10.0f, 10.0f))
				{
					leftEnt.Get<Transform>().SetPositionZ(positionLeft.z);
				}
				if (ImGui::SliderFloat("RotX", &rotationLeft.x, -360.0f, 360.0f))
				{
					leftEnt.Get<Transform>().SetRotationX(rotationLeft.x);
				}
				if (ImGui::SliderFloat("RotY", &rotationLeft.y, -360.0f, 360.0f))
				{
					leftEnt.Get<Transform>().SetRotationY(rotationLeft.y);
				}
				if (ImGui::SliderFloat("RotZ", &rotationLeft.z, -360.0f, 360.0f))
				{
					leftEnt.Get<Transform>().SetRotationZ(rotationLeft.z);
				}
			}
			if (ImGui::CollapsingHeader("Right Wall"))
			{
				if (ImGui::SliderFloat("PosX", &positionRight.x, -10.0f, 10.0f))
				{
					rightEnt.Get<Transform>().SetPositionX(positionRight.x);
				}
				if (ImGui::SliderFloat("PosY", &positionRight.y, -10.0f, 10.0f))
				{
					rightEnt.Get<Transform>().SetPositionY(positionRight.y);
				}
				if (ImGui::SliderFloat("PosZ", &positionRight.z, -10.0f, 10.0f))
				{
					rightEnt.Get<Transform>().SetPositionZ(positionRight.z);
				}
				if (ImGui::SliderFloat("RotX", &rotationRight.x, -360.0f, 360.0f))
				{
					rightEnt.Get<Transform>().SetRotationX(rotationRight.x);
				}
				if (ImGui::SliderFloat("RotY", &rotationRight.y, -360.0f, 360.0f))
				{
					rightEnt.Get<Transform>().SetRotationY(rotationRight.y);
				}
				if (ImGui::SliderFloat("RotZ", &rotationRight.z, -360.0f, 360.0f))
				{
					rightEnt.Get<Transform>().SetRotationZ(rotationRight.z);
				}
			}
			if (ImGui::CollapsingHeader("Back Wall"))
			{
				if (ImGui::SliderFloat("PosX", &positionBack.x, -10.0f, 10.0f))
				{
					backEnt.Get<Transform>().SetPositionX(positionBack.x);
				}
				if (ImGui::SliderFloat("PosY", &positionBack.y, -10.0f, 10.0f))
				{
					backEnt.Get<Transform>().SetPositionY(positionBack.y);
				}
				if (ImGui::SliderFloat("PosZ", &positionBack.z, -10.0f, 10.0f))
				{
					backEnt.Get<Transform>().SetPositionZ(positionBack.z);
				}
				if (ImGui::SliderFloat("RotX", &rotationBack.x, -360.0f, 360.0f))
				{
					backEnt.Get<Transform>().SetRotationX(rotationBack.x);
				}
				if (ImGui::SliderFloat("RotY", &rotationBack.y, -360.0f, 360.0f))
				{
					backEnt.Get<Transform>().SetRotationY(rotationBack.y);
				}
				if (ImGui::SliderFloat("RotZ", &rotationBack.z, -360.0f, 360.0f))
				{
					backEnt.Get<Transform>().SetRotationZ(rotationBack.z);
				}
			}
			if (ImGui::CollapsingHeader("Gate"))
			{
				if (ImGui::SliderFloat("PosX", &positionGate.x, -10.0f, 10.0f))
				{
					andEnt.Get<Transform>().SetPositionX(positionGate.x);
				}
				if (ImGui::SliderFloat("PosY", &positionGate.y, -10.0f, 10.0f))
				{
					andEnt.Get<Transform>().SetPositionY(positionGate.y);
				}
				if (ImGui::SliderFloat("PosZ", &positionGate.z, -10.0f, 10.0f))
				{
					andEnt.Get<Transform>().SetPositionZ(positionGate.z);
				}
				if (ImGui::SliderFloat("RotX", &rotationGate.x, -360.0f, 360.0f))
				{
					andEnt.Get<Transform>().SetRotationX(rotationGate.x);
				}
				if (ImGui::SliderFloat("RotY", &rotationGate.y, -360.0f, 360.0f))
				{
					andEnt.Get<Transform>().SetRotationY(rotationGate.y);
				}
				if (ImGui::SliderFloat("RotZ", &rotationGate.z, -360.0f, 360.0f))
				{
					andEnt.Get<Transform>().SetRotationZ(rotationGate.z);
				}
			}
			if (ImGui::CollapsingHeader("Wire 1"))
			{
				if (ImGui::SliderFloat("PosX", &positionWire.x, -10.0f, 10.0f))
				{
					wireEnt.Get<Transform>().SetPositionX(positionWire.x);
				}
				if (ImGui::SliderFloat("PosY", &positionWire.y, -10.0f, 10.0f))
				{
					wireEnt.Get<Transform>().SetPositionY(positionWire.y);
				}
				if (ImGui::SliderFloat("PosZ", &positionWire.z, -10.0f, 10.0f))
				{
					wireEnt.Get<Transform>().SetPositionZ(positionWire.z);
				}
				if (ImGui::SliderFloat("RotX", &rotationWire.x, -360.0f, 360.0f))
				{
					wireEnt.Get<Transform>().SetRotationX(rotationWire.x);
				}
				if (ImGui::SliderFloat("RotY", &rotationWire.y, -360.0f, 360.0f))
				{
					wireEnt.Get<Transform>().SetRotationY(rotationWire.y);
				}
				if (ImGui::SliderFloat("RotZ", &rotationWire.z, -360.0f, 360.0f))
				{
					wireEnt.Get<Transform>().SetRotationZ(rotationWire.z);
				}
			}
			if (ImGui::CollapsingHeader("Wire 2"))
			{
				if (ImGui::SliderFloat("PosX", &positionWire2.x, -10.0f, 10.0f))
				{
					wireEnt2.Get<Transform>().SetPositionX(positionWire2.x);
				}
				if (ImGui::SliderFloat("PosY", &positionWire2.y, -10.0f, 10.0f))
				{
					wireEnt2.Get<Transform>().SetPositionY(positionWire2.y);
				}
				if (ImGui::SliderFloat("PosZ", &positionWire2.z, -10.0f, 10.0f))
				{
					wireEnt2.Get<Transform>().SetPositionZ(positionWire2.z);
				}
				if (ImGui::SliderFloat("RotX", &rotationWire2.x, -360.0f, 360.0f))
				{
					wireEnt2.Get<Transform>().SetRotationX(rotationWire2.x);
				}
				if (ImGui::SliderFloat("RotY", &rotationWire2.y, -360.0f, 360.0f))
				{
					wireEnt2.Get<Transform>().SetRotationY(rotationWire2.y);
				}
				if (ImGui::SliderFloat("RotZ", &rotationWire2.z, -360.0f, 360.0f))
				{
					wireEnt2.Get<Transform>().SetRotationZ(rotationWire2.z);
				}
			}
			if (ImGui::CollapsingHeader("Wire 3"))
			{
				if (ImGui::SliderFloat("PosX", &positionWire3.x, -10.0f, 10.0f))
				{
					wireEnt3.Get<Transform>().SetPositionX(positionWire3.x);
				}
				if (ImGui::SliderFloat("PosY", &positionWire3.y, -10.0f, 10.0f))
				{
					wireEnt3.Get<Transform>().SetPositionY(positionWire3.y);
				}
				if (ImGui::SliderFloat("PosZ", &positionWire3.z, -10.0f, 10.0f))
				{
					wireEnt3.Get<Transform>().SetPositionZ(positionWire3.z);
				}
				if (ImGui::SliderFloat("RotX", &rotationWire3.x, -360.0f, 360.0f))
				{
					wireEnt3.Get<Transform>().SetRotationX(rotationWire3.x);
				}
				if (ImGui::SliderFloat("RotY", &rotationWire3.y, -360.0f, 360.0f))
				{
					wireEnt3.Get<Transform>().SetRotationY(rotationWire3.y);
				}
				if (ImGui::SliderFloat("RotZ", &rotationWire3.z, -360.0f, 360.0f))
				{
					wireEnt3.Get<Transform>().SetRotationZ(rotationWire3.z);
				}
			}
			if (ImGui::CollapsingHeader("Wire 4"))
			{
				if (ImGui::SliderFloat("PosX", &positionWire4.x, -10.0f, 10.0f))
				{
					wireEnt4.Get<Transform>().SetPositionX(positionWire4.x);
				}
				if (ImGui::SliderFloat("PosY", &positionWire4.y, -10.0f, 10.0f))
				{
					wireEnt4.Get<Transform>().SetPositionY(positionWire4.y);
				}
				if (ImGui::SliderFloat("PosZ", &positionWire4.z, -10.0f, 10.0f))
				{
					wireEnt4.Get<Transform>().SetPositionZ(positionWire4.z);
				}
				if (ImGui::SliderFloat("RotX", &rotationWire4.x, -360.0f, 360.0f))
				{
					wireEnt4.Get<Transform>().SetRotationX(rotationWire4.x);
				}
				if (ImGui::SliderFloat("RotY", &rotationWire4.y, -360.0f, 360.0f))
				{
					wireEnt4.Get<Transform>().SetRotationY(rotationWire4.y);
				}
				if (ImGui::SliderFloat("RotZ", &rotationWire4.z, -360.0f, 360.0f))
				{
					wireEnt4.Get<Transform>().SetRotationZ(rotationWire4.z);
				}
			}
			if (ImGui::CollapsingHeader("Wire 5"))
			{
				if (ImGui::SliderFloat("PosX", &positionWire5.x, -10.0f, 10.0f))
				{
					wireEnt5.Get<Transform>().SetPositionX(positionWire5.x);
				}
				if (ImGui::SliderFloat("PosY", &positionWire5.y, -10.0f, 10.0f))
				{
					wireEnt5.Get<Transform>().SetPositionY(positionWire5.y);
				}
				if (ImGui::SliderFloat("PosZ", &positionWire5.z, -10.0f, 10.0f))
				{
					wireEnt5.Get<Transform>().SetPositionZ(positionWire5.z);
				}
				if (ImGui::SliderFloat("RotX", &rotationWire5.x, -360.0f, 360.0f))
				{
					wireEnt5.Get<Transform>().SetRotationX(rotationWire5.x);
				}
				if (ImGui::SliderFloat("RotY", &rotationWire5.y, -360.0f, 360.0f))
				{
					wireEnt5.Get<Transform>().SetRotationY(rotationWire5.y);
				}
				if (ImGui::SliderFloat("RotZ", &rotationWire5.z, -360.0f, 360.0f))
				{
					wireEnt5.Get<Transform>().SetRotationZ(rotationWire5.z);
				}
			}
			if (ImGui::CollapsingHeader("Lever 1"))
			{
				if (ImGui::SliderFloat("PosX", &positionLever.x, -10.0f, 10.0f))
				{
					buttonEnt.Get<Transform>().SetPositionX(positionLever.x);
				}
				if (ImGui::SliderFloat("PosY", &positionLever.y, -10.0f, 10.0f))
				{
					buttonEnt.Get<Transform>().SetPositionY(positionLever.y);
				}
				if (ImGui::SliderFloat("PosZ", &positionLever.z, -10.0f, 10.0f))
				{
					buttonEnt.Get<Transform>().SetPositionZ(positionLever.z);
				}
				if (ImGui::SliderFloat("RotX", &rotationLever.x, -360.0f, 360.0f))
				{
					buttonEnt.Get<Transform>().SetRotationX(rotationLever.x);
				}
				if (ImGui::SliderFloat("RotY", &rotationLever.y, -360.0f, 360.0f))
				{
					buttonEnt.Get<Transform>().SetRotationY(rotationLever.y);
				}
				if (ImGui::SliderFloat("RotZ", &rotationLever.z, -360.0f, 360.0f))
				{
					buttonEnt.Get<Transform>().SetRotationZ(rotationLever.z);
				}
			}
			if (ImGui::CollapsingHeader("Lever 2"))
			{
				if (ImGui::SliderFloat("PosX", &positionLever2.x, -10.0f, 10.0f))
				{
					buttonEnt2.Get<Transform>().SetPositionX(positionLever2.x);
				}
				if (ImGui::SliderFloat("PosY", &positionLever2.y, -10.0f, 10.0f))
				{
					buttonEnt2.Get<Transform>().SetPositionY(positionLever2.y);
				}
				if (ImGui::SliderFloat("PosZ", &positionLever2.z, -10.0f, 10.0f))
				{
					buttonEnt2.Get<Transform>().SetPositionZ(positionLever2.z);
				}
				if (ImGui::SliderFloat("RotX", &rotationLever2.x, -360.0f, 360.0f))
				{
					buttonEnt2.Get<Transform>().SetRotationX(rotationLever2.x);
				}
				if (ImGui::SliderFloat("RotY", &rotationLever2.y, -360.0f, 360.0f))
				{
					buttonEnt2.Get<Transform>().SetRotationY(rotationLever2.y);
				}
				if (ImGui::SliderFloat("RotZ", &rotationLever2.z, -360.0f, 360.0f))
				{
					buttonEnt2.Get<Transform>().SetRotationZ(rotationLever2.z);
				}
			}
			if (ImGui::CollapsingHeader("Lever 3"))
			{
				if (ImGui::SliderFloat("PosX", &positionLever3.x, -10.0f, 10.0f))
				{
					buttonEnt3.Get<Transform>().SetPositionX(positionLever3.x);
				}
				if (ImGui::SliderFloat("PosY", &positionLever3.y, -10.0f, 10.0f))
				{
					buttonEnt3.Get<Transform>().SetPositionY(positionLever3.y);
				}
				if (ImGui::SliderFloat("PosZ", &positionLever3.z, -10.0f, 10.0f))
				{
					buttonEnt3.Get<Transform>().SetPositionZ(positionLever3.z);
				}
				if (ImGui::SliderFloat("RotX", &rotationLever3.x, -360.0f, 360.0f))
				{
					buttonEnt3.Get<Transform>().SetRotationX(rotationLever3.x);
				}
				if (ImGui::SliderFloat("RotY", &rotationLever3.y, -360.0f, 360.0f))
				{
					buttonEnt3.Get<Transform>().SetRotationY(rotationLever3.y);
				}
				if (ImGui::SliderFloat("RotZ", &rotationLever3.z, -360.0f, 360.0f))
				{
					buttonEnt3.Get<Transform>().SetRotationZ(rotationLever3.z);
				}
			}
		}
		});
#pragma endregion
*/

}

void MainMenu::Update(float dt)
{

	time += dt;
	playerShader->SetUniform("u_Time", time);
	levelShader->SetUniform("u_Time", time);
	gateShader->SetUniform("u_Time", time);
	wireShader->SetUniform("u_Time", time);
	buttonShader->SetUniform("u_Time", time);
	doorShader->SetUniform("u_Time", time);

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

	playerShader->SetUniform("u_Position", currentPos);
	levelShader->SetUniform("u_Position", currentPos);
	gateShader->SetUniform("u_Position", currentPos);
	wireShader->SetUniform("u_Position", currentPos);
	doorShader->SetUniform("u_Position", currentPos);
	buttonShader->SetUniform("u_Position", currentPos);

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
	auto& gateTrans = andEnt.Get<Transform>();
	auto& gateTrans2 = andEnt2.Get<Transform>();
	auto& coilTrans = coilEnt.Get<Transform>();

	backTrans.SetPositionZ(-39.0f);
	backTrans.SetPositionY(9.0f);

	leftTrans.SetPositionX(-39.0f);
	leftTrans.SetRotationY(90.0f);
	leftTrans.SetPositionY(9.0f);

	rightTrans.SetPositionX(39.0f);
	rightTrans.SetRotationY(90.0f);
	rightTrans.SetPositionY(9.0f);

	auto& camera = camEnt.Get<Camera>();

	auto& meshMain = mainPlayer.Get<MorphRenderer>();
	auto& groundMesh = floorEnt.Get<MeshRenderer>();
	auto& leftMesh = leftEnt.Get<MeshRenderer>();
	auto& rightMesh = rightEnt.Get<MeshRenderer>();
	auto& backMesh = backEnt.Get<MeshRenderer>();
	auto& doorMesh = doorEnt.Get<MeshRenderer>();
	auto& buttonMesh = buttonEnt.Get<MeshRenderer>();
	auto& buttonMesh2 = buttonEnt2.Get<MeshRenderer>();
	auto& buttonMesh3 = buttonEnt3.Get<MeshRenderer>();
	auto& wireMesh = wireEnt.Get<MeshRenderer>();
	auto& wireMesh2 = wireEnt2.Get<MeshRenderer>();
	auto& wireMesh3 = wireEnt3.Get<MeshRenderer>();
	auto& wireMesh4 = wireEnt4.Get<MeshRenderer>();
	auto& wireMesh5 = wireEnt5.Get<MeshRenderer>();
	auto& gateMesh = andEnt.Get<MeshRenderer>();
	auto& gateMesh2 = andEnt2.Get<MeshRenderer>();
	auto& coilMesh = coilEnt.Get<MeshRenderer>();

	camera.LookAt(glm::vec3(playerTrans.GetPosition()));

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
	glm::mat4 transformGate = gateTrans.GetModelMatrix();
	glm::mat4 transformGate2 = gateTrans2.GetModelMatrix();
	glm::mat4 transformCoil = coilTrans.GetModelMatrix();

	if (playerTrans.GetPositionX() - buttonTrans.GetPositionX() < 2.0f && playerTrans.GetPositionX() - buttonTrans.GetPositionX() > -2.0f
		&& playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() > -3.0f)
		button1Watch.Poll(window);

	if (playerTrans.GetPositionX() - buttonTrans2.GetPositionX() < 2.0f && playerTrans.GetPositionX() - buttonTrans2.GetPositionX() > -2.0f
		&& playerTrans.GetPositionZ() - buttonTrans2.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans2.GetPositionZ() > -3.0f)
		button2Watch.Poll(window);

	if (playerTrans.GetPositionX() - buttonTrans3.GetPositionX() < 2.0f && playerTrans.GetPositionX() - buttonTrans3.GetPositionX() > -2.0f
		&& playerTrans.GetPositionZ() - buttonTrans3.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans3.GetPositionZ() > -3.0f)
		button3Watch.Poll(window);

#pragma region PlayerMovement
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			playerTrans.SetPositionX(playerTrans.GetPositionX() - 10 * dt);
			playerTrans.SetRotationY(270.0f);
			camera.SetPosition(glm::vec3(playerTrans.GetPositionX(), camera.GetPosition().y, camera.GetPosition().z));
		}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		playerTrans.SetPositionX(playerTrans.GetPositionX() + 10 * dt);
		playerTrans.SetRotationY(90.0f);
		camera.SetPosition(glm::vec3(playerTrans.GetPositionX(), camera.GetPosition().y, camera.GetPosition().z));
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		playerTrans.SetPositionZ(playerTrans.GetPositionZ() - 10 * dt);
		playerTrans.SetRotationY(180.0f);

		if (camFar)
			camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z - 10 * dt));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		playerTrans.SetPositionZ(playerTrans.GetPositionZ() + 10 * dt);
		playerTrans.SetRotationY(0.0f);

		if (camClose)
			camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z + 10 * dt));
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

	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	{
		camera.SetPosition(glm::vec3(camera.GetPosition().x - 10 * dt, camera.GetPosition().y, camera.GetPosition().z));
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		camera.SetPosition(glm::vec3(camera.GetPosition().x + 10 * dt, camera.GetPosition().y, camera.GetPosition().z));
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z - 10 * dt));
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z + 10 * dt));
	}
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
	{
		camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y + 10 * dt, camera.GetPosition().z));
	}
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
	{
		camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y - 10 * dt, camera.GetPosition().z));
	}
#pragma endregion

#pragma region Renders

	playerShader->Bind();
	meshMain.Render(camera, transform);

	levelShader->Bind();
	groundMesh.Render(camera, transformGround);
	leftMesh.Render(camera, transformLeft);
	rightMesh.Render(camera, transformRight);
	backMesh.Render(camera, transformBack);

	doorShader->Bind();
	doorMesh.Render(camera, transformDoor);
	coilMesh.Render(camera, transformCoil);

	wireShader->Bind();
	wireMesh.Render(camera, transformWire);
	wireMesh2.Render(camera, transformWire2);
	wireMesh3.Render(camera, transformWire3);
	wireMesh4.Render(camera, transformWire4);
	wireMesh5.Render(camera, transformWire5);
	
	buttonShader->Bind();
	/*buttonShader->SetUniform("s_Diffuse", 0);
	material.Albedo->Bind(0);*/

	buttonMesh.Render(camera, transformButton);
	buttonMesh2.Render(camera, transformButton2);
	buttonMesh3.Render(camera, transformButton3);

	gateShader->Bind();
	gateMesh.Render(camera, transformGate);
	gateMesh2.Render(camera, transformGate2);



#pragma endregion

	leftEnt.Get<AABB>().Update();
	rightEnt.Get<AABB>().Update();
	backEnt.Get<AABB>().Update();
	doorEnt.Get<AABB>().Update();
	buttonEnt.Get<Lever>().Update();
	buttonEnt2.Get<Lever>().Update();
	buttonEnt3.Get<Lever>().Update();
	wireEnt.Get<Wire>().Update();
	wireEnt2.Get<Wire>().Update();
	wireEnt3.Get<Wire>().Update();
	wireEnt4.Get<Wire>().Update();
	wireEnt5.Get<Wire>().Update();
	andEnt.Get<AndGate>().Update();
	andEnt2.Get<AndGate>().Update();
	
	if (doorEnt.Get<AABB>().GetComplete())
		levelComplete = true;

}

void MainMenu::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}
