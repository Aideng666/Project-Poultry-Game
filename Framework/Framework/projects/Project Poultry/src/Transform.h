#pragma once

#include "GLM/glm.hpp"
#include <vector>

#define GLM_ENABLE_EXPERIMENTAL

class Transform {

public:

	Transform();

	glm::vec3 GetPos();
	glm::vec3 GetScale();
	glm::vec4 GetRotation();




private:
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec4 rotation;
	glm::mat4 globalPos;
	Transform* currentParent;
	std::vector<Transform*> children;


};
