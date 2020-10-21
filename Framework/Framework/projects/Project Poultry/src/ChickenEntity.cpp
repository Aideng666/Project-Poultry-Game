#include "ChickenEntity.h"

entt::entity ChickenEntity::Create()
{
	auto entity = ECS.create();

	return entity;
}
