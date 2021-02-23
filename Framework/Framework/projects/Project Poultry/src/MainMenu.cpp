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
	backEnt = Entity::Create();
	loadEnt = Entity::Create();
	FBO = Entity::Create();
	greyscaleEnt = Entity::Create();
	sepiaEnt = Entity::Create();
	colorCorrectEnt = Entity::Create();
	bloomEnt = Entity::Create();

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
	glm::vec3 ambientCol = glm::vec3(1.0f);
	float     ambientPow = 0.1f;
	float     shininess = 16.0f;

	shader = Shader::Create();
	shader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	shader->LoadShaderPartFromFile("Shaders/menu_frag.glsl", GL_FRAGMENT_SHADER);
	shader->Link();

	SetShaderValues(shader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, ambientCol, ambientPow, shininess);

	//MAKE A LOADING SCREEN SHADER FOR RENDERING THE LOADING SCREEN IMAGE SO THE LIGHT DOESN'T SHOW IN THE LOADING SCREEN

#pragma endregion

#pragma region Texture Stuff
	Texture2D::sptr backMap = Texture2D::LoadFromFile("Textures/Title_ScreenFinal.png");
	Texture2D::sptr loadMap = Texture2D::LoadFromFile("Textures/Loading.jpg");

	Texture2DDescription desc = Texture2DDescription();
	desc.Width = 1;
	desc.Height = 1;
	desc.Format = InternalFormat::RGB8;
	Texture2D::sptr texture2 = Texture2D::Create(desc);
	texture2->Clear();

	backMat.Albedo = backMap;
	loadMat.Albedo = loadMap;
	clearMat.Albedo = texture2;

#pragma endregion

	//Background screen
	backEnt.Add<Transform>();
	backEnt.Get<Transform>().SetPosition(glm::vec3(0.0f, -1.0f, 0.0f));
	backEnt.Get<Transform>().SetScale(glm::vec3(0.268f));
	backEnt.Add<MeshRenderer>(backEnt, *back, shader);

	//Loading screen
	loadEnt.Add<Transform>();
	loadEnt.Get<Transform>().SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	loadEnt.Get<Transform>().SetScale(glm::vec3(0.268f));
	loadEnt.Add<MeshRenderer>(loadEnt, *back, shader);

	//Basic camera
	auto& camera = camEnt.Add<Camera>();
	camera.SetPosition(glm::vec3(0, 10, 0)); // Set initial position
	camera.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
	camera.LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camera.SetFovDegrees(90.0f); // Set an initial FOV

	//Post-Processing Effects
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

	auto bloomEffect = &bloomEnt.Add<Bloom>();
	bloomEffect->Init(width, height);

	effects.push_back(bloomEffect);

	auto colorCorrectEffect = &colorCorrectEnt.Add<ColorCorrect>();
	colorCorrectEffect->Init(width, height);

	effects.push_back(colorCorrectEffect);
}

void MainMenu::Update(float dt)
{
	time += dt;
	shader->SetUniform("u_Time", time);

	//Get references to transforms
	auto& backTrans = backEnt.Get<Transform>();
	auto& loadTrans = loadEnt.Get<Transform>();

	//Get reference to camera
	auto& camera = camEnt.Get<Camera>();

	//Get reference to mesh
	auto& backMesh = backEnt.Get<MeshRenderer>();
	auto& loadMesh = loadEnt.Get<MeshRenderer>();

	//Load the model matrix
	glm::mat4 transformBack = backTrans.GetModelMatrix();
	glm::mat4 transformLoad = loadTrans.GetModelMatrix();

	//Switch scenes
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		loadModels = true;
		isLoading = true;
	}

	//Post-Effect 
	auto basicEffect = &FBO.Get<PostEffect>();

	basicEffect->Clear();

	for (int i = 0; i < effects.size(); i++)
	{
		effects[i]->Clear();
	}

	basicEffect->BindBuffer(0);

	//Render objects
	if (isTextured) 
	{
		shader->Bind();
		shader->SetUniform("s_Diffuse", 0);
		backMat.Albedo->Bind(0);
		backMesh.Render(camera, transformBack);
	}
	else
	{
		shader->Bind();
		shader->SetUniform("s_Diffuse", 0);
		clearMat.Albedo->Bind(0);
		backMesh.Render(camera, transformBack);
	}

	if (isLoading)
	{
		shader->SetUniform("s_Diffuse", 0);
		loadMat.Albedo->Bind(0);
		loadMesh.Render(camera, transformLoad);
	}

	basicEffect->UnbindBuffer();

	effects[activeEffect]->ApplyEffect(basicEffect);

	effects[activeEffect]->DrawToScreen();
}

void MainMenu::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}