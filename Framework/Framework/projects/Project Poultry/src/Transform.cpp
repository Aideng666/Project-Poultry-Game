#include "Transform.h"
#include "GLM/gtx/transform.hpp"


glm::vec3 Transform::GetPos()
{
    return position;
}

glm::vec3 Transform::GetScale()
{
    return scale;
}

glm::vec4 Transform::GetRotation()
{
    return rotation;
}
