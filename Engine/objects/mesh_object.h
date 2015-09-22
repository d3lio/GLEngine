#pragma once
#ifndef _MESH_OBJECT_H_
#define _MESH_OBJECT_H_

#include <vector>
#include "../engine_defines.h"
#include "../engine_math.h"

class MeshObject
{
public:

    MeshObject();
    
    MeshObject(const MeshObject& other);
    virtual ~MeshObject();
    virtual MeshObject& operator=(const MeshObject& other);

    virtual MeshObject& loadAssImp(const char* path);

private:

    std::vector <uint> indices;
    std::vector <glm::vec3> vertices;
    std::vector <glm::vec2> uvs;
    std::vector <glm::vec3> normals;
};

#endif