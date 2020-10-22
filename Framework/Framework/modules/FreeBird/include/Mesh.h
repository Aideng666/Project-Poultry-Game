//Mesh class to laod our objects
/*
	Tyler Wong
	2020-10-21
*/

#pragma once
#include <string>
#include <vector>
#include <GLM/glm.hpp>
#include "VertexArrayObject.h"

namespace freebird
{
	class Mesh
	{
	public:
		Mesh(const std::string& fileName);
		VertexArrayObject::sptr loadMesh();
		VertexArrayObject::sptr makeVAO();
	
	private:
		std::string fileName;
		std::vector<glm::vec3> out_Verts;
		std::vector<glm::vec2> out_UVs;
		std::vector<glm::vec3> out_Norms;
		std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
		static const std::vector<BufferAttribute> buffAttibs;
	};
}