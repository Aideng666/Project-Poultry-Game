#include "Level1.h"
#include <iostream>
#include <GLFW\glfw3.h>

#include "Application.h"
#include <imgui.h>
#include <AABB.h>

using namespace freebird;

Level1::Level1(std::string sceneName, GLFWwindow* wind)
	: Scene(sceneName, wind)
{
	mainPlayer = Entity::Create();
	camEnt = Entity::Create();
	ground = Entity::Create();
	leftWall = Entity::Create();
	rightWall = Entity::Create();
	backWall = Entity::Create();
	andEnt = Entity::Create();
	wireEnt = Entity::Create();
	leverEnt = Entity::Create();
	wireEnt2 = Entity::Create();
	leverEnt2 = Entity::Create();
	doorEnt = Entity::Create();
}

void Level1::InitScene()
{
	Application::SetClearColor(glm::vec4(0.75f, 0.75f, 0.75f, 1.0f));

	scene = new entt::registry();

	Entity::SetReg(scene);

	//Set Up Camera
	auto& camera = camEnt.Add<Camera>();

	camera.SetPosition(glm::vec3(0, 8, 15)); // Set initial position
	camera.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
	camera.LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camera.SetFovDegrees(90.0f); // Set an initial FOV

	//Transforms
	auto& groundTrans = ground.Add<Transform>();
	groundTrans.SetScale(glm::vec3(2.0f, 1.0f, 2.0f));

	auto& leftTrans = leftWall.Add<Transform>();
	leftTrans.SetScale(glm::vec3(1.0f, 1.0f, 2.0f));

	auto& rightTrans = rightWall.Add<Transform>();
	rightTrans.SetScale(glm::vec3(1.0f, 1.0f, 2.0f));

	auto& backTrans = backWall.Add<Transform>();
	backTrans.SetScale(glm::vec3(2.0f, 1.0f, 1.0f));

	auto& playerTrans = mainPlayer.Add<Transform>();
	playerTrans.SetPosition(glm::vec3(0.0f, 1.0f, 5.0f));
	playerTrans.SetRotationY(0.0f);

	auto& gateTrans = andEnt.Add<Transform>();
	gateTrans.SetPosition(glm::vec3(0.0f, 1.0f, 2.0f));
	gateTrans.SetRotationY(90.0f);

	auto& wireTrans = wireEnt.Add<Transform>();
	wireTrans.SetPosition(glm::vec3(-2.0f, 1.0f, 5.0f));
	wireTrans.SetRotationY(90.0f);

	auto& leverTrans = leverEnt.Add<Transform>();
	leverTrans.SetPosition(glm::vec3(-4.0f, 1.0f, 8.0f));
	leverTrans.SetRotationY(90.0f);

	auto& wireTrans2 = wireEnt2.Add<Transform>();
	wireTrans2.SetPosition(glm::vec3(2.0f, 1.0f, 5.0f));
	wireTrans2.SetRotationY(90.0f);

	auto& leverTrans2 = leverEnt2.Add<Transform>();
	leverTrans2.SetPosition(glm::vec3(4.0f, 1.0f, 8.0f));
	leverTrans2.SetRotationY(90.0f);

	auto& doorTrans = doorEnt.Add<Transform>();
	doorTrans.SetPosition(glm::vec3(0.0f, 1.0f, -10.0f));
	doorTrans.SetRotationY(90.0f);

	//Gates
	auto& andGate = andEnt.Add<AndGate>(wireEnt, wireEnt2, doorEnt);

	//Levers
	auto& lever = leverEnt.Add<Lever>(wireEnt);
	lever.SetPowered(false);
	auto& lever2 = leverEnt2.Add<Lever>(wireEnt2);
	lever2.SetPowered(false);

	//Wires
	auto& wire = wireEnt.Add<Wire>(leverEnt);
	auto& wire2 = wireEnt2.Add<Wire>(leverEnt2);

	//AABB
	auto& leftCol = leftWall.Add<AABB>(leftWall, mainPlayer);
	auto& rightCol = rightWall.Add<AABB>(rightWall, mainPlayer);
	auto& backCol = backWall.Add<AABB>(backWall, mainPlayer);
	auto& doorCol = doorEnt.Add<AABB>(doorEnt, mainPlayer);
	doorCol.SetComplete(false);

	//Door
	auto& door = doorEnt.Add<Door>();
	door.SetOpen(false);


	//meshes
	Mesh monkey("Models/Monkey.obj", glm::vec3(1.0f, 0.0f, 0.0f));
	Mesh test("Models/TestPlane.obj");
	Mesh gate("Models/invalid.obj", glm::vec3(1.0f, 0.0f, 0.0f));
	Mesh lev("Models/invalid.obj", glm::vec3(0.0f, 1.0f, 0.0f));
	Mesh wir("Models/invalid.obj", glm::vec3(0.0f, 0.0f, 1.0f));
	Mesh doorM("Models/invalid.obj", glm::vec3(1.0f, 0.0f, 1.0f));

	auto& playerMesh = mainPlayer.Add<Mesh>(monkey);
	auto& groundMesh = ground.Add<Mesh>(test);
	auto& leftMesh = leftWall.Add<Mesh>(test);
	auto& rightMesh = rightWall.Add<Mesh>(test);
	auto& backMesh = backWall.Add<Mesh>(test);
	auto& gateMesh = andEnt.Add<Mesh>(gate);
	auto& leverMesh = leverEnt.Add<Mesh>(lev);
	auto& wireMesh = wireEnt.Add<Mesh>(wir);
	auto& leverMesh2 = leverEnt2.Add<Mesh>(lev);
	auto& wireMesh2 = wireEnt2.Add<Mesh>(wir);
	auto& doorMesh = doorEnt.Add<Mesh>(doorM);

	shader = Shader::Create();
	shader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	shader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	shader->Link();

	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 2.0f);
	glm::vec3 lightCol = glm::vec3(1.f, 1.f, 1.f);
	float     lightAmbientPow = 0.05f;
	float     lightSpecularPow = 1.0f;
	glm::vec3 ambientCol = glm::vec3(1.0f);
	float     ambientPow = 0.1f;
	float     shininess = 4.0f;

	shader->SetUniform("u_LightPos", lightPos);
	shader->SetUniform("u_LightCol", lightCol);
	shader->SetUniform("u_AmbientLightStrength", lightAmbientPow);
	shader->SetUniform("u_SpecularLightStrength", lightSpecularPow);
	shader->SetUniform("u_AmbientCol", ambientCol);
	shader->SetUniform("u_AmbientStrength", ambientPow);
	shader->SetUniform("u_Shininess", shininess);

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
	glm::vec3 positionLever = leverTrans.GetPosition();
	glm::vec3 rotationLever = leverTrans.GetRotation();
	glm::vec3 positionLever2 = leverTrans2.GetPosition();
	glm::vec3 rotationLever2 = leverTrans2.GetRotation();
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
					ground.Get<Transform>().SetPositionX(positionGround.x);
				}
				if (ImGui::SliderFloat("PosY", &positionGround.y, -10.0f, 10.0f))
				{
					ground.Get<Transform>().SetPositionY(positionGround.y);
				}
				if (ImGui::SliderFloat("PosZ", &positionGround.z, -10.0f, 10.0f))
				{
					ground.Get<Transform>().SetPositionZ(positionGround.z);
				}
				if (ImGui::SliderFloat("RotX", &rotationGround.x, -360.0f, 360.0f))
				{
					ground.Get<Transform>().SetRotationX(rotationGround.x);
				}
				if (ImGui::SliderFloat("RotY", &rotationGround.y, -360.0f, 360.0f))
				{
					ground.Get<Transform>().SetRotationY(rotationGround.y);
				}
				if (ImGui::SliderFloat("RotZ", &rotationGround.z, -360.0f, 360.0f))
				{
					ground.Get<Transform>().SetRotationZ(rotationGround.z);
				}
			}
			if (ImGui::CollapsingHeader("Left Wall"))
			{
				if (ImGui::SliderFloat("PosX", &positionLeft.x, -10.0f, 10.0f))
				{
					leftWall.Get<Transform>().SetPositionX(positionLeft.x);
				}
				if (ImGui::SliderFloat("PosY", &positionLeft.y, -10.0f, 10.0f))
				{
					leftWall.Get<Transform>().SetPositionY(positionLeft.y);
				}
				if (ImGui::SliderFloat("PosZ", &positionLeft.z, -10.0f, 10.0f))
				{
					leftWall.Get<Transform>().SetPositionZ(positionLeft.z);
				}
				if (ImGui::SliderFloat("RotX", &rotationLeft.x, -360.0f, 360.0f))
				{
					leftWall.Get<Transform>().SetRotationX(rotationLeft.x);
				}
				if (ImGui::SliderFloat("RotY", &rotationLeft.y, -360.0f, 360.0f))
				{
					leftWall.Get<Transform>().SetRotationY(rotationLeft.y);
				}
				if (ImGui::SliderFloat("RotZ", &rotationLeft.z, -360.0f, 360.0f))
				{
					leftWall.Get<Transform>().SetRotationZ(rotationLeft.z);
				}
			}
			if (ImGui::CollapsingHeader("Right Wall"))
			{
				if (ImGui::SliderFloat("PosX", &positionRight.x, -10.0f, 10.0f))
				{
					rightWall.Get<Transform>().SetPositionX(positionRight.x);
				}
				if (ImGui::SliderFloat("PosY", &positionRight.y, -10.0f, 10.0f))
				{
					rightWall.Get<Transform>().SetPositionY(positionRight.y);
				}
				if (ImGui::SliderFloat("PosZ", &positionRight.z, -10.0f, 10.0f))
				{
					rightWall.Get<Transform>().SetPositionZ(positionRight.z);
				}
				if (ImGui::SliderFloat("RotX", &rotationRight.x, -360.0f, 360.0f))
				{
					rightWall.Get<Transform>().SetRotationX(rotationRight.x);
				}
				if (ImGui::SliderFloat("RotY", &rotationRight.y, -360.0f, 360.0f))
				{
					rightWall.Get<Transform>().SetRotationY(rotationRight.y);
				}
				if (ImGui::SliderFloat("RotZ", &rotationRight.z, -360.0f, 360.0f))
				{
					rightWall.Get<Transform>().SetRotationZ(rotationRight.z);
				}
			}
			if (ImGui::CollapsingHeader("Back Wall"))
			{
				if (ImGui::SliderFloat("PosX", &positionBack.x, -10.0f, 10.0f))
				{
					backWall.Get<Transform>().SetPositionX(positionBack.x);
				}
				if (ImGui::SliderFloat("PosY", &positionBack.y, -10.0f, 10.0f))
				{
					backWall.Get<Transform>().SetPositionY(positionBack.y);
				}
				if (ImGui::SliderFloat("PosZ", &positionBack.z, -10.0f, 10.0f))
				{
					backWall.Get<Transform>().SetPositionZ(positionBack.z);
				}
				if (ImGui::SliderFloat("RotX", &rotationBack.x, -360.0f, 360.0f))
				{
					backWall.Get<Transform>().SetRotationX(rotationBack.x);
				}
				if (ImGui::SliderFloat("RotY", &rotationBack.y, -360.0f, 360.0f))
				{
					backWall.Get<Transform>().SetRotationY(rotationBack.y);
				}
				if (ImGui::SliderFloat("RotZ", &rotationBack.z, -360.0f, 360.0f))
				{
					backWall.Get<Transform>().SetRotationZ(rotationBack.z);
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
			if (ImGui::CollapsingHeader("Lever 1"))
			{
				if (ImGui::SliderFloat("PosX", &positionLever.x, -10.0f, 10.0f))
				{
					leverEnt.Get<Transform>().SetPositionX(positionLever.x);
				}
				if (ImGui::SliderFloat("PosY", &positionLever.y, -10.0f, 10.0f))
				{
					leverEnt.Get<Transform>().SetPositionY(positionLever.y);
				}
				if (ImGui::SliderFloat("PosZ", &positionLever.z, -10.0f, 10.0f))
				{
					leverEnt.Get<Transform>().SetPositionZ(positionLever.z);
				}
				if (ImGui::SliderFloat("RotX", &rotationLever.x, -360.0f, 360.0f))
				{
					leverEnt.Get<Transform>().SetRotationX(rotationLever.x);
				}
				if (ImGui::SliderFloat("RotY", &rotationLever.y, -360.0f, 360.0f))
				{
					leverEnt.Get<Transform>().SetRotationY(rotationLever.y);
				}
				if (ImGui::SliderFloat("RotZ", &rotationLever.z, -360.0f, 360.0f))
				{
					leverEnt.Get<Transform>().SetRotationZ(rotationLever.z);
				}
			}
			if (ImGui::CollapsingHeader("Lever 2"))
			{
				if (ImGui::SliderFloat("PosX", &positionLever2.x, -10.0f, 10.0f))
				{
					leverEnt2.Get<Transform>().SetPositionX(positionLever2.x);
				}
				if (ImGui::SliderFloat("PosY", &positionLever2.y, -10.0f, 10.0f))
				{
					leverEnt2.Get<Transform>().SetPositionY(positionLever2.y);
				}
				if (ImGui::SliderFloat("PosZ", &positionLever2.z, -10.0f, 10.0f))
				{
					leverEnt2.Get<Transform>().SetPositionZ(positionLever2.z);
				}
				if (ImGui::SliderFloat("RotX", &rotationLever2.x, -360.0f, 360.0f))
				{
					leverEnt2.Get<Transform>().SetRotationX(rotationLever2.x);
				}
				if (ImGui::SliderFloat("RotY", &rotationLever2.y, -360.0f, 360.0f))
				{
					leverEnt2.Get<Transform>().SetRotationY(rotationLever2.y);
				}
				if (ImGui::SliderFloat("RotZ", &rotationLever2.z, -360.0f, 360.0f))
				{
					leverEnt2.Get<Transform>().SetRotationZ(rotationLever2.z);
				}
			}
		}
		});
