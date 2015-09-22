#include "base_object.h"

BaseObject::BaseObject()
{
    position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    orientation = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    modelMatrix = glm::mat4(1.0f);
}
BaseObject::BaseObject(const BaseObject& other)
{
    *this = other;
}
BaseObject::~BaseObject()
{
}
BaseObject& BaseObject::operator=(const BaseObject& other)
{
    position = other.position;
    orientation = other.orientation;
    modelMatrix = other.modelMatrix;
    return *this;
}


BaseObject& BaseObject::setPosition(const glm::vec3 _position)
{
    //position = glm::vec4(_position, 1.0f);
    position[0] = _position[0];
    position[1] = _position[1];
    position[2] = _position[2];
    return *this;
}
BaseObject& BaseObject::setOrientation(const glm::vec3 _orientation)
{
    //orientation = glm::vec4(_orientation, 0.0f);
    orientation[0] = _orientation[0];
    orientation[1] = _orientation[1];
    orientation[2] = _orientation[2];
    return *this;
}
BaseObject& BaseObject::setModelMatrix(const glm::mat4 scaleMatrix, const glm::mat4 rotationMatrix, const glm::mat4 translationMatrix)
{
    position[0] = translationMatrix[0][4];
    position[1] = translationMatrix[1][4];
    position[2] = translationMatrix[2][4];
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
    return *this;
}
BaseObject& BaseObject::setModelMatrix(const glm::mat4 scaleMatrix, const glm::mat4 rotationMatrix)
{
    modelMatrix = glm::translate(glm::vec3(position)) * rotationMatrix * scaleMatrix;
    return *this;
}
BaseObject& BaseObject::setModelMatrix(const glm::mat4 _modelMatrix)
{
    modelMatrix = _modelMatrix;
    /*
    //This might be incorrect
    position[0] = modelMatrix[0][4];
    position[1] = modelMatrix[1][4];
    position[2] = modelMatrix[2][4];
    */
    return *this;
}


inline glm::vec4 BaseObject::getPosition() const
{
    return position;
}
inline glm::vec4 BaseObject::getDirection() const
{
    return orientation;
}
inline glm::mat4 BaseObject::getModelMatrix() const
{
    return modelMatrix;
}