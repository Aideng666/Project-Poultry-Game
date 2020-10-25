#include "ChickenEntity.h"


entt::registry ChickenEntity::ECS;

ChickenEntity::ChickenEntity(entt::entity ent)
{
	entID = ent;
}

ChickenEntity ChickenEntity::Create()
{
	entt::entity entity = ECS.create();

	return ChickenEntity(entity);
}


template<typename T>
T& ChickenEntity::Get()
{
	return ECS.get<T>(entID);
}

template<typename T>
void ChickenEntity::Remove()
{
	ECS.remove<T>(entID);
}