#pragma endregion

	if (!imguiStarted)
	{
		InitImGui();
		imguiStarted = true;
	}
}

void Level1::Update(float dt)
{

	//Transforms
	auto& playerTrans = mainPlayer.Get<Transform>();
	auto& groundTrans = ground.Get<Transform>();
	auto& leftTrans = leftWall.Get<Transform>();
	auto& rightTrans = rightWall.Get<Transform>();
	auto& backTrans = backWall.Get<Transform>();
	auto& gateTrans = andEnt.Get<Transform>();
	auto& leverTrans = leverEnt.Get<Transform>();
	auto& wireTrans = wireEnt.Get<Transform>();
	auto& leverTrans2 = leverEnt2.Get<Transform>();
	auto& wireTrans2 = wireEnt2.Get<Transform>();
	auto& doorTrans = doorEnt.Get<Transform>();


	backTrans.SetPositionZ(-10.4f);
	backTrans.SetPositionY(10.4f);
	backTrans.SetRotationX(90.0f);

	leftTrans.SetRotationZ(90.0f);
	leftTrans.SetPositionX(-20.8f);
	leftTrans.SetPositionY(10.4f);

	rightTrans.SetRotationZ(90.0f);
	rightTrans.SetPositionX(20.8f);
	rightTrans.SetPositionY(10.4f);

	//Camera
	auto& camera = camEnt.Get<Camera>();

	//Meshes
	auto& meshMain = mainPlayer.Get<Mesh>();
	auto& groundMesh = ground.Get<Mesh>();
	auto& leftMesh = leftWall.Get<Mesh>();
	auto& rightMesh = rightWall.Get<Mesh>();
	auto& backMesh = backWall.Get<Mesh>();
	auto& gateMesh = andEnt.Get<Mesh>();
	auto& leverMesh = leverEnt.Get<Mesh>();
	auto& wireMesh = wireEnt.Get<Mesh>();
	auto& leverMesh2 = leverEnt2.Get<Mesh>();
	auto& wireMesh2 = wireEnt2.Get<Mesh>();
	auto& doorMesh = doorEnt.Get<Mesh>();

	camera.LookAt(glm::vec3(playerTrans.GetPosition())); // Look at center of the screen

	//Gets the transforms of the objects
	glm::mat4 transform = playerTrans.GetModelMatrix();
	glm::mat4 transformGround = groundTrans.GetModelMatrix();
	glm::mat4 transformLeft = leftTrans.GetModelMatrix();
	glm::mat4 transformRight = rightTrans.GetModelMatrix();
	glm::mat4 transformBack = backTrans.GetModelMatrix();
	glm::mat4 transformGate = gateTrans.GetModelMatrix();
	glm::mat4 transformWire = wireTrans.GetModelMatrix();
	glm::mat4 transformLever = leverTrans.GetModelMatrix();
	glm::mat4 transformWire2 = wireTrans2.GetModelMatrix();
	glm::mat4 transformLever2 = leverTrans2.GetModelMatrix();
	glm::mat4 transformDoor = doorTrans.GetModelMatrix();

	if (camera.GetPosition().z - playerTrans.GetPositionZ() < 7.5f)
		camClose = true;
	else
		camClose = false;

	if (camera.GetPosition().z - playerTrans.GetPositionZ() > 10.0f)
		camFar = true;
	else
		camFar = false;


	if (playerTrans.GetPositionX() - leverTrans.GetPositionX() < 2.0f && playerTrans.GetPositionX() - leverTrans.GetPositionX() > -2.0f
		&& playerTrans.GetPositionZ() - leverTrans.GetPositionZ() < 1.0f && playerTrans.GetPositionZ() - leverTrans.GetPositionZ() > -1.0f)
		lever1Watch.Poll(window);

	if (playerTrans.GetPositionX() - leverTrans2.GetPositionX() < 2.0f && playerTrans.GetPositionX() - leverTrans2.GetPositionX() > -2.0f
		&& playerTrans.GetPositionZ() - leverTrans2.GetPositionZ() < 1.0f && playerTrans.GetPositionZ() - leverTrans2.GetPositionZ() > -1.0f)
		lever2Watch.Poll(window);

	gateWatch.Poll(window);

#pragma region PlayerMovement
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		playerTrans.SetPositionX(playerTrans.GetPositionX() - 5 * dt);
		playerTrans.SetRotationY(270.0f);
		camera.SetPosition(glm::vec3(playerTrans.GetPositionX(), camera.GetPosition().y, camera.GetPosition().z));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		playerTrans.SetPositionX(playerTrans.GetPositionX() + 5 * dt);
		playerTrans.SetRotationY(90.0f);
		camera.SetPosition(glm::vec3(playerTrans.GetPositionX(), camera.GetPosition().y, camera.GetPosition().z));
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		playerTrans.SetPositionZ(playerTrans.GetPositionZ() - 5 * dt);
		playerTrans.SetRotationY(180.0f);

		if (camFar)
			camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z - 5 * dt));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		playerTrans.SetPositionZ(playerTrans.GetPositionZ() + 5 * dt);
		playerTrans.SetRotationY(0.0f);

		if (camClose)
			camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z + 5 * dt));
	}
