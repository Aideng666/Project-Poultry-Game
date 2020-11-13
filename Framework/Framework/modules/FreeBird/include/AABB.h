#pragma once
#include "Entity.h"

namespace freebird
{


	class AABB {

	public:

		AABB(Entity ent, Entity playEnt);

		void Update();

		Entity GetPlayerEnt();
		Entity GetThisEnt();

	private:
		Entity playerEnt, thisEnt;
		bool isColliding;
	};
}