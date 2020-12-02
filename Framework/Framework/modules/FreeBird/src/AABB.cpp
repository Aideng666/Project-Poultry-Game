#include "AABB.h"
#include <Transform.h>
#include <Door.h>
#include <iostream>
#include <AndGate.h>
#include <NotGate.h>

namespace freebird
{
	AABB::AABB(Entity ent, Entity playEnt)
	{
		thisEnt = ent;
		playerEnt = playEnt;
		isColliding = false;
	}

	void AABB::Update()
	{

		//WALL COLLISION
		if (playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() < 1.8f
			&& playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() > -0.1f
			&& thisEnt.Get<Transform>().GetRotation().y == 90.0f)
		{
			playerEnt.Get<Transform>().SetPositionX(playerEnt.Get<Transform>().GetPositionX() + 0.2f);
		}

		if (thisEnt.Get<Transform>().GetPositionX() - playerEnt.Get<Transform>().GetPositionX() < 1.8f
			&& thisEnt.Get<Transform>().GetPositionX() - playerEnt.Get<Transform>().GetPositionX() > -0.1f
			&& thisEnt.Get<Transform>().GetRotation().y == 90.0f)
		{
			playerEnt.Get<Transform>().SetPositionX(playerEnt.Get<Transform>().GetPositionX() - 0.2f);
		}

		if (playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() < 1.8f
			&& playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() > -0.1f
			&& thisEnt.Get<Transform>().GetRotation().y == 0.0f)
		{
			playerEnt.Get<Transform>().SetPositionZ(playerEnt.Get<Transform>().GetPositionZ() + 0.2f);
		}

		if (playerEnt.Get<Transform>().GetPositionZ() > 35.0f)
			playerEnt.Get<Transform>().SetPositionZ(playerEnt.Get<Transform>().GetPositionZ() - 0.2f);

		//DOOR COLLISION
		if (playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() < 3.0f
			&& playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() > -0.1f
			&& playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() < 2.0f
			&& playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() > -2.0f
			&& thisEnt.Has<Door>() && thisEnt.Get<Door>().GetOpen())
		{
			levelComplete = true;
		}

		if (thisEnt.Has<Door>() && !thisEnt.Get<Door>().GetOpen())
			levelComplete = false;

		//OBJECT COLLISION
		if ((thisEnt.Has<AndGate>() || thisEnt.Has<NotGate>()) && nextPos.x - thisEnt.Get<Transform>().GetPositionX() < 5.0f
			&& nextPos.x - thisEnt.Get<Transform>().GetPositionX() > 0.0f && playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() < 2.5f
			&& playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() > -2.5f)
			playerEnt.Get<Transform>().SetCanMoveLeft(false);
		else
			playerEnt.Get<Transform>().SetCanMoveLeft(true);

		if ((thisEnt.Has<AndGate>() || thisEnt.Has<NotGate>()) && thisEnt.Get<Transform>().GetPositionX() - nextPos.x < 5.0f
			&& thisEnt.Get<Transform>().GetPositionX() - nextPos.x > 0.0f && playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() < 2.5f
			&& playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() > -2.5f)
			playerEnt.Get<Transform>().SetCanMoveRight(false);
		else
			playerEnt.Get<Transform>().SetCanMoveRight(true);

		if ((thisEnt.Has<AndGate>() || thisEnt.Has<NotGate>()) && nextPos.z - thisEnt.Get<Transform>().GetPositionZ() < 3.0f
			&& nextPos.z - thisEnt.Get<Transform>().GetPositionZ() > 0.0f
			&& playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() < 4.5f
			&& playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() > -4.5f)
			playerEnt.Get<Transform>().SetCanMoveUp(false);
		else
			playerEnt.Get<Transform>().SetCanMoveUp(true);

		if ((thisEnt.Has<AndGate>() || thisEnt.Has<NotGate>()) && thisEnt.Get<Transform>().GetPositionZ() - nextPos.z < 3.0f
			&& thisEnt.Get<Transform>().GetPositionZ() - nextPos.z > 0.0f
			&& playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() < 4.5f
			&& playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() > -4.5f)
			playerEnt.Get<Transform>().SetCanMoveDown(false);
		else
			playerEnt.Get<Transform>().SetCanMoveDown(true);
	}

	Entity AABB::GetPlayerEnt()
	{
		return playerEnt;
	}

	Entity AABB::GetThisEnt()
	{
		return thisEnt;
	}
	bool AABB::GetComplete()
	{
		return levelComplete;
	}
	void AABB::SetComplete(bool complete)
	{
		levelComplete = complete;
	}
	glm::vec3 AABB::GetNext()
	{
		return nextPos;
	}
	void AABB::SetNext(glm::vec3 next)
	{
		nextPos = next;
	}
}
