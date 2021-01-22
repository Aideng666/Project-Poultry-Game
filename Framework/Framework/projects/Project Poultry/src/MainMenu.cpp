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
	playButton = Entity::Create();
	optionsButton = Entity::Create();

	play = ModelManager::FindMesh(buttonFile);
	options = ModelManager::FindMesh(buttonFile);
	back = ModelManager::FindMesh(backFile);
}

void MainMenu::InitScene()
{
	Application::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

	scene = new entt::registry();

	Entity::SetReg(scene);

#pragma region Shader Stuff

	glm::vec3 lightPos = glm::vec3(0.0f, 50.0f, -35.0f);
	glm::vec3 lightDir = glm::vec3(0.0f, -1.0f, 0.0f);
	glm::vec3 lightCol = glm::vec3(1.f, 1.f, 1.f);
	float     lightAmbientPow = 0.65f;
	float     lightSpecularPow = 1.0f;
	float     lightSpecularPow2 = 0.2f;
	glm::vec3 ambientCol = glm::vec3(1.0f);
	float     ambientPow = 0.1f;
	float     shininess = 16.0f;

	shader = Shader::Create();
	shader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	shader->LoadShaderPartFromFile("Shaders/menu_frag.glsl", GL_FRAGMENT_SHADER);
	shader->Link();

	SetShaderValues(shader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

#pragma endregion


#pragma region Texture Stuff
	Texture2DData::sptr playMap = Texture2DData::LoadFromFile("Textures/Buttons/Default/Play.png");
	Texture2DData::sptr optionsMap = Texture2DData::LoadFromFile("Textures/Buttons/Default/Option.png");
	Texture2DData::sptr backMap = Texture2DData::LoadFromFile("Textures/MainMenuBackground.png");

	Texture2D::sptr diffusePlay = Texture2D::Create();
	diffusePlay->LoadData(playMap);

	Texture2D::sptr diffuseOptions = Texture2D::Create();
	diffuseOptions->LoadData(optionsMap);

	Texture2D::sptr diffuseBack = Texture2D::Create();
	diffuseBack->LoadData(backMap);

	Texture2DDescription desc = Texture2DDescription();
	desc.Width = 1;
	desc.Height = 1;
	desc.Format = InternalFormat::RGB8;
	Texture2D::sptr texture2 = Texture2D::Create(desc);
	texture2->Clear();

	playMat.Albedo = diffusePlay;
	optionsMat.Albedo = diffuseOptions;
	backMat.Albedo = diffuseBack;

#pragma endregion

	auto& playTrans = playButton.Add<Transform>();
	playTrans.SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
	playTrans.SetScale(glm::vec3(1.5f));
	playTrans.SetRotationY(332.0f);

	auto& optionsTrans = optionsButton.Add<Transform>();
	optionsTrans.SetPosition(glm::vec3(0.0f, 0.0f, 6.0f));
	optionsTrans.SetScale(glm::vec3(1.5f));
	optionsTrans.SetRotationY(96.0f);

	auto& backTrans = backEnt.Add<Transform>();
	backTrans.SetPosition(glm::vec3(0.0f, -1.0f, 0.0f));
	backTrans.SetScale(glm::vec3(0.268f));

	auto& playMesh = playButton.Add<MeshRenderer>(playButton, *play, shader);
	auto& optionsMesh = optionsButton.Add<MeshRenderer>(optionsButton, *options, shader);
	auto& backMesh = backEnt.Add<MeshRenderer>(backEnt, *back, shader);

	auto& camera = camEnt.Add<Camera>();
	camera.SetPosition(glm::vec3(0, 10, 0)); // Set initial position
	camera.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
	camera.LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camera.SetFovDegrees(90.0f); // Set an initial FOV
}

void MainMenu::Update(float dt)
{

	time += dt;
	shader->SetUniform("u_Time", time);

	auto& playTrans = playButton.Get<Transform>();
	auto& optionsTrans = optionsButton.Get<Transform>();
	auto& backTrans = backEnt.Get<Transform>();

	auto& camera = camEnt.Get<Camera>();

	/*playTrans.SetRotationY(playTrans.GetRotation().y + 20.0f * dt);

	std::cout << playTrans.GetRotation().y << std::endl;*/

	auto& playMesh = playButton.Get<MeshRenderer>();
	auto& optionsMesh = optionsButton.Get<MeshRenderer>();
	auto& backMesh = backEnt.Get<MeshRenderer>();

	glm::mat4 transformPlay = playTrans.GetModelMatrix();
	glm::mat4 transformOptions = optionsTrans.GetModelMatrix();
	glm::mat4 transformBack = backTrans.GetModelMatrix();

#pragma region CameraMovement

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

	shader->Bind();
	shader->SetUniform("s_Diffuse", 0);
	playMat.Albedo->Bind(0);
	playMesh.Render(camera, transformPlay);


	shader->Bind();
	shader->SetUniform("s_Diffuse", 0);
	optionsMat.Albedo->Bind(0);
	optionsMesh.Render(camera, transformOptions);

	shader->SetUniform("s_Diffuse", 0);
	backMat.Albedo->Bind(0);
	backMesh.Render(camera, transformBack);
}

void MainMenu::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}
