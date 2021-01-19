#include "ModelManager.h"

//namespace freebird
//{
//	std::vector<std::string> ModelManager::m_filesLoaded;
//	std::vector<std::unique_ptr<Mesh>> ModelManager::m_meshes;
//
//	ModelManager::~ModelManager()
//	{
//		//Loops through all the meshes loaded
//		for (unsigned i = 0; i < m_meshes.size(); ++i)
//		{
//			//If the mesh isn't nullptr
//			if (m_meshes[i] != nullptr)
//			{
//				//Delete mesh
//				delete m_meshes[i];
//				//Set it to nullptr
//				m_meshes[i] = nullptr;
//			}
//		}
//	}
//
//	Mesh* ModelManager::LoadMesh(std::string& fileName)
//	{
//		//Adds the filename to the loaded list and loads the mesh to the mesh list
//		m_filesLoaded.push_back(fileName);
//		//Push back a new mesh
//		m_meshes.push_back(new Mesh());
//		//Loads new mesh
//		Mesh* newMesh(fileName);
//		m_meshes[m_meshes.size() - 1] = newMesh;
//	}
//
//}