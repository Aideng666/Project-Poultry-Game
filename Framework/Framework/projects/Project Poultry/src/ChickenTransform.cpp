#include "ChickenTransform.h"
#include "GLM/gtx/transform.hpp"
#include <GLM\gtx\quaternion.hpp>


ChickenTransform::ChickenTransform() {

    position = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    globalPos = glm::mat4(1.0f);

    currentParent = nullptr;

}

glm::vec3 ChickenTransform::GetPos()
{
    return position;
}

glm::vec3 ChickenTransform::GetScale()
{
    return scale;
}

glm::quat ChickenTransform::GetRotation()
{
    return rotation;
}

glm::mat4 ChickenTransform::GetGlobal()
{
    return globalPos;
}

ChickenTransform* ChickenTransform::GetParent()
{
    return currentParent;
}

void ChickenTransform::SetPos(glm::vec3 newPos)
{
    position = newPos;
}

void ChickenTransform::SetScale(glm::vec3 newScale)
{
    scale = newScale;
}

void ChickenTransform::SetRotation(glm::quat newRot)
{
    rotation = newRot;
}

void ChickenTransform::SetParent(ChickenTransform* newParent)
{
    currentParent = newParent;
}

void ChickenTransform::RecomputeGlobal()
{
    if (currentParent != nullptr)
    {
        globalPos = currentParent->GetGlobal() * this->GetGlobal();
    }
    else
        globalPos = glm::translate(position) * glm::toMat4(GetRotation()) * glm::scale(scale);
}
