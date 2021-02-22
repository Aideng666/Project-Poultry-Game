#include "TestScene.h"
#include <iostream>
#include <GLFW\glfw3.h>

#include "Application.h"
#include <MeshRenderer.h>
#include "Texture2DData.h"
#include "Texture2D.h"

TestScene::TestScene(std::string sceneName, GLFWwindow* window)
	: Scene(sceneName, window)
{
	mainPlayer = Entity::Create();
	monkey = ModelManager::FindMesh(monkeyFile);
}

void TestScene::InitScene()
{
	//Sets the clear color
	Application::SetClearColor(glm::vec4(0.08f, 0.17f, 0.31f, 1.0f));

	scene = new entt::registry();

	Entity::SetReg(scene);

	//Shader Stuff
	glm::vec3 lightPos = glm::vec3(0.0f, 0.f, 5.0f);
	glm::vec3 lightCol = glm::vec3(1.f);
	float     lightAmbientPow = 0.09f;
	float     lightSpecularPow = 1.0f;
	glm::vec3 ambientCol = glm::vec3(1.0f);
	float     ambientPow = 0.1f;
	float     shininess = 8.0f;
	float     lightLinearFalloff = 0.09f;
	float     lightQuadraticFalloff = 0.032f;

	shader = Shader::Create();
	shader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	shader->LoadShaderPartFromFile("Shaders/basic_frag.glsl", GL_FRAGMENT_SHADER);
	shader->Link();

	shader->SetUniform("u_LightPos", lightPos);
	shader->SetUniform("u_LightCol", lightCol);
	shader->SetUniform("u_AmbientLightStrength", lightAmbientPow);
	shader->SetUniform("u_SpecularLightStrength", lightSpecularPow);
	shader->SetUniform("u_AmbientCol", ambientCol);
	shader->SetUniform("u_AmbientStrength", ambientPow);
	shader->SetUniform("u_LightAttenuationConstant", 1.0f);
	shader->SetUniform("u_LightAttenuationLinear", lightLinearFalloff);
	shader->SetUniform("u_LightAttenuationQuadratic", lightQuadraticFalloff);
	shader->SetUniform("u_Shininess", shininess);

	//Texture Stuff
	Texture2D::sptr diffuse = Texture2D::LoadFromFile("Textures/Stone.png");

	Texture2DDescription desc = Texture2DDescription();
	desc.Width = 1;
	desc.Height = 1;
	desc.Format = InternalFormat::RGB8;
	Texture2D::sptr texture2 = Texture2D::Create(desc);
	texture2->Clear();

	playerMat.Albedo = diffuse;
	clearMat.Albedo = texture2;

	//Transforms
	mainPlayer.Add<Transform>();
	mainPlayer.Get<Transform>().SetPosition(glm::vec3(0.f));
	mainPlayer.Get<Transform>().SetScale(glm::vec3(2.f));

	mainPlayer.Add<MeshRenderer>(mainPlayer, *monkey, shader);

	auto& camera = camEnt.Add<Camera>();
	camera.SetPosition(glm::vec3(0, 25, 15));
	camera.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
	camera.LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camera.SetFovDegrees(90.0f); // Set an initial FOV
}

void TestScene::Update(float dt)
{
	auto& playerTrans = mainPlayer.Get<Transform>();

	auto& camera = camEnt.Get<Camera>();

	auto& playerMesh = mainPlayer.Get<MeshRenderer>();

	glm::mat4 transform = playerTrans.GetModelMatrix();

	//Player Movement
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		playerTrans.SetPositionZ(playerTrans.GetPositionZ() - 10 * dt);
		playerTrans.SetRotationY(180.0f);
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		playerTrans.SetPositionZ(playerTrans.GetPositionZ() + 10 * dt);
		playerTrans.SetRotationY(0.0f);
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		playerTrans.SetPositionX(playerTrans.GetPositionX() - 10 * dt);
		playerTrans.SetRotationY(270.0f);
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		playerTrans.SetPositionX(playerTrans.GetPositionX() + 10 * dt);
		playerTrans.SetRotationY(90.0f);
	}

	//Camera Movement
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		
	}
	else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		
	}

	//Renders the objects
	if (isTextured)
	{
		shader->Bind();
		shader->SetUniform("s_Diffuse", 0);
		playerMat.Albedo->Bind(0);
		playerMesh.Render(camera, transform);
	}
	else
	{
		shader->Bind();
		shader->SetUniform("s_Diffuse", 0);
		clearMat.Albedo->Bind(0);
		playerMesh.Render(camera, transform);
	}
}