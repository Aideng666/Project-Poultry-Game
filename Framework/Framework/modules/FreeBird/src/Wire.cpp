#include "Wire.h"

namespace freebird
{
	Wire::Wire(Entity last, Entity next)
	{
		lastEnt = last;
		nextEnt = next;
		isPowered = false;
	}

	void Wire::Update()
	{
		if (nextEnt.Has<Wire>() && isPowered)
		{
			nextEnt.Get<Wire>().SetIsPowered(true);
		}
	}

	bool Wire::GetIsPowered()
	{
		return isPowered;
	}

	Entity Wire::GetLast()
	{
		return lastEnt;
	}

	Entity Wire::GetNext()
	{
		return nextEnt;
	}

	void Wire::SetIsPowered(bool power)
	{
		isPowered = power;
	}

	void Wire::SetLast(Entity last)
	{
		lastEnt = last;
	}

	void Wire::SetNext(Entity next)
	{
		nextEnt = next;
	}

}

