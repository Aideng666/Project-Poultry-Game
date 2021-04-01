#pragma once
#include "LogicGate.h"

namespace freebird
{
	class NorGate : public LogicGate
	{
	public:

		NorGate(Entity ent1, Entity ent2, Entity out);

		void Update();

	private:
	};
}