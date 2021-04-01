#pragma once
#include "LogicGate.h"

namespace freebird
{
	class XorGate : public LogicGate
	{
	public:

		XorGate(Entity ent1, Entity ent2, Entity out);

		void Update();

	private:
	};
}