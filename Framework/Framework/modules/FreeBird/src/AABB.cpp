#include "AABB.h"
#include <Transform.h>
#include <Door.h>
#include <iostream>

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
}
