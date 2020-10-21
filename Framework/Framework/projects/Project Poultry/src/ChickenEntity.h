#pragma once

#include "ChickenTransform.h"

#include "entt.hpp"

class ChickenEntity
{
public: 


	ChickenEntity Create();

	ChickenEntity(entt::entity ent);



private:




protected:

	entt::registry ECS;
	entt::entity entID;
};
