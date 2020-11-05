#include "Level2.h"
#include <iostream>
#include <GLFW\glfw3.h>

using namespace freebird;

Level2::Level2(std::string sceneName, GLFWwindow* wind)
	: Scene(sceneName, wind)
{
	mainPlayer = Entity::Create();
	camEnt = Entity::Create();
	testPlane = Entity::Create();
}

void Level2::InitScene()
{
	scene = new entt::registry();

	Entity::SetReg(scene);

	//Set Up Camera
	auto& camera = camEnt.Add<Camera>();

	camera.SetPosition(glm::vec3(0, 3, 3)); // Set initial position
	camera.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
	camera.LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camera.SetFovDegrees(90.0f); // Set an initial FOV

	Mesh monkey("Models/Monkey.obj");
	auto& playerTrans = mainPlayer.Add<Transform>();
	auto& playerMesh = mainPlayer.Add<Mesh>(monkey);

	playerTrans.SetPositionY(1.0f);

	Mesh test("Models/TestPlane.obj");
	auto& planeTrans = testPlane.Add<Transform>();
	auto& planeMesh = testPlane.Add<Mesh>(test);




	//renders.push_back(meshMain);
	//transforms.push_back(playerTrans);

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
	auto& playerTrans = mainPlayer.Get<Transform>();
	auto& planeTrans = testPlane.Get<Transform>();

	//Camera
	auto& camera = camEnt.Get<Camera>();

	//Meshes
	auto& meshMain = mainPlayer.Get<Mesh>();
	auto& planeMesh = testPlane.Get<Mesh>();


	//camera.SetPosition(glm::vec3(playerTrans.GetPositionX(), playerTrans.GetPositionY() + 3, playerTrans.GetPositionZ() + 3));
	//camera.LookAt(glm::vec3(currentScene->GetTransform(0)->GetPosition())); // Look at center of the screen

	shader->Bind();

	
		glm::mat4 transform = playerTrans.GetModelMatrix();
		glm::mat4 transformPlane = planeTrans.GetModelMatrix();

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			playerTrans.SetPositionX(playerTrans.GetPositionX() - 2 * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			playerTrans.SetPositionX(playerTrans.GetPositionX() + 2 * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			playerTrans.SetPositionZ(playerTrans.GetPositionZ() - 2 * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			playerTrans.SetPositionZ(playerTrans.GetPositionZ() + 2 * dt);
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			playerTrans.SetRotationY(playerTrans.GetRotation().y + 100 * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			playerTrans.SetRotationY(playerTrans.GetRotation().y - 100 * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		{
			camera.SetPosition(glm::vec3(camera.GetPosition().x - 2 * dt, camera.GetPosition().y, camera.GetPosition().z));
		}
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		{
			camera.SetPosition(glm::vec3(camera.GetPosition().x + 2 * dt, camera.GetPosition().y, camera.GetPosition().z));
		}
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		{
			camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z - 2 * dt));
		}
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		{
			camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z + 2 * dt));
		}
		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		{
			camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y + 2 * dt, camera.GetPosition().z));
		}
		if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		{
			camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y - 2 * dt, camera.GetPosition().z));
		}


		shader->SetUniformMatrix("u_ModelRotation", glm::mat3(transform));
		shader->SetUniformMatrix("u_ModelViewProjection", camera.GetViewProjection() * transform);
		shader->SetUniformMatrix("u_Model", transform);
		shader->SetUniform("u_CamPos", camera.GetPosition());

		meshMain.Render();

		shader->SetUniformMatrix("u_ModelRotation", glm::mat3(transformPlane));
		shader->SetUniformMatrix("u_ModelViewProjection", camera.GetViewProjection() * transformPlane);
		shader->SetUniformMatrix("u_Model", transformPlane);
		shader->SetUniform("u_CamPos", camera.GetPosition());
		planeMesh.Render();
	
}

void Level2::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;	
	}
}







