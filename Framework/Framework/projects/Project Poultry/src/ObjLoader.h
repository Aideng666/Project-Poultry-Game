#pragma once
#include <vector>
#include <string>
#include <GLM/glm.hpp>

class ObjLoader
{
public:
	static bool LoadFromFile(const std::string& filename, std::vector<glm::vec3>& outV, std::vector<glm::vec2>& outUV, std::vector<glm::vec3>& outN);

protected:
	ObjLoader() = default;
	~ObjLoader() = default;
};
