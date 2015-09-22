#pragma once
#ifndef _BASE_OBJECT_H_
#define _BASE_OBJECT_H_

#include "../engine_defines.h"
#include "../engine_math.h"

class BaseObject
{
public:
    BaseObject();

    BaseObject(const BaseObject& other);
    virtual ~BaseObject();
    virtual BaseObject& operator=(const BaseObject& other);

public:
    
    BaseObject& setPosition(const glm::vec3 _position);
    BaseObject& setOrientation(const glm::vec3 _direction);
    BaseObject& setModelMatrix(const glm::mat4 scaleMatrix, const glm::mat4 rotationMatrix, const glm::mat4 translationMatrix);
    BaseObject& setModelMatrix(const glm::mat4 scaleMatrix, const glm::mat4 rotationMatrix);
    BaseObject& setModelMatrix(const glm::mat4 _modelMatrix);

public:

    inline glm::vec4 getPosition() const;
    inline glm::vec4 getDirection() const;
    inline glm::mat4 getModelMatrix() const;
    
private:
    //MeshObject* mesh; MaterialObject* material; TexObject* texture;
    //RigidBodyObject* rigidBody;
    //ShaderProgramObject* program;

private:

    glm::vec4 position;
    glm::vec4 orientation;
    glm::mat4 modelMatrix;
};

#endif