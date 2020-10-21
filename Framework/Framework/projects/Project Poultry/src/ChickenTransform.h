#pragma once

#include "GLM/glm.hpp"
#include <vector>

#define GLM_ENABLE_EXPERIMENTAL

//Transform class for transformations in main
/*
	Aiden Gimpel
	2020-10-21
*/

class ChickenTransform {

public:

	ChickenTransform();

	glm::vec3 GetPos();
	glm::vec3 GetScale();
	glm::quat GetRotation();
	glm::mat4 GetGlobal();
	ChickenTransform* GetParent();

	void SetPos(glm::vec3 newPos);
	void SetScale(glm::vec3 newScale);
	void SetRotation(glm::quat newRot);
	void SetParent(ChickenTransform* newParent);

	void RecomputeGlobal();




private:

	//needed ChickenTransform variables
	glm::vec3 position;
	glm::vec3 scale;
	glm::quat rotation;
	glm::mat4 globalPos;
	std::vector<ChickenTransform*> children;
	ChickenTransform* currentParent;


};
