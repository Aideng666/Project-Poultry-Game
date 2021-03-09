#pragma once

#include "Entity.h"
#include "Input.h"
#include "Camera.h"
#include "Mesh.h"
#include "Transform.h"
#include "Shader.h"
#include "AndGate.h"
#include "OrGate.h"
#include "NotGate.h"
#include "Texture2D.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <MeshRenderer.h>
#include <ModelManager.h>
#include "Greyscale.h"
#include "Sepia.h"
#include "Bloom.h"
#include "ColorCorrect.h"
#include "FilmGrain.h"
#include "Pixelate.h"

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

	bool GetComplete();
	void SetComplete(bool complete);

	Entity GetCamera();

	entt::registry* GetScene();
	Shader::sptr GetShader();

	bool GetLoad();

	void SetShaderValues(Shader::sptr& shader, glm::vec3 lightPos = glm::vec3(0.f, 0.f, 0.f), 
		glm::vec3 lightDir = glm::vec3(0.f, 0.f, 0.f), glm::vec3 lightCol = glm::vec3(1.0f, 1.0f, 1.0f),
		float lightAmbientPow = 0.f, float lightSpecularPow = 0.f, 
		glm::vec3 ambientCol = glm::vec3(0.f, 0.f, 0.f), float ambientPow = 0.f, float shininess = 0.f);

	struct Mat
	{
		Texture2D::sptr Albedo;
		float Shininess;
	};

	void LoadTexImage();

	//Entity GetFBO();
	//Entity GetGreyscaleEnt();

	std::vector<PostEffect*> GetEffects();

	bool GetTextured();
	void SetTextured(bool isTex);

	int GetActiveEffect();
	void SetActiveEffect(int activeEffect);

protected:

	entt::registry* scene = nullptr;
	std::string name = " ";

	Shader::sptr shader, morphShader, pauseShader;

	GLFWwindow* window;

	Entity camEnt, uiCamEnt;

	Entity FBO, greyscaleEnt, sepiaEnt, colorCorrectEnt, bloomEnt;
	Entity filmGrainEnt, pixelateEnt;

	Entity pauseEnt, optionEnt, exitEnt, retryEnt;

	Mat clearMat, pauseMat, boxMat, curvedPipeMat, straightPipeMat, optionMat, exitMat, retryMat;

	Mesh* options;
	Mesh* exit;
	Mesh* retry;

	std::string pauseButtonFile = "Models/UI_Button.obj";

	std::vector<std::function<void()>> imGuiCallbacks;

	std::vector<Entity> ents;

	bool levelComplete = false;

	unsigned char* image;
	const char* fileName;
	int width, height;

	bool loadModels = false;
	bool isTextured = true;

	bool isPaused = false;
	bool tabletOpen = false;

	bool camClose = false;
	bool camFar = false;

	bool camLeft = false;
	bool camRight = false;

	int lightNum = 5;

	std::vector<PostEffect*> effects;
	int activeEffect = 0;

	KeyPressWatcher pauseWatch = KeyPressWatcher(GLFW_KEY_P, [&]() {
		isPaused = !isPaused;

		if (isPaused)
			lightNum = 2;
		else
			lightNum = 5;
		});

	//FOR ANIMATIONS//
	std::vector<std::unique_ptr<Mesh>> doorFrames, walkFrames, doorCloseFrames;

	Mesh* door1;
	Mesh* door2;
	Mesh* door3;
	Mesh* door4;
	Mesh* door5;
	Mesh* door6;
	Mesh* door7;
	Mesh* door8;
	Mesh* door9;
	Mesh* door10;

	Mesh* walk1;
	Mesh* walk2;
	Mesh* walk3;
	Mesh* walk4;
	Mesh* walk5;
	Mesh* walk6;
	Mesh* walk7;
	Mesh* walk8;
	Mesh* walk9;
	Mesh* walk10;
	Mesh* walk11;
	Mesh* walk12;
	Mesh* walk13;
	Mesh* walk14;

	std::string doorFile1 = "Models/DoorFrames/Door0.obj";
	std::string doorFile2 = "Models/DoorFrames/Door1.obj";
	std::string doorFile3 = "Models/DoorFrames/Door2.obj";
	std::string doorFile4 = "Models/DoorFrames/Door3.obj";
	std::string doorFile5 = "Models/DoorFrames/Door4.obj";
	std::string doorFile6 = "Models/DoorFrames/Door5.obj";
	std::string doorFile7 = "Models/DoorFrames/Door6.obj";
	std::string doorFile8 = "Models/DoorFrames/Door7.obj";
	std::string doorFile9 = "Models/DoorFrames/Door8.obj";
	std::string doorFile10 = "Models/DoorFrames/Door9.obj";

	std::string walkFile1 = "Models/ChickenFrames/Walk1.obj";
	std::string walkFile2 = "Models/ChickenFrames/Walk2.obj";
	std::string walkFile3 = "Models/ChickenFrames/Walk3.obj";
	std::string walkFile4 = "Models/ChickenFrames/Walk4.obj";
	std::string walkFile5 = "Models/ChickenFrames/Walk5.obj";
	std::string walkFile6 = "Models/ChickenFrames/Walk6.obj";
	std::string walkFile7 = "Models/ChickenFrames/Walk7.obj";
	std::string walkFile8 = "Models/ChickenFrames/Walk8.obj";
	std::string walkFile9 = "Models/ChickenFrames/Walk9.obj";
	std::string walkFile10 = "Models/ChickenFrames/Walk10.obj";
	std::string walkFile11 = "Models/ChickenFrames/Walk11.obj";
	std::string walkFile12 = "Models/ChickenFrames/Walk12.obj";
	std::string walkFile13 = "Models/ChickenFrames/Walk13.obj";
	std::string walkFile14 = "Models/ChickenFrames/Walk14.obj";
	///////////////
};