#pragma endregion

#pragma region CameraMovement
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	{
		camera.SetPosition(glm::vec3(camera.GetPosition().x - 5 * dt, camera.GetPosition().y, camera.GetPosition().z));
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		camera.SetPosition(glm::vec3(camera.GetPosition().x + 5 * dt, camera.GetPosition().y, camera.GetPosition().z));
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z - 5 * dt));
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z + 5 * dt));
	}
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
	{
		camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y + 5 * dt, camera.GetPosition().z));
	}
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
	{
		camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y - 5 * dt, camera.GetPosition().z));
	}
#pragma endregion

#pragma region Renders

	shader->Bind();

	shader->SetUniformMatrix("u_ModelRotation", glm::mat3(transform));
	shader->SetUniformMatrix("u_ModelViewProjection", camera.GetViewProjection() * transform);
	shader->SetUniformMatrix("u_Model", transform);
	shader->SetUniform("u_CamPos", camera.GetPosition());

	meshMain.Render();

	shader->SetUniformMatrix("u_ModelRotation", glm::mat3(transformGround));
	shader->SetUniformMatrix("u_ModelViewProjection", camera.GetViewProjection() * transformGround);
	shader->SetUniformMatrix("u_Model", transformGround);
	shader->SetUniform("u_CamPos", camera.GetPosition());

	groundMesh.Render();

	shader->SetUniformMatrix("u_ModelRotation", glm::mat3(transformLeft));
	shader->SetUniformMatrix("u_ModelViewProjection", camera.GetViewProjection() * transformLeft);
	shader->SetUniformMatrix("u_Model", transformLeft);
	shader->SetUniform("u_CamPos", camera.GetPosition());

	leftMesh.Render();

	shader->SetUniformMatrix("u_ModelRotation", glm::mat3(transformRight));
	shader->SetUniformMatrix("u_ModelViewProjection", camera.GetViewProjection() * transformRight);
	shader->SetUniformMatrix("u_Model", transformRight);
	shader->SetUniform("u_CamPos", camera.GetPosition());

	rightMesh.Render();

	shader->SetUniformMatrix("u_ModelRotation", glm::mat3(transformBack));
	shader->SetUniformMatrix("u_ModelViewProjection", camera.GetViewProjection() * transformBack);
	shader->SetUniformMatrix("u_Model", transformBack);
	shader->SetUniform("u_CamPos", camera.GetPosition());

	backMesh.Render();

	shader->SetUniformMatrix("u_ModelRotation", glm::mat3(transformWire));
	shader->SetUniformMatrix("u_ModelViewProjection", camera.GetViewProjection() * transformWire);
	shader->SetUniformMatrix("u_Model", transformWire);
	shader->SetUniform("u_CamPos", camera.GetPosition());

	wireMesh.Render();

	shader->SetUniformMatrix("u_ModelRotation", glm::mat3(transformLever));
	shader->SetUniformMatrix("u_ModelViewProjection", camera.GetViewProjection() * transformLever);
	shader->SetUniformMatrix("u_Model", transformLever);
	shader->SetUniform("u_CamPos", camera.GetPosition());

	leverMesh.Render();

	shader->SetUniformMatrix("u_ModelRotation", glm::mat3(transformGate));
	shader->SetUniformMatrix("u_ModelViewProjection", camera.GetViewProjection() * transformGate);
	shader->SetUniformMatrix("u_Model", transformGate);
	shader->SetUniform("u_CamPos", camera.GetPosition());

	gateMesh.Render();

	shader->SetUniformMatrix("u_ModelRotation", glm::mat3(transformWire2));
	shader->SetUniformMatrix("u_ModelViewProjection", camera.GetViewProjection() * transformWire2);
	shader->SetUniformMatrix("u_Model", transformWire2);
	shader->SetUniform("u_CamPos", camera.GetPosition());

	wireMesh2.Render();

	shader->SetUniformMatrix("u_ModelRotation", glm::mat3(transformLever2));
	shader->SetUniformMatrix("u_ModelViewProjection", camera.GetViewProjection() * transformLever2);
	shader->SetUniformMatrix("u_Model", transformLever2);
	shader->SetUniform("u_CamPos", camera.GetPosition());

	leverMesh2.Render();

	shader->SetUniformMatrix("u_ModelRotation", glm::mat3(transformDoor));
	shader->SetUniformMatrix("u_ModelViewProjection", camera.GetViewProjection() * transformDoor);
	shader->SetUniformMatrix("u_Model", transformDoor);
	shader->SetUniform("u_CamPos", camera.GetPosition());

	doorMesh.Render();
#pragma endregion	

	leverEnt.Get<Lever>().Update();
	leverEnt2.Get<Lever>().Update();
	wireEnt.Get<Wire>().Update();
	wireEnt2.Get<Wire>().Update();
	andEnt.Get<AndGate>().Update();
	leftWall.Get<AABB>().Update();
	rightWall.Get<AABB>().Update();
	backWall.Get<AABB>().Update();
	doorEnt.Get<AABB>().Update();

	if (doorEnt.Get<AABB>().GetComplete())
		levelComplete = true;

	RenderImGui();
}

void Level1::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}
