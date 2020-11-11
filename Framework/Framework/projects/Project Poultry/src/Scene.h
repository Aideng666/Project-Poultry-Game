#pragma once

#include "Entity.h"
#include "Camera.h"
#include "Mesh.h"
#include "Transform.h"
#include "Shader.h"
#include "AndGate.h"
#include "OrGate.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


using namespace freebird;

class Scene
{

public:
	Scene()
	{
		scene = new entt::registry();
	}
	Scene(std::string sceneName, GLFWwindow* wind);
 

	virtual void InitScene();
	virtual void Update(float dt) {}

	virtual void Unload();

	void InitImGui();
	void ShutdownImGui();
	void RenderImGui();

	entt::registry* GetScene();

protected:

	entt::registry* scene = nullptr;
	std::string name = " ";

	Shader::sptr shader;
	GLFWwindow* window;

	std::vector<std::function<void()>> imGuiCallbacks;

	std::vector<Entity> ents;
};
