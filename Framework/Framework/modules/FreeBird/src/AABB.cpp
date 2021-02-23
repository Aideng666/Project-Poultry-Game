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

	AABB::AABB(Entity ent, Entity playEnt, float xOffset, float zOffset)
	{
		thisEnt = ent;
		playerEnt = playEnt;
		isColliding = false;
		_xOffset = xOffset;
		_zOffset = zOffset;

		insideOffsetX = _xOffset - 0.5f;
		insideOffsetZ = _zOffset - 0.5f;
	}

	void AABB::Update()
	{

		//WALL COLLISION
		if (playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() < 1.8f
			&& playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() > -0.1f
			&& thisEnt.Get<Transform>().GetRotation().y == 90.0f && !thisEnt.Has<AndGate>() && !thisEnt.Has<NotGate>())
		{
			playerEnt.Get<Transform>().SetPositionX(playerEnt.Get<Transform>().GetPositionX() + 0.2f);
		}

		if (thisEnt.Get<Transform>().GetPositionX() - playerEnt.Get<Transform>().GetPositionX() < 1.8f
			&& thisEnt.Get<Transform>().GetPositionX() - playerEnt.Get<Transform>().GetPositionX() > -0.1f
			&& thisEnt.Get<Transform>().GetRotation().y == 90.0f && !thisEnt.Has<AndGate>() && !thisEnt.Has<NotGate>())
		{
			playerEnt.Get<Transform>().SetPositionX(playerEnt.Get<Transform>().GetPositionX() - 0.2f);
		}

		if (playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() < 1.8f
			&& playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() > -0.1f
			&& thisEnt.Get<Transform>().GetRotation().y == 0.0f && !thisEnt.Has<AndGate>() && !thisEnt.Has<NotGate>())
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


		//AND GATE COLLISION
		if ((thisEnt.Has<AndGate>() || thisEnt.Has<NotGate>()) && playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() < 5.0f
			&& playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() > 0.0f && playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() < 2.5f
			&& playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() > -2.5f)
			playerEnt.Get<Transform>().SetPositionX(playerEnt.Get<Transform>().GetPositionX() + 0.1f);

		if ((thisEnt.Has<AndGate>() || thisEnt.Has<NotGate>()) && thisEnt.Get<Transform>().GetPositionX() - playerEnt.Get<Transform>().GetPositionX() < 5.0f
			&& thisEnt.Get<Transform>().GetPositionX() - playerEnt.Get<Transform>().GetPositionX() > 0.0f && playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() < 2.5f
			&& playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() > -2.5f)
			playerEnt.Get<Transform>().SetPositionX(playerEnt.Get<Transform>().GetPositionX() - 0.1f);

		if ((thisEnt.Has<AndGate>() || thisEnt.Has<NotGate>()) && playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() < 3.0f
			&& playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() > 0.0f
			&& playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() < 4.5f
			&& playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() > -4.5f)
			playerEnt.Get<Transform>().SetPositionZ(playerEnt.Get<Transform>().GetPositionZ() + 0.1f);

		if ((thisEnt.Has<AndGate>() || thisEnt.Has<NotGate>()) && thisEnt.Get<Transform>().GetPositionZ() - playerEnt.Get<Transform>().GetPositionZ() < 3.0f
			&& thisEnt.Get<Transform>().GetPositionZ() - playerEnt.Get<Transform>().GetPositionZ() > 0.0f
			&& playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() < 4.5f
			&& playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() > -4.5f)
			playerEnt.Get<Transform>().SetPositionZ(playerEnt.Get<Transform>().GetPositionZ() - 0.1f);

		//NOT GATE
		if ((thisEnt.Has<AndGate>() || thisEnt.Has<NotGate>()) && playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() < 3.0f
			&& playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() > 0.0f && playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() < 2.5f
			&& playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() > -2.5f)
			playerEnt.Get<Transform>().SetPositionX(playerEnt.Get<Transform>().GetPositionX() + 0.1f);


		if ((thisEnt.Has<AndGate>() || thisEnt.Has<NotGate>()) && thisEnt.Get<Transform>().GetPositionX() - playerEnt.Get<Transform>().GetPositionX() < 3.0f
			&& thisEnt.Get<Transform>().GetPositionX() - playerEnt.Get<Transform>().GetPositionX() > 0.0f && playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() < 2.5f
			&& playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() > -2.5f)
			playerEnt.Get<Transform>().SetPositionX(playerEnt.Get<Transform>().GetPositionX() - 0.1f);


		if ((thisEnt.Has<AndGate>() || thisEnt.Has<NotGate>()) && playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() < 3.0f
			&& playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() > 0.0f
			&& playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() < 2.5f
			&& playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() > -2.5f)
			playerEnt.Get<Transform>().SetPositionZ(playerEnt.Get<Transform>().GetPositionZ() + 0.1f);


		if ((thisEnt.Has<AndGate>() || thisEnt.Has<NotGate>()) && thisEnt.Get<Transform>().GetPositionZ() - playerEnt.Get<Transform>().GetPositionZ() < 3.0f
			&& thisEnt.Get<Transform>().GetPositionZ() - playerEnt.Get<Transform>().GetPositionZ() > 0.0f
			&& playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() < 2.5f
			&& playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() > -2.5f)
			playerEnt.Get<Transform>().SetPositionZ(playerEnt.Get<Transform>().GetPositionZ() - 0.1f);

		//AMBIENT OBJECTS
		if (playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() < _xOffset
			&& playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() > 0.0f 
			&& playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() < insideOffsetX
			&& playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() > -insideOffsetX
			&& thisEnt.Get<Transform>().GetRotation().y == 180.0f)
			playerEnt.Get<Transform>().SetPositionX(playerEnt.Get<Transform>().GetPositionX() + 0.1f);


		if (thisEnt.Get<Transform>().GetPositionX() - playerEnt.Get<Transform>().GetPositionX() < _xOffset
			&& thisEnt.Get<Transform>().GetPositionX() - playerEnt.Get<Transform>().GetPositionX() > 0.0f 
			&& playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() < insideOffsetX
			&& playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() > -insideOffsetX
			&& thisEnt.Get<Transform>().GetRotation().y == 180.0f)
			playerEnt.Get<Transform>().SetPositionX(playerEnt.Get<Transform>().GetPositionX() - 0.1f);


		if (playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() < _zOffset
			&& playerEnt.Get<Transform>().GetPositionZ() - thisEnt.Get<Transform>().GetPositionZ() > 0.0f
			&& playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() < insideOffsetZ
			&& playerEnt.Get<Transform>().GetPositionX() - thisEnt.Get<Transform>().GetPositionX() > -insideOffsetZ
			&& thisEnt.Get<Transform>().GetRotation().y == 180.0f)
			playerEnt.Get<Transform>().SetPositionZ(playerEnt.Get<Transform>().GetPositionZ() + 0.1f);

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
