//#include "Level3.h"
//#include <iostream>
//#include <GLFW\glfw3.h>
//
//#include "Application.h"
//#include <imgui.h>
//#include <AABB.h>
//
//using namespace freebird;
//
//Level3::Level3(std::string sceneName, GLFWwindow* wind)
//	: Scene(sceneName, wind)
//{
//	mainPlayer = Entity::Create();
//	camEnt = Entity::Create();
//	ground = Entity::Create();
//	leftWall = Entity::Create();
//	rightWall = Entity::Create();
//	backWall = Entity::Create();
//	notEnt = Entity::Create();
//	for (int i = 0; i < 5; ++i)
//	{
//		wires[i] = Entity::Create();
//	}
//	for (int i = 0; i < 3; ++i)
//	{
//		levers[i] = Entity::Create();
//	}
//	for (int i = 0; i < 3; ++i)
//	{
//		andEnts[i] = Entity::Create();
//	}
//	doorEnt = Entity::Create();
//}
//
//void Level3::InitScene()
//{
//	Application::SetClearColor(glm::vec4(0.75f, 0.75f, 0.75f, 1.0f));
//
//	scene = new entt::registry();
//
//	Entity::SetReg(scene);
//
//	shader = Shader::Create();
//	shader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
//	shader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
//	shader->Link();
//
//	glm::vec3 lightPos = glm::vec3(0.0f, 2.0f, -9.0f);
//	glm::vec3 lightDir = glm::vec3(0.0f, -1.0f, 0.0f);
//	glm::vec3 lightCol = glm::vec3(1.f, 1.f, 1.f);
//	float     lightAmbientPow = 0.05f;
//	float     lightSpecularPow = 1.0f;
//	float     lightSpecularPow2 = 0.2f;
//	glm::vec3 ambientCol = glm::vec3(1.0f);
//	float     ambientPow = 0.1f;
//	float     shininess = 4.0f;
//
//	SetShaderValues(shader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);
//
//	//Set Up Camera
//	auto& camera = camEnt.Add<Camera>();
//
//	camera.SetPosition(glm::vec3(0, 8, 15)); // Set initial position
//	camera.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
//	camera.LookAt(glm::vec3(0.0f)); // Look at center of the screen
//	camera.SetFovDegrees(90.0f); // Set an initial FOV
//
//	//Transforms
//	auto& groundTrans = ground.Add<Transform>();
//	groundTrans.SetScale(glm::vec3(2.0f, 1.0f, 2.0f));
//
//	auto& leftTrans = leftWall.Add<Transform>();
//	leftTrans.SetScale(glm::vec3(1.0f, 1.0f, 2.0f));
//
//	auto& rightTrans = rightWall.Add<Transform>();
//	rightTrans.SetScale(glm::vec3(1.0f, 1.0f, 2.0f));
//
//	auto& backTrans = backWall.Add<Transform>();
//	backTrans.SetScale(glm::vec3(2.0f, 1.0f, 1.0f));
//
//	auto& playerTrans = mainPlayer.Add<Transform>();
//	playerTrans.SetPosition(glm::vec3(0.0f, 1.0f, 5.0f));
//	playerTrans.SetRotationY(0.0f);
//
//	auto& andTrans = andEnts[0].Add<Transform>();
//	andTrans.SetPosition(glm::vec3(-6.0f, 1.0f, 2.0f));
//	andTrans.SetRotationY(90.0f);
//
//	auto& andTrans2 = andEnts[1].Add<Transform>();
//	andTrans2.SetPosition(glm::vec3(6.0f, 1.0f, 2.0f));
//	andTrans2.SetRotationY(90.0f);
//
//	auto& andTrans3 = andEnts[2].Add<Transform>();
//	andTrans3.SetPosition(glm::vec3(0.0f, 1.0f, -5.0f));
//	andTrans3.SetRotationY(90.0f);
//
//	auto& notTrans = notEnt.Add<Transform>();
//	notTrans.SetPosition(glm::vec3(0.0f, 1.0f, 5.0f));
//	notTrans.SetRotationY(90.0f);
//
//	auto& wireTrans = wires[0].Add<Transform>();
//	wireTrans.SetPosition(glm::vec3(-6.0f, 1.0f, 5.0f));
//	wireTrans.SetRotationY(90.0f);
//
//	auto& wireTrans2 = wires[1].Add<Transform>();
//	wireTrans2.SetPosition(glm::vec3(6.0f, 1.0f, 5.0f));
//	wireTrans2.SetRotationY(90.0f);
//
//	auto& wireTrans3 = wires[2].Add<Transform>();
//	wireTrans3.SetPosition(glm::vec3(0.0f, 1.0f, 2.0f));
//	wireTrans3.SetRotationY(90.0f);
//
//	auto& wireTrans4 = wires[3].Add<Transform>();
//	wireTrans4.SetPosition(glm::vec3(-3.0f, 1.0f, -1.0f));
//	wireTrans4.SetRotationY(90.0f);
//
//	auto& wireTrans5 = wires[4].Add<Transform>();
//	wireTrans5.SetPosition(glm::vec3(3.0f, 1.0f, -1.0f));
//	wireTrans5.SetRotationY(90.0f);
//
//	auto& leverTrans = levers[0].Add<Transform>();
//	leverTrans.SetPosition(glm::vec3(-6.0f, 1.0f, 8.0f));
//	leverTrans.SetRotationY(90.0f);
//
//	auto& leverTrans2 = levers[1].Add<Transform>();
//	leverTrans2.SetPosition(glm::vec3(0.0f, 1.0f, 8.0f));
//	leverTrans2.SetRotationY(90.0f);
//
//	auto& leverTrans3 = levers[2].Add<Transform>();
//	leverTrans3.SetPosition(glm::vec3(6.0f, 1.0f, 8.0f));
//	leverTrans3.SetRotationY(90.0f);
//
//	auto& doorTrans = doorEnt.Add<Transform>();
//	doorTrans.SetPosition(glm::vec3(0.0f, 1.0f, -10.0f));
//	doorTrans.SetRotationY(90.0f);
//
//	//Gates
//	auto& andGate = andEnts[0].Add<AndGate>(wires[0], wires[2], wires[3]);
//	auto& andGate2 = andEnts[1].Add<AndGate>(wires[1], wires[2], wires[4]);
//	auto& andGate3 = andEnts[2].Add<AndGate>(wires[3], wires[4], doorEnt);
//	auto& notGate = notEnt.Add<NotGate>(levers[1], wires[2]);
//
//	//Levers
//	auto& lever = levers[0].Add<Lever>(wires[0]);
//	lever.SetPowered(false);
//	auto& lever2 = levers[1].Add<Lever>(notEnt);
//	lever2.SetPowered(false);
//	auto& lever3 = levers[2].Add<Lever>(wires[1]);
//	lever3.SetPowered(false);
//
//	//Wires
//	auto& wire = wires[0].Add<Wire>(levers[0]);
//	auto& wire2 = wires[1].Add<Wire>(levers[2]);
//	auto& wire3 = wires[2].Add<Wire>(notEnt);
//	auto& wire4 = wires[3].Add<Wire>(andEnts[0]);
//	auto& wire5 = wires[4].Add<Wire>(andEnts[1]);
//
//	//AABB
//	auto& leftCol = leftWall.Add<AABB>(leftWall, mainPlayer);
//	auto& rightCol = rightWall.Add<AABB>(rightWall, mainPlayer);
//	auto& backCol = backWall.Add<AABB>(backWall, mainPlayer);
//	auto& doorCol = doorEnt.Add<AABB>(doorEnt, mainPlayer);
//	doorCol.SetComplete(false);
//
//	//Door
//	auto& door = doorEnt.Add<Door>();
//	door.SetOpen(false);
//
//
//	//meshes
//	Mesh monkey("Models/Monkey.obj", glm::vec3(1.0f, 0.0f, 0.0f));
//	Mesh test("Models/TestPlane.obj");
//	Mesh gate("Models/invalid.obj", glm::vec3(1.0f, 0.0f, 0.0f));
//	Mesh not("Models/invalid.obj", glm::vec3(1.0f, 1.0f, 0.0f));
//	Mesh lev("Models/invalid.obj", glm::vec3(0.0f, 1.0f, 0.0f));
//	Mesh wir("Models/invalid.obj", glm::vec3(0.0f, 0.0f, 1.0f));
//	Mesh doorM("Models/invalid.obj", glm::vec3(1.0f, 0.0f, 1.0f));
//
//	auto& playerMesh = mainPlayer.Add<MeshRenderer>(mainPlayer, monkey, shader);
//	auto& groundMesh = ground.Add<MeshRenderer>(ground, test, shader);
//	auto& leftMesh = leftWall.Add<MeshRenderer>(leftWall, test, shader);
//	auto& rightMesh = rightWall.Add<MeshRenderer>(rightWall, test, shader);
//	auto& backMesh = backWall.Add<MeshRenderer>(backWall, test, shader);
//	auto& gateMesh = andEnts[0].Add<MeshRenderer>(andEnts[0], gate, shader);
//	auto& gateMesh2 = andEnts[1].Add<MeshRenderer>(andEnts[1], gate, shader);
//	auto& gateMesh3 = andEnts[2].Add<MeshRenderer>(andEnts[2], gate, shader);
//	auto& notMesh = notEnt.Add<MeshRenderer>(notEnt, not, shader);
//	auto& wireMesh = wires[0].Add<MeshRenderer>(wires[0], wir, shader);
//	auto& wireMesh2 = wires[1].Add<MeshRenderer>(wires[1], wir, shader);
//	auto& wireMesh3 = wires[2].Add<MeshRenderer>(wires[2], wir, shader);
//	auto& wireMesh4 = wires[3].Add<MeshRenderer>(wires[3], wir, shader);
//	auto& wireMesh5 = wires[4].Add<MeshRenderer>(wires[4], wir, shader);
//	auto& leverMesh = levers[0].Add<MeshRenderer>(levers[0], lev, shader);
//	auto& leverMesh2 = levers[1].Add<MeshRenderer>(levers[1], lev, shader);
//	auto& leverMesh3 = levers[2].Add<MeshRenderer>(levers[2], lev, shader);
//	auto& doorMesh = doorEnt.Add<MeshRenderer>(doorEnt, doorM, shader);
//
//	//Commented ImGui
//	/*
//#pragma region Entity ImGui Editor
//	glm::vec3 position = playerTrans.GetPosition();
//	glm::vec3 rotation = playerTrans.GetRotation();
//	glm::vec3 positionGround = groundTrans.GetPosition();
//	glm::vec3 rotationGround = groundTrans.GetRotation();
//	glm::vec3 positionLeft = leftTrans.GetPosition();
//	glm::vec3 rotationLeft = leftTrans.GetRotation();
//	glm::vec3 positionRight = rightTrans.GetPosition();
//	glm::vec3 rotationRight = rightTrans.GetRotation();
//	glm::vec3 positionBack = backTrans.GetPosition();
//	glm::vec3 rotationBack = backTrans.GetRotation();
//	glm::vec3 positionWire = wireTrans.GetPosition();
//	glm::vec3 rotationWire = wireTrans.GetRotation();
//	glm::vec3 positionWire2 = wireTrans2.GetPosition();
//	glm::vec3 rotationWire2 = wireTrans2.GetRotation();
//	glm::vec3 positionLever = leverTrans.GetPosition();
//	glm::vec3 rotationLever = leverTrans.GetRotation();
//	glm::vec3 positionLever2 = leverTrans2.GetPosition();
//	glm::vec3 rotationLever2 = leverTrans2.GetRotation();
//	glm::vec3 positionGate = andTrans.GetPosition();
//	glm::vec3 rotationGate = andTrans.GetRotation();
//
//	imGuiCallbacks.push_back([&]() {
//		if (ImGui::CollapsingHeader("Entities"))
//		{
//			if (ImGui::CollapsingHeader("Chicken"))
//			{
//				if (ImGui::SliderFloat("PosX", &position.x, -10.0f, 10.0f))
//				{
//					mainPlayer.Get<Transform>().SetPositionX(position.x);
//				}
//				if (ImGui::SliderFloat("PosY", &position.y, -10.0f, 10.0f))
//				{
//					mainPlayer.Get<Transform>().SetPositionY(position.y);
//				}
//				if (ImGui::SliderFloat("PosZ", &position.z, -10.0f, 10.0f))
//				{
//					mainPlayer.Get<Transform>().SetPositionZ(position.z);
//				}
//				if (ImGui::SliderFloat("RotX", &rotation.x, -360.0f, 360.0f))
//				{
//					mainPlayer.Get<Transform>().SetRotationX(rotation.x);
//				}
//				if (ImGui::SliderFloat("RotY", &rotation.y, -360.0f, 360.0f))
//				{
//					mainPlayer.Get<Transform>().SetRotationY(rotation.y);
//				}
//				if (ImGui::SliderFloat("RotZ", &rotation.z, -360.0f, 360.0f))
//				{
//					mainPlayer.Get<Transform>().SetRotationZ(rotation.z);
//				}
//			}
//			if (ImGui::CollapsingHeader("Ground"))
//			{
//				if (ImGui::SliderFloat("PosX", &positionGround.x, -10.0f, 10.0f))
//				{
//					ground.Get<Transform>().SetPositionX(positionGround.x);
//				}
//				if (ImGui::SliderFloat("PosY", &positionGround.y, -10.0f, 10.0f))
//				{
//					ground.Get<Transform>().SetPositionY(positionGround.y);
//				}
//				if (ImGui::SliderFloat("PosZ", &positionGround.z, -10.0f, 10.0f))
//				{
//					ground.Get<Transform>().SetPositionZ(positionGround.z);
//				}
//				if (ImGui::SliderFloat("RotX", &rotationGround.x, -360.0f, 360.0f))
//				{
//					ground.Get<Transform>().SetRotationX(rotationGround.x);
//				}
//				if (ImGui::SliderFloat("RotY", &rotationGround.y, -360.0f, 360.0f))
//				{
//					ground.Get<Transform>().SetRotationY(rotationGround.y);
//				}
//				if (ImGui::SliderFloat("RotZ", &rotationGround.z, -360.0f, 360.0f))
//				{
//					ground.Get<Transform>().SetRotationZ(rotationGround.z);
//				}
//			}
//			if (ImGui::CollapsingHeader("Left Wall"))
//			{
//				if (ImGui::SliderFloat("PosX", &positionLeft.x, -10.0f, 10.0f))
//				{
//					leftWall.Get<Transform>().SetPositionX(positionLeft.x);
//				}
//				if (ImGui::SliderFloat("PosY", &positionLeft.y, -10.0f, 10.0f))
//				{
//					leftWall.Get<Transform>().SetPositionY(positionLeft.y);
//				}
//				if (ImGui::SliderFloat("PosZ", &positionLeft.z, -10.0f, 10.0f))
//				{
//					leftWall.Get<Transform>().SetPositionZ(positionLeft.z);
//				}
//				if (ImGui::SliderFloat("RotX", &rotationLeft.x, -360.0f, 360.0f))
//				{
//					leftWall.Get<Transform>().SetRotationX(rotationLeft.x);
//				}
//				if (ImGui::SliderFloat("RotY", &rotationLeft.y, -360.0f, 360.0f))
//				{
//					leftWall.Get<Transform>().SetRotationY(rotationLeft.y);
//				}
//				if (ImGui::SliderFloat("RotZ", &rotationLeft.z, -360.0f, 360.0f))
//				{
//					leftWall.Get<Transform>().SetRotationZ(rotationLeft.z);
//				}
//			}
//			if (ImGui::CollapsingHeader("Right Wall"))
//			{
//				if (ImGui::SliderFloat("PosX", &positionRight.x, -10.0f, 10.0f))
//				{
//					rightWall.Get<Transform>().SetPositionX(positionRight.x);
//				}
//				if (ImGui::SliderFloat("PosY", &positionRight.y, -10.0f, 10.0f))
//				{
//					rightWall.Get<Transform>().SetPositionY(positionRight.y);
//				}
//				if (ImGui::SliderFloat("PosZ", &positionRight.z, -10.0f, 10.0f))
//				{
//					rightWall.Get<Transform>().SetPositionZ(positionRight.z);
//				}
//				if (ImGui::SliderFloat("RotX", &rotationRight.x, -360.0f, 360.0f))
//				{
//					rightWall.Get<Transform>().SetRotationX(rotationRight.x);
//				}
//				if (ImGui::SliderFloat("RotY", &rotationRight.y, -360.0f, 360.0f))
//				{
//					rightWall.Get<Transform>().SetRotationY(rotationRight.y);
//				}
//				if (ImGui::SliderFloat("RotZ", &rotationRight.z, -360.0f, 360.0f))
//				{
//					rightWall.Get<Transform>().SetRotationZ(rotationRight.z);
//				}
//			}
//			if (ImGui::CollapsingHeader("Back Wall"))
//			{
//				if (ImGui::SliderFloat("PosX", &positionBack.x, -10.0f, 10.0f))
//				{
//					backWall.Get<Transform>().SetPositionX(positionBack.x);
//				}
//				if (ImGui::SliderFloat("PosY", &positionBack.y, -10.0f, 10.0f))
//				{
//					backWall.Get<Transform>().SetPositionY(positionBack.y);
//				}
//				if (ImGui::SliderFloat("PosZ", &positionBack.z, -10.0f, 10.0f))
//				{
//					backWall.Get<Transform>().SetPositionZ(positionBack.z);
//				}
//				if (ImGui::SliderFloat("RotX", &rotationBack.x, -360.0f, 360.0f))
//				{
//					backWall.Get<Transform>().SetRotationX(rotationBack.x);
//				}
//				if (ImGui::SliderFloat("RotY", &rotationBack.y, -360.0f, 360.0f))
//				{
//					backWall.Get<Transform>().SetRotationY(rotationBack.y);
//				}
//				if (ImGui::SliderFloat("RotZ", &rotationBack.z, -360.0f, 360.0f))
//				{
//					backWall.Get<Transform>().SetRotationZ(rotationBack.z);
//				}
//			}
//			if (ImGui::CollapsingHeader("Gate"))
//			{
//				if (ImGui::SliderFloat("PosX", &positionGate.x, -10.0f, 10.0f))
//				{
//					andEnt.Get<Transform>().SetPositionX(positionGate.x);
//				}
//				if (ImGui::SliderFloat("PosY", &positionGate.y, -10.0f, 10.0f))
//				{
//					andEnt.Get<Transform>().SetPositionY(positionGate.y);
//				}
//				if (ImGui::SliderFloat("PosZ", &positionGate.z, -10.0f, 10.0f))
//				{
//					andEnt.Get<Transform>().SetPositionZ(positionGate.z);
//				}
//				if (ImGui::SliderFloat("RotX", &rotationGate.x, -360.0f, 360.0f))
//				{
//					andEnt.Get<Transform>().SetRotationX(rotationGate.x);
//				}
//				if (ImGui::SliderFloat("RotY", &rotationGate.y, -360.0f, 360.0f))
//				{
//					andEnt.Get<Transform>().SetRotationY(rotationGate.y);
//				}
//				if (ImGui::SliderFloat("RotZ", &rotationGate.z, -360.0f, 360.0f))
//				{
//					andEnt.Get<Transform>().SetRotationZ(rotationGate.z);
//				}
//			}
//			if (ImGui::CollapsingHeader("Wire 1"))
//			{
//				if (ImGui::SliderFloat("PosX", &positionWire.x, -10.0f, 10.0f))
//				{
//					wireEnt.Get<Transform>().SetPositionX(positionWire.x);
//				}
//				if (ImGui::SliderFloat("PosY", &positionWire.y, -10.0f, 10.0f))
//				{
//					wireEnt.Get<Transform>().SetPositionY(positionWire.y);
//				}
//				if (ImGui::SliderFloat("PosZ", &positionWire.z, -10.0f, 10.0f))
//				{
//					wireEnt.Get<Transform>().SetPositionZ(positionWire.z);
//				}
//				if (ImGui::SliderFloat("RotX", &rotationWire.x, -360.0f, 360.0f))
//				{
//					wireEnt.Get<Transform>().SetRotationX(rotationWire.x);
//				}
//				if (ImGui::SliderFloat("RotY", &rotationWire.y, -360.0f, 360.0f))
//				{
//					wireEnt.Get<Transform>().SetRotationY(rotationWire.y);
//				}
//				if (ImGui::SliderFloat("RotZ", &rotationWire.z, -360.0f, 360.0f))
//				{
//					wireEnt.Get<Transform>().SetRotationZ(rotationWire.z);
//				}
//			}
//			if (ImGui::CollapsingHeader("Wire 2"))
//			{
//				if (ImGui::SliderFloat("PosX", &positionWire2.x, -10.0f, 10.0f))
//				{
//					wireEnt2.Get<Transform>().SetPositionX(positionWire2.x);
//				}
//				if (ImGui::SliderFloat("PosY", &positionWire2.y, -10.0f, 10.0f))
//				{
//					wireEnt2.Get<Transform>().SetPositionY(positionWire2.y);
//				}
//				if (ImGui::SliderFloat("PosZ", &positionWire2.z, -10.0f, 10.0f))
//				{
//					wireEnt2.Get<Transform>().SetPositionZ(positionWire2.z);
//				}
//				if (ImGui::SliderFloat("RotX", &rotationWire2.x, -360.0f, 360.0f))
//				{
//					wireEnt2.Get<Transform>().SetRotationX(rotationWire2.x);
//				}
//				if (ImGui::SliderFloat("RotY", &rotationWire2.y, -360.0f, 360.0f))
//				{
//					wireEnt2.Get<Transform>().SetRotationY(rotationWire2.y);
//				}
//				if (ImGui::SliderFloat("RotZ", &rotationWire2.z, -360.0f, 360.0f))
//				{
//					wireEnt2.Get<Transform>().SetRotationZ(rotationWire2.z);
//				}
//			}
//			if (ImGui::CollapsingHeader("Lever 1"))
//			{
//				if (ImGui::SliderFloat("PosX", &positionLever.x, -10.0f, 10.0f))
//				{
//					leverEnt.Get<Transform>().SetPositionX(positionLever.x);
//				}
//				if (ImGui::SliderFloat("PosY", &positionLever.y, -10.0f, 10.0f))
//				{
//					leverEnt.Get<Transform>().SetPositionY(positionLever.y);
//				}
//				if (ImGui::SliderFloat("PosZ", &positionLever.z, -10.0f, 10.0f))
//				{
//					leverEnt.Get<Transform>().SetPositionZ(positionLever.z);
//				}
//				if (ImGui::SliderFloat("RotX", &rotationLever.x, -360.0f, 360.0f))
//				{
//					leverEnt.Get<Transform>().SetRotationX(rotationLever.x);
//				}
//				if (ImGui::SliderFloat("RotY", &rotationLever.y, -360.0f, 360.0f))
//				{
//					leverEnt.Get<Transform>().SetRotationY(rotationLever.y);
//				}
//				if (ImGui::SliderFloat("RotZ", &rotationLever.z, -360.0f, 360.0f))
//				{
//					leverEnt.Get<Transform>().SetRotationZ(rotationLever.z);
//				}
//			}
//			if (ImGui::CollapsingHeader("Lever 2"))
//			{
//				if (ImGui::SliderFloat("PosX", &positionLever2.x, -10.0f, 10.0f))
//				{
//					leverEnt2.Get<Transform>().SetPositionX(positionLever2.x);
//				}
//				if (ImGui::SliderFloat("PosY", &positionLever2.y, -10.0f, 10.0f))
//				{
//					leverEnt2.Get<Transform>().SetPositionY(positionLever2.y);
//				}
//				if (ImGui::SliderFloat("PosZ", &positionLever2.z, -10.0f, 10.0f))
//				{
//					leverEnt2.Get<Transform>().SetPositionZ(positionLever2.z);
//				}
//				if (ImGui::SliderFloat("RotX", &rotationLever2.x, -360.0f, 360.0f))
//				{
//					leverEnt2.Get<Transform>().SetRotationX(rotationLever2.x);
//				}
//				if (ImGui::SliderFloat("RotY", &rotationLever2.y, -360.0f, 360.0f))
//				{
//					leverEnt2.Get<Transform>().SetRotationY(rotationLever2.y);
//				}
//				if (ImGui::SliderFloat("RotZ", &rotationLever2.z, -360.0f, 360.0f))
//				{
//					leverEnt2.Get<Transform>().SetRotationZ(rotationLever2.z);
//				}
//			}
//		}
//		});
//#pragma endregion
//		*/
//
//
//	/*if (!imguiStarted)
//	{
//		InitImGui();
//		imguiStarted = true;
//	}*/
//
//
//	points.push_back(glm::vec3(3.0f, 5.0f, 6.0f));
//	points.push_back(glm::vec3(-3.0f, 5.0f, 6.0f));
//	points.push_back(glm::vec3(-3.0f, 5.0f, 0.0f));
//	points.push_back(glm::vec3(3.0f, 5.0f, 0.0f));
//
//
//	segmentTime = 1.0f;
//
//	if (points.size() > 0)
//		currentPos = points[0];
//
//	StartSegment(0);
//}
//
//void Level3::Update(float dt)
//{
//	timer += dt;
//
//	if (points.size() >= 4)
//	{
//		t = glm::min(t + dt / segmentTime, 1.0f);
//
//		int p1 = currentIndex;
//
//		int p0 = currentIndex - 1;
//
//		if (p0 < 0)
//		{
//			p0 = points.size() - 1;
//		}
//
//		int p2 = currentIndex + 1;
//
//		if (p2 >= points.size())
//			p2 = 0;
//
//		int p3 = p2 + 1;
//
//		if (p3 >= points.size())
//			p3 = 0;
//
//		currentPos = Catmull(points[p0], points[p1], points[p2], points[p3], t);
//
//		if (t >= 1.0f)
//			StartSegment(currentIndex + 1);
//	}
//
//	shader->SetUniform("u_Position", currentPos);
//	shader->SetUniform("u_Time", timer);
//
//	//Transforms
//	auto& playerTrans = mainPlayer.Get<Transform>();
//	auto& groundTrans = ground.Get<Transform>();
//	auto& leftTrans = leftWall.Get<Transform>();
//	auto& rightTrans = rightWall.Get<Transform>();
//	auto& backTrans = backWall.Get<Transform>();
//	auto& andTrans = andEnts[0].Get<Transform>();
//	auto& andTrans2 = andEnts[1].Get<Transform>();
//	auto& andTrans3 = andEnts[2].Get<Transform>();
//	auto& notTrans = notEnt.Get<Transform>();
//	auto& leverTrans = levers[0].Get<Transform>();
//	auto& leverTrans2 = levers[1].Get<Transform>();
//	auto& leverTrans3 = levers[2].Get<Transform>();
//	auto& wireTrans = wires[0].Get<Transform>();
//	auto& wireTrans2 = wires[1].Get<Transform>();
//	auto& wireTrans3 = wires[2].Get<Transform>();
//	auto& wireTrans4 = wires[3].Get<Transform>();
//	auto& wireTrans5 = wires[4].Get<Transform>();
//	auto& doorTrans = doorEnt.Get<Transform>();
//
//
//	backTrans.SetPositionZ(-10.4f);
//	backTrans.SetPositionY(10.4f);
//	backTrans.SetRotationX(90.0f);
//
//	leftTrans.SetRotationZ(90.0f);
//	leftTrans.SetPositionX(-20.8f);
//	leftTrans.SetPositionY(10.4f);
//
//	rightTrans.SetRotationZ(90.0f);
//	rightTrans.SetPositionX(20.8f);
//	rightTrans.SetPositionY(10.4f);
//
//	//Camera
//	auto& camera = camEnt.Get<Camera>();
//
//	//Meshes
//	auto& meshMain = mainPlayer.Get<MeshRenderer>();
//	auto& groundMesh = ground.Get<MeshRenderer>();
//	auto& leftMesh = leftWall.Get<MeshRenderer>();
//	auto& rightMesh = rightWall.Get<MeshRenderer>();
//	auto& backMesh = backWall.Get<MeshRenderer>();
//	auto& andMesh = andEnts[0].Get<MeshRenderer>();
//	auto& andMesh2 = andEnts[1].Get<MeshRenderer>();
//	auto& andMesh3 = andEnts[2].Get<MeshRenderer>();
//	auto& notMesh = notEnt.Get<MeshRenderer>();
//	auto& leverMesh = levers[0].Get<MeshRenderer>();
//	auto& leverMesh2 = levers[1].Get<MeshRenderer>();
//	auto& leverMesh3 = levers[2].Get<MeshRenderer>();
//	auto& wireMesh = wires[0].Get<MeshRenderer>();
//	auto& wireMesh2 = wires[1].Get<MeshRenderer>();
//	auto& wireMesh3 = wires[2].Get<MeshRenderer>();
//	auto& wireMesh4 = wires[3].Get<MeshRenderer>();
//	auto& wireMesh5 = wires[4].Get<MeshRenderer>();
//	auto& doorMesh = doorEnt.Get<MeshRenderer>();
//
//	camera.LookAt(glm::vec3(playerTrans.GetPosition())); // Look at center of the screen
//
//	//Gets the transforms of the objects
//	glm::mat4 transform = playerTrans.GetModelMatrix();
//	glm::mat4 transformGround = groundTrans.GetModelMatrix();
//	glm::mat4 transformLeft = leftTrans.GetModelMatrix();
//	glm::mat4 transformRight = rightTrans.GetModelMatrix();
//	glm::mat4 transformBack = backTrans.GetModelMatrix();
//	glm::mat4 transformGate = andTrans.GetModelMatrix();
//	glm::mat4 transformGate2 = andTrans2.GetModelMatrix();
//	glm::mat4 transformGate3 = andTrans3.GetModelMatrix();
//	glm::mat4 transformNot = notTrans.GetModelMatrix();
//	glm::mat4 transformWire = wireTrans.GetModelMatrix();
//	glm::mat4 transformWire2 = wireTrans2.GetModelMatrix();
//	glm::mat4 transformWire3 = wireTrans3.GetModelMatrix();
//	glm::mat4 transformWire4 = wireTrans4.GetModelMatrix();
//	glm::mat4 transformWire5 = wireTrans5.GetModelMatrix();
//	glm::mat4 transformLever = leverTrans.GetModelMatrix();
//	glm::mat4 transformLever2 = leverTrans2.GetModelMatrix();
//	glm::mat4 transformLever3 = leverTrans3.GetModelMatrix();
//	glm::mat4 transformDoor = doorTrans.GetModelMatrix();
//
//	if (camera.GetPosition().z - playerTrans.GetPositionZ() < 7.5f)
//		camClose = true;
//	else
//		camClose = false;
//
//	if (camera.GetPosition().z - playerTrans.GetPositionZ() > 10.0f)
//		camFar = true;
//	else
//		camFar = false;
//
//
//	for (int i = 0; i < 3; ++i)
//	{
//		if (playerTrans.GetPositionX() - levers[i].Get<Transform>().GetPositionX() < 2.0f
//			&& playerTrans.GetPositionX() - levers[i].Get<Transform>().GetPositionX() > -2.0f
//			&& playerTrans.GetPositionZ() - levers[i].Get<Transform>().GetPositionZ() < 1.0f
//			&& playerTrans.GetPositionZ() - levers[i].Get<Transform>().GetPositionZ() > -1.0f)
//		{
//			if (i == 0)
//				lever1Watch.Poll(window);
//			if (i == 1)
//				lever2Watch.Poll(window);
//			if (i == 2)
//				lever3Watch.Poll(window);
//		}
//	}
//
//#pragma region PlayerMovement
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//	{
//		playerTrans.SetPositionX(playerTrans.GetPositionX() - 5 * dt);
//		playerTrans.SetRotationY(270.0f);
//		camera.SetPosition(glm::vec3(playerTrans.GetPositionX(), camera.GetPosition().y, camera.GetPosition().z));
//	}
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//	{
//		playerTrans.SetPositionX(playerTrans.GetPositionX() + 5 * dt);
//		playerTrans.SetRotationY(90.0f);
//		camera.SetPosition(glm::vec3(playerTrans.GetPositionX(), camera.GetPosition().y, camera.GetPosition().z));
//	}
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//	{
//		playerTrans.SetPositionZ(playerTrans.GetPositionZ() - 5 * dt);
//		playerTrans.SetRotationY(180.0f);
//
//		if (camFar)
//			camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z - 5 * dt));
//	}
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//	{
//		playerTrans.SetPositionZ(playerTrans.GetPositionZ() + 5 * dt);
//		playerTrans.SetRotationY(0.0f);
//
//		if (camClose)
//			camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z + 5 * dt));
//	}
//#pragma endregion
//
//#pragma region CameraMovement
//	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
//	{
//		camera.SetPosition(glm::vec3(camera.GetPosition().x - 5 * dt, camera.GetPosition().y, camera.GetPosition().z));
//	}
//	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
//	{
//		camera.SetPosition(glm::vec3(camera.GetPosition().x + 5 * dt, camera.GetPosition().y, camera.GetPosition().z));
//	}
//	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
//	{
//		camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z - 5 * dt));
//	}
//	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
//	{
//		camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z + 5 * dt));
//	}
//	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
//	{
//		camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y + 5 * dt, camera.GetPosition().z));
//	}
//	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
//	{
//		camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y - 5 * dt, camera.GetPosition().z));
//	}
//#pragma endregion
//
//#pragma region Renders
//
//	shader->Bind();
//
//	meshMain.Render(camera, transform);
//	groundMesh.Render(camera, transformGround);
//	leftMesh.Render(camera, transformLeft);
//	rightMesh.Render(camera, transformRight);
//	backMesh.Render(camera, transformBack);
//	wireMesh.Render(camera, transformWire);
//	wireMesh2.Render(camera, transformWire2);
//	wireMesh3.Render(camera, transformWire3);
//	wireMesh4.Render(camera, transformWire4);
//	wireMesh5.Render(camera, transformWire5);
//	leverMesh.Render(camera, transformLever);
//	leverMesh2.Render(camera, transformLever2);
//	leverMesh3.Render(camera, transformLever3);
//	andMesh.Render(camera, transformGate);
//	andMesh2.Render(camera, transformGate2);
//	andMesh3.Render(camera, transformGate3);
//	notMesh.Render(camera, transformNot);
//	doorMesh.Render(camera, transformDoor);
//
//#pragma endregion	
//
//	for (int i = 0; i < 3; ++i)
//	{
//		levers[i].Get<Lever>().Update();
//	}
//	for (int i = 0; i < 5; ++i)
//	{
//		wires[i].Get<Wire>().Update();
//	}
//	andEnts[0].Get<AndGate>().Update();
//	andEnts[1].Get<AndGate>().Update();
//	andEnts[2].Get<AndGate>().Update();
//	notEnt.Get<NotGate>().Update();
//	leftWall.Get<AABB>().Update();
//	rightWall.Get<AABB>().Update();
//	backWall.Get<AABB>().Update();
//	doorEnt.Get<AABB>().Update();
//
//	if (doorEnt.Get<AABB>().GetComplete())
//		levelComplete = true;
//
//	/*RenderImGui();*/
//}
//
//void Level3::Unload()
//{
//	if (scene != nullptr)
//	{
//		delete scene;
//
//		scene = nullptr;
//	}
//}
//
//glm::vec3 Level3::Catmull(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float t)
//{
//	return 0.5f * (2.0f * p1 + t * (-p0 + p2)
//		+ t * t * (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3)
//		+ t * t * t * (-p0 + 3.0f * p1 - 3.0f * p2 + p3));
//}
//
//float Level3::InverseLerp(float p, float p0, float p1)
//{
//	return (p - p0) / (p1 - p0);
//}
//
//void Level3::StartSegment(int startInd)
//{
//	currentIndex = startInd;
//
//	if (currentIndex >= points.size())
//		currentIndex = 0;
//
//	t = 0.0f;
//}
//
//

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

	floorShader = Shader::Create();
	floorShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	floorShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	floorShader->Link();

	SetShaderValues(floorShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

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

	untexturedShader = Shader::Create();
	untexturedShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	untexturedShader->LoadShaderPartFromFile("Shaders/frag_untextured.glsl", GL_FRAGMENT_SHADER);
	untexturedShader->Link();

	SetShaderValues(untexturedShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

#pragma endregion

#pragma region Texture Stuff
	Texture2DData::sptr buttonMap = Texture2DData::LoadFromFile("Textures/ButtonTexture.png");
	Texture2DData::sptr drumstickMap = Texture2DData::LoadFromFile("Textures/DrumstickTexture.png");
	Texture2DData::sptr doorMap = Texture2DData::LoadFromFile("Textures/DoorTexture.png");
	Texture2DData::sptr floorMap = Texture2DData::LoadFromFile("Textures/FloorTexture.jpg");
	Texture2DData::sptr wallMap = Texture2DData::LoadFromFile("Textures/WallTexture.jpg");
	Texture2DData::sptr wireMap = Texture2DData::LoadFromFile("Textures/WireTexture.png");

	Texture2D::sptr diffuseButton = Texture2D::Create();
	diffuseButton->LoadData(buttonMap);

	Texture2D::sptr diffuseDrum = Texture2D::Create();
	diffuseDrum->LoadData(drumstickMap);

	Texture2D::sptr diffuseDoor = Texture2D::Create();
	diffuseDoor->LoadData(doorMap);

	Texture2D::sptr diffuseFloor = Texture2D::Create();
	diffuseFloor->LoadData(floorMap);

	Texture2D::sptr diffuseWall = Texture2D::Create();
	diffuseWall->LoadData(wallMap);

	Texture2D::sptr diffuseWire = Texture2D::Create();
	diffuseWire->LoadData(wireMap);

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
	doorTrans.SetPosition(glm::vec3(0.0f, 5.0f, -46.0f));
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
	notTrans.SetPosition(glm::vec3(-230.5f, 1.0f, -3.0f));

	auto& coilTrans = coilEnt.Add<Transform>();
	coilTrans.SetPosition(glm::vec3(-15.0f, 1.0f, -46.0f));

	//AABB
	auto& leftCol = leftEnt.Add<AABB>(leftEnt, mainPlayer);
	auto& rightCol = rightEnt.Add<AABB>(rightEnt, mainPlayer);
	auto& backCol = backEnt.Add<AABB>(backEnt, mainPlayer);
	auto& gateCol = andEnt.Add<AABB>(andEnt, mainPlayer);
	auto& gateCol2 = andEnt2.Add<AABB>(andEnt2, mainPlayer);
	auto& gateCol3 = andEnt3.Add<AABB>(andEnt3, mainPlayer);
	auto& gateCol4 = notEnt.Add<AABB>(notEnt, mainPlayer);
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

	Mesh drumstick("Models/Drumstick.obj");
	Mesh floor("Models/Floor.obj");
	Mesh wall("Models/Wall.obj");
	Mesh doorM("Models/Door.obj");
	Mesh pipe("Models/Level1Pipe.obj", glm::vec3(0.6f, 0.45f, 0.0f));
	Mesh buttonM("Models/Button.obj");
	Mesh wireM1("Models/Level3Wire1.obj", glm::vec3(1.0f, 0.0f, 0.0f));
	Mesh wireM2("Models/Level3Wire2.obj", glm::vec3(1.0f, 0.0f, 0.0f));
	Mesh wireM3("Models/Level3Wire3.obj", glm::vec3(1.0f, 0.0f, 0.0f));
	Mesh wireM4("Models/Level3Wire4.obj", glm::vec3(1.0f, 0.0f, 0.0f));
	Mesh wireM5("Models/Level3Wire5.obj", glm::vec3(1.0f, 0.0f, 0.0f));
	Mesh wireM6("Models/Level3Wire6.obj", glm::vec3(1.0f, 0.0f, 0.0f));
	Mesh wireM7("Models/Level3Wire7.obj", glm::vec3(1.0f, 0.0f, 0.0f));
	Mesh wire1Power("Models/Level3Wire1.obj", glm::vec3(0.0f, 1.0f, 0.0f));
	Mesh wire2Power("Models/Level3Wire2.obj", glm::vec3(0.0f, 1.0f, 0.0f));
	Mesh wire3Power("Models/Level3Wire3.obj", glm::vec3(0.0f, 1.0f, 0.0f));
	Mesh wire4Power("Models/Level3Wire4.obj", glm::vec3(0.0f, 1.0f, 0.0f));
	Mesh wire5Power("Models/Level3Wire5.obj", glm::vec3(0.0f, 1.0f, 0.0f));
	Mesh wire6Power("Models/Level3Wire6.obj", glm::vec3(0.0f, 1.0f, 0.0f));
	Mesh wire7Power("Models/Level3Wire7.obj", glm::vec3(0.0f, 1.0f, 0.0f));
	Mesh gate("Models/AndGate.obj", glm::vec3(0.0f, 0.0f, 1.0f));
	Mesh not("Models/NotGate.obj", glm::vec3(1.0f, 0.0f, 1.0f));
	Mesh coil("Models/Coil.obj", glm::vec3(1.0f, 0.0f, 0.0f));
	Mesh coilP("Models/Coil.obj", glm::vec3(0.0f, 1.0f, 0.0f));

	auto& playerMesh = mainPlayer.Add<MorphRenderer>(mainPlayer, drumstick, playerShader);
	auto& floorMesh = floorEnt.Add<MeshRenderer>(floorEnt, floor, floorShader);
	auto& leftMesh = leftEnt.Add<MeshRenderer>(leftEnt, wall, levelShader);
	auto& rightMesh = rightEnt.Add<MeshRenderer>(rightEnt, wall, levelShader);
	auto& backMesh = backEnt.Add<MeshRenderer>(backEnt, wall, levelShader);
	auto& notMesh = notEnt.Add<MeshRenderer>(notEnt, not, untexturedShader);
	auto& gateMesh = andEnt.Add<MeshRenderer>(andEnt, gate, untexturedShader);
	auto& gateMesh2 = andEnt2.Add<MeshRenderer>(andEnt2, gate, untexturedShader);
	auto& gateMesh3 = andEnt3.Add<MeshRenderer>(andEnt3, gate, untexturedShader);
	auto& buttonMesh = buttonEnt.Add<MeshRenderer>(buttonEnt, buttonM, buttonShader);
	auto& buttonMesh2 = buttonEnt2.Add<MeshRenderer>(buttonEnt2, buttonM, buttonShader);
	auto& buttonMesh3 = buttonEnt3.Add<MeshRenderer>(buttonEnt3, buttonM, buttonShader);
	auto& wireMesh = wireEnt.Add<MeshRenderer>(wireEnt, wireM1, wireShader);
	auto& wireMesh2 = wireEnt2.Add<MeshRenderer>(wireEnt2, wireM2, wireShader);
	auto& wireMesh3 = wireEnt3.Add<MeshRenderer>(wireEnt3, wireM3, wireShader);
	auto& wireMesh4 = wireEnt4.Add<MeshRenderer>(wireEnt4, wireM4, wireShader);
	auto& wireMesh5 = wireEnt5.Add<MeshRenderer>(wireEnt5, wireM5, wireShader);
	auto& wireMesh6 = wireEnt6.Add<MeshRenderer>(wireEnt6, wireM6, wireShader);
	auto& wireMesh7 = wireEnt7.Add<MeshRenderer>(wireEnt7, wireM7, wireShader);
	auto& wireMeshP = wirePowered.Add<MeshRenderer>(wirePowered, wire1Power, wireShader);
	auto& wireMeshP2 = wirePowered2.Add<MeshRenderer>(wirePowered2, wire2Power, wireShader);
	auto& wireMeshP3 = wirePowered3.Add<MeshRenderer>(wirePowered3, wire3Power, wireShader);
	auto& wireMeshP4 = wirePowered4.Add<MeshRenderer>(wirePowered4, wire4Power, wireShader);
	auto& wireMeshP5 = wirePowered5.Add<MeshRenderer>(wirePowered5, wire5Power, wireShader);
	auto& wireMeshP6 = wirePowered6.Add<MeshRenderer>(wirePowered6, wire6Power, wireShader);
	auto& wireMeshP7 = wirePowered7.Add<MeshRenderer>(wirePowered7, wire7Power, wireShader);
	auto& doorMesh = doorEnt.Add<MeshRenderer>(doorEnt, doorM, doorShader);
	auto& coilMesh = coilEnt.Add<MeshRenderer>(coilEnt, coil, untexturedShader);
	auto& coilMeshP = coilPowered.Add<MeshRenderer>(coilPowered, coilP, untexturedShader);

	auto& camera = camEnt.Add<Camera>();

	camera.SetPosition(glm::vec3(0, 15, mainPlayer.Get<Transform>().GetPositionZ() + 12)); // Set initial position
	camera.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
	camera.LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camera.SetFovDegrees(90.0f); // Set an initial FOV

}

void Level3::Update(float dt)
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
	auto& wireTrans6 = wireEnt6.Get<Transform>();
	auto& wireTrans7 = wireEnt7.Get<Transform>();
	auto& notTrans = notEnt.Get<Transform>();
	auto& gateTrans = andEnt.Get<Transform>();
	auto& gateTrans2 = andEnt2.Get<Transform>();
	auto& gateTrans3 = andEnt3.Get<Transform>();
	auto& coilTrans = coilEnt.Get<Transform>();

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
	glm::mat4 transformWire6 = wireTrans6.GetModelMatrix();
	glm::mat4 transformWire7 = wireTrans7.GetModelMatrix();
	glm::mat4 transformNot = notTrans.GetModelMatrix();
	glm::mat4 transformGate = gateTrans.GetModelMatrix();
	glm::mat4 transformGate2 = gateTrans2.GetModelMatrix();
	glm::mat4 transformGate3 = gateTrans3.GetModelMatrix();
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
		andEnt.Get<AABB>().SetNext(glm::vec3(playerTrans.GetPositionX() - 10 * dt, playerTrans.GetPositionY(), playerTrans.GetPositionZ()));
		andEnt2.Get<AABB>().SetNext(glm::vec3(playerTrans.GetPositionX() - 10 * dt, playerTrans.GetPositionY(), playerTrans.GetPositionZ()));
		andEnt2.Get<AABB>().SetNext(glm::vec3(playerTrans.GetPositionX() - 10 * dt, playerTrans.GetPositionY(), playerTrans.GetPositionZ()));
		notEnt.Get<AABB>().SetNext(glm::vec3(playerTrans.GetPositionX() - 10 * dt, playerTrans.GetPositionY(), playerTrans.GetPositionZ()));

		if (playerTrans.GetCanMoveLeft())
		{
			playerTrans.SetPositionX(playerTrans.GetPositionX() - 10 * dt);
			playerTrans.SetRotationY(270.0f);
			camera.SetPosition(glm::vec3(playerTrans.GetPositionX(), camera.GetPosition().y, camera.GetPosition().z));
		}
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		andEnt.Get<AABB>().SetNext(glm::vec3(playerTrans.GetPositionX() + 10 * dt, playerTrans.GetPositionY(), playerTrans.GetPositionZ()));
		andEnt2.Get<AABB>().SetNext(glm::vec3(playerTrans.GetPositionX() + 10 * dt, playerTrans.GetPositionY(), playerTrans.GetPositionZ()));
		andEnt3.Get<AABB>().SetNext(glm::vec3(playerTrans.GetPositionX() + 10 * dt, playerTrans.GetPositionY(), playerTrans.GetPositionZ()));
		notEnt.Get<AABB>().SetNext(glm::vec3(playerTrans.GetPositionX() + 10 * dt, playerTrans.GetPositionY(), playerTrans.GetPositionZ()));

		if (playerTrans.GetCanMoveRight())
		{
			playerTrans.SetPositionX(playerTrans.GetPositionX() + 10 * dt);
			playerTrans.SetRotationY(90.0f);
			camera.SetPosition(glm::vec3(playerTrans.GetPositionX(), camera.GetPosition().y, camera.GetPosition().z));
		}
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		andEnt.Get<AABB>().SetNext(glm::vec3(playerTrans.GetPositionX(), playerTrans.GetPositionY(), playerTrans.GetPositionZ() - 10 * dt));
		andEnt2.Get<AABB>().SetNext(glm::vec3(playerTrans.GetPositionX(), playerTrans.GetPositionY(), playerTrans.GetPositionZ() - 10 * dt));
		andEnt3.Get<AABB>().SetNext(glm::vec3(playerTrans.GetPositionX(), playerTrans.GetPositionY(), playerTrans.GetPositionZ() - 10 * dt));
		notEnt.Get<AABB>().SetNext(glm::vec3(playerTrans.GetPositionX(), playerTrans.GetPositionY(), playerTrans.GetPositionZ() - 10 * dt));

		if (playerTrans.GetCanMoveUp())
		{
			playerTrans.SetPositionZ(playerTrans.GetPositionZ() - 10 * dt);
			playerTrans.SetRotationY(180.0f);

			if (camFar)
				camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z - 10 * dt));
		}
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		andEnt.Get<AABB>().SetNext(glm::vec3(playerTrans.GetPositionX(), playerTrans.GetPositionY(), playerTrans.GetPositionZ() + 10 * dt));
		andEnt2.Get<AABB>().SetNext(glm::vec3(playerTrans.GetPositionX(), playerTrans.GetPositionY(), playerTrans.GetPositionZ() + 10 * dt));
		andEnt3.Get<AABB>().SetNext(glm::vec3(playerTrans.GetPositionX(), playerTrans.GetPositionY(), playerTrans.GetPositionZ() + 10 * dt));
		notEnt.Get<AABB>().SetNext(glm::vec3(playerTrans.GetPositionX(), playerTrans.GetPositionY(), playerTrans.GetPositionZ() + 10 * dt));

		if (playerTrans.GetCanMoveDown())
		{
			playerTrans.SetPositionZ(playerTrans.GetPositionZ() + 10 * dt);
			playerTrans.SetRotationY(0.0f);

			if (camClose)
				camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z + 10 * dt));
		}
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
	playerShader->SetUniform("s_Diffuse", 0);
	drumstickMat.Albedo->Bind(0);
	meshMain.Render(camera, transform);

	levelShader->Bind();
	levelShader->SetUniform("s_Diffuse", 0);
	wallMat.Albedo->Bind(0);
	leftMesh.Render(camera, transformLeft);
	rightMesh.Render(camera, transformRight);
	backMesh.Render(camera, transformBack);

	floorShader->Bind();
	floorShader->SetUniform("s_Diffuse", 0);
	floorMat.Albedo->Bind(0);
	groundMesh.Render(camera, transformGround);

	doorShader->Bind();
	doorShader->SetUniform("s_Diffuse", 0);
	doorMat.Albedo->Bind(0);
	doorMesh.Render(camera, transformDoor);
	doorMat.Albedo->UnBind(0);

	untexturedShader->Bind();
	if (wireEnt7.Get<Wire>().GetIsPowered())
		coilMeshP.Render(camera, transformCoil);
	else
		coilMesh.Render(camera, transformCoil);
	gateMesh.Render(camera, transformGate);
	gateMesh2.Render(camera, transformGate2);
	gateMesh3.Render(camera, transformGate3);
	notMesh.Render(camera, transformNot);

	wireShader->Bind();
	wireShader->SetUniform("s_Diffuse", 0);
	wireMat.Albedo->Bind(0);

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

	buttonShader->Bind();
	buttonShader->SetUniform("s_Diffuse", 0);
	buttonMat.Albedo->Bind(0);
	buttonMesh.Render(camera, transformButton);
	buttonMesh2.Render(camera, transformButton2);
	buttonMesh3.Render(camera, transformButton3);

	//gateShader->Bind();



#pragma endregion

	leftEnt.Get<AABB>().Update();
	rightEnt.Get<AABB>().Update();
	backEnt.Get<AABB>().Update();
	doorEnt.Get<AABB>().Update();
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

	if (doorEnt.Get<AABB>().GetComplete())
		levelComplete = true;

}

void Level3::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}

