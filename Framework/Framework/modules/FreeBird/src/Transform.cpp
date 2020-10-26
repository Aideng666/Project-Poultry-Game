#include "Transform.h"

namespace freebird
{
	Transform::Transform()
	{
		position = glm::vec3(0.0f, 0.0f, 0.0f);
		scale = glm::vec3(1.0f, 1.0f, 1.0f);
		rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	}

	glm::vec3 Transform::GetPosition()
	{
		return position;
	}

	float Transform::GetPositionX()
	{
		return position.x;
	}

	float Transform::GetPositionY()
	{
		return position.y;
	}

	float Transform::GetPositionZ()
	{
		return position.z;
	}

	glm::vec3 Transform::GetScale()
	{
		return scale;
	}

	glm::quat Transform::GetRotation()
	{
		return rotation;
	}

	glm::mat3 Transform::GetRotationMatrix()
	{
		return glm::toMat3(rotation);
	}

	glm::mat4 Transform::GetModelMatrix()
	{
		return glm::mat4(glm::translate(glm::mat4(1.0f), position) * glm::toMat4(rotation) * glm::scale(glm::mat4(1.0f), scale));	
	}

	void Transform::SetPosition(glm::vec3 newPos)
	{
		position = newPos;
	}

	void Transform::SetPositionX(float xPos)
	{
		position.x = xPos;
	}

	void Transform::SetPositionY(float yPos)
	{
		position.y = yPos;
	}

	void Transform::SetPositionZ(float zPos)
	{
		position.z = zPos;
	}

	void Transform::SetScale(glm::vec3 newScale)
	{
		scale = newScale;
	}

	void Transform::SetScale(float x, float y, float z)
	{
		scale.x = x;
		scale.y = y;
		scale.z = z;
	}

	void Transform::SetRotation(glm::quat newRot)
	{
		rotation = newRot;
	}

	void Transform::SetRotation(glm::mat3 newRot)
	{
		rotation = newRot;
	}

	void Transform::SetRotationX(float newAngle)
	{
		rotation.x = newAngle;
	}	

	void Transform::SetRotationY(float newAngle)
	{
		rotation.y = newAngle;
	}	

	void Transform::SetRotationZ(float newAngle)
	{
		rotation.z = newAngle;
	}
}