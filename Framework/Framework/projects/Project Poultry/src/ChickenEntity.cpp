#include "ChickenEntity.h"

ChickenEntity::ChickenEntity(entt::entity ent)
{
	entID = ent;
}

ChickenEntity ChickenEntity::Create()
{
	auto entity = ECS.create();

	return ChickenEntity(entity);
}

