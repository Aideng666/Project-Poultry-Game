#pragma once
#include "LogicGate.h"
#include "Header.h"

namespace freebird
{
	class OrGate : public LogicGate
	{
	public:

		OrGate(Entity ent1, Entity ent2);

		void Update();

	private:
	};
}