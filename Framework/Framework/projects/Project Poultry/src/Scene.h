#pragma once

#include "Entity.h"
#include "Camera.h"
#include "Mesh.h"
#include "Transform.h"
#include "Shader.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>

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

	entt::registry* GetScene();

	/*std::vector<Mesh>* GetRenders();
	Mesh* Scene::GetRenders(int index);
	Transform *GetTransform(int index);*/

protected:

	entt::registry* scene = nullptr;
	std::string name = " ";

	//std::vector<Mesh> renders;
	//std::vector<Transform> transforms;

	GLfloat clearcolor[4] = { 1.0, 1.0, 1.0, 1.0 };

	Shader::sptr shader;
	GLFWwindow* window;

};
