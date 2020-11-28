#include "Scene.h"
#include <iostream>

using namespace freebird;

Scene::Scene(std::string sceneName, GLFWwindow* wind)
{
	name = sceneName;
	window = wind;
}

void Scene::InitScene()
{
	scene = new entt::registry();

	Entity::SetReg(scene);


	//Set Up Camera
	Entity camEnt = Entity::Create();
	auto& camera = camEnt.Add<Camera>();

	camera.SetPosition(glm::vec3(0, 3, 3)); // Set initial position
	camera.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
	camera.LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camera.SetFovDegrees(90.0f); // Set an initial FOV
}

void Scene::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}

void Scene::InitImGui() {
	// Creates a new ImGUI context
	ImGui::CreateContext();
	// Gets our ImGUI input/output 
	ImGuiIO& io = ImGui::GetIO();
	// Enable keyboard navigation
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	// Allow docking to our window
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	// Allow multiple viewports (so we can drag ImGui off our window)
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	// Allow our viewports to use transparent backbuffers
	io.ConfigFlags |= ImGuiConfigFlags_TransparentBackbuffers;

	// Set up the ImGui implementation for OpenGL
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 410");

	// Dark mode FTW
	ImGui::StyleColorsDark();

	// Get our imgui style
	ImGuiStyle& style = ImGui::GetStyle();
	//style.Alpha = 1.0f;
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 0.8f;
	}
}

void Scene::ShutdownImGui()
{
	// Cleanup the ImGui implementation
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	// Destroy our ImGui context
	ImGui::DestroyContext();
}

void Scene::RenderImGui() {
	// Implementation new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	// ImGui context new frame
	ImGui::NewFrame();

	if (ImGui::Begin("Entity Controller")) {
		// Render our GUI stuff
		for (auto& func : imGuiCallbacks) {
			func();
		}
		ImGui::End();
	}

	// Make sure ImGui knows how big our window is
	ImGuiIO& io = ImGui::GetIO();
	int width{ 100 }, height{ 100 };
	glfwGetWindowSize(window, &width, &height);
	io.DisplaySize = ImVec2((float)width, (float)height);

	// Render all of our ImGui elements
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// If we have multiple viewports enabled (can drag into a new window)
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		// Update the windows that ImGui is using
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		// Restore our gl context
		glfwMakeContextCurrent(window);
	}
}

bool Scene::GetComplete()
{
	return levelComplete;
}

void Scene::SetComplete(bool complete)
{
	levelComplete = complete;
}

Entity Scene::GetCamera()
{
	return camEnt;
}

entt::registry* Scene::GetScene()
{
	return scene;
}

Shader::sptr Scene::GetShader()
{
	return shader;
}

//void Scene::RenderVAO(Shader::sptr& shader, MeshRenderer& vao, Camera& camera, glm::mat4 transform)
//{
//	shader->SetUniformMatrix("u_ModelRotation", glm::mat3(transform));
//	shader->SetUniformMatrix("u_ModelViewProjection", camera.GetViewProjection() * transform);
//	shader->SetUniformMatrix("u_Model", transform);
//	vao.Render();
//}

void Scene::SetShaderValues(Shader::sptr& shader, glm::vec3 lightPos, glm::vec3 lightDir, glm::vec3 lightCol, float lightAmbientPow, float lightSpecularPow, float lightSpecularPow2, glm::vec3 ambientCol, float ambientPow, float shininess)
{
	shader->SetUniform("u_LightPos", lightPos);
	shader->SetUniform("u_LightDir", lightDir);
	shader->SetUniform("u_LightCol", lightCol);
	shader->SetUniform("u_AmbientLightStrength", lightAmbientPow);
	shader->SetUniform("u_SpecularLightStrength", lightSpecularPow);
	shader->SetUniform("u_SpecularLightStrength2", lightSpecularPow2);
	shader->SetUniform("u_AmbientCol", ambientCol);
	shader->SetUniform("u_AmbientStrength", ambientPow);
	shader->SetUniform("u_Shininess", shininess);
}
