//Mesh class to laod our objects
/*
    Tyler Wong
    2020-10-21
*/

#include "Mesh.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>

// Trim from start (in place)
static inline void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
        }));
}

// Trim from end (in place)
static inline void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
        }).base(), s.end());
}

// Trim from both ends (in place)
static inline void trim(std::string& s) {
    ltrim(s);
    rtrim(s);
}

namespace freebird
{ 
    //Sets the filename of the .obj file
    Mesh::Mesh(const std::string& fileName)
    {
        this->fileName = fileName;
    }
    
    //Loads the .obj file
    VertexArrayObject::sptr Mesh::loadMesh()
    {
        //Open our file in binary mode
        std::ifstream file;
        file.open(fileName, std::ios::binary);
    
        // If our file fails to open, we will throw an error
        if (!file) {
            throw std::runtime_error("File failed to open");
        }
    
        //Temporary vectors to store our obj's data
        std::vector<glm::vec3> temp_verticies, temp_normals;
        std::vector<glm::vec2> temp_uvs;
    
        //Used to read the file
        std::string line;
    
        //Reads through the file
        while (std::getline(file, line))
        {
            trim(line);
    
            //Check for hashtags
            if (line.substr(0, 1) == "#")
            {
                //Do nothing becasue # is a comment
            }
            //Check for any lines containing verticies
            else if (line.substr(0, 2) == "v ")
            {
                //Reads from the line and gets each value of the vertex
                std::istringstream ss = std::istringstream(line.substr(2));
                glm::vec3 pos;
                ss >> pos.x >> pos.y >> pos.z;
                //Adds vertex to the vector
                temp_verticies.push_back(pos);
            }
            //Check for any lines containing uvs/texture coordinates
            else if (line.substr(0, 2) == "vt")
            {
                //Reads from the line and gets each value of the UV
                std::istringstream ss = std::istringstream(line.substr(2));
                glm::vec2 uv;
                ss >> uv.x >> uv.y;
                //Adds uv to the vector
                temp_uvs.push_back(uv);
            }
            //Check for any lines containing normals
            else if (line.substr(0, 2) == "vn")
            {
                //Reads from the line and gets each value of the Normal
                std::istringstream ss = std::istringstream(line.substr(2));
                glm::vec3 norm;
                ss >> norm.x >> norm.y >> norm.z;
                //Adds normal to the vector
                temp_normals.push_back(norm);
            }
            //Checks for any lines containing faces and thus their sets of data
            else if (line.substr(0, 2) == "f ")
            {
                std::istringstream ss = std::istringstream(line.substr(2));
                char s1;
                int v, uv, n;
    
                for (int i = 0; i < 3; i++)
                {
                    ss >> v >> s1 >> uv >> s1 >> n;
                    vertexIndices.push_back(v);
                    uvIndices.push_back(uv);
                    normalIndices.push_back(n);
                }
            }
            else {}
        }
    
        //Gets the attributes and arranges the index of the faces
        for (unsigned int i = 0; i < vertexIndices.size(); i++)
        {
            out_Verts.push_back(temp_verticies[vertexIndices[i] - 1]);
            out_UVs.push_back(temp_verticies[vertexIndices[i] - 1]);
            if (i < normalIndices.size())
            {
                out_Norms.push_back(temp_verticies[vertexIndices[i] - 1]);
            }
        }
    
        return makeVAO();
    }
    
    //Loads the data from the obj file into a VAO
    VertexArrayObject::sptr Mesh::makeVAO()
    {
        VertexBuffer::sptr pos_VBO = VertexBuffer::Create();
        pos_VBO->LoadData(out_Verts.data(), out_Verts.size());
    
        VertexBuffer::sptr uvs_VBO = VertexBuffer::Create();
        uvs_VBO->LoadData(out_UVs.data(), out_UVs.size());
    
        VertexBuffer::sptr norm_VBO = VertexBuffer::Create();
        norm_VBO->LoadData(out_Norms.data(), out_Norms.size());
    
        VertexArrayObject::sptr meshVAO = VertexArrayObject::Create();
    
        meshVAO->AddVertexBuffer(pos_VBO, {
            BufferAttribute(0, 3, GL_FLOAT, false, 0, NULL)
            });
        meshVAO->AddVertexBuffer(uvs_VBO, {
            BufferAttribute(1, 2, GL_FLOAT, false, 0, NULL)
            });
        meshVAO->AddVertexBuffer(norm_VBO, {
            BufferAttribute(2, 3, GL_FLOAT, false, 0, NULL)
            });
    
        return meshVAO;
    }
}