#pragma once

#include "entt.hpp"

class ChickenEntity
{
public: 

	//creates a new entity
	static ChickenEntity Create();

	//Constructor
	ChickenEntity(entt::entity ent);

	//Adds a component to an entity
	template<typename T, typename ... Args>
	T& Add(Args&&... arg)
	{
		return ECS.emplace<T>(entID, std::forward<Args>(arg)...);
	}

	//Gets a component from an entity to edit
	template<typename T>
	static T& Get();

	//Removes a component from an entity
	template<typename T>
	void Remove();


private:
	//Registry and entity id for use with entities in main
	static entt::registry ECS;
	entt::entity entID;
};