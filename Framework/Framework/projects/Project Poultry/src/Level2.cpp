#include "Level2.h"
#include <iostream>
#include <GLFW\glfw3.h>

using namespace freebird;

Level2::Level2(std::string sceneName, GLFWwindow* wind)
	: Scene(sceneName, wind)
{
	mainPlayer = Entity::Create();
	camEnt = Entity::Create();
	ground = Entity::Create();
	leftWall = Entity::Create();
	rightWall = Entity::Create();
	backWall = Entity::Create();
}

void Level2::InitScene()
{
	scene = new entt::registry();

	Entity::SetReg(scene);

	//Set Up Camera
	auto& camera = camEnt.Add<Camera>();

	camera.SetPosition(glm::vec3(0, 8, 10)); // Set initial position
	camera.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
	camera.LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camera.SetFovDegrees(90.0f); // Set an initial FOV

	Mesh monkey("Models/Monkey.obj", glm::vec3(1.0f, 0.0f, 0.0f));
	auto& playerTrans = mainPlayer.Add<Transform>();
	auto& playerMesh = mainPlayer.Add<Mesh>(monkey);

	playerTrans.SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	playerTrans.SetRotationY(0.0f);

	Mesh test("Models/TestPlane.obj");

	//meshes
	auto& groundMesh = ground.Add<Mesh>(test);
	auto& leftMesh = leftWall.Add<Mesh>(test);
	auto& rightMesh = rightWall.Add<Mesh>(test);
	auto& backMesh = backWall.Add<Mesh>(test);

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

}

void Level2::Update(float dt)
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Transforms
	auto& playerTrans = mainPlayer.Add<Transform>();
	auto& groundTrans = ground.Add<Transform>();
	auto& leftTrans = leftWall.Add<Transform>();
	auto& rightTrans = rightWall.Add<Transform>();
	auto& backTrans = backWall.Add<Transform>();

	backTrans.SetPositionZ(-10.4f);
	backTrans.SetPositionY(10.4f);
	backTrans.SetRotationX(90.0f);

	leftTrans.SetRotationZ(90.0f);
	leftTrans.SetRotationY(180.0f);
	leftTrans.SetPositionX(-10.4f);
	leftTrans.SetPositionY(10.4f);

	rightTrans.SetRotationZ(90.0f);
	rightTrans.SetPositionX(10.4f);
	rightTrans.SetPositionY(10.4f);

	//Camera
	auto& camera = camEnt.Get<Camera>();

	//Meshes
	auto& meshMain = mainPlayer.Get<Mesh>();
	auto& groundMesh = ground.Get<Mesh>();
	auto& leftMesh = leftWall.Get<Mesh>();
	auto& rightMesh = rightWall.Get<Mesh>();
	auto& backMesh = backWall.Get<Mesh>();

	camera.LookAt(glm::vec3(playerTrans.GetPosition())); // Look at center of the screen

	//Gets the transforms of the objects
	glm::mat4 transform = playerTrans.GetModelMatrix();
	glm::mat4 transformGround = groundTrans.GetModelMatrix();
	glm::mat4 transformLeft = leftTrans.GetModelMatrix();
	glm::mat4 transformRight = rightTrans.GetModelMatrix();
	glm::mat4 transformBack = backTrans.GetModelMatrix();


	if (camera.GetPosition().z - playerTrans.GetPositionZ() < 7.5f)
		camClose = true;
	else
		camClose = false;

	if (camera.GetPosition().z - playerTrans.GetPositionZ() > 15.0f)
		camFar = true;
	else
		camFar = false;

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
#pragma endregion	
}

void Level2::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;	
	}
}







