#include "ModelManager.h"

namespace freebird
{
	std::vector<std::string> ModelManager::m_filesLoaded;
	std::vector<Mesh*> ModelManager::m_meshes;

	ModelManager::~ModelManager()
	{
		//Loops through all the meshes loaded
		for (unsigned i = 0; i < m_meshes.size(); ++i)
		{
			//If the mesh isn't nullptr
			if (m_meshes[i] != nullptr)
			{
				//Delete mesh
				delete m_meshes[i];
				//Set it to nullptr
				m_meshes[i] = nullptr;
			}
		}
	}

	Mesh* ModelManager::LoadMesh(std::string& fileName)
	{
		//Adds the filename to the loaded list and loads the mesh to the mesh list
		m_filesLoaded.push_back(fileName);
		//Push back a new mesh
		m_meshes.push_back(new Mesh());
		//Loads new mesh
		Mesh newMesh(fileName);
		m_meshes[m_meshes.size() - 1] = &newMesh;

		return m_meshes[m_meshes.size() - 1];
	}

	Mesh* ModelManager::FindMesh(std::string& fileName)
	{
		//Searches list of strings and stores result of iteration
		auto iteration = std::find(m_filesLoaded.begin(), m_filesLoaded.end(), fileName);
		int index = 0;

		//Checks if the file with the given name was already in the list of loaded files
		if (iteration != m_filesLoaded.end())
			index = int(std::distance(m_filesLoaded.begin(), iteration));
		else
			index = -1;

		//checks if index is -1 and if it is, return
		if (index != -1)
			return m_meshes[index];
		else
			return LoadMesh(fileName);
	}

	GLuint ModelManager::GetHandle(std::string& fileName)
	{
		Mesh* mesh = FindMesh(fileName);

		return mesh->GetVBO()->GetHandle();
	}

	std::vector<std::string> ModelManager::GetFilesLoaded()
	{
		return m_filesLoaded;
	}

}