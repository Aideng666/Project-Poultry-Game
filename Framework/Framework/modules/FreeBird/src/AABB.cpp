#include "AABB.h"
#include <Transform.h>

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
		if (playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() < 0.5f
			&& playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() > -0.1f
			&& thisEnt.Get<Transform>().GetRotation().z == 90.0f)
		{
			playerEnt.Get<Transform>().SetPositionX(playerEnt.Get<Transform>().GetPositionX() + 0.1f);
		}

		if (thisEnt.Get<Transform>().GetPositionX() - playerEnt.Get<Transform>().GetPositionX() < 0.5f
			&& thisEnt.Get<Transform>().GetPositionX() - playerEnt.Get<Transform>().GetPositionX() > -0.1f
			&& thisEnt.Get<Transform>().GetRotation().z == 90.0f)
		{
			playerEnt.Get<Transform>().SetPositionX(playerEnt.Get<Transform>().GetPositionX() - 0.1f);
		}

		if (playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() < 0.5f
			&& playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() > -0.1f
			&& thisEnt.Get<Transform>().GetRotation().x == 90.0f)
		{
			playerEnt.Get<Transform>().SetPositionZ(playerEnt.Get<Transform>().GetPositionZ() + 0.1f);
		}
	}

	Entity AABB::GetPlayerEnt()
	{
		return playerEnt;
	}

	Entity AABB::GetThisEnt()
	{
		return thisEnt;
	}
}
